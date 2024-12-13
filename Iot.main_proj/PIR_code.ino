


void AlarmOn() {
int sensorValue = digitalRead(PIR_SENSOR);
 if(sensorValue == HIGH)
 {
  LedBlink();
  Serial.println("Motion\n");
 }
 else
 {
  LEDoff();
  Serial.println("No motion\n");
 }
 delay(500);
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
int sensorValue = digitalRead(PIR_SENSOR);
 if(sensorValue == HIGH)
 {
  LEDoff();
  Serial.println("Alarm OFF\n");
 }
 else
 {
  LEDoff();
 }
 delay(500);
}

