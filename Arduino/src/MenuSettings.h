/*
 * MenuSettings.h
 *
 *  Created on: 2 déc. 2016
 *      Author: jo
 */

#ifndef SRC_MENUSETTINGS_H_
#define SRC_MENUSETTINGS_H_

#include "Arduino.h"
#include "Configuration.h"
#include "Display.h"
#include "ClickEncoder.h"
#include "Function.h"
#include "Save.h"
#include "Winding.h"

#define MIN_LCD			16 // Minimum lcd screen 15 + 1 for null character
#define NOT_SAVE		false
#define SAVE			true
#define SET_CURRENT_SPEED	2
#define EXIT_WINDING		3
#define CONTINUE_WINDING 	4
#define DelayTimeBlock 	 	250
#define DelayTimeBlank 	 	120


class Setting: public Memory
{
public :

  Setting(ClickEncoder *p_Encoder, Display *p_Display, Coil *p_Coil);
  ~Setting();

  void setId(const uint8_t id);
  void resetAction(bool razValues);
  void moveCarriage();
  void moveCoil();
  void runWinding_old(bool resumeCurrent, bool resumeSaved);


private:

  ClickEncoder *_Encoder;
  Display *_Display;
  Coil *_Coil;

  int8_t _speedPercent;
  uint8_t _speed;
  uint8_t _buffSize;

  void affectValues(const char label[], char arrayValue[],uint8_t buffSize ,float *value);
  void idToValue();
  void getFloatingValue();
  void engine(bool save);
  void selectCharacter(int8_t *index, int8_t *last, const char arrayValue[] ,
		       uint8_t buffSize, uint8_t offset, bool cursoJumpEnd);
  void selectCharacter(int8_t *index, int8_t *last);
  int8_t IgnoreChar(int8_t index, int8_t last, const char value[], int arraySize,
		    bool jumpEnd);
  void editValue(char arrayValue[], uint8_t buffSize, int8_t index,
		 ClickEncoder::Button buttonState);
  void saveValue_old(float value);
  uint16_t ajustSpeed(bool initSpeed, int8_t *speedInPercent);
  uint8_t menuSuspend();

  /*Dev----------------------------------------------------------------*/
private:
  uint8_t _idValue;
  char _label[MIN_LCD];

  char *p_arrayValue;
  uint8_t _sizeBuffValue;
  float *p_floatingValue;
  char _unit[3];

  char _actionBar[LCD_CHARS+1];
  uint8_t _positionAB; // Where the action bar will be displayed

  int8_t _index;
  uint8_t _minIndex;

public:
  void actionMenu(const uint8_t id);
  void actionMenu(const uint8_t id, const char label[], char arrayValue[],
		  const uint8_t sizeOfArrayValue,float *value, const char unit[],
		  const char actionBar[], const uint8_t sizeActionBar, uint8_t AB_LinePosition);
  bool runWinding(bool isFirstLunch, bool isNewCoil, uint8_t *tmp_id);

private:
  void setValueFromId();
  void setValues(const char label[], char arrayValue[], const uint8_t sizeOfArrayValue,
		 float *value, const char unit[], const char actionBar[],
		 const uint8_t sizeActionBar, uint8_t AB_LinePosition);
  void setValues(const char label[], const char actionBar[],
		 const uint8_t sizeActionBar, uint8_t AB_LinePosition);
  void setActionBar(char arrayValue[], const uint8_t sizeOfArrayValue,
		    const char actionBar[], const uint8_t sizeActionBar,
		    uint8_t AB_LinePosition);
  void navigationEngine();
  void displaying();
  void cursorMovement(int8_t *lastIndex, uint8_t *lastSense,
		      uint8_t *wordSize, unsigned long *lastTime);
  void editValue(int8_t index);
  bool selectedAction(uint8_t wordSize, uint8_t *tmp_id);
  //CallBacks
  void update();
  void retry();
  void setSave(uint8_t *tmp_id);
  void saveCurrent();
  void resetAll();
  void RAZ_All();
  void moving(bool direction);
  void setWinding(bool isfirstLunch);
  void adjustSpeed();
  void setSuspendMenu(uint8_t *tmp_id);


  /*End Dev----------------------------------------------------------------*/
};

#endif /* SRC_MENUSETTINGS_H_ */
