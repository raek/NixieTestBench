#include "TestBench.h"
#include "DriverInputs.h"
#include "DriverOutputs.h"
#include "Shifting.h"

void setup() {
  setupTestBench();
}

void loop() {
  shifting();
  driverInputs();
  driverOutputs();
  for (;;) {}
}

