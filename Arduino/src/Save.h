/*
 * Save.h
 *
 *  Created on: 5 déc. 2016
 *      Author: jo
 */

#ifndef SRC_SAVE_H_
#define SRC_SAVE_H_

#include "Arduino.h"
#include "Configuration.h"
#include "EEPROMex.h"
#include "Function.h"

// Start EEprom address
#define MEN_BASE  50
// String to check if EEprom memory is initialize
#define MSG_IS_SET "is set"
// Size to store memory
#define BUFFSIZE_WIRE       (COUNTOF(INIT_WIRE))
#define BUFFSIZE_COIL       (COUNTOF(INIT_COIL))
#define BUFFSIZE_TURNS      (COUNTOF(INIT_TURNS))
#define BUFFSIZE_MAX_SPEED  (COUNTOF(INIT_MAXSPEED))
#define BUFFSIZE_MIN_SPEED  (COUNTOF(INIT_MINSPEED))
#define BUFFSIZE_ACC_DELAY  (COUNTOF(INIT_ACC_DELAY))
#define BUFFSIZE_ACC_INCR   (COUNTOF(INIT_ACC_INCR))
#define BUFFSIZE_DEFAULT    (COUNTOF(MSG_IS_SET))

/* ID _________________________________________________________________*/
// Values
#define id_WIRESIZE    1
#define id_COILLENGTH  2
#define id_TURNS       3
#define id_W_SENSE     4
#define id_C_SENSE     5
#define id_MAX_SPEED   6
#define id_MIN_SPEED   7
#define id_ACC_DELAY   8
#define id_ACC_INCR    9

// Actions
#define id_SAVE           20
#define id_RESET          21
#define id_RAZ            22
#define id_MOVE_CARRIAGE  23
#define id_MOVE_COIL      24
#define id_NEW            25
#define id_RESUME         26
#define id_RESUME_SAVE    27
#define id_SUSPEND        28
#define id_HOME           29
#define id_GO_HOME        30


class Memory
{
public :

  Memory();
  ~Memory();

  void init();
  void save(char buffer[], const uint8_t id);
  void read(char buffer[], const uint8_t id);
  //void getSavedTotalSteps(uint32_t *totalSteps);
  void readAll();
  void reset();
  bool isSet();

  // for debug
#ifdef DEBUGoff
  void ReadAddresses();
  void ReadFloatValue();
  void ReadArrayValue();
#endif

protected :

  float WireSize;
  float CoilLength;
  uint16_t Turns;
  uint16_t MaxSpeed;
  uint16_t MinSpeed;
  uint16_t AccDelay;
  uint16_t AccIncr;

  bool WinSense;
  bool CarSense;

  uint16_t CarrPass;
  uint16_t CarrStepPerPass;
  bool CarrDir;
  uint16_t CoilTr;
  uint16_t CoilStepPerTr;
  bool CoilDir;

  char _buff_WireSize[BUFFSIZE_WIRE+1];
  char _buff_CoilLength[BUFFSIZE_COIL+1];
  char _buff_Turns[BUFFSIZE_TURNS+1];
  char _buff_MaxSpeed[BUFFSIZE_MAX_SPEED+1];
  char _buff_MinSpeed[BUFFSIZE_MIN_SPEED+1];
  char _buff_AccDelay[BUFFSIZE_ACC_DELAY+1];
  char _buff_AccIncr[BUFFSIZE_ACC_INCR+1];

  uint8_t _addr_WireSize;
  uint8_t _addr_CoilLength;
  uint8_t _addr_Turns;
  uint8_t _addr_WinSense;
  uint8_t _addr_CarSense;
  uint8_t _addr_MaxSpeed;
  uint8_t _addr_MinSpeed;
  uint8_t _addr_AccDelay;
  uint8_t _addr_AccIncr;
  uint8_t _addr_DefaultSettings;
  uint8_t _addr_CarrPass;
  uint8_t _addr_CarrStepPerPass;
  uint8_t _addr_CarrDir;
  uint8_t _addr_CoilTr;
  uint8_t _addr_CoilStepPerTr;
  uint8_t _addr_CoilDir;
};

#endif /* SRC_SAVE_H_ */
