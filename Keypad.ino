
#include <Keypad.h>
#include <ESP32Servo.h>
#define ROW_NUM     4
#define COLUMN_NUM  3
#define SERVO_PIN 26

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte pin_rows[ROW_NUM] = {18, 5, 17, 16};
byte pin_column[COLUMN_NUM] = {4, 0, 2};

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

const String password = "7890"; 
String input_password;
Servo servoMotor;
int sensorValue;
int Led1 = 32 ;

void setup() {
  Serial.begin(115200);
  input_password.reserve(32); 
  servoMotor.attach(SERVO_PIN);
  pinMode(Led1,OUTPUT);
}

void loop() {
  char key = keypad.getKey();


  if (key) {
    Serial.println(key);

    if (key == '*') {
      input_password = ""; 
    } else if (key == '#') {
      if (password == input_password) {
        Serial.println("The password is correct, Door Opening!");
        DoorOpen();
        delay(5000);
        DoorClose();
        LDR_ON();


      } else {
        Serial.println("The password is incorrect, Door Locked!");
        LDR_OFF();
      }

      input_password = ""; 
    } else {
      input_password += key;
    }    
  }
}
