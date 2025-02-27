void AlarmTriggered() {
  Serial.println("Motion detected!");
  while (AlarmState) {
    LEDon();
    delay(500);
    LEDoff();
    delay(500);
    CheckKeypad();
  }
}


void AlarmOn() {
LEDon();
Serial.println("Alarm On");
}
void LEDon()
{
 digitalWrite(Led1,HIGH);
 
}
void LEDoff()
{
 digitalWrite(Led1,LOW);
}
void AlarmOff() {
  LEDoff();
  Serial.println("Alarm Off");
}

void CheckKeypad() {
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    if (key == '*') {
      input_password = ""; 
    } else if (key == '#') {
      if (AlarmDisarm == input_password) {
        Serial.println("Alarm Password entered, Alarm disarmed");
        AlarmOff();
        Alarm = false;
        AlarmState = false;
      } else {
        Serial.println("Incorrect code");
      }
      input_password = "";
    } else {
      input_password += key;
    }
  }
}
void checkLDR(){
  if (digitalRead(LDR_PIN) == LOW){
    GarageLight_on();
  }
else {
  GarageLight_off();
}
}
