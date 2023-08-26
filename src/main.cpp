#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>

const char* ssid = "embauba32"; //Define o nome do ponto de acesso
const char* pass = "satelitaos2"; //Define a senha

WiFiUDP udp;

IPAddress raspberryPiIP(255, 255, 255, 255);  // Replace with the Raspberry Pi's IP address (192, 168, 4, 255)
const int udpPort = 1234;

void setup() {
  Serial.begin(9600); //Inicia o monitor serial
  WiFi.softAP(ssid, pass); //Inicia o ponto de acesso
  Serial.print("Se conectando a: "); //Imprime mensagem sobre o nome do ponto de acesso
  Serial.println(ssid);
  Serial.print("Endereço de IP: "); //Imprime o endereço de IP
  Serial.println(WiFi.softAPIP()); //Endereço de IP
  udp.begin(udpPort); // Choose a port number
}

void loop() {
  // Create a JSON object
  DynamicJsonDocument jsonDoc(256);
  jsonDoc["sensor"] = "ESP32";
  jsonDoc["data"] = "Hello, Raspberry Pi!";
  
  // Serialize the JSON object to a string
  String jsonStr;
  serializeJson(jsonDoc, jsonStr);
  // Send the JSON packet to the Raspberry Pi's IP address
  udp.beginPacket(raspberryPiIP, udpPort);
  udp.print(jsonStr);
  udp.endPacket();

  delay(1000);
}

// Broadcast the JSON packet to all connected clients
//  IPAddress multicastIP(239, 0, 0, 1);
//  udp.beginPacket(multicastIP, 1234);
//  udp.print(jsonStr);
//  udp.endPacket();