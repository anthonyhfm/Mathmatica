#include "modes/chord.h"

u8 chord_shift = 0;

void bank_press(p, v)
{
    if(v)
    {
        rgb_out(p, 32, 32, 32);
    }
    else
    {
        rgb_out(p, 8, 8, 8);
    }
}

void chord_init()
{
    rgb_out(99, chord_r, chord_g, chord_b);

    for(int i = 0; i < 5; i++) rgb_out(81 + i, 32, 15, 63);
    for(int i = 0; i < 5; i++) rgb_out(71 + i, 5, 5, 63);
    for(int i = 0; i < 5; i++) rgb_out(61 + i, 5, 5, 63);
    for(int i = 0; i < 5; i++) rgb_out(51 + i, 36, 0, 63);
    for(int i = 0; i < 5; i++) rgb_out(41 + i, 36, 0, 63);
    for(int i = 0; i < 5; i++) rgb_out(31 + i, 5, 5, 63);
    for(int i = 0; i < 5; i++) rgb_out(21 + i, 10, 63, 10);
    for(int i = 0; i < 5; i++) rgb_out(11 + i, 32, 15, 63);

    for(int i = 0; i < 6; i++) rgb_out(26 + (i * 10), 63, 16, 0);
    for(int i = 0; i < 2; i++) rgb_out(16 + (i * 70), 63, 32, 16);

    for(int i = 0; i < 7; i++) rgb_out(87 - (i * 10), 8, 8, 8);
    for(int i = 0; i < 7; i++) rgb_out(88 - (i * 10), 8, 8, 8);
    rgb_out(17, 63, 0, 16);
    rgb_out(18, 16, 63, 16);

    rgb_out(80, 32, 32, 32);
    
}

void chord_surface_event(u8 p, u8 v, u8 x, u8 y)
{
    if(v)
    {
        if(p == 0)
        {
            update(mode_setup);
            return;
        }

        if(p == 96 && chord_shift)
        {
            update(mode_scale);
            scale_returnto = mode_chord;
            chord_shift = 0;
        }
    }

    if(x >= 7 && x <= 8 && y >= 2 && y <= 8) bank_press(p, v);

    if(p == 80)
    {
        if(v) chord_shift = 1; else chord_shift = 0;

        if(chord_shift)
        {
            rgb_out(80, 63, 63, 63);
            rgb_out(96, 63, 63, 63);
        }
        else
        {
            rgb_out(80, 32, 32, 32);
            rgb_out(96, 0, 0, 0);
        }
    }
        
    
}


void chord_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) { }
void chord_timer_event() { }