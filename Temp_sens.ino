

#include <DHT.h>
#define DHT11_PIN  21 

DHT dht11(DHT11_PIN, DHT11);

void setup() {
  Serial.begin(9600);
  dht11.begin(); 
}

void loop() {

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
  }

  delay(2000);
}
