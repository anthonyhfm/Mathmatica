#include "modes/step.h"

u8 step_screen[100] = {};

u8 step_ticking = 0;

int tick = 0;
double tick_1 = 0;

void step_init()
{
    rgb_out(99, step_r, step_g, step_b);

    rgb_out(10, 63, 0, 0);
}

u8 lines[8][8] = 
{
    {11, 21, 31, 41, 51, 61, 71, 81},
    {12, 22, 32, 42, 52, 62, 72, 82},
    {13, 23, 33, 43, 53, 63, 73, 83},
    {14, 24, 34, 44, 54, 64, 74, 84},
    {15, 25, 35, 45, 55, 65, 75, 85},
    {16, 26, 36, 46, 56, 66, 76, 86},
    {17, 27, 37, 47, 57, 67, 77, 87},
    {18, 28, 38, 48, 58, 68, 78, 88}
};

void step_timer_event()
{
    for(int i = 0; i < 100; i++) if(step_screen[i] == 1) rgb_out(i, 0, step_screen[i] * 63, 0); else if(step_screen[i] == 2) {step_screen[i] = 0; rgb_out(i, 0, 0, 0);}

    if(!step_ticking) return;
    
    tick_1 += 0.002;

    tick = tick_1;

    for(int i = 0; i < 8; i++) rgb_out(lines[tick][i], step_r, step_g, step_b);

    for(int i = 0; i < 8; i++) if(tick >= 8) rgb_out(lines[8][i], 0, 0, 0);
    for(int i = 0; i < 8; i++) rgb_out(lines[tick - 1][i], 0, 0, 0);
    

    if(tick >= 8) tick_1 = 0;
}

void step_surface_event(u8 p, u8 v, u8 x, u8 y)
{
    if(v)
    {
        if(p == 0)
        {
            update(mode_setup);
            return;
        }
        else if(p == 10)
        {
            step_ticking = (step_ticking)? 0 : 1;

            if(step_ticking)
                rgb_out(10, 0, 63, 0);
            else
                rgb_out(10, 63, 0, 0);
        }
    }

    if(x >= 1 && x <= 8 && y >= 1 && y <= 8)
    {
        if(v)
        {
            if(step_screen[p] != 1)
            {
                step_screen[p] = 1;
            }
            else
            {
                step_screen[p] = 2;
            }
        }
    }

}

void step_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v)
{

}