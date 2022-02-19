#include <WiFi.h>

const char *ssid = "WIFI SSID";
const char *password = "WIFI PASS";

WiFiServer server; // Server Object

void setup()
{
    Serial.begin(115200);
    Serial.println();

    WiFi.mode(WIFI_STA);  
    WiFi.setSleep(false); // Disable Sleep mode for better response time
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected");
    Serial.print("IP Address:");
    Serial.println(WiFi.localIP());

    server.begin(22333); // Server running on port 22333
}

void loop()
{
   // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {

    Serial.println("Client connected");

    String msg = "";
    while (client.connected()) { // Loop while the client is connected 

      if (client.available()){ // When a package (char) is recieved from client

        char c = client.read();
        msg += c; // Each char recieved build the message

        if(c == '\r'){ // If the char is a Carriage Return the string ends  
          client.print("Recieved: "+msg);
          Serial.println("Recieved: "+msg);
          msg = "";
          break; 
        }
      }

    }

    client.stop(); // Close connection
    Serial.println("Client disconnected");
  }
}
