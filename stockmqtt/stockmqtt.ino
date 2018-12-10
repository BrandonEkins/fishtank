#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#define magnetSensor D6

const char* ssid = "BYU-WiFi"; //SSID of your Wi-Fi router
const char* password = ""; //Password of y
const char* mqtt_server = ""; //ip of hub

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
int value = 0;
int state = 2;

void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
}

void callback(char* topic, byte* payload, unsigned int length) {
  char msg[length];
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
		msg += (char)payload[i];
  }
	Serial.println(msg);
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "button";
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("test", clientId.c_str());
      client.subscribe("test");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if(!client.connected()){
    reconnect();
  }
  client.loop();
	//input needed code here
  delay(1000);
  
}
