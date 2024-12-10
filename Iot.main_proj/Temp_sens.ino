




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
    Serial.print("°C  ~  ");

    if(tempC > 23){
      Serial.print("\nFan on , temperature too hot");
    }else {
      Serial.print("\nFan off , temperature is good");
    }
  }

  delay(2000);
}
