
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "BYU-WiFi"; //SSID of your Wi-Fi router
const char* password = ""; //Password of your Wi-Fi router
double lightamount = 0;
#define pPin D6 //photo resistor pin
#define tPin D7 //Temp pin
#define lPin D4 //light pin

void temp(){
  digitalWrite(pPin, LOW);
  digitalWrite(tPin, HIGH);
  int reading = analogRead(A0);
  float voltage = (reading * 5.0)/ 1024.0;
  Serial.print(voltage);
  float tempc = (voltage-0.5) * 100;
  float tempf = (tempc * 9.0 / 5.0 ) + 32;
  Serial.print("Temp: ");
  Serial.println(tempc);
  Serial.println(tempf);
  digitalWrite(tPin, LOW);
  char message[56]; 
  sprintf(message, "%d", tempf);
  //server.send(200, "text/html", message);
	//send via mqtt
}

void photoResistor(){
  lightOn();
  delay(1000);
  digitalWrite(tPin, LOW);
  digitalWrite(pPin, HIGH);
  lightamount = analogRead(A0);
  Serial.print("Light: ");
  Serial.println(lightamount);
  char message[56]; 
  sprintf(message, "%d", lightamount);
  digitalWrite(pPin, LOW);
  delay(1000);
  lightOff();
  //server.send(200, "text/html", message);
	//send via mqtt
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
  Serial.println(WiFi.macAddress());
}
void callback(char* topic, byte* payload, unsigned int length) {
  char msg[length];
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
		//msg = msg + (char)payload[i];
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
void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(tPin, OUTPUT);
  pinMode(pPin, OUTPUT);
  pinMode(lPin, OUTPUT);
  setup_wifi();
  
}

void loop()
{
  server.handleClient();
}
