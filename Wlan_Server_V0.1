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

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "index.h"  //Web page header file

int counter=0;  //counter for checking connection status in loop

WebServer server(80);  //Setup a HTTP server

//Set WiFi SSID and password
const char* ssid = "Kewwin_02"; //WiFi SSID
const char* password = "2214934027604276"; //WiFi password

const int Analog_channel_pin = 34;  //Analog Channel Pin



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
  
  if(!MDNS.begin("cubesat")) {
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
    counter=0;
  } else {
    counter++;
  }
  
  delay(100);
}
