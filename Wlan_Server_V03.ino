//===============================================================
// @file:     GroundControl_V0.1
// @brief:    Communication CubeSat - Ground Control
//
// @authors:  Adrian Setka, Immanuel Weule
//
// @hardware: ESP32-DevKitC V4 (ESP32-WROOM-32U)
// @comments: Can only connect to 2,4 GHz, not to 5 GHz
//
// @date:     2021-07-12
//
// @links:    https://randomnerdtutorials.com/esp32-esp8266-plot-chart-web-server/
//            https://randomnerdtutorials.com/esp32-mpu-6050-web-server/
//            https://randomnerdtutorials.com/esp32-async-web-server-espasyncwebserver-library/
//            https://randomnerdtutorials.com/esp32-esp8266-input-data-html-form/
//===============================================================



//===============================================================
// Header files, variable declarations and WiFi setup
//===============================================================

#include <Arduino.h>

#include <WiFi.h>
#include <AsyncTCP.h>
#include <SPIFFS.h> //File system

#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>  //For URL/name instead of IP address
#include <analogWrite.h>

//Set WiFi SSID and password
const char* ssid = "Kewwin_02"; //WiFi SSID
const char* password = "2214934027604276"; //WiFi password
//const char* ssid = "Apartment 322"; //WiFi SSID
//const char* password = "06456469822825645048"; //WiFi password

const char* http_username = "admin";  // username for login
const char* http_password = "admin";  // password for login

const char* PARAM_COMMAND = "inCommand"; //Variable for commandline
const char* PARAM_INIT = "inInit"; //Variable for initilization

int counter=0;  //Counter for checking connection status in loop

AsyncWebServer server(80);  //Setup a HTTP server



//Just for test purposes of sensormonitoring
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp; //I2C sensor connection of BMP280 modul



//===============================================================
// Function declarations
//===============================================================

void ConnectToWiFi() {
  Serial.println("Connecting to ");
  Serial.print(ssid);
  
  WiFi.disconnect();
  WiFi.begin(ssid, password); //For ESP as a station; for ESP as AP use "WiFi.softAP(ssid, password)"

  //Wait for WiFi to connect
  while(WiFi.waitForConnectResult() != WL_CONNECTED){      
      Serial.print(".");
      delay(100);
  }
    
  //If connection is successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); //IP address assigned to your ESP

  return;
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if(!file || file.isDirectory()){
    Serial.println("- empty file or failed to open file");
    return String();
  }
  Serial.println("- read from file:");
  String fileContent;
  while(file.available()){
    fileContent+=String((char)file.read());
  }
  file.close();
  Serial.println(fileContent);
  return fileContent;
}

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, "w");
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
  file.close();
}

//Replaces placeholder with stored values
String processor(const String& var){
  //Serial.println(var);
  if(var == "inCommand"){
    return readFile(SPIFFS, "/inCommand.txt");
  }
  else if(var == "inInit"){
    return readFile(SPIFFS, "/inInit.txt");
  }
  return String();
}



//===============================================================
// Test Functions
//===============================================================


String readBMP280Temperature() {
  // Read temperature as Celsius (the default)
  float t = bmp.readTemperature();
  // Convert temperature to Fahrenheit
  //t = 1.8 * t + 32;
  if (isnan(t)) {    
    Serial.println("Failed to read from BMP280 sensor!");
    return "";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

String readBMP280Altitude() {
  float h = bmp.readAltitude(1013.25);
  if (isnan(h)) {
    Serial.println("Failed to read from BMP280 sensor!");
    return "";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}

String readBMP280Pressure() {
  float p = bmp.readPressure() / 100.0F;
  if (isnan(p)) {
    Serial.println("Failed to read from BMP280 sensor!");
    return "";
  }
  else {
    Serial.println(p);
    return String(p);
  }
}

/* String readPhoto() {
  float ph = analogRead(Analog_Pin);
  if (isnan(ph)) {
    Serial.println("Failed to read from analog sensor!");
    return "";
  }
  else {
    Serial.println(ph);
    return String(ph);
  }
} */



//===============================================================
// Setup
//===============================================================

void setup(void){
  
  Serial.begin(115200); //Open a serial connection
  Serial.println("Booting...");

  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    //while (1) delay(10);
  }
  
  //Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  //Initialize how ESP should act - AP or STA (comment out one initialization)
  //WiFi.mode(WIFI_AP); //Access point mode: stations can connect to the ESP
  WiFi.mode(WIFI_STA); //Station mode: the ESP connects to an access point

  ConnectToWiFi();

  if(!MDNS.begin("cubesat")) {  //Argument of MDNS.begin holds website name (".local" has to be added)
     Serial.println("Error starting mDNS");
     return;
  }
  
  //Handle Web Server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    request->send_P(200, "text/plain", readBMP280Temperature().c_str());
  });
  server.on("/altitude", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    request->send_P(200, "text/plain", readBMP280Altitude().c_str());
  });
  server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    request->send_P(200, "text/plain", readBMP280Pressure().c_str());
  });
  server.on("/command", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    request->send(SPIFFS, "/inCommand.txt", "text/plain");
  });
  /* server.on("/photo", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readPhoto().c_str());
  }); */
  
  //Send a GET request to <ESP_IP>/get?inputString=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    String inputMessage;
    // GET inCommand value on <ESP_IP>/get?inCommand=<inputMessage>
    if (request->hasParam(PARAM_COMMAND)) {
      inputMessage = request->getParam(PARAM_COMMAND)->value();
      writeFile(SPIFFS, "/inCommand.txt", inputMessage.c_str());
    }
    //GET inInt value on <ESP_IP>/get?inpInt=<inputMessage>
    else if (request->hasParam(PARAM_INIT)) {
      inputMessage = request->getParam(PARAM_INIT)->value();
      writeFile(SPIFFS, "/inInit.txt", inputMessage.c_str());
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/text", inputMessage);
  });

  /*To get update of ADC Value only
  server.on("/readADC", [] (AsyncWebServerRequest *request) {
    if(!request->authenticate(http_username, http_password))
      return request->requestAuthentication();
    int a = analogRead(Analog_Pin);
    String adcValue = String(a);
    request->send(200, "text/plane", adcValue);
  }); */
  
  
  server.onNotFound(notFound);
  server.begin();
}



//===============================================================
// Loop
//===============================================================

void loop(void){

  //Check if ESP is still connected to WiFi and reconnect if connection was lost
  if(counter>6) { //Dont check connection status in every loop (for better runtime)
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi not connected. Try to reconnect...");
      ConnectToWiFi();
    }
    counter=0;
  } else {
    counter++;
  }
  
  //To access your stored values on inCommand, inInit
  readFile(SPIFFS, "/inCommand.txt");
  readFile(SPIFFS, "/inInit.txt");

/*
  // to access your stored values on inCommand, inInit
  String yourInputCommand = readFile(SPIFFS, "/inCommand.txt");
  Serial.print("*** Your inputCommand: ");
  Serial.println(yourInputCommand);
  
  String yourInputInit = readFile(SPIFFS, "/inInit.txt");
  Serial.print("*** Your inputInit: ");
  Serial.println(yourInputInit);
*/

  delay(10000);
}
