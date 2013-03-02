#include "Arduino.h"
#include "DriverInputs.h"
#include "TestBench.h"

static void showDiagram();
static void configureProbe();
static void testDriverInputs();
static void askToProbeDriverInput(int driver, int index);
static boolean testDriverInput(int driver, int index);

static int driverInputPinTable[] = {3, 4, 6, 7};
static int driverInputBitTable[] = {0, 3, 1, 2};

void driverInputs() {
  showDiagram();
  configureProbe();
  testDriverInputs();
}

static void showDiagram() {
  Serial.println("driver 1  driver 2      driver 3  driver 4");
  Serial.println("++++++++  ++++++++      ++++++++  ++++++++");
  Serial.println("D      |  D      |      D      |  D      |");
  Serial.println("++++++++  ++++++++      ++++++++  ++++++++");
  Serial.println("  ^^ ^^     ^^ ^^         ^^ ^^     ^^ ^^ ");
  Serial.println("  34 67     34 67         34 57     34 67 ");
  Serial.println();
}

static void configureProbe() {
  setProbeMode(PROBE_PULLUP_OFF);
}

static void testDriverInputs() {
  for (int driver = 0; driver < 4; driver++) {
    for (int index = 0; index < 4; index++) {
      askToProbeDriverInput(driver, index);
      reportResult(testDriverInput(driver, index));
    }
  }
}

static void askToProbeDriverInput(int driver, int index) {
  Serial.print("Please put the probe at pin ");
  Serial.print(driverInputPinTable[index]);
  Serial.print(" of driver ");
  Serial.print(driver + 1);
  Serial.println(" and press the button...");
  waitForButton();
  Serial.println("Testing...");
  Serial.print("  ");
}

static boolean testDriverInput(int driver, int index) {
  boolean result = true;
  int pos = 4 * driver + driverInputBitTable[index];
  for (int i = 0; i < 16; i++) {
    shiftBitOut(LOW);
  }
  triggerLatch();
  shiftBitOut(HIGH);
  for (int i = 0; i < 16; i++) {
    triggerLatch();
    boolean expected = (i == pos) ? HIGH : LOW;
    boolean actual = readProbe();
    boolean localResult = (actual == expected);
    if (!localResult) {
      result = false;
    }
    showProgress(localResult);
    shiftBitOut(LOW);
  }
  return result;
}

