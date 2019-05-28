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


#include "Arduino.h"
#include "libPlc.h"

extern unsigned int scanValue = 0;

Stack stack;

// Read an IO input
void LD(IO& input) {
	extern Stack stack;
	stack.push(input.read());
}

// Read an auxiliary input (variable supplied as integer)
void LD(int input) {
	extern Stack stack;
	stack.push(input);
}


// Read an negated auxiliary input (variable supplied as integer)
void LDN(int input) {
	extern Stack stack;
	stack.push(!input);
}

// Read an negated IO input
void LDN(IO& input) {
	extern Stack stack;
	stack.push(!input.read());
}

// Output to an auxiliary variable
void ST(int& output) {
	extern Stack stack;
	output=stack.pop();
}

// Output to an IO
void ST(IO& output) {
	extern Stack stack;
	output.write(stack.pop());
}

// Inverted output to an auxiliary variable
void STN(int& output) {
	extern Stack stack;
	output=!stack.pop();
}

// Inverted output to an IO
void STN(IO& output) {
	extern Stack stack;
	output.write(!stack.pop());
}

// AND scanValue with input (IO input)
void AND(IO& input) {
	extern Stack stack;
	stack.push(stack.pop() && input.read());
}

// AND scanValue with auxiliary variable (variable supplied as unsigned integer)
void AND(int input) {
	extern Stack stack;
	stack.push(stack.pop() && input);
}

// AND two values on top of stack
void AND(void) {
	extern Stack stack;
	int a = stack.pop();
	int b = stack.pop();
	stack.push(a && b);
}

// AND scanValue with inverted input (IO input)
void ANDN(IO& input) {
	extern Stack stack;
	stack.push(stack.pop() && !input.read());
}

// AND scanValue with inverted auxiliary variable (variable supplied as unsigned integer)
void ANDN(int input) {
	extern Stack stack;
	stack.push(stack.pop() && !input);
}


// OR scanValue with input (IO input)
void OR(IO& input) {
	extern Stack stack;
	stack.push(stack.pop() || input.read());
}

// OR scanValue with auxiliary variable (variable supplied as unsigned integer)
void OR(int input) {
	extern Stack stack;
	stack.push(stack.pop() || input);
}

// OR two values on top of stack
void OR(void) {
	extern Stack stack;
	int a = stack.pop();
	int b = stack.pop();
	stack.push(a || b);
}

// OR scanValue with inverted input (IO input)
void ORN(IO& input) {
	extern Stack stack;
	stack.push(stack.pop() || !input.read());
}

// OR scanValue with inverted auxiliary variable (variable supplied as unsigned integer)
void ORN(int input) {
	extern Stack stack;
	stack.push(stack.pop() || !input);
}


// XOR scanValue with input (IO input)
void XOR(IO& input) {
	extern Stack stack;
	stack.push(stack.pop() != input.read());
}

// XOR scanValue with auxiliary variable (variable supplied as unsigned integer)
void XOR(int input) {
	extern Stack stack;
	stack.push(stack.pop() != input);
}

// XOR two values on top of stack
void XOR(void) {
	extern Stack stack;
	int a = stack.pop();
	int b = stack.pop();
	stack.push(a != b);
}

// XOR scanValue with inverted input (IO input)
void XORN(IO& input) {
	extern Stack stack;
	stack.push(stack.pop() == input.read());
}

// XOR scanValue with inverted auxiliary variable (variable supplied as unsigned integer)
void XORN(int input) {
	extern Stack stack;
	stack.push(stack.pop() == input);
}

// XNOR two values on top of stack
void XORN(void) {
	extern Stack stack;
	int a = stack.pop();
	int b = stack.pop();
	stack.push(a == b);
}

/////Arithmetic functions///////
// ADD scanValue with input (IO input)
void ADD(IO& input) {
	extern Stack stack;
	stack.push(stack.pop() + input.read());
}

// ADD scanValue with auxiliary variable (variable supplied as unsigned integer)
void ADD(int input) {
	extern Stack stack;
	stack.push(stack.pop() + input);
}

// ADD two values on top of stack
void ADD(void) {
	extern Stack stack;
	int a = stack.pop();
	int b = stack.pop();
	stack.push(a + b);
}

// SUB scanValue with input (IO input)
void SUB(IO& input) {
	extern Stack stack;
	stack.push(stack.pop() - input.read());
}

