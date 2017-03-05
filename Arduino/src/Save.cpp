/*
 * Save.cpp
 *
 *  Created on: 5 déc. 2016
 *      Author: jo
 */

#include "Save.h"

Memory::Memory()
: WireSize(0),
  CoilLength(0),
  Turns(0),
  MaxSpeed(0),
  MinSpeed(0),
  AccDelay(0),

  WinSense(0),
  CarSense(0),

  TotalSteps(0),
  LayerSteps(0),
  LayerCoilSteps(0)
{
  // start reading from position memBase (address 0) of the EEPROM. Set maximumSize to EEPROMSizeUno
  // Writes before membase or beyond EEPROMSizeUno will only give errors when _EEPROMEX_DEBUG is set
  EEPROM.setMemPool(MEN_BASE, EEPROMSizeUno);

  _addr_WireSize	= EEPROM.getAddress(sizeof(char)*BUFFSIZE_WIRE);
  _addr_CoilLength	= EEPROM.getAddress(sizeof(char)*BUFFSIZE_COIL);
  _addr_Turns		= EEPROM.getAddress(sizeof(char)*BUFFSIZE_TURNS);
  _addr_MaxSpeed	= EEPROM.getAddress(sizeof(char)*BUFFSIZE_MAX_SPEED);
  _addr_MinSpeed	= EEPROM.getAddress(sizeof(char)*BUFFSIZE_MIN_SPEED);
  _addr_AccDelay	= EEPROM.getAddress(sizeof(char)*BUFFSIZE_ACC_DELAY);
  _addr_WinSense	= EEPROM.getAddress(sizeof(char)*BUFFSIZE_SENSE);
  _addr_CarSense	= EEPROM.getAddress(sizeof(char)*BUFFSIZE_SENSE);
  _addr_DefaultSettings	= EEPROM.getAddress(sizeof(char)*BUFFSIZE_DEFAULT);
  _addr_TotalSteps	= EEPROM.getAddress(sizeof(uint32_t));
  _addr_LayerSteps	= EEPROM.getAddress(sizeof(uint32_t));
  _addr_LayerCoilSteps	= EEPROM.getAddress(sizeof(uint32_t));

  // If is the first use or if data are corrupted do reset.
  if( !isSet() ) reset();

  // Read and set all data saved in eeprom memory.
  readAll();
}
Memory::~Memory(){}

void Memory::save(char buffer[], const uint8_t id)
{
  //ReadAddresses();
  switch (id)
  {
    case id_WIRESIZE :
      {
	EEPROM.updateBlock<char>(_addr_WireSize, buffer, BUFFSIZE_WIRE);
	break;
      }
    case id_COILLENGTH :
      {
	EEPROM.updateBlock<char>(_addr_CoilLength, buffer, BUFFSIZE_COIL);
	break;
      }
    case id_TURNS :
      {
	EEPROM.updateBlock<char>(_addr_Turns, buffer, BUFFSIZE_TURNS);
	break;
      }
    case id_MAX_SPEED :
      {
	EEPROM.updateBlock<char>(_addr_MaxSpeed, buffer, BUFFSIZE_MAX_SPEED);
	break;
      }
    case id_MIN_SPEED :
      {
	EEPROM.updateBlock<char>(_addr_MinSpeed, buffer, BUFFSIZE_MIN_SPEED);
	break;
      }
    case id_ACC_DELAY :
      {
	EEPROM.updateBlock<char>(_addr_AccDelay, buffer, BUFFSIZE_ACC_DELAY);
	break;
      }
    case id_W_SENSE :
      {
	EEPROM.updateBlock<char>(_addr_WinSense, buffer, BUFFSIZE_SENSE);
	break;
      }
    case id_C_SENSE :
      {
	EEPROM.updateBlock<char>(_addr_CarSense, buffer, BUFFSIZE_SENSE);
	break;
      }
    case id_RESUME_SAVE :
      {
	EEPROM.updateLong(_addr_TotalSteps, TotalSteps);
	EEPROM.updateLong(_addr_LayerSteps, LayerSteps);
	EEPROM.updateLong(_addr_LayerCoilSteps, LayerCoilSteps);
	break;
      }
  }
}

