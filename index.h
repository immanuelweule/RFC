//===============================================================
// @file:      index.h
// @brief:     TBD
//
// @authors:   circuits4you.com
//             (https://circuits4you.com/2018/11/20/web-server-
//              on-esp32-how-to-update-and-display-sensor-values/)
// @coauthors: Adrian Setka, Immanuel Weule
//
// @hardware:  ESP32-DevKitC V4 (ESP32-WROOM-32U)
// @comments:  Can only connect to 2,4 GHz, not to 5 GHz
//
// @date:      2021-05-29
//===============================================================

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head><meta name="viewport" content="width=device-width, initial-scale=1">
<style> html {font-family: Arial;display: inline-block;margin: 0px auto;text-align: center;}h2 { font-size: 3.0rem; }
{ font-size: 3.0rem; }.units { font-size: 1.2rem; }.dht-labels{font-size: 1.5rem;vertical-align:middle;padding-bottom: 15px;}
table, th, td {
  border: 2px solid black;
  border-collapse: collapse;
  padding: 8px 0;
}
table {
  border-spacing: 50px;
  margin-left:auto;margin-right:auto;
}
input { 
    text-align: center; 
}
</style>
</head>

<body>
<h2>Satellite Ground Control</h2>
<form id="commandline">
<input type="submit" value="Send" style="float: right; width: 8%; margin-right: 26%" />
<div style="overflow: hidden; padding-right: .5em; margin-left: 13%">
   <input type="text" style=" float: right; width: 60%;" name='commands'/>
   <label for="commands" style=" float: right; margin-right: 1%">Commandline: </label>
</div>
</form>

<p>Sensordaten vom Thermistor (Test): <span id="ADCValue">0</span></p></font>
<h3><u>Sonsor data</u></h3>
<p align='center'>
<table style="width:30%">
<colgroup>
       <col span="1" style="width: 40%;">
       <col span="1" style="width: 20%;">
       <col span="1" style="width: 20%;">
       <col span="1" style="width: 20%;">
</colgroup>
  <tr style="background-color: #aaa">
    <th></th>
    <th>Value</th> 
    <th>Unit</th>
    <th>Timestamp</th>
  </tr>
  <tr>
    <td style="background-color: #aaa">EPM</td>
    <td><span id="ADCValue">0</span></td>
    <td></td>
    <td><span id="timeEPM">00:00</span></td>
  </tr>
  <tr>
    <td style="background-color: #aaa">ODC</td>
    <td><span id="ADCValue">0</span></td>
    <td></td>
    <td><span id="timeODC">00:00</span></td>
  </tr>
  <tr>
    <td style="background-color: #aaa">TMS1</td>
    <td><span id="ADCValue">0</span></td>
    <td></td>
    <td><span id="timeTMS1">00:00</span></td>
  </tr>
  <tr>
    <td style="background-color: #aaa">TMS2</td>
    <td><span id="ADCValue">0</span></td>
    <td></td>
    <td><span id="timeTMS2">00:00</span></td>
  </tr>
  <tr>
    <td style="background-color: #aaa">Payload</td>
    <td><span id="ADCValue">0</span></td>
    <td></td>
    <td><span id="timePAY">00:00</span></td>
  </tr>
</table>
</p>
<br>
<h3><u>Initilization</u></h3>
<p align='center'>
<table style="width:50%">
<form id="initilization">
<colgroup>
       <col span="1" style="width: 20%;">
       <col span="1" style="width: 15%;">
       <col span="1" style="width: 15%;">
       <col span="1" style="width: 10%;">
       <col span="1" style="width: 10%;">
       <col span="1" style="width: 10%;">
       <col span="1" style="width: 10%;">