// SUB scanValue with auxiliary variable (variable supplied as unsigned integer)
void SUB(int input) {
	extern Stack stack;
	stack.push(stack.pop() - input);
}

// SUB two values on top of stack
void SUB(void) {
	extern Stack stack;
	int a = stack.pop();
	int b = stack.pop();
	stack.push(a - b);
}

// MUL scanValue with input (IO input)
void MUL(IO& input) {
	extern Stack stack;
	stack.push(stack.pop() * input.read());
}

// MUL scanValue with auxiliary variable (variable supplied as unsigned integer)
void MUL(int input) {
	extern Stack stack;
	stack.push(stack.pop() * input);
}

// MUL two values on top of stack
void MUL(void) {
	extern Stack stack;
	int a = stack.pop();
	int b = stack.pop();
	stack.push(a * b);
}

// DIV scanValue with input (IO input)
void DIV(IO& input) {
	extern Stack stack;
	stack.push(stack.pop() / input.read());
}

// DIV scanValue with auxiliary variable (variable supplied as unsigned integer)
void DIV(int input) {
	extern Stack stack;
	stack.push(stack.pop() / input);
}

// DIV two values on top of stack
void DIV(void) {
	extern Stack stack;
	int a = stack.pop();
	int b = stack.pop();
	stack.push(a / b);
}


/////Timers///////
void TON(unsigned long &timerState, unsigned long timerPeriod) {
	extern Stack stack;
	int scanValue = stack.pop();
	if (scanValue == 0) {									// timer is disabled
		timerState = 0;										// Clear timerState (0 = 'not started')
	}
	else {													// Timer is enabled
		if (timerState == 0) {								// Timer hasn't started counting yet
			timerState = millis();							// Set timerState to current time in milliseconds
			scanValue = 0;									// Result = 'not finished' (0)
		}
		else {												// Timer is active and counting
			if (millis() > (timerState + timerPeriod)) {	// Timer has finished
				scanValue = 1;								// Result = 'finished' (1)
			}
			else {											// Timer has not finished
				scanValue = 0;								// Result = 'not finished' (0)
			}
		}
	}
	stack.push(scanValue);										// Return result (1 = 'finished',
															// 0 = 'not started' / 'not finished')
}

void TP(unsigned long &timerState, unsigned long timerPeriod) {
	extern Stack stack;
	int scanValue=stack.pop();
	if (scanValue && (timerState==0)){
		timerState = millis();
	}
	if ((timerState!=0)){
		if (millis() > (timerState + timerPeriod)){
			if(scanValue==0){
				timerState=0;
			}
			scanValue = 0;
		} else {
			scanValue = 1;
		}
	}




	// if ((scanValue == 0) && (timerState == 0)) {					// timer is either not triggered or finished
	// 	timerState = 0;										// Clear timerState (0 = 'not started')
	// }
	// else {													// Timer is enabled
	// 	if (timerState == 0) {								// Timer hasn't started counting yet
	// 		timerState = millis();							// Set timerState to current time in milliseconds
	// 		scanValue = 0;									// Result = 'not finished' (0)
	// 	}
	// 	else {												// Timer is active and counting
	// 		if (millis() > (timerState + timerPeriod)) {	// Timer has finished
	// 			scanValue = 0;								// Pulse = 'finished' (0)
	// 			timerState = 0;
	// 		}
	// 		else {											// Timer has not finished
	// 			scanValue = 1;								// Pulse = 'Active' (1)
	// 		}
	// 	}
	// }
	stack.push(scanValue);										// Return result (1 = 'finished',
															// 0 = 'not started' / 'not finished')
}

void TOF(unsigned long &timerState, unsigned long timerPeriod) {
	extern Stack stack;
	int scanValue=stack.pop();
	if (scanValue == 0) {									// Timer input is off (scanValue = 0)
		if (timerState == 0) {								// Timer is not started so do nothing
		}
		else {												// Timer is active and counting
			if (millis() > (timerState + timerPeriod)) {	// Timer has finished
				scanValue = 0;								// Result = 'turn-off delay finished' (0)
			}
			else {											// Timer has not finished
				scanValue = 1;								// Result = 'turn-off delay not finished' (1)
			}
		}
	}
	else {													// Timer input is high (scanValue = 1)
		timerState = millis();								// Set timerState to current time in milliseconds
	}
	stack.push(scanValue);										// Return result (1 = 'finished',
															// 0 = 'not started' / 'finished')
}

