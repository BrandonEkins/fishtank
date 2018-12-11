#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
const char* ssid = "BYU-WiFi"; //SSID of your Wi-Fi router
const char* password = ""; //Password of y
const char* mqtt_server = ""; //ip of hub

#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

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

void setup() {
  Serial.begin(9600);
  //setup_wifi();
  //client.setServer(mqtt_server, 1883);
  //client.setCallback(callback);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Hello");
  display.display();
  delay(10000);
  #include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
// SCL GPIO5
// SDA GPIO4
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);
 
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
 
 
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
 
 
void setup()   {
  Serial.begin(9600);
 
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
  // init done
 
  //display.display();
  //delay(2000);
 
  //// Clear the buffer.
  //display.clearDisplay();
 
  //// text display tests
  //display.setTextSize(1);
  //display.setTextColor(WHITE);
  //display.setCursor(0,0);
  //display.println("Hello, world!");
  //display.display();
  //delay(2000);
  //display.clearDisplay();
 
}
 
 
void loop() {
 
}
}

void loop() {
  if(!client.connected()){
    reconnect();
  }
  client.loop();
  //input needed code here
  
}
