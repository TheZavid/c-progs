#include "funshield.h"


struct Button{
        long deadline;
        unsigned char pin;
};


unsigned long first_press = 1000000; // 1 second
unsigned long latter_press = 300000; // 300 ms
Button button_A, button_B, button_C;
bool stopped = true, lapped = false;
long anchor = 0;
long cur_time = 0; // actual time
int mcsec = 0, sec = 0; // what is going to be displayed
unsigned long max_time = 1000000000; // 1 thousand seconds in micros


inline long duration(long now, long then) {return (now-then);}


void
init(Button& b, int which)
{
        b.pin = which;
        pinMode(which,INPUT);
}


int
get_pulse(Button& b)
{
        if(digitalRead(b.pin) == OFF) {
                return 0;
        }
        long now = micros();
        if (duration(now, b.deadline) > 0) {
                b.deadline = now + latter_press;
                return 1;
        } else {return 0;}
}


/* Write a decimal number between 0 and 9 to one of the 4 digits of the display */
void
write_number_to_segment(int segment, int value)
{
        digitalWrite(latch_pin,LOW); // set to low to make a rising edge later
        shiftOut(data_pin, clock_pin, MSBFIRST, value);
        shiftOut(data_pin, clock_pin, MSBFIRST, segment);
        digitalWrite(latch_pin,HIGH); // create rising edge which writes our data
}


inline long get_sec () {return (cur_time / 1000000);} // divide by million to get seconds
inline long get_mcsec () {return ((cur_time / 100000) % 10);} // to get 0.1 precisions

void
update_to_display()
{
        sec = get_sec();
        mcsec = get_mcsec();
}

void
display_curtime()
{
        write_number_to_segment(digit_muxpos[3], digits[mcsec]);
        write_number_to_segment(digit_muxpos[2], digits[sec % 10] & 0x7f); // by bitwise operation we turn on decimal point
        int tmpsec = sec / 10;
        int i = 1;
        while (tmpsec > 0) {
                write_number_to_segment(digit_muxpos[i], digits[tmpsec % 10]);
                tmpsec /= 10;
                i--;
        }
}


void
setup()
{
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
        if (!stopped)
                cur_time = micros() - anchor;
        if (!lapped)
                update_to_display();
        if (get_pulse(button_A) && !lapped) {
                stopped = !stopped;
                anchor = micros() - cur_time; // update anchor to work for present time (last anchor was set non zero time ago)
        }
        if (get_pulse(button_B) && !stopped)
                lapped = !lapped;
        if (get_pulse(button_C) && stopped)
                cur_time = 0;
        display_curtime();
}
