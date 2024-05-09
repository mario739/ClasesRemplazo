#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiSTA.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiType.h>
#include <WiFiUdp.h>

#include <WebServer.h>
#include <WiFi.h>

#define LED1 15
#define LED2 2
#define LED3 4
#define LED4 18
#define RETARDO 100

int led_status1=0;
int led_status2=0;
int led_status3=0;
int led_status4=0;

const char* ssid     = "Esp32"; // Change this to your WiFi SSID
const char* password = "012345678"; // Change this to your WiFi password

//IPAddress ip(192,168,4,22);
//IPAddress gateway(192,168,4,9);
//IPAddress subnet(255,255,255,0);

WebServer server(80);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //Creamos el punto de acceso
  WiFi.softAP(ssid,password);
  //WiFi.softAPConfig(ip, gateway, subnet);

  IPAddress ip=WiFi.softAPIP();

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  Serial.println();
  Serial.println("******************************************************");
  Serial.println("nombre de la red:");
  Serial.println(ssid);
  Serial.println("La ip es:");
  Serial.println(ip);

  /*WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());*/

  Serial.print("Nombre de la red:");
  Serial.print(ssid);

  server.on("/",resp_req); 
  server.on("/led/1",toggle_led1);
  server.on("/led/2",toggle_led2);
  server.on("/led/3",toggle_led3);
  server.on("/led/4",toggle_led4);
  server.onNotFound(handle_NoFound);

  server.begin();
  Serial.println("Servidor HTTP iniciado");
  delay(100);
}


void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

String respuesta="<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width,initial-scale=1'><title>LED Dashboard</title><link href='https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css' rel='stylesheet' integrity='sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC' crossorigin='anonymous'></head><body><h1>LED Dashboard</h1><table><tr class='text-center'><td><button id='led-1-toggle' type='button' class='btn btn-secondary'>LED 1</button></td><td><button id='led-2-toggle' type='button' class='btn btn-secondary'>LED 2</button></td><td><button id='led-3-toggle' type='button' class='btn btn-secondary'>LED 3</button></td><td><button id='led-4-toggle' type='button' class='btn btn-secondary'>LED 4</button></td></tr><tr class='text-center'><td><div id='led-1-status' class='badge bg-danger'>OFF</div></td><td><div id='led-2-status' class='badge bg-danger'>OFF</div></td><td><div id='led-3-status' class='badge bg-danger'>OFF</div></td><td><div id='led-4-status' class='badge bg-danger'>OFF</div></td></tr></table><script>var led1Toggle = document.getElementById('led-1-toggle'); led1Toggle.addEventListener('click', function () { toggleLed(1); }); var led2Toggle = document.getElementById('led-2-toggle'); led2Toggle.addEventListener('click', function () { toggleLed(2); }); var led3Toggle = document.getElementById('led-3-toggle'); led3Toggle.addEventListener('click', function () { toggleLed(3); }); var led4Toggle = document.getElementById('led-4-toggle'); led4Toggle.addEventListener('click', function () { toggleLed(4); }); var toggleLed = function (ledNumber) { fetch('/led/' + ledNumber).then((response) => { response.text().then((status) => { var element = document.getElementById( 'led-' + ledNumber + '-status' ); if (status == '1') { element.innerText = 'ON'; element.className = 'badge btn-success'; } else { element.innerText = 'OFF'; element.className = 'badge btn-danger'; } }); }); };</script></body></html>";

void resp_req()
{
  server.send(200,"text/html", respuesta);
}

void toggle_led1()
{
  if (led_status1==0) 
  {
    digitalWrite(LED1, HIGH);
    server.send(200,"text/html", "1");
    led_status1=1;
  }
  else {
    digitalWrite(LED1, LOW);
    server.send(200,"text/html", "0");
    led_status1=0;
  }
}

void toggle_led2()
{
    if (led_status2==0) 
  {
    digitalWrite(LED2, HIGH);
    server.send(200,"text/html", "1");
    led_status2=1;
  }
  else {
    digitalWrite(LED2, LOW);
    server.send(200,"text/html", "0");
    led_status2=0;
  }
}

void toggle_led3()
{
    if (led_status3==0) 
  {
    digitalWrite(LED3, HIGH);
    server.send(200,"text/html", "1");
    led_status3=1;
  }
  else {
    digitalWrite(LED3, LOW);
    server.send(200,"text/html", "0");
    led_status3=0;
  }

}

void toggle_led4()
{
    if (led_status4==0) 
  {
    digitalWrite(LED4, HIGH);
    server.send(200,"text/html", "1");
    led_status4=1;
  }
  else {
    digitalWrite(LED4, LOW);
    server.send(200,"text/html", "0");
    led_status4=0;
  }

}

void handle_NoFound()
{
  server.send(404,"text/plain", "Not Found");
}
