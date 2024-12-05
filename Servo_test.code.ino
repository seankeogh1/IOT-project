

void DoorOpen() {
  for (int pos = 0; pos <= 180; pos += 1) {
    servoMotor.write(pos);
  }
}

void DoorClose(){
  for (int pos = 180; pos >= 0; pos -= 1) {
    servoMotor.write(pos);
  }
}

void LDR_ON()
{
  sensorValue = analogRead(A0); 
  
  if(sensorValue < 500 ){
    digitalWrite(Led1, HIGH);
  }
  else{
    digitalWrite(Led1, LOW);
  }
}
void LDR_OFF()
{
  sensorValue = analogRead(A0); 
  
  if(sensorValue < 500 ){
    digitalWrite(Led1, LOW);
  }
  else{
    digitalWrite(Led1, LOW);
  }
}