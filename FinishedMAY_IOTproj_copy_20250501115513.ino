#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <ESP32Servo.h>
#include <Keypad.h>

const char* ssid = "James";
const char* password = "spain123";

#define ROW_NUM     4
#define COLUMN_NUM  3
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte pin_rows[ROW_NUM] = {18, 5, 17, 16};
byte pin_column[COLUMN_NUM] = {4, 0, 2};
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

#define DHTPIN 21
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define SERVO_PIN 26
Servo servoMotor;

#define PIR_SENSOR 19
#define Led1 27

WebServer server(80);

bool doorOpen = false;
bool AlarmState = false;
bool Alarm = false;
const String AlarmDisarm = "3690";
const String AlarmArm = "4321";
const String doorpassword = "7890"; 
String input_password;

void handleLogin();
void handleControlPage();

void handleData() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    server.send(500, "application/json", "{\"error\":\"Sensor read failed\"}");
    return;
  }

  String json = "{\"temperature\":" + String(temp, 1) + ",\"humidity\":" + String(hum, 1) + "}";
  server.send(200, "application/json", json);
}

void handleOpenDoor() {
  if (!doorOpen) {
    DoorOpen();
    doorOpen = true;
    server.send(200, "text/plain", "Door opened");
  } else {
    server.send(400, "text/plain", "Door is already open");
  }
}

void handleCloseDoor() {
  if (doorOpen) {
    DoorClose();
    doorOpen = false;
    server.send(200, "text/plain", "Door closed");
  } else {
    server.send(400, "text/plain", "Door is already closed");
  }
}

void AlarmOn() {
  AlarmState = true;
  digitalWrite(Led1, HIGH);
  Serial.println("Alarm On");
}

void AlarmOff() {
  AlarmState = false;
  digitalWrite(Led1, LOW);
  Serial.println("Alarm Off");
}

void AlarmTriggered() {
  Serial.println("Motion Detected! Alarm Triggered!");
  for (int i = 0; i < 10; i++) {
    digitalWrite(Led1, HIGH);
    delay(250);
    digitalWrite(Led1, LOW);
    delay(250);
  }
}

void GarageLight_on() {
  digitalWrite(Led1, HIGH);
  delay(3000);
  digitalWrite(Led1, LOW);
}

void DoorOpen() {
  for (int pos = 0; pos <= 180; pos++) {
    servoMotor.write(pos);
    delay(5);
  }
}

void DoorClose() {
  for (int pos = 180; pos >= 0; pos--) {
    servoMotor.write(pos);
    delay(5);
  }
}

void GetTemp() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C, Humidity: ");
  Serial.print(hum);
  Serial.println(" %");
}

