// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "BuggyAWD-AP";
const char* password = "abc42069";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output21State = "off";
String output18State = "off";
String output19State = "off";
String output22State = "off";

// Assign output variables to GPIO pins
const int output21 = 21;
const int output18 = 18;
const int output19 = 19;
const int output22 = 22;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output21, OUTPUT);
  pinMode(output18, OUTPUT);
  pinMode(output19, OUTPUT);
  pinMode(output22, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output21, LOW);
  digitalWrite(output18, LOW);
  digitalWrite(output19, LOW);
  digitalWrite(output22, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}

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
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Turns the GPIOs on and off       
            // UP
            if (header.indexOf("GET /up") >= 0) {
              if (output21State == "off" && output18State == "off") {
                // Liga UP
                Serial.println("UP pressed - GPIO 21 on & GPIO 18 on");
                turnOffAllOutputs();  // Desliga todos os outros botões
                output21State = "on";
                output18State = "on";
                digitalWrite(output21, HIGH);
                digitalWrite(output18, HIGH);
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
              Serial.println("DOWN pressed - GPIO 19 & GPIO 22 on");
              turnOffAllOutputs();
              output19State = "on";
              output22State = "on";
              digitalWrite(output19, HIGH);
              digitalWrite(output22, HIGH);
            } else if (header.indexOf("GET /down/off") >= 0) {
              Serial.println("DOWN released - GPIO 19 & GPIO 22 off");
              output19State = "off";
              output22State = "off";
              digitalWrite(output19, LOW);
              digitalWrite(output22, LOW);

            // LEFT
            } else if (header.indexOf("GET /left/on") >= 0) {
              Serial.println("LEFT pressed - GPIO 21 & GPIO 19 on");
              turnOffAllOutputs();
              output21State = "on";
              output19State = "on";
              digitalWrite(output21, HIGH);
              digitalWrite(output19, HIGH);
            } else if (header.indexOf("GET /left/off") >= 0) {
              Serial.println("LEFT released - GPIO 21 & GPIO 19 off");
              output21State = "off";
              output19State = "off";
              digitalWrite(output21, LOW);
              digitalWrite(output19, LOW);

            // RIGHT
            } else if (header.indexOf("GET /right/on") >= 0) {
              Serial.println("RIGHT pressed - GPIO 18 & GPIO 22 on");
              turnOffAllOutputs();
              output18State = "on";
              output22State = "on";
              digitalWrite(output18, HIGH);
              digitalWrite(output22, HIGH);
            } else if (header.indexOf("GET /right/off") >= 0) {
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
            
            // Display the HTML web page
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
            client.println(".footer { position: absolute; bottom: 10px; right: 10px; font-style: italic; font-size: 12px; }");
            client.println(".button-reset { background-color: #ff4747; }");
            client.println("</style></head>");
            
            client.println("<body><div class=\"layout\">");
            client.println("<div class=\"header\">~ le controls</div>");
            
             // UP
            client.println("<div class=\"gpio gpio26\"><p>GPIO 21 - State " + output21State + "&nbsp;&nbsp;&nbsp;&nbsp; GPIO 18 - State " + output18State + "</p>");
            if (output21State == "on" && output18State == "on" && output19State == "off" && output22State == "off") {
              client.println("<p><a href=\"/up/off\"><button class=\"button-grey button-green\">UP</button></a></p>");
            } 
             else {
              client.println("<p><a href=\"/up\"><button class=\"button-grey\">UP</button></a></p>");
            } 
            client.println("</div>");


            // LEFT
            client.println("<div class=\"gpio gpio21\"><p>GPIO 21 - State " + output21State + "&nbsp;&nbsp;&nbsp;&nbsp; GPIO 19 - State " + output19State + "</p>");
            if (output21State == "on" && output18State == "off" && output19State == "on" && output22State == "off") {
              client.println("<p><a href=\"/left/off\"><button class=\"button-grey button-green\">LEFT</button></a></p>");
            } else {
              client.println("<p><a href=\"/left/on\"><button class=\"button-grey\">LEFT</button></a></p>");
            }
            client.println("</div>");

            // RIGHT
            client.println("<div class=\"gpio gpio18\"><p>GPIO 18 - State " + output18State + "&nbsp;&nbsp;&nbsp;&nbsp; GPIO 22 - State " + output22State + "</p>");
            if (output21State == "off" && output18State == "on" && output19State == "off" && output22State == "on") {
              client.println("<p><a href=\"/right/off\"><button class=\"button-grey button-green\">RIGHT</button></a></p>");
            } else {
              client.println("<p><a href=\"/right/on\"><button class=\"button-grey\">RIGHT</button></a></p>");
            }
            client.println("</div>");

            // DOWN
            client.println("<div class=\"gpio gpio27\"><p>GPIO 19 - State " + output19State + "&nbsp;&nbsp;&nbsp;&nbsp; GPIO 22 - State " + output22State + "</p>");
            if (output19State == "on" && output22State == "on") {
              client.println("<p><a href=\"/down/off\"><button class=\"button-grey button-green\">DOWN</button></a></p>");
            } else {
              client.println("<p><a href=\"/down/on\"><button class=\"button-grey\">DOWN</button></a></p>");
            }
            client.println("</div>");

            // RESET
            client.println("<div class=\"gpio reset\"><p>RESET</p>");
            client.println("<p><a href=\"/reset\"><button class=\"button-grey button-reset\">RESET</button></a></p>");
            client.println("</div>");
            
            client.println("<div class=\"footer\">by Eduardoros & gbzinsheik</div>");
            client.println("</div></body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    //Serial.println("Client disconnected.");
    Serial.println("");
  }
}