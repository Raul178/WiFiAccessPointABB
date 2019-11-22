#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "SonoUnWiFi"
#define APPSK  "password"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;
String pagina1 = "<html><head><style>.div {  display: flex;  justify-content: center;}.button {  display:block;  width: 50%;  font-family: Sans-Serif;  background-color: #0078B6;  color: white;  padding: 35px 65px;  text-align: center;  text-decoration: none;  font-size: 32pt;  margin: 6px 4px;}</style></head><body><div class='div'><a class='button' href='pos1'>Posizione 1</a></div><div class='div'><a class='button' href='pos2'>Posizione 2</a></div><div class='div'><a class='button' href='pos3'>Posizione 3</a></div><div class='div'><a class='button' href='pos4'>Posizione 4</a></div></body></html>";

//durata in ms
const int durata=5000;
const int _D0 = 16;
const int _D1 = 5;
const int _D2 = 4;
const int _D3 = 0;
const int _D4 = 2;


ESP8266WebServer server(80);

/* Go to http://192.168.4.1 in a web browser
   connected to this access point.
*/
void handleRoot() {
  server.send(200, "text/html", pagina1);
}

void pos(int pin)
{
  digitalWrite(_D0, 1);
  digitalWrite(pin, 1);
  server.send(200, "text/html", pagina1);
  delay(durata);
  digitalWrite(_D0, 0);
  digitalWrite(pin, 0);
}

void setup() {
  
  pinMode(_D0, OUTPUT);
  pinMode(_D1, OUTPUT);
  pinMode(_D2, OUTPUT);
  pinMode(_D3, OUTPUT);
  pinMode(_D4, OUTPUT);
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);

  //posizione 1
  server.on("/pos1", []() {
    pos(_D1);
  });

  //posizione 2
  server.on("/pos2", []() {
    pos(_D2);
  });
  
  //posizione 3
  server.on("/pos3", []() {
    pos(_D3);
  });
  
  //posizione 4
  server.on("/pos4", []() {
    pos(_D4);
  });
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
