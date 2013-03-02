#include "Arduino.h"
#include "TestBench.h"

void setupTestBench() {
  pinMode(storeClockPin, OUTPUT);
  digitalWrite(storeClockPin, LOW);
  pinMode(shiftClockPin, OUTPUT);
  digitalWrite(shiftClockPin, LOW);
  pinMode(dataToBoardPin, OUTPUT);
  digitalWrite(dataToBoardPin, LOW);
  pinMode(dataFromBoardPin, INPUT);
  pinMode(probePin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void shiftBitOut(boolean b) {
  digitalWrite(dataToBoardPin, b);
  digitalWrite(shiftClockPin, HIGH);
  digitalWrite(shiftClockPin, LOW);
}

boolean shiftBitIn() {
  boolean b = digitalRead(dataFromBoardPin);
  shiftBitOut(LOW);
  return b;
}

void triggerLatch() {
  digitalWrite(storeClockPin, HIGH);
  digitalWrite(storeClockPin, LOW);
}

void setProbeMode(int probeMode) {
  pinMode(probePin, probeMode);
}

boolean readProbe() {
  return digitalRead(probePin);
}

void waitForButton() {
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  while (digitalRead(buttonPin)) {}
  while (!digitalRead(buttonPin)) {}
}

void showProgress(boolean localResult) {
  if (localResult) {
    Serial.print(".");
  } else {
    Serial.print("X");
  }
}

void reportResult(boolean result) {
  Serial.println();
  if (result) {
    Serial.println("OK");
  } else {
    Serial.println("FAILED");
  }
  Serial.println();
}

