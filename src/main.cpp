#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Ticker.h>

#define WIFI_SSID "Lab-Eng"
#define WIFI_PASSWORD "Lab-Eng123!"
#define MQTT_BROKER "broker.emqx.io"
#define MQTT_TOPIC_PUBLISH "esp32_test/data"
#define MQTT_TOPIC_SUBSCRIBE "esp32_test/data"

Ticker timerPublish;

char g_szDeviceId[30];

Ticker timerMqtt;

//const char* mqtt_server = "broker.emqx.io" ; //MQTT broker address

WiFiClient espClient;
PubSubClient mqtt(espClient);

boolean mqtt_connect ();
void Wificonnect ();


void mqtt_connect(){
Serial.print("Connecting to MQTT server....);

if(mqtt.connect("ESP32Client")){
  Serial.println("connected");
  mqtt.publish("esp32_test/data", "Hello from ESP32");
  mqtt.subscribe("esp32_test/data");
}
else{
  Serial.print("failed, rc=");
  Serial.print(mqtt.state());
  Serial.println(" try again in 5 seconds");
  // Wait 5 seconds before retrying
  delay(5000);
}

}

void reconnect() {
  // Loop until we're reconnected
  while (!mqtt.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (mqtt.connect("ESP32Client_stf_jkt11")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
     // mqtt.publish("outTopic", "hello world");
      // ... and resubscribe
     // mqtt.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }



void setup() {

Serial.begin (115200);
pinMode(LED_BUILTIN, OUTPUT);
Serial.println ("Booting....");
WiFi.mode(WIFI_STA);
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
while (WiFi.waitForConnectResult() != WL_CONNECTED) {
  Serial.println("Connection Failed! Rebooting...");
  delay(5000);
  ESP.restart();
}
Serial.print ("System started. IP address: ");
Serial.println (WiFi.localIP());
Serial.printf("RSSI: %d\n", WiFi.RSSI()); //rssi is the signal strength
mqtt.setServer(mqtt_server, 1883);
reconnect();
}

void loop() {
  // digitalWrite(LED_BUILTIN, HIGH);
  // delay(100);
  // digitalWrite(LED_BUILTIN, LOW);
  // delay(100);
  mqtt.loop();
  if (!mqtt.connected())
  mqtt.publish("esp32_test/data", "Hello from ESP32");

  //   reconnect();
  // }

}