#include <libPlc.h>

/*
 * libPlc logic functions example
 * J. P. C. Cajueiro, 2015
 * Uses Multi-Function Shield
 */

// Inputs buttons connected to ground with pull-up resistor
IO S1(A1,INPUT,INVERTED); 
IO S2(A2,INPUT,INVERTED);
IO S3(A3,INPUT,INVERTED);

// Output leds connected to VCC, light up when LOW
IO D1(13,OUTPUT,INVERTED);
IO D2(12,OUTPUT,INVERTED);
IO D3(11,OUTPUT,INVERTED);
IO D4(10,OUTPUT,INVERTED);

void setup() {
  // nothing to do here
}

void loop() {
	// D1 = S1 AND S2
	LD(S1); 
	AND(S2);
	ST(D1);
	// D2 = NOT(S1 OR S2)
	LD(S1);
	OR(S2);
	STN(D2);
	// D3 = S1 XOR S2
	LD(S1);
	XOR(S2);
	ST(D3);
	// D4 = S1 XOR NOT(S2) = NOT(S1 XOR S2)
	LD(S1);
	XORN(S2);
	ST(D4);
}
