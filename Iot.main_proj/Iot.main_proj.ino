
#include <Keypad.h>
#include <ESP32Servo.h>
#include <DHT.h>
#define ROW_NUM     4
#define COLUMN_NUM  3
#define SERVO_PIN 26
#define DHT11_PIN  21 
#define LDR_PIN  22
#define Led1 27  
#define PIR_SENSOR 19
#define ANALOG_THRESHOLD  500



char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte pin_rows[ROW_NUM] = {18, 5, 17, 16};
byte pin_column[COLUMN_NUM] = {4, 0, 2};

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

DHT dht11(DHT11_PIN, DHT11);

const String password = "7890"; 
const String AlarmDisarm = "3690";
const String AlarmArm = "4321";
String input_password;
Servo servoMotor;
int sensorValue;

void setup() {
  Serial.begin(115200);
  input_password.reserve(32); 
  servoMotor.attach(SERVO_PIN);
  pinMode(Led1,OUTPUT);
  dht11.begin(); 
  analogSetAttenuation(ADC_11db);
  pinMode(PIR_SENSOR, INPUT);
}

void loop() {
  char key = keypad.getKey();
  bool Alarm = false;
  while (Alarm == true){
    AlarmOn();
  }


  if (key) {
    Serial.println(key);

    if (key == '*') {
      input_password = ""; 
    } else if (key == '#') {
      if (password == input_password) {
        Serial.println("The password is correct, Door Opening!");
        DoorOpen();
        GetTemp();
        delay(5000);
        DoorClose();


      } else if (AlarmDisarm == input_password){
        Serial.println("Alarm Password entered\n Alarm disarmed");
        AlarmOff();
        Alarm = false;
      }else if (AlarmArm == input_password){
        Serial.println("Alarm Password entered \n Alarm Armed!");
        AlarmOn();
        Alarm = true;
      }
      
      else {
        Serial.println("The password is incorrect, Door Locked!");
      }

      input_password = ""; 
    } else {
      input_password += key;
    }    
  }
}
