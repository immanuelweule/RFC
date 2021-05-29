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
<style>
.card{
    max-width: 400px;
     min-height: 250px;
     background: #02b875;
     padding: 30px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}
</style>
<body>

<div class="card">
  <h4>The ESP32 Update web page without refresh</h4><br>
  <h1>Sensor Value:<span id="ADCValue">0</span></h1><br>
  <br><a href="https://circuits4you.com">Circuits4you.com</a>
</div>
<script>

setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
}, 2000); //2000mSeconds update rate

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
</script>
</body>
</html>
)=====";
