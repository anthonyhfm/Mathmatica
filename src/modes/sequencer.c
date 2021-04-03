#include "modes/sequencer.h"

u8 seq_mode = 0; // DR and other modes

u8 seq_screen[4][100][3] = {};

u8 seq_places[32] = {81, 82, 83, 84, 85, 86, 87, 88, 71, 72, 73, 74, 75, 76, 77, 78, 61, 62, 63, 64, 65, 66, 67, 68, 51, 52, 53, 54, 55, 56, 57, 58};
u8 seq_tick = 0;

void set_seqLed(u8 mode, u8 p, u8 r, u8 g, u8 b)
{
    seq_screen[mode][p][0] = r;
    seq_screen[mode][p][1] = g;
    seq_screen[mode][p][2] = b;
}

void sequencer_init()
{
    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            set_seqLed(seq_mode, 51 + (x + (y * 10)), 0, 28 >> 2, 63 >> 2);
        }
    }

    if(seq_mode == 0)
    {
        for(int y = 0; y < 4; y++)
        {
            for(int x = 0; x < 4; x++)
            {
                set_seqLed(seq_mode, 11 + (x + (y * 10)), 63, 16, 0);
            }
        }
    }
    else if(seq_mode == 1)
    {
        for(int i = 0; i < 4; i++)
        {
            set_seqLed(seq_mode, 11 + (i * 10), 52, 32, 63);
            for(int x = 0; x < 6; x++) set_seqLed(seq_mode, (12 + x) + (i * 10), 32, 5, 63);
            set_seqLed(seq_mode, 18 + (i * 10), 52, 32, 63);
        }
    }
    else if(seq_mode == 2)
    {
        for(int i = 0; i < 4; i++)
        {
            set_seqLed(seq_mode, 11 + (i * 10), 44, 63, 44);
            for(int x = 0; x < 6; x++) set_seqLed(seq_mode, (12 + x) + (i * 10), 15, 63, 15);
            set_seqLed(seq_mode, 18 + (i * 10), 44, 63, 44);
        }
    }
    else if(seq_mode == 3)
    {
        for(int i = 0; i < 4; i++)
        {
            set_seqLed(seq_mode, 11 + (i * 10), 63, 36, 63);
            for(int x = 0; x < 6; x++) set_seqLed(seq_mode, (12 + x) + (i * 10), 63, 15, 63);
            set_seqLed(seq_mode, 18 + (i * 10), 63, 36, 63);
        }
    }

    for(int i = 0; i < 100; i++) rgb_out(i, seq_screen[seq_mode][i][0], seq_screen[seq_mode][i][1], seq_screen[seq_mode][i][2]);

    rgb_out(1, 63 >> 2, (32 >> 2) >> 2, 0);
    rgb_out(3, 32 >> 2, 0, 63 >> 2);
    rgb_out(5, 10 >> 2, 63 >> 2, 10 >> 2);
    rgb_out(7, 63 >> 2, 10 >> 2, 63 >> 2);

    switch(seq_mode)
    {
        case 0:
            rgb_out(1, 63, 32 >> 2, 0);
            break;
        
        case 1:
            rgb_out(3, 32, 0, 63);
            break;

        case 2:
            rgb_out(5, 10, 63, 10);
            break;

        case 3:
            rgb_out(7, 63, 10, 63);
            break;
    }

    rgb_out(99, sequencer_r, sequencer_g, sequencer_b);
}

void sequencer_timer_event()
{

}

void sequencer_surface_event(u8 p, u8 v, u8 x, u8 y)
{
    if(seq_mode == 0)
    {
        if(x >= 1 && x <= 4 && y >= 1 && y <= 4)
        {
            if(v) rgb_out(p, 63, 63, 63);
            else rgb_out(p, 63, 16, 0);
        }
    }
    else
    {
        if(x >= 1 && x <= 8 && y >= 1 && y <= 4)
        {
            if (x == 8 && y >= 1 && y <= 3)
            {
                if(v) rgb_out(p + 3, 63, 63, 63);
                else rgb_out(p + 3, seq_screen[seq_mode][p][0], seq_screen[seq_mode][p][1], seq_screen[seq_mode][p][2]);
            }

            if (x == 1 && y >= 2 && y <= 4)
            {
                if(v) rgb_out(p - 3, 63, 63, 63);
                else rgb_out(p - 3, seq_screen[seq_mode][p][0], seq_screen[seq_mode][p][1], seq_screen[seq_mode][p][2]);
            }

            if(v) rgb_out(p, 63, 63, 63);
            else rgb_out(p, seq_screen[seq_mode][p][0], seq_screen[seq_mode][p][1], seq_screen[seq_mode][p][2]);
        }
    }

    if(v)
    {
        if(p == 0)
        {
            update(mode_setup);
            return;
        }
        if(p == 1 && seq_mode != 0)
        {
            seq_mode = 0;
            refresh();
        }
        else if(p == 3 && seq_mode != 1)
        {
            seq_mode = 1;
            refresh();
        }
        else if(p == 5 && seq_mode != 2)
        {
            seq_mode = 2;
            refresh();
        }
        else if(p == 7 && seq_mode != 3)
        {
            seq_mode = 3;
            refresh();
        }
    }

}

void sequencer_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v)
{

}