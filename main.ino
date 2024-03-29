#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
int TRIGGER = D3;
int ECHO   = D2;
// Replace with your network credentials
const char* ssid = "bhuvana";
const char* password = "asdfghjkl";
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
String page = "";
int data; 
void setup(void){
 pinMode(TRIGGER, OUTPUT); 
 pinMode(ECHO, INPUT); 
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", [](){
    page = "<head><meta http-equiv=\"refresh\" content=\"2\"></head><center><h1> Welcome BHUVANESHWARI!!Your tank is monitored </h1><h3>Current water level is :-</h3> <h4>"+String(data)+"</h4></center>";
    server.send(200, "text/html", page);
  });
  server.begin();
  Serial.println("Web server started!");
}
 void loop(void){
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGGER, LOW);
  long duration = pulseIn(ECHO, HIGH);
  data = (duration/2) / 29.09;
  server.handleClient();
}