void TC(unsigned long &timer1State, unsigned long timer1Period, unsigned long &timer2State, unsigned long timer2Period) {
	extern Stack stack;
	int scanValue=stack.pop();
	if (scanValue == 0) {									// Enable input is off (scanValue = 0)
		timer2State = 0;									// Ready to start LOW pulse period when enabled
		timer1State = 1;
	}
	else {													// Enabled
		if (timer2State == 0) {								// Low pulse Active
			if (timer1State == 1) {							// LOW pulse period starting
				timer1State = millis();						// Set timerState to current time in milliseconds
			}
			else if (millis() > (timer1State + timer1Period)) {	// Low pulse period has finished
				timer1State = 0;	
				timer2State = 1;							// Ready to start HIGH pulse period
			}
			scanValue = 0;									// Result = 'Pulse LOW' (0)
		}
		if (timer1State == 0) {								// High pulse Active
			if (timer2State == 1) {							// HIGH pulse period starting
				timer2State = millis();						// Set timerState to current time in milliseconds
			}
			else if (millis() > (timer2State + timer2Period)) {	// High pulse has finished
				timer2State = 0;	
				timer1State = 1;							// Ready to start LOW pulse period
			}
			scanValue = 1;									// Result = 'Pulse HIGH' (1)
		}
	}
	stack.push(scanValue);										// Return result (1 = 'finished',	
}


////////Comparisons//////////
// Test whether scanValue is greater than an analog variable
void GT(int input) {
	extern Stack stack;
	int scanValue=stack.pop();
	scanValue = (scanValue > input)?1:0;
	stack.push(scanValue);
}

// Test whether scanValue is greater than an analog input
void GT(IO& input) {
	extern Stack stack;
	int scanValue=stack.pop();
	scanValue = (scanValue > input.read())?1:0;
	stack.push(scanValue);
}

//Test whether top of stack is greater than second value of stack
void GT(void) {
	extern Stack stack;
	int scanValue = (stack.pop() > stack.pop())?1:0;
	stack.push(scanValue);
}

// Test whether scanValue is less than an analog variable
void LT(int input) {
	extern Stack stack;
	int scanValue=stack.pop();
	scanValue = (scanValue < input)?1:0;
	stack.push(scanValue);
}

// Test whether scanValue is less than an analog input
void LT(IO& input) {
	extern Stack stack;
	int scanValue=stack.pop();
	scanValue = (scanValue < input.read())?1:0;
	stack.push(scanValue);
}

//Test whether top of stack is less than second value of stack
void LT(void) {
	extern Stack stack;
	int scanValue =	(stack.pop() < stack.pop())?1:0;
	stack.push(scanValue);
}

// Test whether scanValue is greater or equal than an analog variable
void GE(int input) {
	extern Stack stack;
	int scanValue=stack.pop();
	scanValue = (scanValue >= input)?1:0;
	stack.push(scanValue);
}

// Test whether scanValue is greater or equal than an analog input
void GE(IO& input) {
	extern Stack stack;
	int scanValue=stack.pop();
	scanValue = (scanValue >= input.read())?1:0;
	stack.push(scanValue);
}

//Test whether top of stack is greater or equal than second value of stack
void GE(void) {
	extern Stack stack;
	int scanValue = (stack.pop() >= stack.pop())?1:0;
	stack.push(scanValue);
}

// Test whether scanValue is less or equal than an analog variable
void LE(int input) {
	extern Stack stack;
	int scanValue=stack.pop();
	scanValue = (scanValue <= input)?1:0;
	stack.push(scanValue);
}

// Test whether scanValue is less or equal than an analog input
void LE(IO& input) {
	extern Stack stack;
	int scanValue=stack.pop();
	scanValue = (scanValue <= input.read())?1:0;
	stack.push(scanValue);
}

//Test whether top of stack is less or equal than second value of stack
void LE(void) {
	extern Stack stack;
	int scanValue =	(stack.pop() <= stack.pop())?1:0;
	stack.push(scanValue);
}

///////Set and reset/////
// Set a latched variable
void S(int& output) {
	extern Stack stack;
	if(stack.pop())
		output=true;
}

// Set a latched output IO
void S(IO& output) {
	extern Stack stack;
	if(stack.pop())
		output.write(true);
}

