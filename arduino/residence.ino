#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h>

boolean incoming = 0;
int rele1 = 0;
int rele2 = 0;
int Botao = 0;
const int btt = 6;
const int LM35 = A5;           // Pino Analogico onde vai ser ligado ao pino 2 do LM35
const int REFRESH_RATE = 2000; //Tempo de atualização entre as leituras em ms
const float CELSIUS_BASE = 0.4887585532746823069403714565;
byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 25, 177);
EthernetServer server(80);
EthernetClient client;

void setup()
{
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(9600);
  pinMode(btt, INPUT);
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
}

float readTemperature()
{
  return (analogRead(LM35) * CELSIUS_BASE);
}
void loop()
{
  int estadoanterior = Botao;
  Botao = digitalRead(btt);
  if (Botao == HIGH && estadoanterior == LOW)
  {
    if (rele1 == 1)
    {
      rele1 = 0;
      digitalWrite(7, LOW);
    }
    else
    {
      rele1 = 1;
      digitalWrite(7, HIGH);
    }
  }
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
  root["temperature"] = readTemperature();
  if (client.connect("192.168.25.3", 8080))
  {
    client.println("POST /residence/backend/temperatures HTTP/1.1");
    client.println("Host: 192.168.25.3");
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(200);
    client.println();
    root.prettyPrintTo(client);
    client.println();
    Serial.println("Success");
    client.stop();
    delay(600000 * 3);
  }
  else
    Serial.println("Fail");
  /*
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    String str;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        str.concat(c);
        if(str.endsWith("/1on")) rele1 =1;
        else if(str.endsWith("/1off")) rele1 =0;
        if(str.endsWith("/2on")) rele2 =1;
        else if(str.endsWith("/2off")) rele2 =0;
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/json");
          client.println();
          //client.println(str);
          //client.println("<br />Temperatura: ");
          StaticJsonBuffer<200> jsonBuffer;
          JsonObject& root = jsonBuffer.createObject();
          root["temperature"] = readTemperature();
          //client.println(readTemperature());
          //client.println("<br />Rele 01: ");
          if(rele1 == 1)
          {            
            root["rele1"] = "ON";
            //client.println("ON" );
            digitalWrite(7, HIGH);
          }
          else if (rele1 ==0)
          {
            root["rele1"] = "OFF";
            digitalWrite(7, LOW);
          }
          //client.println("<br />Rele 02: ");
          if(rele2 == 1)
          {
            root["rele2"] = "ON";
            digitalWrite(8, HIGH);
          }
          else if (rele2 ==0)
          {
            root["rele2"] = "OFF";
            digitalWrite(8, LOW);
          }
          root.prettyPrintTo(client);
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }*/
}
