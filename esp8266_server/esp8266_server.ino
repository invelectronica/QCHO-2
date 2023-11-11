// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "datos.h"

#define debug 1    // SET TO 0 OUT TO REMOVE TRACES
#if     debug
#define debugBegin(...) Serial.begin(__VA_ARGS__)
#define debugP(...)      Serial.print(__VA_ARGS__)
#define debugW(...)     Serial.write(__VA_ARGS__)
#define debugln(...)    Serial.println(__VA_ARGS__)
#else
#define debugBegin(...)
#define debugP(...)
#define debugW(...)
#define debugln(...)
#endif

byte Estado; //= false;
byte ZAlarm=5;
byte ZAlarm1=20;
int  timeAnt;
const uint32_t TiempoEsperaWifi = 5000;

unsigned long TiempoActual = 0;
unsigned long TiempoAnterior = 0;
const long TiempoCancelacion = 500;

ESP8266WebServer server(80);
IPAddress ip(192,168,0,100);     
IPAddress gateway(192,168,0,1);   
IPAddress subnet(255,255,255,0);

void setup() {
  Serial.begin(115200);
  debugln("\nIniciando Wifi");
  WiFi.begin(ssid_1, password_1);
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);
  debugP("Conectando a Wifi ..");
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    debugP(".");
  }
  Serial.println(".. Conectado");
  debugP("SSID:");
  debugP(WiFi.SSID());
  debugP(" ID:");
  Serial.println(WiFi.localIP());

  server.on("/", mensajeBase);
  server.on("/lon",[](){Serial.println(1);});
  server.on("/lof",[](){Serial.println(2);});
  server.on("/ron",[](){Serial.println(3);});
  server.on("/rof",[](){Serial.println(4);});
  server.on("/alarma", HTTP_GET, handleObtenerVariable);
  server.onNotFound(mensajeError);

  server.begin();
  Serial.println("Servidor iniciado"); 

  timeAnt=millis();
}

void loop() {
  server.handleClient();
  
  if(millis()-timeAnt>=8000){
    ZAlarm+=1;
    timeAnt=millis();
  }
}

void mensajeBase() {
  Pagina.replace("{variable}", String(ZAlarm1));
  server.send(200, "text/html", Pagina);
}

void mensajeError() {
  String mensaje = "<h1>404</h1>";
  mensaje += "Pagina No encontrada</br>";
  mensaje += "Intenta otra pagina</br>";
  server.send(404, "text/html", mensaje);
}

void handleObtenerVariable() {
  server.send(200, "text/plain", String(ZAlarm));
}