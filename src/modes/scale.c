#include "modes/scale.h"

u8 channel_scale[16] = {21, 22, 23, 24, 25, 26, 27, 28, 11, 12, 13, 14, 15, 16, 17, 18};

u8 roots[12] = {51, 52, 53, 54, 55, 56, 57, 62, 63, 65, 66, 67};

u8 scale_channel = 0;
u8 scale = 0;

u8 fucking_reverser[2] = {2, 1};

void scale_init()
{
    for(int i = 0; i < 16; i++) rgb_out(channel_scale[i], 63 >> 2, 63 >> 2, 16 >> 2);
    rgb_out(channel_scale[scale_channel], 63, 63, 16);

    for(int i = 0; i < 16; i++) rgb_out(channel_scale[i] + 20, 17 >> 2, 17 >> 2, 63 >> 2);
    rgb_out(channel_scale[scale] + 20, 63, 63, 32);

    for(int i = 0; i < 12; i++) rgb_out(roots[i], 16, 16, 16);
}

void scale_timer_event()
{

}

void scale_surface_event(u8 p, u8 v, u8 x, u8 y)
{
    if(v)
    {
        if(p == 0)
        {
            update(scale_returnto);
            return;
        }

        for(int i = 0; i < 16; i++)
        {
            if(p == channel_scale[i])
            {
                scale_channel = i;
                refresh();
                return;
            }

            if(p == channel_scale[i] + 20)
            {
                scale = i;
                refresh();
                return;
            }
        }
    }
}

void scale_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v)
{

}