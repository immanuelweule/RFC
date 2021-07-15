//===============================================================
// @file:     GroundControl_V0.1
// @brief:    Communication CubeSat - Ground Control
//
// @authors:  Adrian Setka, Immanuel Weule
//
// @hardware: ESP32-DevKitC V4 (ESP32-WROOM-32U)
// @comments: Can only connect to 2,4 GHz, not to 5 GHz
//
// @date:     2021-05-29
//===============================================================



//===============================================================
// Header files, variable declarations and WiFi setup
//===============================================================

//Header
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <ESPmDNS.h>  //for URL/name instead of IP address
#include <SPI.h>
#include "index.h"  //Web page header file

//Variables
int counter=0;  //counter for checking connection status in loop

//SPI setup
#define SCLK 13   //HSPICLK
#define MISO 14   //HSPIQ (also referred to as Q)
#define MOSI 16   //HSPID (also referred to as D)
#define SS 23     //Slave Select (SS), randomly chosen pin     

//alternative definitions:
//SPICLK 20
//SPIQ 21
//SPID 22
//or for VSPI:
//VSPICLK 30
//VSPIQ 31
//VSPID 37
//source: https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32d_esp32-wroom-32u_datasheet_en.pdf, page 9

static const int spiClk = 1000000; // 1 MHz

//Set WiFi SSID and password
const char* ssid = "Kewwin_02"; //WiFi SSID
const char* password = "2214934027604276"; //WiFi password

const int Analog_channel_pin = 34;  //Analog Channel Pin

WebServer server(80);  //Setup a HTTP server



//===============================================================
// Function declarations
//===============================================================

//This routine is executed when you open its IP in browser
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}


void handleADC() {
 int a = analogRead(Analog_channel_pin);
 String adcValue = String(a);
 
 server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}


void ConnectToWiFi() {
  Serial.println("Connecting to ");
  Serial.print(ssid);
  
  WiFi.disconnect();
  WiFi.begin(ssid, password); //For ESP as a station; for ESP as a AP use "WiFi.softAP(ssid, password)"

  //Wait for WiFi to connect
  while(WiFi.waitForConnectResult() != WL_CONNECTED){      
      Serial.print("");
  }
    
  //If connection is successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); //IP address assigned to your ESP

  return;
}


//FOLLOWING FUNCTION IS UNUSED SO FAR
byte SPI_Comm(byte dataToSend){
  byte receivedData; //declare variable for received data
  
  SPI.beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  
  digitalWrite(SS, LOW); //enable SS
  
  receivedData=SPI.transfer(dataToSend); //sending and receiving happens simultaneously
  
  digitalWrite(SS, HIGH); //disable SS
  
  return receivedData;
}



//===============================================================
// Setup
//===============================================================

void setup(void){
  Serial.begin(115200); //Open a serial connection
  Serial.println("Booting Sketch...");

  //Initialize how ESP should act - AP or STA (comment out one initialization)
  //WiFi.mode(WIFI_AP); //Access point mode: stations can connect to the ESP
  WiFi.mode(WIFI_STA); //Station mode: the ESP connects to an access point

  ConnectToWiFi();

  //To avoid the need of using the IP address to access the website,
  // declare a domain name. https://techtutorialsx.com/2020/04/17/esp32-mdns-address-resolution/
  if(!MDNS.begin("cubesat")) {  //argument of MDNS.begin holds website name (".local" has to be added)
     Serial.println("Error starting mDNS");
     return;
  }
  
  server.on("/", handleRoot); //This is display page
  server.on("/readADC", handleADC); //To get update of ADC Value only
  
  server.begin(); //Start server
  Serial.println("HTTP server started.");
}



//===============================================================
// Loop
//===============================================================

void loop(void){
  server.handleClient();
  
  //Check if ESP is still connected to WiFi and reconnect if connection was lost
  if(counter>100) { //Dont check connection status in every loop (for better runtime)
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi not connected. Try to reconnect...");
      ConnectToWiFi();
    }
    counter=0;  //If connection has just been checked, set counter back to 0...
  } else {
    counter++;  //...else, increase counter
  }
  
  delay(100); //slow down the loop, to save energy
}
