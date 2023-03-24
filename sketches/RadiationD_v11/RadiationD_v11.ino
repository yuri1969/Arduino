/*
 *  UNO Rev3
 *  Geiger-Counter-RadiationD-v1.1(CAJOE)
 *
 *  Wiring
 *  ----------------------------
 *  RadiationD_v11 -> UNO Rev3
 *  ----------------------------
 *             GND -> GND
 *             5V  -> 5V
 *             VIN -> DIGITAL #2
 *
 */
#include <util/atomic.h>

// Digital pin #2 is usable for interrupts
const byte CAJOE_INPUT = 2;
// This is a property of GM tube M4011
// cpm / 151 = uSv/h
const byte TUBE_CONVERSION_INDEX = 151;
const word MINUTE = 60000;

// Limits cpm to 65535
volatile word impulseCounter = 0;


void setup() {
  pinMode(CAJOE_INPUT, INPUT);

  attachInterrupt(digitalPinToInterrupt(CAJOE_INPUT), registerIncomingImpulse, FALLING);

  Serial.begin(9600);
}


void loop() {
  word cpm;

  // Accuracy is +-1ms in 2min
  delay(MINUTE);

  // Make the word (16b) read atomic
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
     cpm = impulseCounter;
  }

  Serial.println(String(cpm) + "cpm");
  Serial.println(String(cpm / TUBE_CONVERSION_INDEX) + "uSv/h");

  impulseCounter = 0;
}


void registerIncomingImpulse() {
  impulseCounter++;
}
