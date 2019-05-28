#include <libPlc.h>
/*
 * libPlc timers example
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

unsigned long T1,T2,T3,T4a,T4b; // One for each timer used, 2 for periodic

void setup() {
  // nothing to do here
}

void loop() {
  // Read S1 and apply the 4 different timers
 LD(S1);
 DUP(); 
 DUP();
 DUP();        // Here the stack has 4 copies of S1 value
 TON(T1,1000); // apply one through TON (milisseconds delay on rise)
 ST(D1);       // to D1
 TOF(T2,1000); // apply one through TOF (milisseconds delay on rise)
 ST(D2);
 TP(T3,1000); // apply one through TP
 ST(D3);
 TC(T4a,300,T4b,300); // apply one through TON
 ST(D4);
}
