#include <WiFi.h>

void InitWiFi(char *ssid, char *password)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    Serial.print("WiFi connecting");
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Local IP: " + WiFi.localIP());
}