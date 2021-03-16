#include "modes/scale.h"

u8 channel_scale[16] = {21, 22, 23, 24, 25, 26, 27, 28, 11, 12, 13, 14, 15, 16, 17, 18};

u8 finger_set = 4;

u8 chromatic = 1;

u8 scale_scales[16][8] =
{
    {0, 2, 3, 5, 7, 8, 10},
    {0, 2, 4, 5, 7, 9, 11},
    {0, 2, 3, 5, 7, 9, 10},
    {0, 1, 3, 5, 7, 8, 10},
    {0, 2, 4, 5, 7, 9, 10},
    {0, 2, 3, 5, 7, 9, 11},
    {0, 2, 3, 5, 7, 8, 11},
    {0, 2, 3, 4, 5, 7, 9, 10},
    {0, 3, 5, 6, 7, 10},
    {0, 3, 5, 7, 10},
    {0, 2, 3, 6, 7, 8, 11},
    {0, 2, 3, 6, 7, 9, 10},
    {0, 1, 4, 6, 7, 9, 11},
    {1, 3, 5, 6, 7, 11},
    {0, 2, 4, 6, 8, 10},
    {0, 2, 3, 7, 8}
};

u8 roots[12] = 
{
    51, 
    62, 
    52, 
    63, 
    53, 
    54, 
    65, 
    55, 
    66, 
    56, 
    67, 
    57
};

u8 scale_root = 0;

u8 scale_channel = 0;
u8 scale = 0;

void scale_init()
{
    rgb_out(96, 63, 32 >> 2, 0);

    for(int i = 0; i < 16; i++) rgb_out(channel_scale[i], 63 >> 2, 63 >> 2, 16 >> 2);
    rgb_out(channel_scale[scale_channel], 63, 63, 16);

    for(int i = 0; i < 16; i++) rgb_out(channel_scale[i] + 20, 17 >> 2, 32 >> 2, 63 >> 2);
    rgb_out(channel_scale[scale] + 20, 63, 63, 46);

    for(int i = 0; i < 12; i++) rgb_out(roots[i], 16, 16, 16);

    if(!chromatic)
    {
        for(int i = 0; i < 5; i++) rgb_out(81 + i, 63, 16, 0);
        rgb_out(81 + finger_set, 63, 63, 32);
        rgb_out(88, 16, 63, 16);
    }
    else
    {
        for(int i = 0; i < 5; i++) rgb_out(81 + i, 16, 16, 16);
        rgb_out(81 + finger_set, 63, 63, 32);
        rgb_out(88, 63, 0, 0);
    }

    rgb_out(roots[scale_root], 63, 0, 32);
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
        if(p == 96)
        {
            update(scale_returnto);
            return;
        }
        else if(p >= 81 && p <= 85)
        {
            finger_set = p - 81;
            refresh();
        }
        else if(p == 88)
        {
            chromatic = (chromatic)? 0 : 1;
            refresh();
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

        for(int i = 0; i < 12; i++) // Root Notes
        {
            if(p == roots[i])
            {
                scale_root = i;
                refresh();
            }
        }
    }
}

void scale_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v)
{

}