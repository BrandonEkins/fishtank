#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

char ssid[] = "BYU-WiFi"; //SSID of your Wi-Fi router
char pass[] = ""; //Password of your Wi-Fi router

double lightamount = 0;
#define pPin D6 //photo resistor pin
#define tPin D7 //Temp pin
#define lPin D3 //light pin

String temp(){
  digitalWrite(pPin, LOW);
  digitalWrite(tPin, HIGH);
  int reading = analogRead(A0);
  float voltage = (reading * 5.0)/ 1024.0;
  float tempc = (voltage-0.5) * 100;
  float tempf = (tempc * 9.0 / 5.0 ) + 32;
  digitalWrite(tPin, LOW);
  return String(tempf);
}

String photoResistor(){
  
  digitalWrite(lPin, HIGH);
  delay(500);
  digitalWrite(tPin, LOW);
  digitalWrite(pPin, HIGH);
  lightamount = analogRead(A0);
  digitalWrite(pPin, LOW);
  delay(500);
  digitalWrite(lPin, LOW);
  return String(lightamount);
}



void setup() {
  pinMode(A0, INPUT);
  pinMode(tPin, OUTPUT);
  pinMode(pPin, OUTPUT);
  pinMode(lPin, OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");

  }
  Serial.print("IP Address:");
  Serial.println(WiFi.localIP());
}



void loop() {

  HTTPClient http;

  String m1 = photoResistor();
  delay(1000);
  String m2 = temp(); 
  Serial.println("http://10.37.62.102/getInfo.php?photo="+ m1+ "&temp=" + m2);
  http.begin("http://10.37.62.102/getInfo.php?photo="+ m1+ "&temp=" + m2);
  int httpCode = http.GET();
  http.end();
  Serial.println(httpCode);
  delay(10000);
}
