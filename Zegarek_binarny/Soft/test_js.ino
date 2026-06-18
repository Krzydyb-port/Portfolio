//============================================
//ESP8266 Web Server (HTML + CSS + JavaScript)
//============================================
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer_Generic.h>
#include <time.h>
#include <DS1307.h> //tmp
#include "webpageCode.h"
//------------------------------------------
ESP8266WebServer server(80);
const char* ssid_AP = "Zegarek";
const char* password_AP = "password";
char SSID [100] = "";
char PASS [100] = "";
int brightness = 100;
uint8_t hours = 0;
uint8_t minutes = 0;
uint8_t seconds = 0;
uint8_t trash = 0;
uint16_t trash2 = 0;
int tizo_value = 114;
String tizo = "CET-1CEST,M3.5.0,M10.5.0/3"; // Set for Warsaw
int counter1 = 0;
bool first_c = true;
bool tz_man = false; // Set to timezone time
WebSocketsServer webSocket = WebSocketsServer(81);
//------------------------------------------
//RTC begins
DS1307 rtc;
//#include <Wire.h> // must be included here so that Arduino library object file references work
//#include <RtcDS1307.h>
//RtcDS1307<TwoWire> Rtc(Wire);
//RTC end


//esp32-hal-time.c begin
//Get local time, idk what ms are for but set it to 1000
bool getLocalTime(struct tm * info, uint32_t ms){
    uint32_t start = millis();
    time_t now;
    while((millis()-start) <= ms) {
        time(&now);
        localtime_r(&now, info);
        if(info->tm_year > (2016 - 1900)){
            return true;
        }
        delay(10);
    }
    return false;
}
//esp32-hal-time.c end
//------------------------------------------
//NTP begin
void setTimezone(String timezone){
  Serial.printf("  Setting Timezone to %s\n",timezone.c_str());
  setenv("TZ",timezone.c_str(),1);  //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
  tzset();
}
void initTime(String timezone){
  struct tm timeinfo;

  Serial.println("Setting up time");
  configTime(0, 0, "pool.ntp.org");    // First connect to NTP server, with 0 TZ offset
  if(!getLocalTime(&timeinfo,10000)){
    Serial.println("  Failed to obtain time in init");
    //websocet time time server connection error
    return;
  }
  Serial.println("  Got the time from NTP");
  // Now we can set the real timezone
  setTimezone(timezone);
}
void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo,10000)){
    Serial.println("Failed to obtain time in print");
    //websocet time accusition error
    return;
  }
  hours = timeinfo.tm_hour;
  minutes = timeinfo.tm_min;
  seconds = timeinfo.tm_sec;
  //Debug
  //Serial.println(hours);
  //Serial.print(":");
  //Serial.print(minutes);
  //Serial.print(":");
  //Serial.print(seconds);
}
//NTP end
//------------------------------------------
void webpage(){
  server.send(200,"text/html", webpageCode);
}
bool WiFi_connect()
{
  WiFi.begin(SSID,PASS);
  uint8_t networkTimeOut = 0;
  while(WiFi.status() != WL_CONNECTED){     
    if(networkTimeOut > 15){
      //websocket wywala info o blędzie połaczenia
      webSocket.broadcastTXT("1rStatus: WiFi not connected!");
      Serial.print("Connection Failed :(");
      return 0;
    }
    Serial.println("Connecting...");
    delay(1000);
    networkTimeOut++;
  }
    if(WiFi.status() == WL_CONNECTED){
      Serial.print("Connected! IP address: ");
      Serial.println(WiFi.localIP());
      webSocket.broadcastTXT("0" + WiFi.localIP().toString());
      webSocket.broadcastTXT("1gStatus: WiFi connected!");
      first_c = false;
      initTime(tizo);
    }
    return 1;
}
//------------------------------------------
void webSocketEvent(const uint8_t& num, const WStype_t& type, uint8_t * payload, const size_t& length){
  (void) length;
  char* str = NULL;
  switch (type)
  {
    case WStype_TEXT:
    // Debug 
       Serial.printf("%s\n", payload);
    //end Debug
       switch(payload[0])
       {
          case '0':
              update_site();
          break;
          case '1':
            str = (char*)&payload[1];
            strcpy(SSID,(const char*)str);
            Serial.printf("%s\n", SSID);
          break;
          case '2':{
             str = (char*)&payload[1];
            strcpy(PASS,(const char*)str);
            Serial.printf("%s\n", PASS);
            WiFi_connect();
            break;
          }
          case '3':
            //zmiana strefy czasowej i wczytanie nowego czasu z nowej strefy właczenie ntp
            //
            //zmienic strefe czasową można tylko jak się połączysz
            tizo_value = (int)payload[1];
            Serial.printf("Tutaj wartość: %i",tizo_value);
            switch(tizo_value){
              case '0':
               tizo = "<-12>12";
              break;
              case '1':
                tizo = "<-11>11";
              break;
              case '2':
                tizo = "<-10>10";
              break;
              case '3':
                tizo = "<-09>9";
              break;
              case '4':
                tizo = "<-08>8";
              break;
              case '5':
                tizo = "<-07>7";
              break;
              case '6':
                tizo ="<-06>6";
              break;
              case '7':
                tizo ="<-05>5";
              break;
              case '8':
                tizo ="<-04>4";
              break;
              case '9':
                tizo ="<-03>3";
              break;
              case 'q':
                tizo ="<-02>2";
              break;
              case 'w':
                tizo ="<-01>1";
              break;
              case 'e':
                tizo ="GMT0";
              break;
              case 'r':
                tizo = "CET-1CEST,M3.5.0,M10.5.0/3";
              break;
              case 't':
                tizo = "<+01>-1";
              break;
              case 'y':
                tizo = "<+02>-2";
              break;
              case 'u':
                tizo = "<+03>-3";
              break;
              case 'i':
                tizo = "<+04>-4";
              break;
              case 'o':
                tizo = "<+05>-5";
              break;
              case 'p':
                tizo = "<+06>-6";
              break;
              case 'a':
                tizo = "<+07>-7";
              break;
              case 's':
                tizo = "<+08>-8";
              break;
              case 'd':
                tizo = "<+09>-9";
              break;
              case 'f':
                tizo = "<+10>-10";
              break;
              case 'g':
               tizo = "<+11>-11";
              break;
              case 'h':
                tizo = "<+12>-12";
              break;
              case 'j':
                tizo = "<+13>-13";
              break;
              case 'k':
                tizo = "<+14>-14";
              break;
            }
            //tylko jak jest się połączonym można zmienić strefe czasową
            setTimezone(tizo);
            if(WiFi.status() == WL_CONNECTED){
              printLocalTime();
              rtc.set(seconds,minutes,hours,0,0,0);
              tz_man = false;
            }
          break;
          case '4':
            //zmiana jasnosci swiecenia
            str = (char*)&payload[1];
            brightness = atoi(str);
            Serial.print(brightness);
          break;
          case '5':
            str = (char*)&payload[1];
            hours = atoi(str);
            rtc.set(seconds,minutes,hours,0,0,0);
            //zmiana czasu ad hoc z wyłączeniem ntp
          break;
          case '6':
            str = (char*)&payload[1];
            minutes = atoi(str);
            rtc.set(seconds,minutes,hours,0,0,0);
            //zmiana czasu ad hoc z wyłączeniem ntp
          break;
          case '7':
            str = (char*)&payload[1];
            seconds = atoi(str);
            tz_man = true;
            rtc.set(seconds,minutes,hours,0,0,0);
            //zmiana czasu ad hoc z wyłączeniem ntp
          break;
          default:
            Serial.print("default");
          break;
       }
      // send message to client
      // webSocket.sendTXT(num, "message here");

      // send data to all connected clients
      // webSocket.broadcastTXT("message here");
      break;

    case WStype_BIN:
      // Serial.printf("[%u] get binary length: %u\n", num, length);
      // hexdump(payload, length);

      // send message to client
      // webSocket.sendBIN(num, payload, length);
      break;
     default:
      break;
  }
}
void update_site()
{
  if(WiFi.status() == WL_CONNECTED)
  {
    webSocket.broadcastTXT("0" + WiFi.localIP().toString());
    webSocket.broadcastTXT("1gStatus: WiFi connected!");
  }
    if(WiFi.status() != WL_CONNECTED)
  {
    webSocket.broadcastTXT("0 ");
    webSocket.broadcastTXT("1rStatus: WiFi not connected!");
  }
  webSocket.broadcastTXT("3"+ String(brightness));
  webSocket.broadcastTXT("2"+ String((char)(uint8_t)tizo_value));
}
//------------------------------------------
void i_shift_reg(byte digits, byte digitm, byte digith)
{
  byte jeds = digits%10;
  byte dzies = digits/10;
  byte jedm = digitm%10;
  byte dziem = digitm/10; 
  byte jedh = digith%10;
  byte dzieh = digith/10;  
    for(byte i = 0; i< 4; i++)
  {
    if(bitRead(jeds,i) == 1)
    {
      digitalWrite(D5,HIGH); //SER
    }
    else
    {
      digitalWrite(D5,LOW);
    }
        if(bitRead(jedm,i) == 1)
    {
      digitalWrite(D6,HIGH);
    }
    else
    {
      digitalWrite(D6,LOW);
    }
        if(bitRead(jedh,i) == 1)
    {
      digitalWrite(D7,HIGH);
    }
    else
    {
      digitalWrite(D7,LOW);
    }

  digitalWrite(D4, HIGH); // SRCLK
  digitalWrite(D4, LOW); // SRCLK
  }

    for(byte i = 0; i< 3; i++)
  {
      if(bitRead(dzies,i) == 1)
    {
      digitalWrite(D5,HIGH); //SER
    }
    else
    {
      digitalWrite(D5,LOW);
    }
        if(bitRead(dziem,i) == 1)
    {
      digitalWrite(D6,HIGH);
    }
    else
    {
      digitalWrite(D6,LOW);
    }
        if(bitRead(dzieh,i) == 1)
    {
      digitalWrite(D7,HIGH);
    }
    else
    {
      digitalWrite(D7,LOW);
    }
  digitalWrite(D4, HIGH); // SRCLK
  digitalWrite(D4, LOW); // SRCLK
  }
  digitalWrite(D4, HIGH); // SRCLK
  digitalWrite(D4, LOW); // SRCLK

  digitalWrite(D3, HIGH); // RCLK
  digitalWrite(D3, LOW); // RCLK
}
//=================================================================
void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid_AP,password_AP);
  //while(WiFi.status()!=WL_CONNECTED){delay(500);Serial.print(".");}
  //Serial.println();
  Serial.print("IP Address: "); Serial.println(WiFi.softAPIP());
  //pinMode(D5, INPUT);
  server.on("/", webpage);
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  pinMode(D3, OUTPUT); //RCLK
  pinMode(D4, OUTPUT); //SRCLK
  pinMode(D5, OUTPUT); //Seconds SER
  pinMode(D6, OUTPUT); //Minutes SER
  pinMode(D7, OUTPUT); //Hours SER
  rtc.begin();
  rtc.start();
  //digitalWrite(D2,LOW);
  //digitalWrite(D5,HIGH);
  //Rtc.Begin();
  //#if defined(WIRE_HAS_TIMEOUT)
  //  Wire.setWireTimeout(3000 /* us */, true /* reset_on_timeout */);
  //#endif

}
//=================================================================
void loop()
{
  //if(digitalRead(D5) == 1) webSocket.broadcastTXT("10");
  //else webSocket.broadcastTXT("01");
  server.handleClient();
  webSocket.loop();
  //countery wywalić???
  if(WiFi.status() != WL_CONNECTED && first_c == false)
  {
    WiFi_connect();
  }
  if(WiFi.status() == WL_CONNECTED && tz_man == false)
  {
    printLocalTime();
    rtc.set(seconds,minutes,hours,0,0,0);
    counter1 = 0;
  }
  if(brightness == 0)
  {
    i_shift_reg(0,0,0);
  }
  else
  {
    rtc.get(&seconds,&minutes,&hours,&trash,&trash,&trash2);
      //Serial.print(hours);
     // Serial.print(":");
     // Serial.print(minutes);
      //Serial.print(":");
      //Serial.printf("%i\n",seconds);
    i_shift_reg(seconds,minutes,hours);
    delayMicroseconds(brightness);
    //i_shift_reg(0,D1);
  }
  delayMicroseconds(100);

}