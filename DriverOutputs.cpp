#include "Arduino.h"
#include "DriverOutputs.h"
#include "TestBench.h"

static void showDiagram();
static void configureProbe();
static void testDriverOutputs();
static void askToProbeDriverOutput(int driver, int index);
static boolean testDriverOutput(int driver, int index);
static boolean testNibble(int driver, int digit, int nibble);
static void writeDriver(int driver, int nibble);
static void shiftOutNibble(int nibble);

static int driverOutputPinTable[] = {1, 2, 8, 9, 10, 11, 13, 14, 15, 16};
static int digitTable[] = {8, 9, 2, 3, 7, 6, 4, 5, 1, 0};

void driverOutputs() {
  showDiagram();
  configureProbe();
  testDriverOutputs();
}

static void showDiagram() {
  Serial.println("driver 1  driver 2      driver 3  driver 4");
  Serial.println("1111 11   1111 11       1111 11   1111 11 ");
  Serial.println("6543 109  6543 109      6543 109  6543 109");
  Serial.println("vvvv vvv  vvvv vvv      vvvv vvv  vvvv vvv");
  Serial.println("++++++++  ++++++++      ++++++++  ++++++++");
  Serial.println("D      |  D      |      D      |  D      |");
  Serial.println("++++++++  ++++++++      ++++++++  ++++++++");
  Serial.println("^^     ^  ^^     ^      ^^     ^  ^^     ^");
  Serial.println("12     8  12     8      12     8  12     8");
  Serial.println();
}

static void configureProbe() {
  setProbeMode(PROBE_PULLUP_ON);
}

static void testDriverOutputs() {
  for (int driver = 0; driver < 4; driver++) {
    for (int index = 0; index < 10; index++) {
      askToProbeDriverOutput(driver, index);
      reportResult(testDriverOutput(driver, index));
    }
  }
}

static void askToProbeDriverOutput(int driver, int index) {
  Serial.print("Please put the probe at pin ");
  Serial.print(driverOutputPinTable[index]);
  Serial.print(" of driver ");
  Serial.print(driver + 1);
  Serial.println(" and press the button...");
  waitForButton();
  Serial.println("Testing...");
  Serial.print("  ");
}

static boolean testDriverOutput(int driver, int index) {
  boolean result = true;
  int digit = digitTable[index];
  for (int nibble = 0; nibble < 16; nibble++) {
    boolean localResult = testNibble(driver, digit, nibble);
    if (!localResult) {
      result = false;
    }
    showProgress(localResult);
  }
  return result;
}

static boolean testNibble(int driver, int digit, int nibble) {
  writeDriver(driver, nibble);
  boolean expected;
  if (nibble < 10) {
    expected = (nibble == digit) ? LOW : HIGH;
  } else {
    expected = HIGH;
  }
  boolean actual = readProbe();
  return actual == expected;
}

static void writeDriver(int driver, int nibble) {
  for (int i = 3; i >= 0; i--) {
    if (i == driver) {
      shiftOutNibble(nibble);
    } else {
      shiftOutNibble(15);
    }
  }
  triggerLatch();
}

static void shiftOutNibble(int nibble) {
  int x = nibble;
  shiftBitOut((nibble & 0x08) != 0);
  shiftBitOut((nibble & 0x04) != 0);
  shiftBitOut((nibble & 0x02) != 0);
  shiftBitOut((nibble & 0x01) != 0);
}

