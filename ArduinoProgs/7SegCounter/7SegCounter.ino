#include "funshield.h"


enum ButtonState {UP, DOWN};
struct Button{
        long deadline;
        ButtonState state;
        unsigned char pin;
        int modifier;
};
const unsigned char led[]={led4_pin,led3_pin,led2_pin,led1_pin};
const int nleds = sizeof (led) / sizeof (led[0]);
const int limit = 10000;

unsigned long first_press = 1000000; // 1 second
unsigned long latter_press = 300000; // 300 ms
Button button_A, button_B, button_C;
int cur_number;
int cur_digit; // which digit we use


inline long duration(long now, long then) {return (now-then);}


void
init(Button& b, int which)
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
                        } else {return 0;}
        }
}


void
modify_curn(int modifier)
{
        // we need to add a correct power of ten
        for (int i = 0; i < cur_digit; i++)
                modifier *= 10;

        int tmp = cur_number + modifier;

        while (tmp < 0)
                tmp = limit + tmp;

        cur_number = tmp % limit;
}



/* Write a decimal number between 0 and 9 to one of the 4 digits of the display */
void
write_number_to_segment(int segment, int value)
{
        digitalWrite(latch_pin,LOW); // set to low to make a rising edge later
        shiftOut(data_pin, clock_pin, MSBFIRST, digits[value]);
        shiftOut(data_pin, clock_pin, MSBFIRST, digit_muxpos[3-segment] );
        digitalWrite(latch_pin,HIGH); // create rising edge which writes our data
}


void
display_curn()
{
        int decd;
        int cpn = cur_number;

        // we get the digit which we should display
        for (int c = 0; c < cur_digit; c++)
                cpn /= 10;
        decd = cpn % 10;

        write_number_to_segment(cur_digit, decd);
}


void
setup()
{
        // init all LEDs
        for(int i = 0; i < nleds; i++) {
                pinMode(led[i], OUTPUT);
                digitalWrite(led[i],OFF);
        }
        init(button_A, button1_pin);
        init(button_B, button2_pin);
        init(button_C, button3_pin);
        pinMode(latch_pin,OUTPUT);
        pinMode(clock_pin,OUTPUT);
        pinMode(data_pin,OUTPUT);
}


void
loop()
{
        if (get_pulse(button_A))
                modify_curn(1);
        if (get_pulse(button_B))
                modify_curn(-1);
        if (get_pulse(button_C))
                cur_digit = (cur_digit + 1) % 4;
        display_curn();
}