// Reset (clear) a latched variable
void R(int& output) {
	extern Stack stack;
	if(stack.pop())
		output=false;
}

// Reset (clear) a latched output IO
void R(IO& output) {
	extern Stack stack;
	if(stack.pop())
		output.write(false);
}

// Up, down, or up-down counter
Counter::Counter(unsigned int pv)	// Counter constructor method
{									// (Default values are for an up counter)
	P = pv;		    				// Set preset value using supplied parameter
	V = 0;			    			// Running count = zero
	D = P==V;					// Up counter upper Q output = 0
	_ctUpEdge = 0;					// Prepare rising edge detect for up counter
	_ctDownEdge = 0;				// Prepare rising edge detect for down counter
	overflow = 0;
	underflow = 0;
}
/*
Counter::Counter(unsigned int pv, unsigned int direction)	// Counter constructor method
{									// (Second parameter sets default direction)
	_pv = pv;						// Set preset value using supplied parameter
	if(direction == 0){				// Set start values for an up counter
		_ct = 0;					// Running count = zero
		_uQ = 0;					// Up counter upper Q output = 0
		_lQ = 1;					// Down counter lower Q output = 1
	}
	else {							// Set start values for a down counter
		_ct = _pv;					// Running count = preset value
		_uQ = 1;					// Up counter upper Q output = 1
		_lQ = 0;					// Down counter lower Q output = 0
	}
	_ctUpEdge = 0;					// Prepare rising edge detect for up counter
	_ctDownEdge = 0;				// Prepare rising edge detect for down counter
}
*/
void Counter::reset()				// Clear counter method
{
	extern Stack stack;
	int scanValue=stack.pop();
	if(scanValue == 1) {			// Enabled if scanValue = 1
		V = 0;  					// Running count = 0
		D = V==P;					// Up counter upper Q output = 0
		overflow = 0;
		underflow = 0;
		_ctUpEdge = 0;				// Prepare rising edge detect for up counter
		_ctDownEdge = 0;			// Prepare rising edge detect for down counter
	}
//	stack.push(scanValue);										// Return result (1 = 'finished',	
}

void Counter::preset()				// Preset counter method
{
	extern Stack stack;
	int scanValue=stack.pop();
	if(scanValue == 1) {			// Enabled if scanValue = 1
		V = P;					// Running count = preset value
		D = 1;					// Up counter upper Q output = 1
		overflow = 0;
		underflow = 0;
		_ctUpEdge = 0;				// Prepare rising edge detect for up counter
		_ctDownEdge = 0;			// Prepare rising edge detect for down counter
	}
//	stack.push(scanValue);										// Return result (1 = 'finished',	
}

void Counter::up()				// Count up method
{
	extern Stack stack;
	int scanValue=stack.pop();
	if (scanValue == 0) {		// clock = 0 so clear counter edge detect
		_ctUpEdge = 0;
	} else if (_ctUpEdge == 0) {						// Clock = 1
		_ctUpEdge = 1;		// Set counter edge
		if (V==9999){
			V=0;
			overflow = 1;
		} else {
			V++;				// Increment count
			overflow = 0;
		}
		D = V==P;
	}
}

void Counter::down()			// Count down method
{
	extern Stack stack;
	int scanValue=stack.pop();
	if (scanValue == 0) {		// clock = 0 so clear counter edge detect
		_ctDownEdge = 0;
	} else if (_ctDownEdge == 0) {						// Clock = 1
		_ctDownEdge = 1;		// Set counter edge
		if (V==0){
			V=10000;
			underflow = 1;
		} else {
			V--;				// Decrement count
			underflow = 0;
		}
		D = V==P;
	}
}

// Shift register
Shift::Shift()						// Shift register constructor method
{									// (Register width = 32 bits)
	_sreg = 0;						// Set  the shift register to zero
	_srLeftEdge = 0;				// Prepare rising edge detect for left shift
	_srRightEdge = 0;				// Prepare rising edge detect for right shift
}

Shift::Shift(unsigned int sreg)	    // Shift register constructor method
{									// (Register width = 32 bits)
	_sreg = sreg;					// Set initial value
	_srLeftEdge = 0;				// Prepare rising edge detect for left shift
	_srRightEdge = 0;				// Prepare rising edge detect for right shift
}

