/*
 *  UNO Rev3
 *  Geiger-Counter-RadiationD-v1.1(CAJOE)
 *
 *  Wiring:
 *    GND -> GND
 *    5V  -> 5V
 *    VIN -> DIGITAL #2
 *
 */
#include <util/atomic.h>

// Digital pin #2 is usable for interrupts
const byte CAJOE_INPUT = 2;
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

  impulseCounter = 0;
}


void registerIncomingImpulse() {
  impulseCounter++;
}

