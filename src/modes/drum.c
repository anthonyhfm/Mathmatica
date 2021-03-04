#include "modes/drum.h"

const u8 colors[4][3] = 
{
    {63, 63, 0}, 
    {63, 20, 20}, 
    {20, 20, 63}, 
    {20, 63, 20}
};

void drum_press(u8 p, u8 v)
{
    if(translate_to_drum(p) > 35 && translate_to_drum(p) < 36 + 16)
    {
        if(v)
            rgb_out(p, 0, 63, 0);
        else
            rgb_out(p, colors[0][0], colors[0][1], colors[0][2]);
    }
    else if(translate_to_drum(p) > 51 && translate_to_drum(p) < 52 + 16)
    {
        if(v)
            rgb_out(p, 0, 63, 0);
        else
            rgb_out(p, colors[1][0], colors[1][1], colors[1][2]);
    }
    else if(translate_to_drum(p) > 67 && translate_to_drum(p) < 68 + 16)
    {
        if(v)
            rgb_out(p, 0, 63, 0);
        else
            rgb_out(p, colors[2][0], colors[2][1], colors[2][2]);
    }
    else if(translate_to_drum(p) > 83 && translate_to_drum(p) < 84 + 16)
    {
        if(v)
            rgb_out(p, 0, 63, 0);
        else
            rgb_out(p, colors[3][0], colors[3][1], colors[3][2]);
    }
    else
    {
        if(p == 80) return;

        if(v)
            rgb_out(p, 0, 63, 0);
        else
            rgb_out(p, 0, 0, 0);
    }
}

void drum_init()
{

    for(int i = 0; i < 16; i++)
    {
        rgb_out(translate_to_prog(i + 36), colors[0][0], colors[0][1], colors[0][2]);

        rgb_out(translate_to_prog(i + 52), colors[1][0], colors[1][1], colors[1][2]);

        rgb_out(translate_to_prog(i + 68), colors[2][0], colors[2][1], colors[2][2]);

        rgb_out(translate_to_prog(i + 84), colors[3][0], colors[3][1], colors[3][2]);
    }

    

}

void drum_surface_event(u8 p, u8 v, u8 x, u8 y)
{
    if(v)
    {
        if(p == 0)
        {
            update(mode_setup);
            return;
        }
        v = 127;


    }

    drum_press(p, v);

    midi_out(translate_to_drum(p), v);
}

void drum_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v)
{
    
}

void drum_timer_event() {}