const char * MAIN_page= "<!DOCTYPE html>"
"<html lang='fr'>"
"<head>"
  "<meta charset='UTF-8'>"
  "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
"</head>"
"<body>"
"<style>"
"body{"
"margin: 0;"
"width: 100%;"
"height: 100vh;"
"font-family: 'Exo', sans-serif;"
"color: #fff;"
"background: linear-gradient(-45deg, #ee7752, #e73c7e, #23a6d5, #23d5ab);"
"background-size: 400% 400%;"
"animation: gradientBG 15s ease infinite;"
"}"
"@keyframes gradientBG {"
"	0% {background-position: 0% 50%;}50% {background-position: 100% 50%;}100% {background-position: 0% 50%;}}"
".center-fixed { position: fixed !important;}"
".center {"
  "position: absolute;"
  "left: 50%;"
  "top: 50%;"
  "-webkit-transform: translate(-50%,-50%);"
  "-ms-transform: translate(-50%,-50%);"
  "transform: translate(-50%,-50%);"
  "text-align: center;"
"}"
".button--moema {padding: 1.5em 3em;border-radius: 50px;background: #7986cb;color: #fff;-webkit-transition: background-color 0.3s, color 0.3s;transition: background-color 0.3s, color 0.3s;}"
".button--moema.button--inverted {background: transparent;color: #fff;border:1px solid whitesmoke;}"
".button--moema::before {content: '';position: absolute;top: -20px;left: -20px;bottom: -20px;right: -20px;background: inherit;"
"border-radius: 50px;z-index: -1;opacity: 0.4;-webkit-transform: scale3d(0.8, 0.5, 1);transform: scale3d(0.8, 0.5, 1);}"
".button--moema:hover {-webkit-transition: background-color 0.1s 0.3s, color 0.1s 0.3s;"
"	transition: background-color 0.1s 0.3s, color 0.1s 0.3s;color: #ECEFF1;background-color: #3f51b5;-webkit-animation: anim-moema-1 0.3s forwards;animation: anim-moema-1 0.3s forwards;}"
".button--moema.button--inverted:hover {color: #fff;background-color: transparent;}"
".button--moema:hover::before {-webkit-animation: anim-moema-2 0.3s 0.3s forwards;animation: anim-moema-2 0.3s 0.3s forwards;}"
"@-webkit-keyframes anim-moema-1 {60% {-webkit-transform: scale3d(0.8, 0.8, 1);transform: scale3d(0.8, 0.8, 1);}85% {-webkit-transform: scale3d(1.1, 1.1, 1);transform: scale3d(1.1, 1.1, 1);}100% {-webkit-transform: scale3d(1, 1, 1);transform: scale3d(1, 1, 1);}}"
"@keyframes anim-moema-1 {60% {-webkit-transform: scale3d(0.8, 0.8, 1);transform: scale3d(0.8, 0.8, 1);}"
"	85% {-webkit-transform: scale3d(1.1, 1.1, 1);transform: scale3d(1.1, 1.1, 1);}100% {-webkit-transform: scale3d(1, 1, 1);transform: scale3d(1, 1, 1);}}"
"@-webkit-keyframes anim-moema-2 {to {opacity: 0;-webkit-transform: scale3d(1, 1, 1);transform: scale3d(1, 1, 1);}}"
"@keyframes anim-moema-2 {	to {opacity: 0;-webkit-transform: scale3d(1, 1, 1);transform: scale3d(1, 1, 1);}}"
"a{color:inherit !important;text-decoration: none !important;}"
"</style>"
"<div class='center center-fixed'>"
"<button  class='button button--moema button--inverted button--text-thick button--size-s'><a href='http://192.168.1.30/open'>Ouvrir Porte</a></button>"
"</div>"
"</body>"
"</html>";






