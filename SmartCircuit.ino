#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* Put your SSID & Password */
const char* ssid = "Smart Circuit";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

/* Set  IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);


uint8_t relay1pin = 5;//D1
bool relay1 = LOW;


uint8_t relay2pin = 4;//D2
bool relay2 = LOW;


uint8_t relay3pin = 14;//D5
bool relay3 = LOW;


uint8_t relay4pin = 12;//D6
bool relay4 = LOW;

void setup() {
  Serial.begin(115200);
  
  pinMode(relay1pin, OUTPUT);
  pinMode(relay2pin, OUTPUT);
  pinMode(relay3pin, OUTPUT);
  pinMode(relay4pin, OUTPUT);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.on("/",OnConnect);
  server.on("/relay1on",relay1on);
  server.on("/relay1off",relay1off);
  server.on("/relay2on",relay2on);
  server.on("/relay2off",relay2off);
   server.on("/relay3on",relay3on);
  server.on("/relay3off",relay3off);
   server.on("/relay4on",relay4on);
  server.on("/relay4off",relay4off);
  server.onNotFound(NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();

   
    

   

  delay(500);

  if(relay1)
    digitalWrite(relay1pin, LOW);
  else
    digitalWrite(relay1pin, HIGH);
  
  if(relay2)
    digitalWrite(relay2pin, LOW);
  else
    digitalWrite(relay2pin, HIGH);

  if(relay3)
    digitalWrite(relay3pin, LOW);
  else
    digitalWrite(relay3pin, HIGH);
    
  if(relay4)
    digitalWrite(relay4pin, LOW);
  else
    digitalWrite(relay4pin, HIGH);
}
void update_status(){
  server.send(200, "text/html", SendHTML(relay1,relay2,relay3,relay4));  // we send HTML page alng with updated LED status.
}
void OnConnect() {
  relay1 = LOW;
  relay2 = LOW;
  relay3 = LOW;
  relay4 = LOW;
  update_status();
}

void relay1on() {
  relay1 = HIGH;
  update_status();
}

void relay1off() {
  relay1 = LOW;
  update_status();
}

void relay2on() {
  relay2= HIGH;
  update_status();
}

void relay2off() {
  relay2 = LOW;
  update_status();
}

void relay3on() {
  relay3= HIGH;
  update_status();
}

void relay3off() {
  relay3 = LOW;
  update_status();
}

void relay4on() {
  relay4= HIGH;
  update_status();
}

void relay4off() {
  relay4 = LOW;
  update_status();
}
void NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t relay1stat,uint8_t relay2stat,uint8_t relay3stat,uint8_t relay4stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Device Control</title>\n";
  ptr +="<style>html { font-family: Arial; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #343444;margin: 50px auto 30px;} h3 {color: #434444;margin-bottom: 50px;}\n";

  ptr +=".button {display: block;width: 100px;background-color: #1abc9c;border:none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 50%;}\n";
  ptr +=".button-on {background-color: #ff9900;}\n";
  ptr +=".button-on:active {background-color: #996633;}\n";
  ptr +=".button-off {background-color: #003399;}\n";
  ptr +=".button-off:active {background-color: #003366;}\n";
  
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 based Arduino Web Server</h1>\n";
  
  if(relay1stat)
      ptr +="<p>Device1 Status: ON</p><a class=\"button button-off\" href=\"/relay1off\">OFF</a>\n";
  else
      ptr +="<p>Device1 Status: OFF</p><a class=\"button button-on\" href=\"/relay1on\">ON</a>\n";

  if(relay2stat)
      ptr +="<p>Device1 Status: ON</p><a class=\"button button-off\" href=\"/relay2off\">OFF</a>\n";
  else
      ptr +="<p>Device1 Status: OFF</p><a class=\"button button-on\" href=\"/relay2on\">ON</a>\n";
      
  if(relay3stat)
      ptr +="<p>Device1 Status: ON</p><a class=\"button button-off\" href=\"/relay3off\">OFF</a>\n";
  else
      ptr +="<p>Device1 Status: OFF</p><a class=\"button button-on\" href=\"/relay3on\">ON</a>\n";
      
  if(relay4stat)
      ptr +="<p>Device1 Status: ON</p><a class=\"button button-off\" href=\"/relay4off\">OFF</a>\n";
  else
      ptr +="<p>Device1 Status: OFF</p><a class=\"button button-on\" href=\"/relay4on\">ON</a>\n";

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}