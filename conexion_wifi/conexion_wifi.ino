#include <WiFi.h>

#define LEDROJO 18
#define RETARDO 100

const char* ssid     = "Mario Aguilar"; // Change this to your WiFi SSID
const char* password = "MRAASMM1468"; // Change this to your WiFi password

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LEDROJO, OUTPUT);
  Serial.println();
  Serial.println("******************************************************");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LEDROJO, HIGH);
  Serial.println("LED ON");
  delay(RETARDO);
  digitalWrite(LEDROJO,LOW);
  Serial.println("LED OFF");
  delay(RETARDO);
}
