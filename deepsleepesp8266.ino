
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* SSID = "SSID";
const char* PSK = "password";
const char* MQTT_BROKER = "192.168.4.1";
 
WiFiClient espClient;
PubSubClient client(espClient);

void startDeepSleep()

{
    Serial.println("Going to deep sleep...");
    ESP.deepSleep(60 * 1000000);
    yield();
  
}
 

void setup_wifi() {
    int failed = 0;
    WiFi.mode(WIFI_STA);
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(SSID);
    WiFi.begin(SSID, PSK);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        failed++;
        if (failed == 10
        
        )  { startDeepSleep();}
    }
    Serial.println(WiFi.localIP());
}
 
void reconnect() {
    while (!client.connected()) {
        Serial.print("Reconnecting...");
        if (!client.connect("ESP8266Client")) {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" retrying in 5 seconds");
            delay(5000);
        }
    }
}


void setup() {   
    Serial.begin(9600);
    setup_wifi();
    client.setServer(MQTT_BROKER, 1883);
         if (!client.connected()) {
        reconnect();
    }
    client.publish("/home/data", "Hello World");
    delay(1000);
    startDeepSleep();
}


void loop() {
    
}
