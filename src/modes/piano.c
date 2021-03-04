#include "modes/piano.h"

u8 bblocks[11] = {12, 13, 14, 15, 16, 17, 22, 23, 25, 26, 27};
u8 pblocks[2] = {11, 18};
u8 piano_midi[52] = {36, 38, 40, 41, 43, 45, 47, 48, 37, 39, 42, 44, 46, 48, 50, 52, 53, 55, 57, 59, 60, 49, 51, 54, 56, 58, 60, 62, 64, 65, 67, 69, 71, 72, 61, 63, 66, 68, 70, 72, 74, 76, 77, 79, 81, 83, 84, 73, 75, 78, 80, 82};
u8 piano_pressable[52] = {11, 12, 13, 14, 15, 16, 17, 18, 22, 23, 25, 26, 27, 31, 32, 33, 34, 35, 36, 37, 37, 42, 43, 45, 46, 47, 51, 52, 53, 54, 55, 56, 57, 58, 62, 63, 65, 66, 67, 71, 72, 73, 74, 75, 76, 77, 78, 82, 83, 85, 86, 87};

void piano_init() 
{
    for(int i = 0; i < 4; i++)
    {
        for(int x = 0; x < 11; x++) rgb_out(bblocks[x] + (20 * i), 0, 32, 63);
        for(int x = 0; x < 2; x++) rgb_out(pblocks[x] + (20 * i), 63, 0, 63);
    }
}

void piano_press(u8 p, u8 v)
{
    for(int i = 0; i < 4; i++)
    {
        for(int x = 0; x < 11; x++)
        {
            if(v)
            {
                if(p == bblocks[x] + (20 * i)) rgb_out(p, 0, 63, 0);
            }
            else
            {
                if(p == bblocks[x] + (20 * i)) rgb_out(p, 0, 32, 63);
            }
        }

        for(int x = 0; x < 2; x++)
        {
            if(v)
            {
                if(p == pblocks[x] + (20 * i)) rgb_out(p, 0, 63, 0);
            }
            else
            {
                if(p == pblocks[x] + (20 * i)) rgb_out(p, 63, 0, 63);
            }
        }

    }

    for(int i = 0; i < 52; i++)
    {
        if(piano_pressable[i] == p)
        {
            midi_out(piano_midi[i], v);
        }
    }
}

void piano_surface_event(u8 p, u8 v, u8 x, u8 y) 
{
	if(v)
    {
        if(p == 0)
        {
            update(mode_setup);
            return;
        }
        
    }
    
    if(x == 8 && y >= 1 && y <= 5) piano_press(p + 13, v);
    if(x == 1 && y >= 3 && y <= 7) piano_press(p - 13, v);
    

    piano_press(p, v);
}

void piano_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) 
{
	
}

void piano_timer_event() {}