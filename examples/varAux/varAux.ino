#include <libPlc.h>
/*
 * libPlc example logic example using auxiliar variable
 * solve D1 = (S1 AND S2) OR (S1 AND S3) OR (S2 AND S3)
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
  int aux1; // auxiliar variable for storing intermediary results
  LD(S1);
  AND(S2);
  ST(aux1);
  LD(S1);
  AND(S3);
  OR(aux1);
  ST(aux1);
  LD(S2);
  AND(S3);
  OR(aux1);
  ST(D1);
}
