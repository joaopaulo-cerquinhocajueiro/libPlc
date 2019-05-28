#include <libPlc.h>
/*
 * libPlc using S (set) and R (reset)
 * also implements a 3-state machine
 * J. P. C. Cajueiro, 2015
 * Uses Multi-Function Shield
 */

// Inputs buttons connected to ground with pull-up resistor
IO S1(A1,INPUT,INVERTED); 
IO S2(A2,INPUT,INVERTED);
IO S3(A3,INPUT,INVERTED);

int oldS3; // a copy of S3 for edge detection

// Output leds connected to VCC, light up when LOW
IO D1(13,OUTPUT,INVERTED);
IO D2(12,OUTPUT,INVERTED);
IO D3(11,OUTPUT,INVERTED);
IO D4(10,OUTPUT,INVERTED);

// D2, D3 and D4 are states of a state machine
// require copies for avoiding errors when defining new state
int newD2=1; 
int newD3=0;
int newD4=0;

void setup() {
  // using S and R is good to define an initial value
  // for the outputs
  LD(1);      // load a literal 1 in the stack
  R(D1);      // clear D1 R
  LD(newD2);
  ST(D2);      // and set D2 with R
  LD(newD3);
  ST(D3);      // and set D2 with R
  LD(newD4);
  ST(D4);      // and set D2 with R
  

  LD(S3);
  ST(oldS3); //get a initial value of S3
}

void loop() {
  //////// Set with S1, reset with S2 ////////
  LD(S1); // if S1 pressed
  S(D1);  // set D1
  LD(S2); // if s2 pressed
  R(D1);  // reset D1

  //////// Rise detector ////////
  LD(S3);
  DUP();       // duplicate S3
  ANDN(oldS3); // if S3 is 1 and oldS3 is 0, it is an rise
  SWP();       // swap the top of the stack
  ST(oldS3);   // save the duplicated S3
  
  //////// Define new state ////////
  DUP();    // make 2 copies of the detected rise
  DUP();
  AND(D2);  // if rise and state is D2,
  DUP();
  R(newD2); // new state is D3
  S(newD3);
  AND(D3);  // if rise and state is D2,
  DUP();
  R(newD3); // new state is D4
  S(newD4);
  AND(D4);  // if rise and state is D2,
  DUP();
  R(newD4); // new state is D2
  S(newD2);
 
  //////// Update the state ////////
  LD(newD2);
  ST(D2);
  LD(newD3);
  ST(D3);
  LD(newD4);
  ST(D4);
}