</colgroup>
  <tr style="background-color: #aaa">
    <th></th>
    <th>ComEn line</th> 
    <th>PS line</th>
    <th>SR</th>
    <th>AI</th>
    <th>SPI</th>
    <th>I2C</th>
  </tr>
  <tr>
    <td style="background-color: #aaa">EPM</td>
    <td><input type="number" id="epm" min="1" max="9" name="epm" style="width:90%"></td>
    <td><input type="number" id="epm" min="1" max="9" name="epm" style="width:90%"></td>
    <td><input type="radio" id="epm" name="epm" value="0"></td>
    <td><input type="radio" id="epm" name="epm" value="0"></td>
    <td><input type="radio" id="epm" name="epm" value="0"></td>
    <td><input type="radio" id="epm" name="epm" value="0"></td>
  </tr>
  <tr>
    <td style="background-color: #aaa">ODC</td>
    <td><input type="number" maxlength="2" id="odc" min="1" max="9" name="odc" style="width:90%"></td>
    <td><input type="number" id="odc" min="1" max="9" name="odc" style="width:90%"></td>
    <td><input type="radio" id="odc" name="odc" value="0"></td>
    <td><input type="radio" id="odc" name="odc" value="0"></td>
    <td><input type="radio" id="odc" name="odc" value="0"></td>
    <td><input type="radio" id="odc" name="odc" value="0"></td>
  </tr>
  <tr>
    <td style="background-color: #aaa">TMS1</td>
    <td><input type="number" id="tms1" min="1" max="10" name="tms1" style="width:90%"></td>
    <td><input type="number" id="tms1" min="1" max="10" name="tms1" style="width:90%"></td>
    <td><input type="radio" id="tms1" name="tms1" value="0"></td>
    <td><input type="radio" id="tms1" name="tms1" value="0"></td>
    <td><input type="radio" id="tms1" name="tms1" value="0"></td>
    <td><input type="radio" id="tms1" name="tms1" value="0"></td>
  </tr>
  <tr>
    <td style="background-color: #aaa">TMS2</td>
    <td><input type="number" id="tms2" min="1" max="9" name="tms2" style="width:90%"></td>
    <td><input type="number" id="tms2" min="1" max="9" name="tms2" style="width:90%"></td>
    <td><input type="radio" id="tms2" name="tms2" value="0"></td>
    <td><input type="radio" id="tms2" name="tms2" value="0"></td>
    <td><input type="radio" id="tms2" name="tms2" value="0"></td>
    <td><input type="radio" id="tms2" name="tms2" value="0"></td>
  </tr>
  <tr>
    <td style="background-color: #aaa">Payload</td>
    <td><input type="number" id="pay" min="1" max="9" name="payload" style="width:90%"></td>
    <td><input type="number" id="pay" min="1" max="9" name="payload" style="width:90%"></td>
    <td><input type="radio" id="pay" name="payload" value="0"></td>
    <td><input type="radio" id="pay" name="payload" value="0"></td>
    <td><input type="radio" id="pay" name="payload" value="0"></td>
    <td><input type="radio" id="pay" name="payload" value="0"></td>
  </tr>
  <tr>
    <td colspan="6"></td>
    <td ><input type="submit" value="Send Config"></td>
  </tr>
</form>
</table>

<script>
setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
}, 2000); //2000 msec update rate

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readADC", true);
  xhttp.send();
}

window.addEventListener( "load", function () {
  function sendData() {
    const XHR = new XMLHttpRequest();

    // Bind the FormData object and the form element
    const FD = new FormData( form );

    // Define what happens on successful data submission
    XHR.addEventListener( "load", function(event) {
      alert( event.target.responseText );
    } );

    // Define what happens in case of error
    XHR.addEventListener( "error", function( event ) {
      alert( 'Oops! Something went wrong.' );
    } );

    // Set up our request
    XHR.open( "POST", "https://example.com/cors.php" );

    // The data sent is what the user provided in the form
    XHR.send( FD );
  }

  // Access the form element...
  const form = document.getElementById( "initilization" );

  // ...and take over its submit event.
  form.addEventListener( "submit", function ( event ) {
    event.preventDefault();

    sendData();
  } );
} );
window.addEventListener( "load", function () {
  function sendData() {
    const XHR = new XMLHttpRequest();

    // Bind the FormData object and the form element
    const FD = new FormData( form );

    // Define what happens on successful data submission
    XHR.addEventListener( "load", function(event) {
      alert( event.target.responseText );
    } );

    // Define what happens in case of error
    XHR.addEventListener( "error", function( event ) {
      alert( 'Oops! Something went wrong.' );
    } );

    // Set up our request
    XHR.open( "POST", "https://example.com/cors.php" );

    // The data sent is what the user provided in the form
    XHR.send( FD );
  }

  // Access the form element...
  const form = document.getElementById( "commandline" );

  // ...and take over its submit event.
  form.addEventListener( "submit", function ( event ) {
    event.preventDefault();

    sendData();
  } );
} );



</script>
</body>
</html>
)=====";
