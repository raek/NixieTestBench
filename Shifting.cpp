#include "TestBench.h"
#include "Shifting.h"

static void showDescription();
static boolean testShifting();
static void shiftOutPattern();
static boolean verifyPattern();

byte pattern[] = {0x13, 0x37};

void shifting() {
  showDescription();
  reportResult(testShifting());
}

static void showDescription() {
  Serial.println("Testing shift register loop...");
  Serial.print("  ");
}

static boolean testShifting() {
  shiftOutPattern();
  return verifyPattern();
}

static void shiftOutPattern() {
  for (int i = 0; i < 2; i++) {
    byte x = pattern[i];
    for (int j = 0; j < 8; j++) {
      shiftBitOut((x & 0x01) != 0);
      x = x >> 1;
    }
  }
}

static boolean verifyPattern() {
  boolean result = true;
  for (int i = 0; i < 2; i++) {
    byte x = pattern[i];
    for (int j = 0; j < 8; j++) {
      byte y = shiftBitIn();
      boolean localResult = (y == (x & 0x01));
      if (!localResult) {
        result = false;
      }
      showProgress(localResult);
      x = x >> 1;
    }
  }
  return result;
}

