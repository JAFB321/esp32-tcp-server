#include <WiFi.h>

const char *ssid = "********";
const char *password = "********";

WiFiServer server; // Declara el objeto del servidor

void setup()
{
    Serial.begin(115200);
    Serial.println();

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false); // Desactiva la suspensión de wifi en modo STA para mejorar la velocidad de respuesta
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected");
    Serial.print("IP Address:");
    Serial.println(WiFi.localIP());

    server.begin(22333); // El servidor comienza a escuchar el puerto número 22333
}

void loop()
{
    WiFiClient client = server.available(); // Intenta crear un objeto de cliente
    if (client) // Si el cliente actual está disponible
    {
        Serial.println("[Client connected]");
        String readBuff;
        while (client.connected()) // Si el cliente está conectado
        {
            if (client.available()) // Si hay datos legibles
            {
                char c = client.read(); // Leer un byte
                                        // También puede utilizar otros métodos como readLine ()
                readBuff += c;
                if(c == '\r') // Retorno de carro recibido
                {
                    client.print("Received: " + readBuff); // Enviar al cliente
                    Serial.println("Received: " + readBuff); // Imprimir desde el puerto serie
                    readBuff = "";
                    break; //Fuera de la lupa
                }
            }
        }
        client.stop(); // Finalizar la conexión actual:
        Serial.println("[Client disconnected]");
    }
}
