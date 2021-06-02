
#include <PubSubClient.h>


#include <WiFi.h>
//#include <WiFiClient.h>



const char* SSID = "ssid";
const char* PSK = "pw";
const char* MQTT_BROKER = "192.168.4.1";
 
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
 
void startDeepSleep(){
  Serial.println("Going to deep sleep...");
  esp_deep_sleep_start();
  delay(100);
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
        if (failed == 5)  { startDeepSleep();}
    }
 
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
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
    esp_sleep_enable_timer_wakeup(60 * 1000000);
    Serial.begin(9600);
    setup_wifi();
    client.setServer(MQTT_BROKER, 1883);
    

     if (!client.connected()) {
        reconnect();
    }
     
    snprintf (msg, 50, "Alive since %ld milliseconds", millis());
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("/home/data", "Hello World");
    delay(1000);
    startDeepSleep();
}
void loop() {
 
   
}