#include "funshield.h"
#include "input.h"

// map of letter glyphs.... I'd prefer hex
constexpr byte LETTER_GLYPH[] {
    0b10001000,   // A
    0b10000011,   // b
    0b11000110,   // C
    0b10100001,   // d
    0b10000110,   // E
    0b10001110,   // F
    0b10000010,   // G
    0b10001001,   // H
    0b11111001,   // I
    0b11100001,   // J
    0b10000101,   // K
    0b11000111,   // L
    0b11001000,   // M
    0b10101011,   // n
    0b10100011,   // o
    0b10001100,   // P
    0b10011000,   // q
    0b10101111,   // r
    0b10010010,   // S
    0b10000111,   // t
    0b11000001,   // U
    0b11100011,   // v
    0b10000001,   // W
    0b10110110,   // ksi
    0b10010001,   // Y
    0b10100100,   // Z
};
constexpr byte EMPTY_GLYPH = 0xFF; // all 1s means none displayed (reverse logic)    
constexpr int positionsCount = 4; // input here the size of the target display, can hold as much as int does :D
constexpr long scrollingInterval = 300000;
long deadline;
SerialInputHandler input;
char* msg_p; // pointer to the char array which holds message received
byte cur_frame[positionsCount]; // array which holds current frame of animation

// index of the last char of the message, it is 4 if we have not encountered last char yet, its -1 animation is finished
int last_index = positionsCount;
int cur_index = 0; // current index of cur_frame to display


inline long duration(long now, long then) {return (now-then);}


void
modify_cur_msg_p()
{
    msg_p++;
    if (*msg_p == '\0') // current message is terminated
        last_index--;
}


byte
char_to_glyph(char ch)
{
    byte glyph = EMPTY_GLYPH;
    if (isAlpha(ch))
        glyph = LETTER_GLYPH[ ch - (isUpperCase(ch) ? 'A' : 'a') ];
    return glyph;
}


void
modify_cur_frame()
{
    for (int i = 1; i < positionsCount; i++)
        cur_frame[i-1] = cur_frame[i];
    
    cur_frame[positionsCount - 1] = EMPTY_GLYPH;
    // if we still have not encountered last char
    if (last_index == positionsCount) {
        cur_frame[positionsCount - 1] = char_to_glyph(*msg_p);
        modify_cur_msg_p();
    } else {
        last_index--;
        // if we have finished the animation for the current message
        if (last_index < 0) {
            last_index = positionsCount;
            msg_p = (char*)input.getMessage();
        }
    }
}


/** 
 * Show chararcter on given position. If character is not letter, empty glyph is displayed instead.
 * @param ch character to be displayed
 * @param pos position (0 = leftmost)
 */
void
displayChar(byte glyph, byte pos)
{
    digitalWrite(latch_pin, LOW);
    shiftOut(data_pin, clock_pin, MSBFIRST, glyph);
    shiftOut(data_pin, clock_pin, MSBFIRST, 1 << pos);
    digitalWrite(latch_pin, HIGH);
}

// this function assumes that display will finish displaying cur_frame before it's changed i.e. in 300ms
// in case the target display cant do that either increase scrolling interval or add boolean to confirm the function finished cur_frame
void
display_frame()
{
    displayChar(cur_frame[cur_index], byte(cur_index));
    cur_index = (cur_index + 1) % positionsCount;
}


void
setup()
{
    pinMode(latch_pin, OUTPUT);
    pinMode(clock_pin, OUTPUT);
    pinMode(data_pin, OUTPUT);
    
    // set cur_frame to contain only empty glyphs
    for (int i = 0; i < positionsCount; i++)
        cur_frame[i] = EMPTY_GLYPH;

    input.initialize();
    msg_p = (char*)input.getMessage();
    deadline = micros();
}


void 
loop()
{
    input.updateInLoop();
    if (duration(micros(), deadline) >= 0) {
        modify_cur_frame();
        deadline = micros() + scrollingInterval;
    }
    display_frame();
}
