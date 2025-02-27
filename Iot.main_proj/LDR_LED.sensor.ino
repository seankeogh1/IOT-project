void LedBlink (){
 digitalWrite(Led1,HIGH);
 delay(500);
 digitalWrite(Led1, LOW);
 delay(500);
}
void GarageLight_on(){
  digitalWrite(GARAGE_LED,HIGH);
}
void GarageLight_off(){
  digitalWrite(GARAGE_LED,LOW);
}
