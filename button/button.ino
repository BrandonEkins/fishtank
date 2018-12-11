#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
const char* ssid = "Chicken Hat"; //SSID of your Wi-Fi router
const char* password = "super 40141 HAIRcut party"; //Password of y
const char* mqtt_server = "192.168.44.88"; //ip of hub
char message_buff[50];
#define OLED_RESET 0  // GPIO0
#define buttonPin D8
Adafruit_SSD1306 display(OLED_RESET);
String light;
String temp;
WiFiClient espClient;
PubSubClient client(espClient);
int buttonToggle = 1;
int buttonState = 0;
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
  // create character buffer with ending null terminator (string)
  int i = 0;
  for(i=0; i<length; i++) {
    message_buff[i] = payload[i];
  }
  message_buff[i] = '\0';
  
  String msgString = String(message_buff);
  Serial.println(msgString);
  String msgtopic = String(topic); 
  if (msgtopic.equals("light")){
    light = msgString;
  }
  else if (msgtopic.equals("temp")){
    temp = msgString;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Dirt: " + light);
  display.println("Temp: " + temp);
  display.display();  
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
      client.subscribe("temp");
      client.subscribe("light");
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
  pinMode(buttonPin, INPUT);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
  display.clearDisplay();
}

void loop() {
  if(!client.connected()){
    reconnect();
  }
  client.loop();
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && buttonToggle != buttonState){
    Serial.println("HIGH");
    client.publish("button", "1");
    buttonToggle = buttonState;
  }
  else if (buttonState == LOW && buttonToggle != buttonState){
    Serial.println("LOW");
    buttonToggle = buttonState;
  }
  
}
