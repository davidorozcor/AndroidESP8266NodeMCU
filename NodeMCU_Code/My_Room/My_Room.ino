#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

//Our Wi-Fi ssdid and password
char* ssid = "WirelessName"; //Put your Wi-Fi ssdid here
char* password = "password"; //Your Wi-Fi Password
String room_light = "0";
String mirror_light = "0";
String bed_light = "0";
String fan = "0";

// NETWORK: to setup Static IP
IPAddress ip(192, 168, x, x); //example 1,100 -- REPLACE x,x
IPAddress gateway(192, 168, x, x); // 1, 254 -- REPLACE x,x
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server; //server variable

void setup() {
  initializePin(); //call function
  
  // Static IP Setup
  WiFi.config(ip, gateway, subnet);

  //Making Connection With netword
  WiFi.begin(ssid, password);
  
  //Serial.begin(115200);
  //Serial.print("Searching Connection");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println("");
  Serial.print("IP Address: "); //Show the IP Address to access your NodeMCU
  Serial.print(WiFi.localIP());
  
  serverSection();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();

}

void initializePin(){
  
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);

  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
}

void serverSection(){
  server.on("/", []() {
    server.send(200, "text/html", "<!DOCTYPE html><html><meta charset='UTF-8'><head></head><body><h2>Sulkiflee's Room</h2><h3><a href='/room_light'>ไฟห้อง</a></h3><br><h3><a href='/mirror_light'>ไฟหน้ากระจก</a></h3><br><h3><a href='/bed_light'>ไฟเตียง</a></h3><br><h3><a href='/fan'>พัดลม</a></h3><br></body></html>");
  });

  server.on("/room_light", room_light_state);
  server.on("/mirror_light", mirror_light_state);
  server.on("/bed_light", bed_light_state);
  server.on("/fan", fan_state);

  server.on("/status", all_state);
  
  server.begin();
}

void room_light_state(){
  if(room_light == "0"){
    room_light = "1";
    digitalWrite(D5, HIGH);
    server.send(200, "text/html", room_light);
  }else{
    room_light = "0";
    digitalWrite(D5, LOW);
    server.send(200, "text/html", room_light);
  }
}

void mirror_light_state(){
  if(mirror_light == "0"){
    mirror_light = "1";
    digitalWrite(D6, HIGH);
    server.send(200, "text/html", mirror_light);
  }else{
    mirror_light = "0";
    digitalWrite(D6, LOW);
    server.send(200, "text/html", mirror_light);
  }
}

void bed_light_state(){
  if(bed_light == "0"){
    bed_light = "1";
    digitalWrite(D7, HIGH);
    server.send(200, "text/html", bed_light);
  }else{
    bed_light = "0";
    digitalWrite(D7, LOW);
    server.send(200, "text/html", bed_light);
  }
}

void fan_state(){
  if(fan == "0"){
    fan = "1";
    digitalWrite(D8, HIGH);
    server.send(200, "text/html", fan);
  }else{
    fan = "0";
    digitalWrite(D8, LOW);
    server.send(200, "text/html", fan);
  }
}

void all_state(){
  server.send(200, "text/html", "{'rl':'"+room_light+"','ml':'"+mirror_light+"','bl':'"+bed_light+"','fan':'"+fan+"'}");
}


