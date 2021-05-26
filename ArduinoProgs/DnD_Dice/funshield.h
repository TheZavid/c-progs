// Funshield constants

#ifndef FUNSHIELD_CONSTANTS_H__
#define FUNSHIELD_CONSTANTS_H__

// convenience constants for switching on/off
constexpr int ON = LOW;
constexpr int OFF = HIGH;

// 7-segs
constexpr int latch_pin = 4;
constexpr int clock_pin = 7;
constexpr int data_pin = 8;

// buzzer
constexpr int beep_pin = 3;

// LEDs
constexpr int led1_pin = 13;
constexpr int led2_pin = 12;
constexpr int led3_pin = 11;
constexpr int led4_pin = 10;

// buttons
constexpr int button1_pin = A1;
constexpr int button2_pin = A2;
constexpr int button3_pin = A3;

// trimr
constexpr int trimr_pin = A0;

// digits
constexpr int digits[11] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xff };
constexpr int digit_muxpos[4] = { 0x01, 0x02, 0x04, 0x08 };

#define fastDigitalWrite(pin, value) do{\
  unsigned char __v__=value;\
  constexpr unsigned char __port__=-1+3*(((unsigned char[]){4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3})[pin]);\
  constexpr unsigned char __bit__=((unsigned char[]){0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5})[pin];\
  asm volatile("	sbrc	%2, 0\n"\
               "	sbi	%0, %1\n"\
               "	sbrs	%2, 0\n"\
               "	cbi	%0, %1\n" : : "i"(__port__), "i"(__bit__), "r" (__v__));\  
}while(0)

#define constDigitalWrite(pin, value) do{\
  constexpr unsigned char __v__=value;\
  constexpr unsigned char __port__=-1+3*(((unsigned char[]){4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3})[pin]);\
  constexpr unsigned char __bit__=((unsigned char[]){0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5})[pin];\
  if(__v__) asm volatile("        sbi     %0, %1\n" : : "i"(__port__), "i"(__bit__));\
  else      asm volatile("        cbi     %0, %1\n" : : "i"(__port__), "i"(__bit__));\
}while(0)

inline void slowDigitalWriteFn(unsigned char a, unsigned char b) {digitalWrite(a,b);}

#define digitalWrite(a,b) fastDigitalWrite(a,b)
#define slowDigitalWrite(a,b) slowDigitalWriteFn(a,b)

/* In your code, add
 *
 *  #ifndef slowDigitalWrite
 *    #define slowDigitalWrite(a,b) digitalWrite(a,b)
 *    #define constDigitalWrite(a,b) digitalWrite(a,b)
 *  #endif
 *
 * right after #include "funshield.h" to maintain compatibility with ReCodex. Note that
 * you have to use slowDigitalWrite() whenever the pin value is not a constant known at
 * the compile time. For example for(i=0; i<4; i++) slowDigitalWrite(led[i],1);
 *
 * The constDigitalWrite() is 2 times as fast as fastDigitalWrite() (i.e. our new
 * digitalWrite()) but it requires the value to be constant as well.
 *
 * See https://www.microcontrollertips.com/delay-i-o-arduino-functions-vs-coding-mcu/
 * if you are interested how inefficiently slowDigitalWrite() is implemented. 
 */


#endif
