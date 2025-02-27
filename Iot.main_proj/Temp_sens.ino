



void GetTemp() {

  float humi  = dht11.readHumidity();

  float tempC = dht11.readTemperature();


  if ( isnan(tempC) || isnan(humi)) {
    Serial.println("Failed to read from DHT11 sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%");


    Serial.print("  |  ");

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print("°C");

    if(tempC > 23){
      Serial.print("\nFan on , temperature too hot");
      digitalWrite(Led1,HIGH);
    }else {
      Serial.print("\nFan off , temperature is good");
      digitalWrite(Led1,LOW);
    }
  }

  delay(2000);
}
