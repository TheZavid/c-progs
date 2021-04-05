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
const int limit = pow(2, nleds);
// change modifiers according to need
const int Abmodifier = 1;
const int Bbmodifier = -1;

unsigned long first_press = 1000000; // 1 second
unsigned long latter_press = 300000; // 300 ms
Button button_A, button_B;
int cur_number = 0;



inline long duration(long now, long then) {return (now-then);}


void
init(Button& b, int which, int modifier)
{
        b.pin = which;
        b.state = UP;
        b.modifier = modifier;
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
        int tmp = cur_number + modifier;
        // I use while loop for cases when modifier exceeds the limit
        // for example modifier = -32 and limit = 16
        while (tmp < 0)
                tmp = limit + tmp;
        cur_number = tmp % limit;
}


void
display_curn()
{
        int bind;
        // I perform a series of  shifts to "get" binary repr of a cur_number
        // nleds represent the digits we hold in a number
        for (int c = 0; c < nleds; c++) {
                bind = cur_number >> c;

                // I use mask to get the value of LSb
                if (bind & 1)
                        digitalWrite(led[c], ON);
                else
                        digitalWrite(led[c], OFF);
        }
}


void
setup()
{
        Serial.begin(9600);
        // init all LEDs
        for(int i = 0; i < nleds; i++) {
                pinMode(led[i], OUTPUT);
                digitalWrite(led[i],OFF);
        }
        init(button_A, button1_pin, Abmodifier);
        init(button_B, button2_pin, Bbmodifier);
}


void
loop()
{
        if (get_pulse(button_A)) {
                modify_curn(button_A.modifier);
                Serial.println(cur_number);
        }
        if (get_pulse(button_B)) {
                modify_curn(button_B.modifier);
                Serial.println(cur_number);
        }
        display_curn();
}
