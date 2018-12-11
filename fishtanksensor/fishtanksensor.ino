
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Chicken Hat"; //SSID of your Wi-Fi router
const char* password = "super 40141 HAIRcut party"; //Password of your Wi-Fi router
const char* mqtt_server = "192.168.44.88"; //ip of hub 

double lightamount = 0;
double temperature = 0;
#define pPin D6 //photo resistor pin
#define tPin D7 //Temp pin
#define lPin D4 //light pin
WiFiClient espClient;
PubSubClient client(espClient);
char message_buff[50];

void temp(){
  digitalWrite(pPin, LOW);
  digitalWrite(tPin, HIGH);
  temperature = analogRead(A0);
  float voltage = (temperature * 5.0)/ 1024.0;
  float tempc = (voltage-0.5) * 100;
  float tempf = (tempc * 9.0 / 5.0 ) + 32;
  Serial.println(tempf);
  digitalWrite(tPin, LOW);
  String pubString = String(tempf);
  pubString.toCharArray(message_buff, pubString.length()+1);
  client.publish("temp", message_buff);
}

void photoResistor(){
  lightOn();
  delay(1000);
  digitalWrite(tPin, LOW);
  digitalWrite(pPin, HIGH);
  lightamount = analogRead(A0);
  Serial.println(lightamount);
  digitalWrite(pPin, LOW);
  delay(1000);
  lightOff();
  String pubString = String(lightamount);
  pubString.toCharArray(message_buff, pubString.length()+1);
  client.publish("light", message_buff);
}

void lightOn(){
  digitalWrite(lPin, HIGH);
}

void lightOff(){
  digitalWrite(lPin, LOW);
}

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
}

void callback(char* topic, byte* payload, unsigned int length) {
  char msg[length];
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  // create character buffer with ending null terminator (string)
  int i = 0;
  for(i=0; i<length; i++) {
    message_buff[i] = payload[i];
  }
  message_buff[i] = '\0';
  
  String msgString = String(message_buff);
	Serial.println(msgString);
  if (msgString.equals("light")){
    photoResistor();
  }
  else if (msgString.equals("temp")){
    temp();
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "button";
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("status", clientId.c_str());
      client.subscribe("command");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(tPin, OUTPUT);
  pinMode(pPin, OUTPUT);
  pinMode(lPin, OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if(!client.connected()){
    reconnect();
  }
  client.loop();
  //photoResistor();
  //temp();
  delay(1000);
}
