// Biblioteca Wi-Fi
#include <WiFi.h>

#define PIN_D32 32
#define TRIGGER_PIN 12
#define ECHO_PIN 13

// Constante para a velocidade do som em cm/s
#define VELOCIDADE_SOM 34300 // em cm/s (340 m/s)

// Credenciais da network
const char* ssid     = "BuggyAWD-AP";
const char* password = "abc42069";

// Set web server port number to 80
WiFiServer server(80);

// Variavel para guardar o HTTP request
String header;

// Variáveis auxliares para guardar o estado de output atual
String output21State = "off";
String output18State = "off";
String output19State = "off";
String output22State = "off";

// Associando as variáveis de output aos pinos GPIO
const int output21 = 21;
const int output18 = 18;
const int output19 = 19;
const int output22 = 22;

// Variáveis para cálculo da distância
long duracao; 
float distancia;

void setup() {
  Serial.begin(115200);

  // Configuração de input/output dos pinos

  // Sensores dianteiros
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Bateria
  pinMode(PIN_D32, OUTPUT);
  
  // Botões de movimento
  pinMode(output21, OUTPUT);    
  pinMode(output18, OUTPUT);
  pinMode(output19, OUTPUT);
  pinMode(output22, OUTPUT);

  digitalWrite(output21, LOW);
  digitalWrite(output18, LOW);
  digitalWrite(output19, LOW);
  digitalWrite(output22, LOW);

  // Conecta ao Wi-Fi com o SSID e senha
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}

// Função desliga todos os inputs (de movimento)
// Acionada quando há um novo comando de movimento para evitar curto circuito na placa
void turnOffAllOutputs() {
  digitalWrite(output21, LOW);
  digitalWrite(output18, LOW);
  digitalWrite(output19, LOW);
  digitalWrite(output22, LOW);
  output21State = "off";
  output18State = "off";
  output19State = "off";
  output22State = "off";
}

