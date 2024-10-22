#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266HTTPClient.h>
String URL= "http://api.thingspeak.com/update?api_key=MU42NV03DHPFR5KP&field1=";
#include<String>
String apiKey = "MU42NV03DHPFR5KP"; // Enter your Write API key from ThingSpeak
const char *ssid = "Harshvardhan"; // replace with your wifi ssid and wpa2 key
const char *pass = "12345678";
const char* server = "api.thingspeak.com";
WiFiClient client;
void setup(){

Serial.begin(9600);
delay(10);
Serial.println("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");



  // Serial.begin(9600);
  // // WiFi.disconnect();
  // // delay(2000);
  // delay(10);

  // Serial.println("Start connection");
  // WiFi.begin("Harshvardhan", "12345678");
  // while((!(WiFi.status() == WL_CONNECTED))){
  //   delay(200);
  //   Serial.print("..");
  // }
  // Serial.println("Connected");
}

void loop(){
  if(Serial.available()>0){
    String data= Serial.readStringUntil('\n');
    // String data= Serial.readString();
    
    Serial.println(data);
    // Serial.print("\n");
    delay(1000);
    int comma= data.indexOf(",");
    if(comma != -1){
      float t= data.substring(0,comma).toFloat();
      float h= data.substring(comma+1).toFloat();
      float m= data.substring(comma+7).toFloat();
      float l= data.substring(comma+13).toFloat();
      float rd= data.substring(comma+19).toFloat();
      float vt= data.substring(comma+23).toFloat();
      float f= data.substring(comma+25).toFloat();
      // Serial.print(t);
      // Serial.println(h);
      sendData(t,h,m,l,rd,vt,f);
    }
  }
}
void sendData(float h, float t, float m, float l, float rd, float vt, float f){
  WiFiClient client;
  HTTPClient http;
  String newURL = URL + String(t)+"&field2="+String(h)+"&field3="+String(m)+"&field4="+String(l)+"&field5="+String(rd)+"&field6="+String(vt)+"&field7="+String(f);
  http.begin(client,newURL);
  int responsecode= http.GET();
  String data = http.getString();
  // Serial.println(data);
  http.end();
}