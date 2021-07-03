const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html charset="UTF-8">
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style> html {display: inline-block;margin: 0px auto;text-align: center;}
    input {
      text_align: center;
    }
    input[type=text]{ 
      text-align: center; 
      width: 60%;
    }
    
  </style>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
    <link rel="stylesheet" href="http://cdnjs.cloudflare.com/ajax/libs/bootstrap-table/1.11.0/bootstrap-table.min.css">
    <script src="http://cdnjs.cloudflare.com/ajax/libs/bootstrap-table/1.11.0/bootstrap-table.min.js"></script>
    <link href="https://maxcdn.bootstrapcdn.com/bootswatch/3.3.7/superhero/bootstrap.min.css" rel="stylesheet" title="main">
      
  </head>
  <body>
    <div class="container-fluid">
      <h1>Satellite Ground Control</h1>
      <ul class="nav nav-tabs" id="tab">
        <li class="active"><a href="#tab_measures" data-toggle="tab">Measures</a></li>
        <li><a href="#tab_commands" data-toggle="tab">Commands</a></li>
        <li><a href="#tab_graphs" data-toggle="tab">Graphics</a></li>
        <li><a href="#tab_gpio" data-toggle="tab">GPIO  </a></li>
        <li><a href="#tab_initialization" data-toggle="tab">Initialization</a></li>
        <li><a href="#tab_configuration" data-toggle="tab">Configuration</a></li>
      </ul>
      <div class="tab-content">
        <div class="tab-pane fade in active" id="tab_measures">         
          <h2>Sensordata</h2>
          <br>
          <p>Sensordaten vom Thermistor (Test): <span id="ADCValue">0</span></p></font>
          <br>
          <div class="tables">
            <table id="tab_measures" data-toggle="table" data-show-colunns="true">
              <thead>
                <tr>
                  <th class="text-center">ODC</th>
                  <th class="text-center">Value</th>
                  <th class="text-center">Unit</th>
                  <th class="text-center">Timestamp</th>
                </tr>
              </thead>
              <tbody>
                <tr>
                  <td>Modul1</td>
                  <td></td>
                  <td></td>
                  <td>00:00</td>
                  <tr>
                  <td>Modul2</td>
                  <td></td>
                  <td></td>
                  <td>00:00</td>
                </tr>
                </tr>
              </tbody>
              </table>
            <br>
              <table id="tab_measures" data-toggle="table" data-show-colunns="true">
              <thead>
                <tr>
                  <th class="text-center">EPM</th>
                  <th class="text-center">Value</th>
                  <th class="text-center">Unit</th>
                  <th class="text-center">Timestamp</th>
                </tr>
              </thead>
              <tbody >
                <tr>
                  <td>Modul1</td>
                  <td></td>
                  <td></td>
                  <td>00:00</td>
                  <tr>
                  <td>Modul2</td>
                  <td></td>
                  <td></td>
                  <td>00:00</td>
                </tr>
                </tr>
              </tbody>
              </table>
            </div>
              <br>
              <div class="tables">
              <table id="tab_measures" data-toggle="table" data-show-colunns="true">
              <thead>
                <tr>
                  <th class="text-center">PAY</th>
                  <th class="text-center">Value</th>
                  <th class="text-center">Unit</th>
                  <th class="text-center">Timestamp</th>
                </tr>
              </thead>
              <tbody>
                <tr>
                  <td>Modul1 </td>
                  <td></td>
                  <td></td>
                  <td>00:00</td>
                  <tr>
                  <td>Modul2</td>
                  <td></td>
                  <td></td>
                  <td>00:00</td>
                </tr>
                </tr>
              </tbody>
              </table>
            <br>
              <table id="tab_measures" data-toggle="table" data-show-colunns="true">
              <thead>
                <tr>
                  <th class="text-center">TMS</th>
                  <th class="text-center">Value</th>
                  <th class="text-center">Unit</th>
                  <th class="text-center">Timestamp</th>
                </tr>
              </thead>
              <tbody>
                <tr>
                  <td>Modul1</td>
                  <td></td>
                  <td></td>
                  <td>00:00</td>
                </tr>
                <tr>
                  <td>Modul2</td>
                  <td></td>
                  <td></td>
                  <td>00:00</td>
                </tr>
              </tbody>
              </table>
            </div>
        </div>
        <div class="tab-pane fade" id="tab_commands">
          <h2>Command Interface</h2>
          <br>
          <form action="/get" target="hidden-form">
            <p>Command line : </p> <input type="text" name="inCommand">
            <input type="submit" value="Submit" onclick="submitMessage()">
            <br>
            <br>(last send  command: %inCommand%)
          </form><br>
        </div>  
        <div class="tab-pane fade" id="tab_graphs">
          <h2>Graphs</h2>
          <br>
        </div>
        <div class="tab-pane fade" id="tab_gpio">
          <h2>GPIO</h2>
          <br>
          <div class="row">
            <div class="col-xs-6 col-md-4">
              <h4 class="text-left">D5
                <div class="span badge" id="D5_etat">OFF</div>
              </h4>
            </div>
            <div class="col-xs-6 col-md-4">
              <div class="button btn btn-success btn-lg" id="D5_On" type="button">ON</div>
            </div>
            <div class="col-xs-6 col-md-4">
              <div class="button btn btn-danger btn-lg" id="D5_Off" type="button">OFF</div>
            </div>
            <div class="col-xs-6 col-md-4">
              <h4 class="text-left">D6
                <div class="span badge" id="D6_etat">OFF</div>
              </h4>
            </div>
            <div class="col-xs-6 col-md-4">
              <div class="button btn btn-success btn-lg" id="D6_On" type="button">ON</div>
            </div>
            <div class="col-xs-6 col-md-4">
              <div class="button btn btn-danger btn-lg" id="D6_Off" type="button">OFF</div>
            </div>
            <div class="col-xs-6 col-md-4">
              <h4 class="text-left">D7
                <div class="span badge" id="D7_etat">OFF</div>
              </h4>
            </div>
            <div class="col-xs-6 col-md-4">
              <div class="button btn btn-success btn-lg" id="D7_On" type="button">ON</div>
            </div>
            <div class="col-xs-6 col-md-4">
              <div class="button btn btn-danger btn-lg" id="D7_Off" type="button">OFF</div>
            </div>
            <div class="col-xs-6 col-md-4">
              <h4 class="text-left">D8
                <div class="span badge" id="D8_etat">OFF</div>
              </h4>
            </div>
            <div class="col-xs-6 col-md-4">
              <div class="button btn btn-success btn-lg" id="D8_On" type="button">ON</div>
            </div>
            <div class="col-xs-6 col-md-4">
              <div class="button btn btn-danger btn-lg" id="D8_Off" type="button">OFF</div>
            </div>
          </div>
        </div>
        <div class="tab-pane fade" id="tab_initialization">
          <h2>Initialization</h2>
          <br>
            <p>Use the initilization table to send the present hardware configuration so that the satellite will work properly.</p>
          <table id="tab_initialization" data-toggle="table" data-show-colunns="true" style="text-align: center>
          <form id="initilization" action="/get" target="hidden-form">
            <colgroup>
                 <col span="1" >
                 <col span="1" >
                 <col span="1" >
                 <col span="1" >
                 <col span="1" >
                 <col span="1" >
                 <col span="1" >
            </colgroup>
            <tr>
              <th></th>
              <th class="text-center">ComEn line</th> 
              <th class="text-center">PS line</th>
              <th class="text-center">SR</th>
              <th class="text-center">AI</th>
              <th class="text-center">SPI</th>
              <th class="text-center">I2C</th>
            </tr>
            <tr>
              <td>EPM</td>
              <td><input type="number" id="epm" min="1" max="9" name="epm"></td>
              <td><input type="number" id="epm" min="1" max="9" name="epm"></td>
              <td><input type="radio" id="epm" name="epm" value="0"></td>
              <td><input type="radio" id="epm" name="epm" value="0"></td>
              <td><input type="radio" id="epm" name="epm" value="0"></td>
              <td><input type="radio" id="epm" name="epm" value="0"></td>
            </tr>
            <tr>
              <td>ODC</td>
              <td><input type="number" maxlength="2" id="odc" min="1" max="9" name="odc"></td>
              <td><input type="number" id="odc" min="1" max="9" name="odc"></td>
              <td><input type="radio" id="odc" name="odc" value="0"></td>
              <td><input type="radio" id="odc" name="odc" value="0"></td>
              <td><input type="radio" id="odc" name="odc" value="0"></td>
              <td><input type="radio" id="odc" name="odc" value="0"></td>
            </tr>
            <tr>
              <td>TMS1</td>
              <td><input type="number" id="tms1" min="1" max="9" name="tms1"></td>
              <td><input type="number" id="tms1" min="1" max="9" name="tms1"></td>
              <td><input type="radio" id="tms1" name="tms1" value="0"></td>
              <td><input type="radio" id="tms1" name="tms1" value="0"></td>
              <td><input type="radio" id="tms1" name="tms1" value="0"></td>
              <td><input type="radio" id="tms1" name="tms1" value="0"></td>
            </tr>
            <tr> 
              <td>TMS2</td>
              <td><input type="number" id="tms2" min="1" max="9" name="tms2"></td>
              <td><input type="number" id="tms2" min="1" max="9" name="tms2"></td>
              <td><input type="radio" id="tms2" name="tms2" value="0"></td>
              <td><input type="radio" id="tms2" name="tms2" value="0"></td>
              <td><input type="radio" id="tms2" name="tms2" value="0"></td>
              <td><input type="radio" id="tms2" name="tms2" value="0"></td>
            </tr>
            <tr>
              <td>Payload</td>
              <td><input type="number" id="pay" min="1" max="9" name="payload" ></td>
              <td><input type="number" id="pay" min="1" max="9" name="payload" ></td>
              <td><input type="radio" id="pay" name="payload" value="0"></td>
              <td><input type="radio" id="pay" name="payload" value="0"></td>
              <td><input type="radio" id="pay" name="payload" value="0"></td>
              <td><input type="radio" id="pay" name="payload" value="0"></td>
            </tr>
            <tr>
              <td colspan="6"></td>
              <td ><input type="submit" value="Send" onclick="submitMessage()"></td>
            </tr><br>
            </form>
          </table>
        </div>
        <div class="tab-pane fade" id="tab_configuration">
          <h2>Settings</h2>
          <div class="btn-group">
            <button class="btn btn-default" id="labelTheme">Design</button>
            <button class="btn btn-default dropdown-toggle" data-toggle="dropdown"><span class="caret"></span></button>
            <ul class="dropdown-menu">
              <li><a class="change-style-menu-item" href="#" rel="cerulean">Cerulean</a></li>
              <li><a class="change-style-menu-item" href="#" rel="darkly">Darkly</a></li>
              <li><a class="change-style-menu-item" href="#" rel="flatly">Flatly</a></li>
              <li><a class="change-style-menu-item" href="#" rel="lumen">Lumen</a></li>
              <li><a class="change-style-menu-item" href="#" rel="readable">Readable</a></li>
              <li><a class="change-style-menu-item" href="#" rel="sandstone">Sandstone</a></li>
              <li><a class="change-style-menu-item" href="#" rel="slate">Slate</a></li>
              <li><a class="change-style-menu-item" href="#" rel="spacelab">Spacelab</a></li>
            </ul>
          </div>
        </div>
      </div>
    </div>

    <div class="row" style="position:absolute; bottom:0; width:100%">
        <div class="col-xs-2 col-md-1"><img src="https://wiwi.uni-giessen.de/ep_file/fb02/show/2642/411/JLU-Logo-Symbol-gro_.png" width="30" height="30">
        </div>
        <div class="col-xs-2 col-md-1">
          <p>CubeSat Project</p>
        </div>
        <div class="text-right">
          <p><a href="https://www.uni-giessen.de/studium/studienangebot/master/ptra">JLU Giessen PTRA</a></p>
        </div>
      </div>
    </div>
    
    <script>
     
      //XML send function
      setInterval(function() {
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
      
      //SPIFFS save function
      function submitMessage() {
        alert("Saved value to ESP SPIFFS");
        setTimeout(function(){ document.location.reload(false); }, 500);   
      }
      
      // Change current theme
      // Adapted from : https://wdtz.org/bootswatch-theme-selector.html
      var supports_storage = supports_html5_storage();
      if (supports_storage) {
        var theme = localStorage.theme;
        if ( typeof theme != 'undefined' ) {
          console.log("Change the theme " + theme);
          set_theme(get_themeUrl(theme));
        }
      }
      
      // New theme selected
      jQuery(function($){
        $('body').on('click', '.change-style-menu-item', function() {
          var theme_name = $(this).attr('rel');
          console.log("To theme" + theme_name);
          var theme_url = get_themeUrl(theme_name);
          console.log("URL theme : " + theme_url);
          set_theme(theme_url);
        });
      });
      // Get theme URL
      function get_themeUrl(theme_name){
        $('#labelTheme').html("Design : " + theme_name);
        var url_theme = "";
        if ( theme_name === "bootstrap" ) {
          url_theme = "https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css";
        } else {
          url_theme = "https://maxcdn.bootstrapcdn.com/bootswatch/3.3.7/" + theme_name + "/bootstrap.min.css";
        }
        if (supports_storage) {
          // save into the local database the selected theme
          localStorage.theme = theme_name;
        }
        return url_theme;
      }
      // Apply theme
      function set_theme(theme_url) {
        $('link[title="main"]').attr('href', theme_url);
      }
      // local storage available ?
      function supports_html5_storage(){
        try {
          return 'localStorage' in window && window['localStorage'] !== null;
        } catch (e) {
          return false;
        }
      }
    </script>
  </body>
</html>
)rawliteral";
