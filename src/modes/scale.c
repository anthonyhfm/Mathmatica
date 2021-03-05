#include "modes/scale.h"

u8 channel_scale[16] = {21, 22, 23, 24, 25, 26, 27, 28, 11, 12, 13, 14, 15, 16, 17, 18};

u8 finger_set = 4;

u8 chromatic = 0;

u8 roots[12] = {51, 52, 53, 54, 55, 56, 57, 62, 63, 65, 66, 67};
u8 preset_scales[16][7] = 
{
    {52, 63, 54, 55, 66, 67},
    {52, 53, 54, 55, 56, 57},
    {52, 63, 54, 55, 56, 67},
    {62, 63, 54, 55, 66, 67},
    {52, 53, 54, 55, 56, 67},
    {52, 63, 54, 55, 56, 57},
    {52, 63, 54, 55, 66, 57},
    {52, 53, 63, 54, 55, 56, 67},
    {63, 54, 55, 65, 67},
    {63, 54, 55, 67},
    {52, 63, 55, 65, 66, 57},
    {52, 63, 55, 65, 56, 67},
    {62, 53, 55, 65, 56, 57},
    {62, 63, 54, 55, 65, 57},
    {52, 53, 65, 66, 67},
    {52, 63, 55, 66}
};

u8 root = 0;

u8 scale_channel = 0;
u8 scale = 0;

void scale_init()
{
    for(int i = 0; i < 16; i++) rgb_out(channel_scale[i], 63 >> 2, 63 >> 2, 16 >> 2);
    rgb_out(channel_scale[scale_channel], 63, 63, 16);

    for(int i = 0; i < 16; i++) rgb_out(channel_scale[i] + 20, 17 >> 2, 32 >> 2, 63 >> 2);
    rgb_out(channel_scale[scale] + 20, 63, 63, 46);

    for(int i = 0; i < 12; i++) rgb_out(roots[i], 16, 16, 16);


    

    rgb_out(roots[0], 63, 0, 32);

    for(int x = 0; x < 7; x++) rgb_out(preset_scales[scale][x], 17, 32, 63);

    if(chromatic)
    {
        for(int i = 0; i < 5; i++) rgb_out(81 + i, 63, 32, 0);
        rgb_out(81 + finger_set, 63, 63, 32);
        rgb_out(88, 8, 63, 8);
    }
    else
    {
        for(int i = 0; i < 5; i++) rgb_out(81 + i, 16, 16, 16);
        rgb_out(81 + finger_set, 63, 63, 32);
        rgb_out(88, 63, 8, 8);
    }

    // rgb_out(roots[root], 17, 32, 63); // Blue glowing Root
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

        for(int i = 0; i < 12; i++)
        {
            if(p == roots[i])
            {
                root = i;
                refresh();
            }
        }
    }
}

void scale_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v)
{

}