void handleLogin() {
  server.send(200, "text/html", R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login</title>
    <link href='https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css' rel='stylesheet'>
    <style>
        *{ margin: 0; padding: 0; box-sizing: border-box; font-family:"Poppins" sans-serif; }
        body{ background : url(https://www.dueruote.it/content/dueruote/it/pubbliredazionale/bacheca/2021/03/01/Hoermann/jcr:content/social-image.img.png/1612878357306.png);
         background-size: cover;
        background-position: center; min-height: 98vh; justify-content: center; display: flex; align-items: center; min-height: 100vh; }
        .wrapper{ width: 420px;
         background: transparent; border: 2px solid rgba(255, 255, 255, .2);
         color: antiquewhite;
         backdrop-filter: blur(20px); border-radius: 10px; padding: 30px 40px; }
        .wrapper h1 { font-size: 36px; text-align: center; }
        .input-control{ position: relative; width: 100%; height: 50px; margin: 30px 0; }
        .input-control input{ width: 100%; height: 100%; background: transparent; border: none; outline: none;
         border: 2px solid rgba(255, 255, 255, 0.2); border-radius: 40px; font-size: 16px; color: #fff; padding: 20px 45px 20px 20px; }
        .input-control input::placeholder { color:aliceblue; } 
        .wrapper .btn { width: 100%; height: 45px; background: #fff; border: none; outline: none; border-radius: 40px;
         box-shadow: 0 0 10px rgba(0, 0, 0, .1); cursor: pointer; font-size: 16px; color: #333; font-weight: 600; }
    </style>
</head>
<body>
    <div class="wrapper">
        <form id="LoginForm" onsubmit="return loginUser();">
            <h1>Login</h1>
            <div class="input-control">
                <input id="Code" type="text" placeholder="Code" required>
                <i class='bx bx-dialpad'></i>
            </div>
            <button type="submit" class="btn"> Login </button>
        </form>
    </div>
    <script>
        function loginUser(){
            event.preventDefault();
            let codeInput = document.getElementById("Code").value.trim();
            let correctCode = "1234";
            if(codeInput === correctCode) {
                window.location.href = "/control"; 
            } else {
                alert("Incorrect code :(");
            }
        }
    </script>
</body>
</html>
)rawliteral");
}

void handleControlPage() {
  server.send(200, "text/html", R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <title>Your Smart Garage</title>
    <style>
        body { background: url(https://www.shutterstock.com/image-vector/calm-peaceful-morning-scenery-mountain-600nw-2021679185.jpg); background-size: cover; display: flex; flex-direction: column; align-items: center; justify-content: flex-start; height: 100vh; margin: 0; }
        .header h1 { font-size: 50px; text-align: center; background-color: aliceblue;
        color: black; border-radius: 10px;
        font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif; width: 100%; padding: 10px; }
        #sensor-info { position: absolute;
        top: 20px;
        right: 20px;
        font-size: 18px;
        background-color: rgba(255, 255, 255, 0.8);
        padding: 10px; border-radius: 10px; }
        #doorHead, #alarmHead { background-color: darkcyan; width: 250px; height: 50px;
        border-radius: 10px; text-align: center; font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif; font-size: larger;
         line-height: 50px; margin-top: 20px; }
        .button-container { display: flex; flex-direction: column; align-items: center; gap: 20px; margin-top: 20px; }
        button { border: 4px solid black; height: 100px;
         width: 150px; color: azure; border-radius: 20px; font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif; font-size: large; display: block;
          text-align: center; }
        #AlarmOn { background-color: green; }
        #AlarmOff { background-color: brown; }
        #OpenDoor { background-color: blueviolet; }
        #CloseDoor { background-color: blueviolet; }
        @media (max-width: 768px) { .header h1 { font-size: 40px; } button { width: 120px; height: 80px; font-size: medium; } #sensor-info { font-size: 14px; } }
    </style>
</head>
<body>
    <div class="header"><h1>Your Smart Garage</h1></div>
    <div id="sensor-info">
        <p id="temp">Temperature: -- °C</p>
        <p id="hum">Humidity: -- %</p>
    </div>
    <div id="doorHead"><p>Door</p></div>
    <div class="button-container">
        <button id="OpenDoor" onclick="openDoor();">Open Door</button>
        <button id="CloseDoor" onclick="closeDoor()">Close Door</button>
    </div>
    <div id="alarmHead"><p>Alarm</p></div>
    <div class="button-container">
        <button id="AlarmOn" onclick="alarmOn()">Enable Alarm</button>
        <button id="AlarmOff" onclick="alarmOff()">Disable Alarm</button>
    </div>
    <script>
        async function fetchSensorData() {
            try {
                const data = await fetch('/data');
                const json = await data.json();
                document.getElementById("temp").innerText = `Temperature: ${json.temperature} °C`;
                document.getElementById("hum").innerText = `Humidity: ${json.humidity} %`;
            } catch (error) {
                console.error("Failed to fetch sensor data", error);
            }
        }
        async function openDoor() {
            await fetch('/open-door');
            document.getElementById("OpenDoor").disabled = true;
            document.getElementById("CloseDoor").disabled = false;
        }
        async function closeDoor() {
            await fetch('/close-door');
            document.getElementById("CloseDoor").disabled = true;
            document.getElementById("OpenDoor").disabled = false;
        }
        function alarmOn() {
            fetch('/alarm-on');
            document.getElementById("AlarmOn").disabled = true;
            document.getElementById("AlarmOff").disabled = false;
        }
        function alarmOff() {
            fetch('/alarm-off');
            document.getElementById("AlarmOff").disabled = true;
            document.getElementById("AlarmOn").disabled = false;
        }
        setInterval(fetchSensorData, 2000);
    </script>
</body>
</html>
)rawliteral");
}

void setup() {
  Serial.begin(115200);
  input_password.reserve(32); 
  dht.begin();
  servoMotor.attach(SERVO_PIN);
  pinMode(Led1, OUTPUT);
  pinMode(PIR_SENSOR, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.on("/", HTTP_GET, handleLogin);
  server.on("/control", HTTP_GET, handleControlPage);
  server.on("/data", HTTP_GET, handleData);
  server.on("/open-door", HTTP_GET, handleOpenDoor);
  server.on("/close-door", HTTP_GET, handleCloseDoor);
  server.on("/alarm-on", HTTP_GET, AlarmOn);
  server.on("/alarm-off", HTTP_GET, AlarmOff);

  server.begin();
  Serial.println("Server started");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
  char key = keypad.getKey();

  if (Alarm && digitalRead(PIR_SENSOR) == HIGH) {
    AlarmTriggered();
  }

  if (key) {
    Serial.println(key);

    if (key == '*') {
      input_password = ""; 
    } else if (key == '#') {
      if (doorpassword == input_password) {
        Serial.println("Correct password, opening door.");
        DoorOpen();
        GetTemp();
        delay(5000);
        DoorClose();
        GarageLight_on();
      } else if (AlarmDisarm == input_password) {
        Serial.println("Alarm disarmed");
        AlarmOff();
        Alarm = false;
      } else if (AlarmArm == input_password) {
        Serial.println("Alarm armed");
        AlarmOn();
        Alarm = true;
      } else {
        Serial.println("Incorrect password");
      }
      input_password = "";
    } else {
      input_password += key;
    }
  }
}
