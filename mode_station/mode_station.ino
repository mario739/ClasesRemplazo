#include <WebServer.h>
#include <WiFi.h>

#define LEDROJO 18
#define RETARDO 100

const char* ssid     = "Mario Aguilar"; // Change this to your WiFi SSID
const char* password = "MRAASMM1468"; // Change this to your WiFi password

WebServer server(80);
String respuesta="<h1> HOLA DESDE LA ESP32 </h1>";

void resp_req()
{
  server.send(200,"text/html", respuesta);
}

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

  server.on("/",resp_req);
  server.begin();
  Serial.println("Servidor HTTP iniciado");
  delay(100);
}


void loop() {
  // put your main code here, to run repeatedly:
  /*digitalWrite(LEDROJO, HIGH);
  Serial.println("LED ON");
  delay(RETARDO);
  digitalWrite(LEDROJO,LOW);
  Serial.println("LED OFF");
  delay(RETARDO);*/
  server.handleClient();
}
