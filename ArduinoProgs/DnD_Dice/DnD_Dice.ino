#include "funshield.h"


enum ButtonState {UP, DOWN};
struct Button{
        long deadline;
        ButtonState state;
        unsigned char pin;
};

struct Display {
    byte cur_frame[4];
    char cur_step;
    long deadline;
};
unsigned long first_press = 1000000; // 1 second
unsigned long latter_press = 70000; // 300 ms
long t_disp_on = 60; // time individual column is on
long t_disp_off = 160; // time individual column is off
char throws[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // choices for throws
char dices[] = {4, 6, 8, 10, 12, 20, 100}; // choices for dices

const unsigned char font[]={0b11111100,0b01100000,0b11011010,0b11110010,0b01100110,
                            0b10110110,0b10111110,0b11100000,0b11111110,0b11110110}; // font for digits in Lsb where 1 is on, 0 is off

char cur_throw, cur_dice;
bool config_mode = true;
int cur_combo;
byte d_char = 0b01111010; // letter 'd'
Button button_A, button_B, button_C;
Display display;


inline long duration(long now, long then) {return (now-then);}


void
init_button(Button& b, int which)
{
        b.pin = which;
        b.state = UP;
        pinMode(which,INPUT);
}

int
get_pulse(Button& b)
{
        if(digitalRead(b.pin) == OFF) {
                b.state = UP;
                return 0;
        }
        long now = micros();
        switch(b.state)
        {
                case UP: // this represents a change from DOWN to UP
                        b.deadline = now + first_press;
                        b.state = DOWN;
                        return 1;
                case DOWN: // this represent button hold
                        if (duration(now, b.deadline) > 0) {
                                b.deadline = now + latter_press;
                                return 1;
                        } else return 0;
        }
}


int
throw_dice()
{
    int output = random(1, 101);
    while (output > dices[cur_dice])
        output = random(1, 101);
    return output;
}

void
simulate_throwing()
{
    randomSeed(button_A.deadline);
    cur_combo = 0;
    for (size_t i=0; i < throws[cur_throw]; i++)
        cur_combo += throw_dice();
}


void
modify_cur_frame()
{
    if(config_mode){
        display.cur_frame[0] = font[throws[cur_throw]];
        display.cur_frame[1] = d_char;
        if (dices[cur_dice] < 10) {
            display.cur_frame[2] = font[dices[cur_dice]];
            display.cur_frame[3] = 0;
        } else {
            display.cur_frame[2] = font[(dices[cur_dice] / 10) % 10];
            display.cur_frame[3] = font[dices[cur_dice] % 10];
        }
    } else {
        int tmp = cur_combo;
        int i = 3;
        while (tmp > 0) {
            display.cur_frame[i--] = font[tmp % 10];
            tmp /= 10;
        }
        while (i >= 0)
            display.cur_frame[i--] = 0;
    }
}

inline void shift_out8(unsigned char data)
{
    for(signed char i=7; i>=0; i--,data>>=1){
        fastDigitalWrite(data_pin,data&1);  /* set up the data bit */ // fast digital write is used instead, help get rid of the "blinking"
        constDigitalWrite(clock_pin,HIGH);  /* upon clock rising edge, the 74HC595 will shift the data bit in */
        constDigitalWrite(clock_pin,LOW);
    }
}

void
shift_out(unsigned int bit_pattern)
{
    shift_out8(bit_pattern);
    shift_out8(bit_pattern>>8);  
    constDigitalWrite(latch_pin,HIGH); /* upon latch_pin rising edge, both 74HC595s will instantly change its outputs to */
    constDigitalWrite(latch_pin,LOW);  /* its internal value that we've just shifted in */
}


// 0 column is the leftmost digit
void
disp_7seg(unsigned char column, unsigned char glowing_leds_bitmask)
{
    shift_out(1<<(8+4+(3 - column)) | (0xFF^glowing_leds_bitmask));
}

int
display_cur_frame()
{
    if (duration(micros(), display.deadline)) {
        if (display.cur_step < 4) {
            disp_7seg(display.cur_step, display.cur_frame[display.cur_step]);
            display.cur_step++;
            display.deadline += t_disp_on;
        } else {
            display.cur_step = 0;
            display.deadline += t_disp_off;
            shift_out(0);
            return 1;
        }
    }
    return 0;
}

void
setup()
{
        init_button(button_A, button1_pin);
        init_button(button_B, button2_pin);
        init_button(button_C, button3_pin);
        pinMode(latch_pin,OUTPUT);
        pinMode(clock_pin,OUTPUT);
        pinMode(data_pin,OUTPUT);
        constDigitalWrite(clock_pin, LOW);
        constDigitalWrite(latch_pin, LOW);
        for (int i = 0; i < 4; i++)
            display.cur_frame[i] = 0;
}


void
loop()
{
    if (get_pulse(button_A)) {
        if (config_mode) config_mode = false;
        simulate_throwing();
    }
    if (get_pulse(button_B)) {
        if (!config_mode)
            config_mode = true;
        else
            cur_throw = (cur_throw + 1) % 9;
    }
    if (get_pulse(button_C)) {
        if (!config_mode)
            config_mode = true;
        else
            cur_dice = (cur_dice + 1) % 7;
    }
    if(display_cur_frame())
        modify_cur_frame();    
}
