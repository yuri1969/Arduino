/*
 *  UNO Rev3
 *  Temperature & Humidity Sensor DHT22 (AM2302)
 *
 *  Wiring
 *  ----------------------------
 *  DHT22 -> UNO Rev3
 *
 *  +-------+
 *  |+++++++|
 *  |+++++++|
 *  |+++++++|
 *  +-------+
 *  |       |
 *  ++-+-+-++
 *   | | | |
 *   1 2 3 4
 *
 *  ----------------------------
 *     1 -> 5V
 *     2 -> DIGITAL #2
 *       |-> 10k Ω -> 5V
 *     3 ->
 *     4 -> GND
 *
 */
// Provided by "DHT Sensor Library"
// Tools-Manage Libraries...-Search "DHT"-Install
#include "DHT.h"

// Digital pin #2
#define DHT_INPUT 2
// Sensor type DHT 22 (AM2302)
#define DHT_TYPE DHT22

#define DELAY_MS 5000

// Initialize the DHT sensor
DHT dht(DHT_INPUT, DHT_TYPE);

void setup() {
  dht.begin();

  Serial.begin(9600);
}

void loop() {
  delay(DELAY_MS);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Catch reading errors
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error reading from the DHT sensor!");
    return;
  }

  Serial.println(String(temperature) + "°C - " + String(humidity) + "%");
}
