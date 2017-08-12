#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"
#include "Configuration.h"
#include "Fastio.h"
#include "TimerOne.h"

#define COIL      1
#define CARRIAGE  2

#define ACC 1000

#define MOTOR_INT 10 // microseconds
#define RPM_TO_INT(rpm) ((600000 / rpm) / STEPS_PER_TR * MOTOR_INT)

void motorsInit();
void motorsStart();
void motorsStop();
void engineMotors();

void oneStep(bool M_coil, bool M_carr);

uint16_t getMotorCoilTr();
bool getWindingStatus();

void setMotors(bool M_coil, bool M_coilDir, bool M_carr, bool M_carrDir, uint16_t maxWindingSpeed);
void setDisplacement(uint16_t tr);

#endif
