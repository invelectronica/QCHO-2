// Creado ChepeCarlos de ALSW
// Tutorial Completo en https://nocheprogramacion.com
// Canal Youtube https://youtube.com/alswnet?sub_confirmation=1
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "datos.h"

#define debug 0    // SET TO 0 OUT TO REMOVE TRACES
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

const uint32_t TiempoEsperaWifi = 5000;

unsigned long TiempoActual = 0;
unsigned long TiempoAnterior = 0;
const long TiempoCancelacion = 500;

ESP8266WebServer server(80);
IPAddress ip(192,168,0,100);     
IPAddress gateway(192,168,0,1);   
IPAddress subnet(255,255,255,0);


void mensajeArgumento() {
  String mensaje = "Valores Recividos\n\n";
  mensaje += "URI: ";
  mensaje += server.uri();
  mensaje += "\nMetodo: ";
  mensaje += (server.method() == HTTP_GET) ? "GET" : "POST";
  mensaje += "\nArgumentos: ";
  mensaje += server.args();
  mensaje += "\n";

  for (int i = 0; i < server.args() ; i++) {
    mensaje += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  mensaje += "\n";

  if (server.hasArg("pollo")) {
    mensaje += "El Pollo dice " + server.arg("pollo");
  } else {
    mensaje += "No hay pollo";
  }

  server.send(200, "text/plain", mensaje);
}

void mensajeBase() {
  server.send(200, "text/html", Pagina);
}
void mensajeError() {
  String mensaje = "<h1>404</h1>";
  mensaje += "Pagina No encontrada</br>";
  mensaje += "Intenta otra pagina</br>";
  server.send(404, "text/html", mensaje);
}

void setup() {
  Serial.begin(115200);
  debugln("\nIniciando Wifi");
  
  WiFi.begin(ssid_1, password_1);
  //wifiMulti.addAP(ssid_1, password_1);
  
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
  server.on("/lon",[](){Serial.println("Lampara On");});
  server.on("/lof",[](){Serial.println("Lampara Off");server.send(200, "text/plain","verde");});
  server.on("/ron",[](){Estado=1;});
  server.on("/rof",lamparaReflector);
  
  server.on("/valor", mensajeArgumento);

  server.onNotFound(mensajeError);

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient();
}
void lamparaReflector(){
  
}



void ResponderCliente(WiFiClient& cliente) {
  cliente.print(Pagina);
}