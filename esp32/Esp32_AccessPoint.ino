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
String output26State = "off";
String output27State = "off";
String output21State = "off";
String output18State = "off";

// Assign output variables to GPIO pins
const int output26 = 26;
const int output27 = 27;
const int output21 = 21;
const int output18 = 18;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  pinMode(output21, OUTPUT);
  pinMode(output18, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);
  digitalWrite(output21, LOW);
  digitalWrite(output18, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}

void turnOffAllOutputs() {
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);
  digitalWrite(output21, LOW);
  digitalWrite(output18, LOW);
  output26State = "off";
  output27State = "off";
  output21State = "off";
  output18State = "off";
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
            if (header.indexOf("GET /up") >= 0) {
              if (output21State == "off" && output18State == "off") {
                Serial.println("UP pressed - GPIO 21 on & GPIO 18 on");
                turnOffAllOutputs();
                output21State = "on";
                output18State = "on";
                digitalWrite(output21, HIGH);
                digitalWrite(output18, HIGH);
              } else if (header.indexOf("GET /up/off") >= 0) {
                Serial.println("UP released - GPIO 21 off & GPIO 18 off");
                output21State = "off";
                output18State = "off";
                digitalWrite(output21, LOW);
                digitalWrite(output18, LOW);
              }
            } else if (header.indexOf("GET /down/on") >= 0) {
              Serial.println("DOWN pressed - GPIO 27 on");
              turnOffAllOutputs();
              output27State = "on";
              digitalWrite(output27, HIGH);
            } else if (header.indexOf("GET /down/off") >= 0) {
              Serial.println("DOWN released - GPIO 27 off");
              output27State = "off";
              digitalWrite(output27, LOW);
            } else if (header.indexOf("GET /left/on") >= 0) {
              Serial.println("LEFT pressed - GPIO 21 on");
              turnOffAllOutputs();
              output21State = "on";
              digitalWrite(output21, HIGH);
            } else if (header.indexOf("GET /left/off") >= 0) {
              Serial.println("LEFT released - GPIO 21 off");
              output21State = "off";
              digitalWrite(output21, LOW);
            } else if (header.indexOf("GET /right/on") >= 0) {
              Serial.println("RIGHT pressed - GPIO 18 on");
              turnOffAllOutputs();
              output18State = "on";
              digitalWrite(output18, HIGH);
            } else if (header.indexOf("GET /right/off") >= 0) {
              Serial.println("RIGHT released - GPIO 18 off");
              output18State = "off";
              digitalWrite(output18, LOW);
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
            client.println(".reset { grid-area: reset; }");
            client.println(".footer { position: absolute; bottom: 10px; right: 10px; font-style: italic; font-size: 12px; }");
            client.println(".button-reset { background-color: #ff4747; }");
            client.println("</style></head>");
            
            client.println("<body><div class=\"layout\">");
            client.println("<div class=\"header\">~ le controls</div>");
            
            // UP
            client.println("<div class=\"gpio gpio26\"><p>GPIO 21 and 18 State " + output21State + "</p>");
            if (output21State == "off" && output18State == "off") {
              client.println("<p><a href=\"/up\"><button class=\"button-grey\">UP</button></a></p>");
            } else if (output21State == "off" && output18State == "on") {
              client.println("<p><a href=\"/up/off\"><button class=\"button-grey\">UP</button></a></p>");
            } else if (output21State == "on" && output18State == "off") {
              client.println("<p><a href=\"/up/off\"><button class=\"button-grey\">UP</button></a></p>");
            } else if (output21State == "on" && output18State == "on") {
              client.println("<p><a href=\"/up/off\"><button class=\"button-grey button-green\">UP</button></a></p>");
            }
            client.println("</div>");

            // LEFT
            client.println("<div class=\"gpio gpio21\"><p>GPIO 21 - State " + output21State + "</p>");
            if (output21State == "off") {
              client.println("<p><a href=\"/left/on\"><button class=\"button-grey\">LEFT</button></a></p>");
            } else if (output21State == "off" && output18State == "on") {
              client.println("<p><a href=\"/up/off\"><button class=\"button-grey\">UP</button></a></p>");
            } else if (output21State == "on" && output18State == "on") {
              client.println("<p><a href=\"/up/off\"><button class=\"button-grey button-green\">UP</button></a></p>");
            } else if (output21State == "on" && output18State == "off") {
              client.println("<p><a href=\"/left/off\"><button class=\"button-grey button-green\">LEFT</button></a></p>");
            } 
            client.println("</div>");

            // RIGHT
            client.println("<div class=\"gpio gpio18\"><p>GPIO 18 - State " + output18State + "</p>");
            if (output18State == "off") {
              client.println("<p><a href=\"/right/on\"><button class=\"button-grey\">RIGHT</button></a></p>");
            } else if (output21State == "on" && output18State == "off") {
              client.println("<p><a href=\"/up/off\"><button class=\"button-grey\">UP</button></a></p>");
            } else if (output21State == "on" && output18State == "on") {
              client.println("<p><a href=\"/up/off\"><button class=\"button-grey button-green\">UP</button></a></p>");
            } else if (output21State == "off" && output18State == "on") {
              client.println("<p><a href=\"/right/off\"><button class=\"button-grey button-green\">RIGHT</button></a></p>");
            }
            client.println("</div>");

            // DOWN
            client.println("<div class=\"gpio gpio27\"><p>GPIO 27 - State " + output27State + "</p>");
            if (output27State == "off") {
              client.println("<p><a href=\"/down/on\"><button class=\"button-grey\">DOWN</button></a></p>");
            } else {
              client.println("<p><a href=\"/down/off\"><button class=\"button-grey button-green\">DOWN</button></a></p>");
            }
            client.println("</div>");

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
