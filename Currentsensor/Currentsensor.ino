#include <WiFi.h>

const char* ssid = "iPhone";
const char* password = "Ela2010?";

WiFiServer server(80);

#define SENSOR_PIN 2 // Data pin for the ACS712

void setup() {
  Serial.begin(115200);

  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client) { // If you get a client,
    Serial.println("New Client."); // Print a message out the serial port
    String currentLine = ""; // Make a String to hold incoming data from the client

    while (client.connected()) { // Loop while the client's connected
      if (client.available()) { // If there's bytes to read from the client,
        char c = client.read(); // Read a byte, then
        Serial.write(c); // Print it out the serial monitor
        if (c == '\n') { // If the byte is a newline character

          // If the current line is blank, you got two newline characters in a row.
          // That's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            
            // Read current from ACS712 sensor
            float voltage = analogRead(SENSOR_PIN) * (5.0 / 1024.0); // Adjust based on your reference voltage
            float current = (voltage - 2.5) / 0.066; // Adjust based on your ACS712 version (20A version in this example)

            // Send the current reading to the client
            client.print("Stroom: ");
            client.print(current);
            client.println(" A");

            // The HTTP response ends with another blank line:
            client.println();
            // Break out of the while loop:
            break;
          } else { // If you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') { // If you got anything else but a carriage return character,
          currentLine += c; // Add it to the end of the currentLine
        }
      }
    }
    // Close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