void Memory::read(char buffer[], const uint8_t id)
{
  switch (id)
  {
    case id_WIRESIZE :
      {
	EEPROM.readBlock<char>(_addr_WireSize, buffer, BUFFSIZE_WIRE);
	break;
      }
    case id_COILLENGTH :
      {
	EEPROM.readBlock<char>(_addr_CoilLength, buffer, BUFFSIZE_COIL);
	break;
      }
    case id_TURNS :
      {
	EEPROM.readBlock<char>(_addr_Turns, buffer, BUFFSIZE_TURNS);
	break;
      }
    case id_MAX_SPEED :
      {
	EEPROM.readBlock<char>(_addr_MaxSpeed, buffer, BUFFSIZE_MAX_SPEED);
	break;
      }
    case id_MIN_SPEED :
      {
	EEPROM.readBlock<char>(_addr_MinSpeed, buffer, BUFFSIZE_MIN_SPEED);
	break;
      }
    case id_ACC_DELAY :
      {
	EEPROM.readBlock<char>(_addr_AccDelay, buffer, BUFFSIZE_ACC_DELAY);
	break;
      }
    case id_W_SENSE :
      {
	EEPROM.readBlock<char>(_addr_WinSense, buffer, BUFFSIZE_SENSE);
	break;
      }
    case id_C_SENSE :
      {
	EEPROM.readBlock<char>(_addr_CarSense, buffer, BUFFSIZE_SENSE);
	break;
      }
    case id_RESUME_SAVE :
      {
	TotalSteps = EEPROM.readLong(_addr_TotalSteps);
	LayerSteps = EEPROM.readLong(_addr_LayerSteps);
	LayerCoilSteps= EEPROM.readLong(_addr_LayerCoilSteps);
	break;
      }
  }
}

void Memory::getSavedTotalSteps(uint32_t *totalSteps)
{
  *totalSteps = EEPROM.readLong(_addr_TotalSteps);
}

void Memory::readAll()
{
  // Read the eeprom memory and set buffers with values saved
  read(_buff_WireSize,id_WIRESIZE);
  read(_buff_CoilLength, id_COILLENGTH);
  read(_buff_Turns, id_TURNS);
  read(_buff_MaxSpeed,id_MAX_SPEED);
  read(_buff_MinSpeed, id_MIN_SPEED);
  read(_buff_AccDelay, id_ACC_DELAY);
  read(_buff_WinSense, id_W_SENSE);
  read(_buff_CarSense, id_C_SENSE);

  // Convert value within array in a float or numeric value.
  WireSize 	= atof(_buff_WireSize);
  CoilLength 	= atof(_buff_CoilLength);
  Turns 	= atof(_buff_Turns);
  MaxSpeed 	= atof(_buff_MaxSpeed);
  MinSpeed 	= atof(_buff_MinSpeed);
  AccDelay 	= atof(_buff_AccDelay);
  buffercmp((char*)MSG_CLOCK, _buff_WinSense, BUFFSIZE_SENSE)? WinSense = CLOCK : WinSense = C_CLOCK;
  buffercmp((char*)MSG_CLOCK, _buff_CarSense, BUFFSIZE_SENSE)? CarSense = CLOCK : CarSense = C_CLOCK;
}

