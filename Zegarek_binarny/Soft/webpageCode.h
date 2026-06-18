//=========================================
//HTML + CSS + JavaScript codes for webpage
//=========================================
const char webpageCode[] =
R"=====(
<!DOCTYPE html>
<html>
<head>
    <title>Binary Clock</title>
    <style>
        body {
            background-color: #000000;
            color: #FFFFFF;
            font-family: 'Press Start 2P', cursive;
            font-size: 18px;
        }

        .container {
            margin-top: 100px;
            text-align: center;
			box-sizing: border-box;
        }

        input[type="text"], input[type="number"] {
            width: auto;
			minWidth: 200px;
			font-family: 'Press Start 2P', cursive;
            padding: 10px;
            font-size: 16px;
        }

        .slider {
            width: 300px;
            margin: 20px auto;
        }

        .slider input[type="range"] {
            -webkit-appearance: none;
            width: 100%;
            height: 10px;
            border-radius: 5px;
            background: #FFFFFF;
            outline: none;
        }

        .slider input[type="range"]::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 20px;
            height: 20px;
            border-radius: 50%;
            background: #FFFFFF;
            cursor: pointer;
        }

        .slider input[type="range"]::-moz-range-thumb {
            width: 20px;
            height: 20px;
            border-radius: 50%;
            background: #FFFFFF;
            cursor: pointer;
        }

        .slider .range-labels {
            display: flex;
            justify-content: space-between;
            margin-top: 10px;
            font-size: 14px;
            color: #FFFFFF;
        }

        .slider .range-labels span {
            flex: 1;
            text-align: center;
        }
		.slider .range-labels span:first-child {
            text-align: left;
        }

        .slider .range-labels span:last-child {
            text-align: right;
        }
		    .button {
            display: inline-block;
            padding: 10px 20px;
            background-color: #ffffff;
            color: #000000;
            font-size: 18px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            box-shadow: 0 3px 6px rgba(0, 0, 0, 0.16);
            transition: background-color 0.3s, box-shadow 0.3s;
			font-family: 'Press Start 2P', cursive;
        }

        .button:hover {
            background-color: #2980b9;
            cursor: pointer;
        }

        .button:active {
            box-shadow: 0 1px 3px rgba(0, 0, 0, 0.3);
            transform: translateY(1px);
        }
        .status {
            display: inline-block;
            width: 40px;
            height: 40px;
            border-radius: 50%;
            background-color: red;
            margin-right: 5px;
            vertical-align: middle;
        }

        .status-label {
            vertical-align: middle;
        }
    </style>
	<link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Press+Start+2P&display=swap">
    <script>
	//WebSocket przychodzące:
	//0 - Ip adress
	//1 - Status | info
	//2 - tz
	//3 - jasnosc
	//4 - 
	//WebSocket wychodzace:
	//1 - SSID
	//2 - Password
	//3 - tz
	//4 - jasnosc
	//5 - 
		//Zmienne globalne
		var SSID = "";
		var password = "";
		var tz ="";
		var IP = "";
		var hours = "";
		var minutes = "";
		var seconds = "";
		//Obsługa socketu
		socket = new WebSocket("ws:/" + "/" + location.host + ":81");
		socket.onopen = function(e) {  console.log("[socket] socket.onopen "); socket.send("0");};
        socket.onerror = function(e) {  console.log("[socket] socket.onerror "); };
        socket.onmessage = function(e) {  
            console.log("[socket] " + e.data);
			switch(e.data[0]){
				case("0"): //zmiana adresu IP
					IP = e.data.substr(1,e.data.length);
					document.getElementById("ipAddress").textContent = IP;
				break;
				case("1"): // zmiana statusu
					switch(e.data[1]){
					case("r"):
						document.getElementById("kolko").style.backgroundColor = "red";
					break;
					case("g"):
						document.getElementById("kolko").style.backgroundColor = "green";
					break;
					}
					document.getElementById("status_text").textContent = e.data.substr(2,e.data.length);
				break;
				case("2"): // zmiana strefy czasowej
					document.getElementById("timezone-offset").value = e.data.substr(1,e.data.length);
				break;
				case("3"): // zmiana jasnosc
					document.getElementById("slider").value = e.data.substr(1,e.data.length);
					document.getElementById("sliderValue").textContent = e.data.substr(1,e.data.length);
				break;
				default:
				break;
			}
        };
		
		//Funkcje wejściowe
		function handleClick() {
            //console.log("Przycisk został kliknięty!");
			//console.log(SSID);
			//console.log(password);
			//console.log(tz);
			socket.send("1"+SSID);
			socket.send("2"+password);
			//socket.send("3"+tz);
            //Tutaj możesz umieścić dodatkowe instrukcje, które mają być wykonane po kliknięciu przycisku
        }
		function handleTimeChange(){
			hours = document.getElementById("hours").value;
			minutes = document.getElementById("minutes").value;
			seconds = document.getElementById("seconds").value;
			socket.send("5"+hours);
			socket.send("6"+minutes);
			socket.send("7"+seconds);
		}
        function handleSliderChange(event) {
            var value = event.target.value;
            //console.log(value);  // Wyświetlenie wartości suwaka w konsoli (można dostosować)
			//socket.send("3"+getElementById("slider").value);
            // Aktualizacja wartości w tekście
            var valueText = document.getElementById("sliderValue");
            valueText.textContent = value;
			socket.send("4"+value);
        }

		function validateHours(event) {
			var input = event.target;
			var value = input.value;

			// Usuń wszystko, co nie jest cyfrą
			value = value.replace(/\D/g, "");

			// Ogranicz liczbę do maksymalnie 23
			if (parseInt(value) > 23) {
				value = "23";
			}
			if (value.length > 2) {
				value = value.slice(0, 2);
			}
			// Ustaw zaktualizowaną wartość w polu tekstowym
			input.value = value;
        }
		function validateMinutes(event) {
            var input = event.target;
            var value = input.value;

            // Usuń wszystko, co nie jest cyfrą
            value = value.replace(/\D/g, "");

            // Ogranicz liczbę do maksymalnie 59
            if (parseInt(value) > 59) {
                value = "59";
            }
			if (value.length > 2) {
                value = value.slice(0, 2);
            }
            // Ustaw zaktualizowaną wartość w polu tekstowym
            input.value = value;
        }
        function handlePasswordInputChange(event) {
			if (event.inputType === "deleteContentBackward") {
				//console.log("Wciśnięto klawisz backspace.");
				password = password.slice(0, -1);
			}
			else{
				var input = event.target;
				var tmp = input.value;
				password += tmp[tmp.length-1];
				var maskedValue = input.value.replace(/./g, '*');
				input.value = maskedValue;
				//console.log("Wprowadzona wartość:", maskedValue);
			}
				//console.log("Oryginalna wartość:", password);
        }
		function handleSSIDInputChange(event) {
				SSID = document.getElementById("SSID").value;
				//console.log("Oryginalna wartość:", SSID);
        }
		function tzChange(event){
			tz = document.querySelector('#timezone-offset').options[document.querySelector('#timezone-offset').selectedIndex].value;
			socket.send("3"+tz);
		}
    </script>
