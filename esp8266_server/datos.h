const char* ssid_1     = "ARRIS-3535";
const char* password_1 = "50A5DC443535";

String Pagina =  R"====(<!DOCTYPE html>
<html>
  <head>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
    <title>Servidor </title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <style>
      body {
        background-color: #424242;
      }
      h1{
        color: #A52A2A;
        text-shadow: 3px 3px 4px #000000;
        padding: 3px;
      }
      h2{
        background-color: rgb(47, 47, 47);
        color: white;
        padding:2px;
        margin: 0;
      }
      h4{
        color: white;
      }
      p{
        color: white;
        font-size: 1.7rem;
      }
    .container {
        max-width: 1000px;
        width: 100%;
        display: flex;
        flex-wrap: wrap;
        justify-content: center;
        gap: 2rem;
      }
      .container0{
        display: flex;
        flex-direction: row;
        justify-content: center;
        align-content: center;
        flex-wrap: wrap;
        padding-top: 20px;
        gap: 2rem;  
      }
      .cajaAlarmas{  
        display: flex;
        justify-content:center;
        flex-wrap: wrap;
        gap: 20px;
      }
      .cajaPpal{
        display: flex;
        flex-direction: column;
        gap: 18px;
     }
     .cajasSecundarias{
        border: 5px solid #424242; 
        background-color: #43614a; 
        width:150px;
        height: 45px;
        border-radius: 20px;
     }
     button {
        width: 150px;
        height: 50px;
        background: #424242;
        border: none;
        border-radius: 10px;
        box-shadow: -3px -3px 5px rgba(158, 197, 233, 0.5),
                      3px 3px 5px rgba(0,0,0, .25);
        color: white;
        font-size: 1.7rem;
      }
    .switch-holder {
      display: flex;
      width: 220px;
      padding: 10px 20px;
      border-radius: 10px;
      margin-bottom: 30px;
      box-shadow:-3px -3px 5px rgba(213, 215, 216, 0.5),
                  3px 3px 5px rgba(0,0,0, .25);
                  inset: 8px 8px 15px rgba(122, 120, 120, 0.7),
                  inset 10px 10px 10px rgba(0,0,0, .3);
      justify-content: space-between;
      align-items: center;
    }
    .switch-toggle {
      height: 40px;
    }
    .switch-toggle input[type="checkbox"] {
      position: absolute;
      opacity: 0;
      z-index: -2;
    }
    .switch-toggle input[type="checkbox"] + label {
      position: relative;
      display: inline-block;
      width: 100px;
      height: 40px;
      border-radius: 20px;
      margin: 0;
      cursor: pointer;
      box-shadow: inset -8px -8px 15px rgba(163, 154, 154, 0.6),
                inset 10px 10px 10px rgba(0,0,0, .25);
    }
    .switch-toggle input[type="checkbox"] + label::before {
      position: absolute;
      content: 'OFF';
      font-size: 13px;
      text-align: center;
      line-height: 25px;
      top: 8px;
      left: 8px;
      width: 45px;
      height: 25px;
      border-radius: 20px;
      background-color: #d1dad3;
      box-shadow: -3px -3px 5px rgba(255,255,255,.5),
                  3px 3px 5px rgba(0,0,0, .25);
      transition: .3s ease-in-out;
    }
    .switch-toggle input[type="checkbox"]:checked + label::before {
      left: 50%;
      content: 'ON';
      color: #fff;
      background-color: #00b33c;
      box-shadow: -3px -3px 5px rgba(255,255,255,.5),
                  3px 3px 5px #00b33c;
    }
  </style>
  </head>
  <body>
    <center>
      <h1>FORT Security</h1> 
      <hr style="height: 2px;width: 30%;background-color: rgb(58, 57, 57);">
      <div class="container0" >
        <div class="switch-holder">
            <div class="switch-label">
                <p>Sirena</p>
            </div>
            <div class="switch-toggle">
              <input type="checkbox" id="sirena2">
              <label for="sirena2"></label>
          </div>
        </div>
        <div class="switch-holder">
            <div class="switch-label">
                <p>Reflector</p>
            </div>
            <div class="switch-toggle">
                <input type="checkbox" id="reflector2">
                <label for="reflector2"></label>
            </div>
        </div>
      </div>
      <div class="cajaAlarmas" >
        <div class="cajaPpal">
          <button id="11">Zona 1</button>  
          <button id="12">Zona 2</button>
          <button id="13">Zona 3</button>
          <button id="14">Zona 4</button>
        </div>
        <br>
        <div class="cajaPpal">
            <button id="15">Zona 5</button>  
            <button id="16">Zona 6</button>
            <button id="17">Zona 7</button>
            <button id="18">Zona 8</button>
          </div>
      </div>
      <br>
      <hr style="height: 2px;width: 40%;background-color: rgb(58, 57, 57);">
      <div>
        <a href="https://invelectronica.com/seguridad-perimetral/" target="_blank" rel="noreferrer noopener" style="font-size: 25px;color: rgb(64, 131, 233);text-shadow: 3px 3px 4px #000000;">www.invelectronica.com</a>
      </div>
      <p>Modelo Q-CH0-2 / 2023 </p>
      <p id=msg >{variable}</p>
  </div>
  </center>
  
  <script>
  let delServer;
  let varButton;
  
  const Sirena = document.querySelector("#sirena2");
  const Reflector = document.querySelector("#reflector2");

  Sirena.addEventListener("click",()=>{
  var vlrSirena=Sirena.checked;    
    if(vlrSirena){
      vlrSirena="lon";
    }else{
      vlrSirena="lof";
    }
    consultaGET(vlrSirena);
  });
  
  Reflector.addEventListener("click",()=>{
  var vlrReflector=Reflector.checked;  
    if(vlrReflector){
      vlrReflector="ron"
    }else{
      vlrReflector="rof"  
    }
    consultaGET(vlrReflector);
  });
  
  function ejecutarAjax(url, callback) {
  //creamos elemento XMLHttpRequest 
  var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        callback(this.responseText);
      }
    };
    xhttp.open("GET", url, true);
    xhttp.send();
  }
  
  function consultaGET(consulta) {
    ejecutarAjax(consulta, function(responseText) {
      console.log(Http.responseText);
    });
  }

  function actualizarVariable() {
  var elementos = document.querySelectorAll('button');
    ejecutarAjax("/alarma", function(responseText) {
    //obtenemos variable del server
    document.getElementById("msg").innerHTML = responseText;
    varButton=responseText;
    if (varButton>=11 && varButton<=18){
      elementos.forEach(function(elemento) {  
        //console.log("elemento.id: ",elemento.id, "variable: ",varButton);
        if(varButton==elemento.id){
          //console.log("Ya entre..");
          document.getElementById(elemento.id).style.backgroundColor="#d1dad3";
        }
      });
    }else if(varButton>=1 && varButton<=8){  
      console.log("entre 1 y 8");
      elementos.forEach(function(elemento) {  
        const boton = document.getElementById(elemento.id);    
        let textButton=boton.textContent || boton.innerText;
        console.log("texto en boton ",textButton);
        if(textButton.includes(varButton)){
          console.log("Reviso texto..");
          document.getElementById(elemento.id).style.backgroundColor="#424242";
        }
      });
    }
    }); 
  }

    
  // Actualizar la variable cada 5000 milisegundos (5 segundos)
  setInterval(actualizarVariable, 5000);    

  </script>
  </body>
</html>)====";