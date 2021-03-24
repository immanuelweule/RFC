#include <WiFi.h>
#include <SPI.h>

// +++++++++++++++++++ Start of Webserver Library +++++++++++++++++++

WiFiClient myclient;
WiFiServer server(80);


// SSID and Password of your Wifi network
const char* txtSSID = "Kewwin_02";
const char* txtPassword = "2214934027604276";

IPAddress local_IP (192, 168, 1, 100); // Set your Static IP address
IPAddress gateway (192, 168, 1, 9); // Set your Gateway IP address
IPAddress dns (8, 8, 8, 8);
IPAddress subnet (255, 255, 255, 0);
int status = WL_IDLE_STATUS;



void Webserver_Start() {
  server.begin();     // Start TCP/IP-Server on ESP32
}



//  Call this function regularly to look for client requests
//  template see https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/examples/SimpleWiFiServer/SimpleWiFiServer.ino
//  returns empty string if no request from any client
//  returns GET Parameter: everything after the "/?" if ADDRESS/?xxxx was entered by the user in the webbrowser
//  returns "-" if ADDRESS but no GET Parameter was entered by the user in the webbrowser
//  remark: client connection stays open after return

String Webserver_GetRequestGETParameter() {
  String GETParameter = "";
  
  myclient = server.available();   // listen for incoming clients

  //Serial.print(".");
  if (myclient) {                            // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                 // make a String to hold incoming data from the client

    while (myclient.connected()) {           // loop while the client's connected

      if (myclient.available()) {            // if there's bytes to read from the client,
        char c = myclient.read();            // read a byte, then
        Serial.write(c);                     // print it out the serial monitor

        if (c == '\n') {                     // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request
          if (currentLine.length() == 0) {
            if (GETParameter == "") {
              GETParameter = "-";
              Serial.print("GET PARAMETER WIRD - GESETZT");
              };    // if no "GET /?" was found so far in the request bytes, return "-"
            
            // break out of the while loop:
            break;
        
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
          
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
          //Serial.println(currentLine);
        }

        if (c=='\r' && currentLine.startsWith("GET /?")) {
        // we see a "GET /?" in the HTTP data of the client request
        // user entered ADDRESS/?xxxx in webbrowser, xxxx = GET Parameter
          GETParameter = currentLine.substring(currentLine.indexOf('?') + 1, currentLine.indexOf(' ', 6));    // extract everything behind the ? and before a space
          Serial.println("GET PARAMETER WIRD GEBAUT");
          Serial.println(GETParameter);
        }
      }
    }    
  }
  return GETParameter;
}



// Send HTML page to client, as HTTP response
// client connection must be open (call Webserver_GetRequestGETParameter() first)

void Webserver_SendHTMLPage(String HTMLPage) {
   String httpResponse = "";

   // begin with HTTP response header
   httpResponse += "HTTP/1.1 200 OK\r\n";
   httpResponse += "Content-type:text/html\r\n\r\n";

   // then the HTML page
   httpResponse += HTMLPage;

   // The HTTP response ends with a blank line:
   httpResponse += "\r\n";
    
   // send it out to TCP/IP client = webbrowser 
   myclient.println(httpResponse);

   // close the connection
   myclient.stop();
    
   Serial.println("Client Disconnected.");
};



// +++++++++++++++++++ End of Webserver library +++++++++++++++++++++



// this section handles configuration values which can be configured via webpage form in a webbrowser

// 8 configuration values max
String ConfigName[8];     // name of the configuration value
String ConfigValue[8];    // the value itself (String)
int    ConfigStatus[8];   // status of the value    0 = not set    1 = valid   -1 = not valid



// Initalize the values 

void InitializeConfigValues() {
  for (int count = 0; count < 8; count++)
  {
    ConfigName[count] = "";
    ConfigValue[count] = "";
    ConfigStatus[count] = 0;
  }
}



// Build a HTML page with a form which shows textboxes to enter the values
// returns the HTML code of the page

String EncodeFormHTMLFromConfigValues(String TitleOfForm, int CountOfConfigValues) {
   // Head of the HTML page
   String HTMLPage = "<!DOCTYPE html><html><body><h2>" + TitleOfForm + "</h2><form><table>";

   // for each configuration value
   for (int c = 0; c < CountOfConfigValues; c++) {
    // set background color by the status of the configuration value
    String StyleHTML = "";
    if (ConfigStatus[c] == 0) { StyleHTML = " Style =\"background-color: #FFE4B5;\" " ;};   // yellow
    if (ConfigStatus[c] == 1) { StyleHTML = " Style =\"background-color: #98FB98;\" " ;};   // green
    if (ConfigStatus[c] == -1) { StyleHTML = " Style =\"background-color: #FA8072;\" " ;};  // red

    // build the HTML code for a table row with configuration value name and the value itself inside a textbox   
    String TableRowHTML = "<tr><th>" + ConfigName[c] + "</th><th><input name=\"" + ConfigName[c] + "\" value=\"" + ConfigValue[c] + "\" " + StyleHTML + " /></th></tr>";

    // add the table row HTML code to the page
    HTMLPage += TableRowHTML;
   }

   // add the submit button
   HTMLPage += "</table><br/><input type=\"submit\" value=\"Submit\" />";

   // footer of the webpage
   HTMLPage += "</form></body></html>";
   
   return HTMLPage;
}



// Decodes a GET parameter (expression after ? in URI (URI = expression entered in address field of webbrowser)), like "Country=Germany&City=Aachen"
// and set the ConfigValues

int DecodeGETParameterAndSetConfigValues(String GETParameter) {
   
   int posFirstCharToSearch = 1;
   int count = 0;
   
   // while a "&" is in the expression, after a start position to search
   while (GETParameter.indexOf('&', posFirstCharToSearch) > -1) {
     int posOfSeparatorChar = GETParameter.indexOf('&', posFirstCharToSearch);  // position of & after start position
     int posOfValueChar = GETParameter.indexOf('=', posFirstCharToSearch);      // position of = after start position
  
     ConfigValue[count] = GETParameter.substring(posOfValueChar + 1, posOfSeparatorChar);  // extract everything between = and & and enter it in the ConfigValue
      
     posFirstCharToSearch = posOfSeparatorChar + 1;  // shift the start position to search after the &-char 
     count++;
   }

   // no more & chars found
   
   int posOfValueChar = GETParameter.indexOf('=', posFirstCharToSearch);       // search for =
   
   ConfigValue[count] = GETParameter.substring(posOfValueChar + 1, GETParameter.length());  // extract everything between = and end of string
   count++;

   return count;  // number of values found in GET parameter
}





void ConnectToWiFi() {
  boolean success = true;
  int counter = 0;
  
  Serial.print("Attempting to connect to Wifi: ");
  Serial.print(txtSSID);
  WiFi.disconnect();
  WiFi.begin(txtSSID, txtPassword);
  WiFi.config(local_IP, dns, gateway); //(doesnt work, probably ip out of range of router)

  
  // we wait until connection is established or 10 seconds are gone
  while (WiFi.status() != WL_CONNECTED && counter < 10) {
    delay(1000);
    Serial.print(".");
    counter++;
  }
  Serial.println(".");
  // not connected
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connection failed");
    success = false;
  } else {
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Connection in ");
    Serial.print(counter);
    Serial.println(" sec.");
  }
  return;
}





