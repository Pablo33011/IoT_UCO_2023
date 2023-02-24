#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "Pablo";
const char *password = "andres11";

ESP8266WebServer server(80);

int ledPin = D4;
int ledPin2 = D3;
bool ledState = LOW;
bool ledState2 = LOW;
String paginaInicio;

void mostrarPagina()
{
  String paginaInicio = "<html><head><title>Control de LED</title></head><body>";
  paginaInicio += "<h1>Control de LED</h1>";
  paginaInicio += "<p>Seleccione el LED a controlar:</p>";
  paginaInicio += "<p><a href='/led1'><button>LED 1</button></a></p>";
  paginaInicio += "<p><a href='/led2'><button>LED 2</button></a></p>";
  paginaInicio += "</body></html>";

  server.send(200, "text/html", paginaInicio);
}
void encenderLed1()
{
  String led1Page = "<html>";
  led1Page += "<head><title>Control de LED</title></head>";
  led1Page += "<body><h1>Control de LED 1</h1>";
  led1Page += "<button onclick=\"sendRequest('on')\">Encender LED</button>";
  led1Page += "<button onclick=\"sendRequest('off')\">Apagar LED</button>";
  led1Page += "<script>";
  led1Page += "function sendRequest(state) {";
  led1Page += "console.log('led1On');";
  led1Page += "var xhttp = new XMLHttpRequest();";
  led1Page += "xhttp.open('POST', '/led1', true);";
  led1Page += "xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');";
  led1Page += "xhttp.send('command=' + state);";
  led1Page += "}";
  led1Page += "</script>";
  led1Page += "</body></html>";

  server.send(200, "text/html", led1Page);
}
void obtenerEstadoLed1()
{
  if (server.hasArg("command"))
  {
    String command = server.arg("command");
    Serial.println(command);
    if (command == "on")
    {
      ledState = HIGH;
    }
    else if (command == "off")
    {
      ledState = LOW;
    }

    digitalWrite(ledPin, ledState);
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void encenderLed2()
{
  String led2Page = "<html>";
  led2Page += "<head><title>Control de LED</title></head>";
  led2Page += "<body><h1>Control de LED 2</h1>";
  led2Page += "<button onclick=\"sendRequest('on')\">Encender LED</button>";
  led2Page += "<button onclick=\"sendRequest('off')\">Apagar LED</button>";
  led2Page += "<script>";
  led2Page += "function sendRequest(state) {";
  led2Page += "console.log('led2On');";
  led2Page += "var xhttp = new XMLHttpRequest();";
  led2Page += "xhttp.open('POST', '/led2', true);";
  led2Page += "xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');";
  led2Page += "xhttp.send('command=' + state);";
  led2Page += "}";
  led2Page += "</script>";
  led2Page += "</body></html>";

  server.send(200, "text/html", led2Page);
}
void obtenerEstadoLed2()
{
  if (server.hasArg("command"))
  {
    String command = server.arg("command");
    Serial.println(command);
    if (command == "on")
    {
      ledState2 = HIGH;
    }
    else if (command == "off")
    {
      ledState2 = LOW;
    }

    digitalWrite(ledPin2, ledState2);
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin, ledState);
  digitalWrite(ledPin2, ledState2);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conexión a WiFi establecida");

  server.on("/", HTTP_GET, mostrarPagina);
  server.on("/led1", HTTP_GET, encenderLed1);
  server.on("/led1", HTTP_POST, obtenerEstadoLed1);
  server.on("/led2", HTTP_GET, encenderLed2);
  server.on("/led2", HTTP_POST, obtenerEstadoLed2);

  server.begin();
  Serial.println("Servidor iniciado");

  Serial.print("Dirección IP del servidor: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  server.handleClient();
}