</head>
<body>
    <div class="container">
        <h1>Binary CLock</h1>
        <form>
            <p>IP Adress: <span id="ipAddress"></span></p>
            <br><br>
			<label for="SSID">Network Name:</label>
            <input type="text" id="SSID" placeholder="Enter network name" oninput="handleSSIDInputChange(event)">
			<br><br>
			<label for="password">Password:</label>
            <input type="text" id="password" placeholder="Enter password" oninput="handlePasswordInputChange(event)">
			<br><br>
			<span class="status" id="kolko"></span>
			<span class="status-label" id = "status_text">Status: WiFi not connected!</span>
			<br><br>
            <label>Czas:</label>
            <input type="number" id="hours" placeholder="Hours" min="0" max="23" step="1"  oninput="validateHours(event)">
            <input type="number" id="minutes" placeholder="Minutes" min="0" max="59" step="1"  oninput ="validateMinutes(event)" >
            <input type="number" id="seconds" placeholder="Seconds" min="0" max="59" step="1"  oninput ="validateMinutes(event)">
			<br><br>
			<div class="options">
				<select name="timezone_offset" id="timezone-offset" class="span5" onchange ="tzChange(event)">
				<option value="0">(GMT -12:00) Eniwetok, Kwajalein</option>
				<option value="1">(GMT -11:00) Midway Island, Samoa</option>
				<option value="2">(GMT -10:00) Hawaii</option>
				<option value="3">(GMT -9:00) Alaska</option>
				<option value="4">(GMT -8:00) Pacific Time (US &amp; Canada)</option>
				<option value="5">(GMT -7:00) Mountain Time (US &amp; Canada)</option>
				<option value="6">(GMT -6:00) Central Time (US &amp; Canada), Mexico City</option>
				<option value="7">(GMT -5:00) Eastern Time (US &amp; Canada), Bogota, Lima</option>
				<option value="8">(GMT -4:00) Atlantic Time (Canada), Caracas, La Paz</option>
				<option value="9">(GMT -3:00) Brazil, Buenos Aires, Georgetown</option>
				<option value="q">(GMT -2:00) Mid-Atlantic</option>
				<option value="w">(GMT -1:00) Azores, Cape Verde Islands</option>
				<option value="e" >(GMT) Western Europe Time, London</option>
				<option value="r"selected="selected" >(GMT +1:00) Warsaw, Vienna, Sarajewo, Skopje</option>
				<option value="t">(GMT +2:00) Kaliningrad, South Africa</option>
				<option value="y">(GMT +3:00) Baghdad, Riyadh, Moscow, St. Petersburg</option>
				<option value="u">(GMT +3:30) Tehran</option>
				<option value="i">(GMT +4:00) Abu Dhabi, Muscat, Baku, Tbilisi</option>
				<option value="o">(GMT +5:00) Ekaterinburg, Islamabad, Karachi, Tashkent</option>>
				<option value="p">(GMT +6:00) Almaty, Dhaka, Colombo</option>
				<option value="a">(GMT +7:00) Bangkok, Hanoi, Jakarta</option>
				<option value="s">(GMT +8:00) Beijing, Perth, Singapore, Hong Kong</option>
				<option value="d">(GMT +9:00) Tokyo, Seoul, Osaka, Sapporo, Yakutsk</option>
				<option value="f">(GMT +10:00) Eastern Australia, Guam, Vladivostok</option>
				<option value="g">(GMT +11:00) Magadan, Solomon Islands, New Caledonia</option>>
				<option value="h">(GMT +12:00) Auckland, Wellington, Fiji, Kamchatka</option>
				<option value="j">(GMT +13:00) Apia, Nukualofa</option>
				<option value="k">(GMT +14:00) Line Islands, Tokelau</option>
			</select>
			</div>

			<div class="slider">
                <input type="range" id="slider" min="0" max="100" value="50" step="1" oninput="handleSliderChange(event)">
                <div class="range-labels">
                    <span>0</span>
                    <span>50</span>
                    <span>100</span>
                </div>
            </div>
            <p>Brightness: <span id="sliderValue">50</span></p>
        </form>
		<button class="button" onclick="handleTimeChange()">Manual time change</button>
		<button class="button" onclick="handleClick()">Connect to network</button>
    </div>
</body>
</html>
)=====";