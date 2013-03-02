#ifndef TEST_BENCH_H
#define TEST_BENCH_H

#include "Arduino.h"

const int storeClockPin = 2;
const int shiftClockPin = 3;
const int dataToBoardPin = 4;
const int dataFromBoardPin = 5;
const int buttonPin = 6;
const int probePin = 7;
const int ledPin = 13;

#define PROBE_PULLUP_OFF INPUT
#define PROBE_PULLUP_ON INPUT_PULLUP

void setupTestBench();
void shiftBitOut(boolean b);
boolean shiftBitIn();
void triggerLatch();
void setProbeMode(int probeMode);
boolean readProbe();
void waitForButton();
void showProgress(boolean localResult);
void reportResult(boolean result);

#endif

