/*
  libPlc Version 0.1, last updated 6th June, 2015.
  A simple IL language for Programmable Logic Controller (PLC) running
  on Arduino and compatibles.

  Author:    J.P.C. Cajueiro
  
  Based on:
  plcLib Version 1.0, last updated 23rd December, 2014.
  
  Author:    W. Ditch
  Publisher: www.electronics-micros.com

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details, available from:
  <http://www.gnu.org/licenses/>
*/

#ifndef libPlc_h
#define libPlc_h

#include "Arduino.h"

#define DIRECT 0
#define INVERTED 1
#define ANALOG 2

class Stack
{
  public:
    Stack();
  void push(int value);
  int pop();
  void swap();
  void dup();
  void println();
  private:
  int _sreg[32];
  int _sp;
};

class IO
{
public:
  IO(int pin, unsigned int direction);
  IO(int pin, unsigned int direction, unsigned int mode);
  unsigned int read(void);
  void write(int value);
private:
  int _value;
  int _pin;
  unsigned int _dir;
  unsigned int _mode;
};

void LD(IO& input);
void LD(int input);
void LDN(int input);
void LDN(IO& input);
void ST(int& output);
void ST(IO& output);
void STN(int& output);
void STN(IO& output);
void AND(int input);
void AND(IO& input);
void AND(void);
void ANDN(int input);
void ANDN(IO& input);
//void ANDN(void);
void OR(int input);
void OR(IO& input);
void OR(void);
void ORN(int input);
void ORN(IO& input);
//void ORN(void);
void XOR(int input);
void XOR(IO& input);
void XOR(void);
void XORN(int input);
void XORN(IO& input);
void XORN(void);
void ADD(int input);
void ADD(IO& input);
void ADD(void);
void SUB(int input);
void SUB(IO& input);
void SUB(void);
void MUL(int input);
void MUL(IO& input);
void MUL(void);
void DIV(int input);
void DIV(IO& input);
void DIV(void);
void TON(unsigned long &timerState, unsigned long timerPeriod);
void TP(unsigned long &timerState, unsigned long timerPeriod);
void TOF(unsigned long &timerState, unsigned long timerPeriod);
void TC(unsigned long &timer1State, unsigned long timer1Period, unsigned long &timer2State, unsigned long timer2Period);
void GT(int input);
void GT(IO& input);
void GT(void);
void LT(int input);
void LT(IO& input);
void LT(void);
void GE(int input);
void GE(IO& input);
void GE(void);
void LE(int input);
void LE(IO& input);
void LE(void);
void S(int& output);
void S(IO& output);
void R(int& output);
void R(IO& output);

void DUP();
void SWP();

class Counter
{
  public:
    Counter(unsigned int presetValue);
    //Counter(unsigned int presetValue, unsigned int direction);
    void up();
    void down();
    void preset();
    void reset();
    unsigned int V; //value
    unsigned int P; //preset
    unsigned int D; //done
    unsigned int overflow;
    unsigned int underflow;
  private:
    unsigned int _ctUpEdge;
	  unsigned int _ctDownEdge;
};

class Shift
{
  public:
    Shift();
	Shift(unsigned int sreg);
	unsigned int bitValue(unsigned int bitno);
	unsigned int value();
	void reset();
	void inputBit();
	void shiftLeft();
	void shiftRight();
  private:
    unsigned int _srLeftEdge;
    unsigned int _srRightEdge;
	unsigned int _sreg;
	unsigned int _inbit;
};
#endif