unsigned int Shift::bitValue(unsigned int bitno)	// Read a bit at a specified position
{
	if(bitRead(_sreg, bitno) == 1) {
		scanValue = 1;				// Tested bit = 1
	}
	else {
		scanValue = 0;				// Tested bit = 0
	}
	return(scanValue);				// Return tested bit value
}

unsigned int Shift::value()			// Return the current shift register value
{
	return(_sreg);
}

void Shift::reset()					// Reset the shift register if scanValue = 0
{
	if(scanValue == 1){
		_sreg = 0;					// Set  the shift register to zero
		_srLeftEdge = 0;			// Prepare rising edge detect for left shift
		_srRightEdge = 0;			// Prepare rising edge detect for right shift
		}
}

void Shift::inputBit()				// Set the input bit of the shift register
{
	if (scanValue == 0) {			// If scanValue = 0, clear input bit
		_inbit = 0;
	}
	else {							// Otherwise set the input bit
		_inbit = 1;
	}
}

void Shift::shiftRight()			// Shift right method
{
	if (scanValue == 0) {			// clock = 0 so clear shift right edge detect
		_srRightEdge = 0;
	}
	else {							// Clock = 1
		if (_srRightEdge == 0) {	// Rising edge detected so shift right
			_srRightEdge = 1;		// Set shift right edge detect
			_sreg = _sreg >> 1;		// Shift to the right
			if (_inbit == 1) {		// Shift-in new input bit at LHS
				bitSet(_sreg, 15);
			}
		}
	}
}

void Shift::shiftLeft()				// Shift left method
{
	if (scanValue == 0) {			// clock = 0 so clear shift left edge detect
		_srLeftEdge = 0;
	}
	else {							// Clock = 1
		if (_srLeftEdge == 0) {		// Rising edge detected so shift left
			_srLeftEdge = 1;		// Set shift left edge detect
			_sreg = _sreg << 1;		// Shift to the left
			if (_inbit == 1) {		// Shift-in new input bit at RHS
				bitSet(_sreg, 0);
			}
		}
	}
}

// Single-bit Software Stack
Stack::Stack()						// Stack constructor method
{									// (Register width = 32 bits)
	_sp = 0;						// Set the stack to zero
}

void Stack::push(int value)			// Push value onto the stack
{
	if (_sp<32){
		_sreg[_sp]	= value;
		_sp++;
	}
}

int Stack::pop()					// Pop value from the stack
{
	if (_sp>0){
		_sp--;
		return _sreg[_sp];
	} else {
		return -1;				// if empty stack, return -1
	}
}

void Stack::swap()				// OR scanValue with value Popped from stack method
{
	if(_sp>1){
		int oldTop = _sreg[_sp-1];
		_sreg[_sp-1] = _sreg[_sp-2];
		_sreg[_sp-2] = oldTop;
	}
}

void SWP(){
	stack.swap();
}

void Stack::dup()
{
	if ((_sp>0)&&(_sp<32)){
		_sreg[_sp]	= _sreg[_sp-1];
		_sp++;
	}
}

void DUP(){
	stack.dup();
}

void Stack::println(){
	if(_sp==0){
		Serial.println('-');
	} else {
		for(int i=0;i<_sp;i++){
			Serial.print(_sreg[i]);
			Serial.print('\t');
		}
		Serial.print('\n');		
	}
}

IO::IO(int pin, unsigned int direction, unsigned int mode){
	_pin=pin;
	_dir=direction;
	_mode=mode;
	_value=0;
	pinMode(_pin,_dir);
}

IO::IO(int pin, unsigned int direction){
	_pin=pin;
	_dir=direction;
	_mode=0;
	_value=0;
	pinMode(_pin,_dir);
}

unsigned int IO::read(void){
	if(_dir==INPUT){ 				//if it is an input
		if(_mode==2){ 				//if it is analog
			_value=analogRead(_pin);
		} else if (_mode==1){ 		//if it is inverted digital
			_value=!digitalRead(_pin);
		} else { 					//if it is digital
			_value=digitalRead(_pin);
		}
	}
	return _value;
}

void IO::write(int value){
	if(_dir==OUTPUT){ 				//if it is output
		_value=value; 				//update the internal value
		if(_mode==2){ 				//if it is analog
			analogWrite(_pin,_value/4);
		} else if (_mode==1){ 		//if it is inverted digital
			digitalWrite(_pin,!_value);
		} else { 					//if it is digital
			digitalWrite(_pin,_value);
		}
	}
}