void loop(){

  WiFiClient client = server.available(); 

  if (client) {                             // Se um novo cliente conecta,
    Serial.println("New Client.");          
    String currentLine = "";                // Faz uma string para guardar informação vindas do cliente
    while (client.connected()) {            // Loop enquando o cliente estiver conectado
      if (client.available()) {             // Se houver bytes para ler do cliente
        char c = client.read();             // Lê o byte
        Serial.write(c);                    // Printa o byte no monitor serial
        header += c;
        if (c == '\n') {                    
          // Fim do http request
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Cáculo da bateria:

              // 4096           ------    100%
              // analogValue    ------    batPerc%

              // batPerc = (100 * analogValue) / 4096
              
              int analogValue = analogRead(PIN_D32);

              int batPerc = (100 * analogValue / 4096);
              Serial.println(String("Battery life: ") + batPerc + "%");

              Serial.print("analogValue: ");
              Serial.print(analogValue);
              Serial.println();

              Serial.print("batPerc: "); 
              Serial.print(batPerc);
              Serial.println();

            // Cáculo dos sensores de distância:  (ESTÁ CAUSANDO DELAY NOS BOTÕES!!!)

              // Gera um pulso no pino Trigger
              //digitalWrite(TRIGGER_PIN, LOW);
              //delayMicroseconds(2);
              //digitalWrite(TRIGGER_PIN, HIGH);
              //delayMicroseconds(10);
              //digitalWrite(TRIGGER_PIN, LOW);

              // Lê o tempo de ida e volta do sinal no pino Echo
              //duracao = pulseIn(ECHO_PIN, HIGH);

              // Calcula a distância (tempo/2 * velocidade do som)
              //distancia = (duracao * VELOCIDADE_SOM) / 2 / 10000.0;
            
              // Exibe a duração do puloso e a distância no monitor serial
              //Serial.print("Duracao: ");
              //Serial.print(duracao);
              //Serial.println();

              //Serial.print("Distancia: ");
              //Serial.print(distancia);
              //Serial.println(" cm");

              // Atraso para evitar sobrecarga no monitor serial
              //delay(500);

            // Movimentação:  
                 
            // UP
            if (header.indexOf("GET /up") >= 0) {
              if (output21State == "off" || output18State == "off") {
                // Liga UP
                Serial.println("UP pressed - GPIO 21 on & GPIO 18 on");
                turnOffAllOutputs();  // Desliga todos os outros botões
                output21State = "on";
                output18State = "on";
                digitalWrite(output21, HIGH);
                digitalWrite(output18, HIGH);
                digitalWrite(output22, LOW);
                digitalWrite(output19, LOW);
              } else {
                // Desliga UP
                Serial.println("UP released - GPIO 21 off & GPIO 18 off");
                output21State = "off";
                output18State = "off";
                digitalWrite(output21, LOW);
                digitalWrite(output18, LOW);
              }
            }
            // DOWN
            else if (header.indexOf("GET /down/on") >= 0) {
              // Liga DOWN
              Serial.println("DOWN pressed - GPIO 19 & GPIO 22 on");
              turnOffAllOutputs();
              output19State = "on";
              output22State = "on";
              digitalWrite(output19, HIGH);
              digitalWrite(output22, HIGH);
            } else if (header.indexOf("GET /down/off") >= 0) {
              // Desliga DOWN
              Serial.println("DOWN released - GPIO 19 & GPIO 22 off");
              output19State = "off";
              output22State = "off";
              digitalWrite(output19, LOW);
              digitalWrite(output22, LOW);

            // LEFT
            } else if (header.indexOf("GET /left/on") >= 0) {
              // Liga LEFT
              Serial.println("LEFT pressed - GPIO 21 & GPIO 19 on");
              turnOffAllOutputs();
              output21State = "on";
              output19State = "on";
              digitalWrite(output21, HIGH);
              digitalWrite(output19, HIGH);
            } else if (header.indexOf("GET /left/off") >= 0) {
              // Desliga LEFT
              Serial.println("LEFT released - GPIO 21 & GPIO 19 off");
              output21State = "off";
              output19State = "off";
              digitalWrite(output21, LOW);
              digitalWrite(output19, LOW);

            // RIGHT
            } else if (header.indexOf("GET /right/on") >= 0) {
              // Liga RIGHT
              Serial.println("RIGHT pressed - GPIO 18 & GPIO 22 on");
              turnOffAllOutputs();
              output18State = "on";
              output22State = "on";
              digitalWrite(output18, HIGH);
              digitalWrite(output22, HIGH);
            } else if (header.indexOf("GET /right/off") >= 0) {
              // Desliga RIGHT
              Serial.println("RIGHT released - GPIO 18 & GPIO 22 off");
              output18State = "off";
              output22State = "off";
              digitalWrite(output18, LOW);
              digitalWrite(output22, LOW);

            // RESET
            } else if (header.indexOf("GET /reset") >= 0) {
              Serial.println("RESET pressed");
              turnOffAllOutputs();
            }
            
          // Página web:

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: flex; flex-direction: column; align-items: center; justify-content: center;}");
            client.println(".button-grey { background-color: #b5b5b5; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 5px; cursor: pointer;}");
            client.println(".button-green {background-color: #4caf50;}");
            client.println(".layout { display: grid; grid-template-areas: \"header header\" \"gpio26 gpio26\" \"gpio21 gpio18\" \"gpio27 gpio27\" \"reset reset\"; gap: 20px; text-align: center;}");
            client.println(".gpio { padding: 20px; border: 1px solid #ddd;}");
            client.println(".header { grid-area: header; font-size: 40px; font-weight: bold; }");
            client.println(".gpio26 { grid-area: gpio26; }");
            client.println(".gpio21 { grid-area: gpio21; }");
            client.println(".gpio18 { grid-area: gpio18; }");
            client.println(".gpio27 { grid-area: gpio27; }");
            client.println(".gpio27 { grid-area: gpio27; }");
            client.println(".reset { grid-area: reset; }");
            client.println(".battery { font-size: 18px; margin-top: 20px; text-align: center; }");
            client.println(".footer { position: absolute; bottom: 10px; right: 10px; font-style: italic; font-size: 12px; }");
            client.println(".button-reset { background-color: #ff4747; }");
            client.println("</style></head>");
            
            client.println("<body><div class=\"layout\">");
            client.println("<div class=\"header\">~ le controls</div>");
            
             // Botão UP
              client.println("<div class=\"gpio gpio26\"><p>GPIO 21 - State " + output21State + "&nbsp;&nbsp;&nbsp;&nbsp; GPIO 18 - State " + output18State + "</p>");
              if (output21State == "on" && output18State == "on" && output19State == "off" && output22State == "off") {
                client.println("<p><a href=\"/up/off\"><button class=\"button-grey button-green\">UP</button></a></p>");
              } 
              else {
                client.println("<p><a href=\"/up\"><button class=\"button-grey\">UP</button></a></p>");
              } 
              client.println("</div>");

            // Botão LEFT
              client.println("<div class=\"gpio gpio21\"><p>GPIO 21 - State " + output21State + "<br>GPIO 19 - State " + output19State + "</p>");
              if (output21State == "on" && output18State == "off" && output19State == "on" && output22State == "off") {
                client.println("<p><a href=\"/left/off\"><button class=\"button-grey button-green\">LEFT&nbsp</button></a></p>");
              } else {
                client.println("<p><a href=\"/left/on\"><button class=\"button-grey\">LEFT</button></a></p>");
              }
              client.println("</div>");

            // Botão RIGHT
              client.println("<div class=\"gpio gpio18\"><p>GPIO 18 - State " + output18State + "<br>GPIO 22 - State " + output22State + "</p>");
              if (output21State == "off" && output18State == "on" && output19State == "off" && output22State == "on") {
                client.println("<p><a href=\"/right/off\"><button class=\"button-grey button-green\">RIGHT</button></a></p>");
              } else {
                client.println("<p><a href=\"/right/on\"><button class=\"button-grey\">RIGHT</button></a></p>");
              }
              client.println("</div>");

            // Botão DOWN
              client.println("<div class=\"gpio gpio27\"><p>GPIO 19 - State " + output19State + "&nbsp;&nbsp;&nbsp;&nbsp; GPIO 22 - State " + output22State + "</p>");
              if (output19State == "on" && output22State == "on") {
                client.println("<p><a href=\"/down/off\"><button class=\"button-grey button-green\">DOWN</button></a></p>");
              } else {
                client.println("<p><a href=\"/down/on\"><button class=\"button-grey\">DOWN</button></a></p>");
              }
              client.println("</div>");

            // Botão RESET/Display da bateria
              client.println(String("<div class=\"gpio reset\"><p>Battery life: ") + batPerc + "%</p>");
              client.println("<p><a href=\"/reset\"><button class=\"button-grey button-reset\">RESET</button></a></p>");
              client.println("</div>");

            // Footer com os créditos
              client.println("<div class=\"footer\">by Eduardoros & gbzinsheik");
              client.println("</div>");

            client.println("</body></html>");          
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;
        }
      }
    }
    // Limpa variável header
    header = "";
    // Fecha a conexão
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