void Memory::reset()
{
  EEPROM.writeBlock<char>(_addr_WireSize, INIT_WIRE, BUFFSIZE_WIRE);
  EEPROM.writeBlock<char>(_addr_CoilLength, INIT_COIL, BUFFSIZE_COIL);
  EEPROM.writeBlock<char>(_addr_Turns, INIT_TURNS, BUFFSIZE_TURNS);
  EEPROM.writeBlock<char>(_addr_MaxSpeed, INIT_MAXSPEED, BUFFSIZE_MAX_SPEED);
  EEPROM.writeBlock<char>(_addr_MinSpeed, INIT_MINSPEED, BUFFSIZE_MIN_SPEED);
  EEPROM.writeBlock<char>(_addr_AccDelay, INIT_ACC_DELAY, BUFFSIZE_ACC_DELAY);
  EEPROM.writeBlock<char>(_addr_WinSense, MSG_C_CLOCK, BUFFSIZE_SENSE);
  EEPROM.writeBlock<char>(_addr_CarSense, MSG_CLOCK, BUFFSIZE_SENSE);

  EEPROM.writeBlock<char>(_addr_DefaultSettings, MSG_IS_SET, BUFFSIZE_DEFAULT);

  EEPROM.writeLong(_addr_TotalSteps, 0);
  EEPROM.writeLong(_addr_LayerSteps, 0);
  EEPROM.writeLong(_addr_LayerCoilSteps, 0);
}

bool Memory::isSet()
{
  char set[BUFFSIZE_DEFAULT];
  EEPROM.readBlock<char>(_addr_DefaultSettings, set, BUFFSIZE_DEFAULT);

  // True if the two buffers are equals
  return buffercmp((char*)MSG_IS_SET, set, BUFFSIZE_DEFAULT);
}

/* Debug -------------------------------------------------------------------*/
#ifdef DEBUGoff
void Memory::ReadAddresses()
{
  Serial.print("adress wire: "); Serial.println(_addr_WireSize);
  Serial.print("adress coil: "); Serial.println(_addr_CoilLength);
  Serial.print("adress turns: "); Serial.println(_addr_Turns);
  Serial.print("adress max: "); Serial.println(_addr_MaxSpeed);
  Serial.print("adress min: "); Serial.println(_addr_MinSpeed);
  Serial.print("adress acc: "); Serial.println(_addr_AccDelay);
  Serial.print("adress win: "); Serial.println(_addr_WinSense);
  Serial.print("adress car: "); Serial.println(_addr_CarSense);
  Serial.print("adress default: "); Serial.println(_addr_DefaultSettings);
  Serial.println(" ");
}

void Memory::ReadFloatValue()
{
  Serial.print("float wire: "); Serial.println(WireSize);
  Serial.print("float coil: "); Serial.println(CoilLength);
  Serial.print("float turns: "); Serial.println(Turns);
  Serial.print("float max: "); Serial.println(MaxSpeed);
  Serial.print("float min: "); Serial.println(MinSpeed);
  Serial.print("float acc: "); Serial.println(AccDelay);
  Serial.print("val win: "); Serial.println(WinSense);
  Serial.print("val car: "); Serial.println(CarSense);
  Serial.println(" ");
}

void Memory::ReadArrayValue()
{
  char _buff_DefaultSettings[BUFFSIZE_DEFAULT] = {0};

  Serial.print("array wire: "); Serial.println(_buff_WireSize);
  Serial.print("array coil: "); Serial.println(_buff_CoilLength);
  Serial.print("array turns: "); Serial.println(_buff_Turns);
  Serial.print("array max: "); Serial.println(_buff_MaxSpeed);
  Serial.print("array min: "); Serial.println(_buff_MinSpeed);
  Serial.print("array acc: "); Serial.println(_buff_AccDelay);
  Serial.print("array win: "); Serial.println(_buff_WinSense);
  Serial.print("array car: "); Serial.println(_buff_CarSense);
  EEPROM.readBlock<char>(_addr_DefaultSettings, _buff_DefaultSettings, BUFFSIZE_DEFAULT);
  Serial.print("array default: "); Serial.println(_buff_DefaultSettings);
  Serial.println(" ");
}
#endif