//------------------------- SETTINGS PAGE --------------------------------------
char SETTINGS_PAGE[] PROGMEM = R"=====(
  <!DOCTYPE html>
  <html lang='en'>
  <head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
  </head>
  <body>
  <style>
  body{
    margin: 0;
  	width: 100%;
  	height: 100vh;
  	color: #fff;
  	background: linear-gradient(-45deg, #ee7752, #e73c7e, #23a6d5, #23d5ab);
  	background-size: 400% 400%;
  	animation: gradientBG 15s ease infinite;
    font-family: Arial, Helvetica, sans-serif !important;
  }
  @keyframes gradientBG {
  	0% {
  		background-position: 0% 50%;
  	}
  	50% {
  		background-position: 100% 50%;
  	}
  	100% {
  		background-position: 0% 50%;
  	}
  }
  .center-fixed {
    position: fixed !important;
  }
  .center {
    position: absolute;
    left: 50%;
    top: 50%;
    -webkit-transform: translate(-50%,-50%);
    -ms-transform: translate(-50%,-50%);
    transform: translate(-50%,-50%);
    text-align: center;
  }

  .button--moema {
  	padding: 1.5em 3em;
  	border-radius: 50px;
  	background: #7986cb;
  	color: #fff;
  	-webkit-transition: background-color 0.3s, color 0.3s;
  	transition: background-color 0.3s, color 0.3s;
    outline:0 !important;
  }
  .button--moema.button--inverted {
  	background: transparent;
  	color: #fff;
    border:1px solid whitesmoke;
  }
  .button--moema::before {
  	content: '';
  	position: absolute;
  	top: -20px;
  	left: -20px;
  	bottom: -20px;
  	right: -20px;
  	background: inherit;
  	border-radius: 50px;
  	z-index: -1;
  	opacity: 0.4;
  	-webkit-transform: scale3d(0.8, 0.5, 1);
  	transform: scale3d(0.8, 0.5, 1);
  }
  .button--moema:hover {
  	-webkit-transition: background-color 0.1s 0.3s, color 0.1s 0.3s;
  	transition: background-color 0.1s 0.3s, color 0.1s 0.3s;
  	color: #ECEFF1;
  	background-color: #3f51b5;
  	-webkit-animation: anim-moema-1 0.3s forwards;
  	animation: anim-moema-1 0.3s forwards;
  }
  .button--moema.button--inverted:hover {
  	color: #fff;
  	background-color: transparent;
  }
  .button--moema:hover::before {
  	-webkit-animation: anim-moema-2 0.3s 0.3s forwards;
  	animation: anim-moema-2 0.3s 0.3s forwards;
  }
  @-webkit-keyframes anim-moema-1 {
  	60% {
  		-webkit-transform: scale3d(0.8, 0.8, 1);
  		transform: scale3d(0.8, 0.8, 1);
  	}
  	85% {
  		-webkit-transform: scale3d(1.1, 1.1, 1);
  		transform: scale3d(1.1, 1.1, 1);
  	}
  	100% {
  		-webkit-transform: scale3d(1, 1, 1);
  		transform: scale3d(1, 1, 1);
  	}
  }
  @keyframes anim-moema-1 {
  	60% {
  		-webkit-transform: scale3d(0.8, 0.8, 1);
  		transform: scale3d(0.8, 0.8, 1);
  	}
  	85% {
  		-webkit-transform: scale3d(1.1, 1.1, 1);
  		transform: scale3d(1.1, 1.1, 1);
  	}
  	100% {
  		-webkit-transform: scale3d(1, 1, 1);
  		transform: scale3d(1, 1, 1);
  	}
  }
  @-webkit-keyframes anim-moema-2 {
  	to {
  		opacity: 0;
  		-webkit-transform: scale3d(1, 1, 1);
  		transform: scale3d(1, 1, 1);
  	}
  }
  @keyframes anim-moema-2 {
  	to {
  		opacity: 0;
  		-webkit-transform: scale3d(1, 1, 1);
  		transform: scale3d(1, 1, 1);
  	}
  }
  a{color:inherit !important;text-decoration: none !important;}
  input{ display: block; width: 75%; margin:20px auto;	padding: 1.5em 3em;border-radius: 50px; background: white; border:2px solid white; text-align:center;outline:0 !important;}
  </style>
  <div class='center center-fixed' style='width: 90%;padding: 20px;background: rgba(0,0,0,.5);border-radius:15px ; color:white'>
    <img src="data:image/png;base64,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" alt="Red dot" />
    <h2 style='text-align:center; color:white'> PARAMETRE</h2>
    <form>

        <div>
          <input value="" id="ssid" placeholder="Nom du reseau wifi">
        </div>
        <div>
          <input type="password" value="" id="password" placeholder="Mot de passe">
        </div>
        <div>
          <button class="button button--moema button--inverted button--text-thick button--size-s" id="savebtn" type="button" onclick="myFunction()">Sauvgarder</button>
        </div>

    </form>

  </div>
</body>
<script>
function myFunction()
{
  console.log("button was clicked!");

  var ssid = document.getElementById("ssid").value;
  var password = document.getElementById("password").value;
  var data = {ssid:ssid, password:password};

  var xhr = new XMLHttpRequest();
  var url = "/settings";

  xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      // Typical action to be performed when the document is ready:
      if(xhr.responseText != null){
        console.log(xhr.responseText);
      }
    }
  };

  xhr.open("POST", url, true);
  xhr.send(JSON.stringify(data));
};
</script>
</html>
)=====";