void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.println("ESP32 awake"); 
  
  // connect to WiFi network
  ConnectToWiFi();
  
  // initialize config values and set first 3 names of values to LED1...LED3
  InitializeConfigValues();
  ConfigName[0] = "LED1";
  ConfigName[1] = "LED2";
  ConfigName[2] = "LED3";

  // start the webserver to listen for request of clients in WLAN
  Webserver_Start();
}

// check the ConfigValues and set ConfigStatus
// process the ConfigValues to switch something
void ProcessAndValidateConfigValues(int countValues) {
  if (countValues > 8) {countValues = 8;};

  // for each ConfigValue
  for (int cn = 0; cn < countValues; cn++) {
    // in our application the values must be "00" or "FF" (as text string)
    if ((ConfigValue[cn].equals("00")) || (ConfigValue[cn].equals("FF"))) {
      ConfigStatus[cn] = 1;    // Value is valid
    }
    else {
      ConfigStatus[cn] = -1;   // Value is not valid
    }
  }
}

int timer = 0;



void loop() {

  String GETParameter = Webserver_GetRequestGETParameter();   // look for client request
  int countValues = 0;
  
  if (GETParameter.length() > 0) {     // we got a request, client connection stays open
  
    if (GETParameter.length() > 1) {    // request contains some GET parameter
      int countValues = DecodeGETParameterAndSetConfigValues(GETParameter);     // decode the GET parameter and set ConfigValues
      ProcessAndValidateConfigValues(countValues);                              // check and process ConfigValues
    } else {
      int countValues = 1;
    }

    String HTMLPageWithConfigForm = EncodeFormHTMLFromConfigValues("ESP32 Webserver Demo", countValues);   // build a new webpage with form and new ConfigValues entered in textboxes
   
    Webserver_SendHTMLPage(HTMLPageWithConfigForm);    // send out the webpage to client = webbrowser and close client connection
  }

  if (timer>50) {
  timer = 0;
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi not connected. Try to reconnect");
      ConnectToWiFi();
    }
  } else {
    timer++;
  }
  Serial.println("Hier sollte ConfigValue stehen");
  Serial.println(ConfigValue[0]);
  Serial.println(GETParameter);
  
  delay(2000);
}