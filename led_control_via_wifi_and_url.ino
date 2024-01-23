#include <ESP8266WiFi.h>
const char* ssid = "Pawan";
const char* password = "12345678";

WiFiServer server(80);
void setup() {
 Serial.begin(9600);
 delay(10);
 pinMode(LED_BUILTIN, OUTPUT);
 digitalWrite(LED_BUILTIN, 0);
 
 // Connect to WiFi network
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);
 
 WiFi.begin(ssid, password);
 
 while (WiFi.status() != WL_CONNECTED) 
 {
 delay(500);
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 
 // Print the IP address
 Serial.println(WiFi.localIP());
 
 // Start the server
 server.begin();
 Serial.println("Server started");
}
void loop() {
 
 // Check if a client has connected
 WiFiClient client = server.available();
 if (!client) 
 {
 return;
 }
 
 // Wait until the client sends some data
 Serial.println("new client");
 while(!client.available())
 {
 delay(1);
 }
 
 // Read the first line of the request
 String req = client.readStringUntil('\r');
 Serial.println(req);
 client.flush();
 
 // Match the request
 int val;
 String m;
 if (req.indexOf("/LED/ON") != -1){
 m = "LED is ON";
 digitalWrite(LED_BUILTIN, 0);
 }
 else if (req.indexOf("/LED/OFF") != -1){
 m = "LED is OFF";
 digitalWrite(LED_BUILTIN, 1);
 }
 else {
 Serial.println("invalid request");
 client.stop();
 return;
 }
 client.flush();
 // Prepare the response
 String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE 
HTML>\r\n<head><meta http-equiv=\"Access-Control-Allow-Origin\" 
content=\"*\"></head>\n<html>\r\n" +m;
 s += "</html>\n";
 // Send the response to the client
 client.print(s);
 delay(1);
 Serial.println("Client disonnected");
 // The client will actually be disconnected 
 // when the function returns and 'client' object is detroyed
}
