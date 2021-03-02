#include "modes/setup.h"

u8 jump = 0;

void setup_init()
{
    rgb_out(81, legacy_r >> 2, legacy_g >> 2, legacy_b >> 2);
    rgb_out(71, programmer_r >> 2, programmer_g >> 2, programmer_b >> 2);
    rgb_out(61, drum_r >> 2, drum_g >> 2, drum_b >> 2);

    for(int i = 0; i < 8; i++)
        rgb_out(31 + i, 17, 17, 60);

    rgb_out(31 + brightness, 63, 63, 63);

    for(int i = 0; i < 4; i++)
        rgb_out(11 + i, 63 >> 2, 20 >> 2, 63 >> 2);

    rgb_out(11 + palette_index, 63, 20, 63);
    if(palette_index == 3) rgb_out(15, 63, 63, 0);

    for(int i = 0; i < 4; i++) rgb_out(91 + i, 63 >> 2, 0, 0);
    rgb_out(91 + flip_index, 63, 0, 0);

    switch(mode_default)
    {
        case mode_legacy:
            rgb_out(81, legacy_r, legacy_g, legacy_b);
            break;
        case mode_programmer:
            rgb_out(71, programmer_r, programmer_g, programmer_b);
            break;
        case mode_drum:
            rgb_out(61, drum_r, drum_g, drum_b);
            break;
        default:
            mode_default = mode_legacy;
            refresh();
            break;
        
    }
}

void setup_timer_event()
{

}

void setup_surface_event(u8 p, u8 v, u8 x, u8 y)
{
    if(v)
    {
        jump = 1;
        
        if(p == 0 && jump)
        {
            jump = 0;
            update(mode_default);
        }

        else if(p == 81)
        {
            mode_default = mode_legacy;
            refresh();
        }
        else if(p == 71)
        {
            mode_default = mode_programmer;
            refresh();
        }
        else if(p == 61)
        {
            mode_default = mode_drum;
            refresh();
        }
        else if(p >= 31 && p <= 38)
        {
            brightness = p - 31;
            refresh();
        }
        else if(p >= 11 && p <= 14)
        {
            palette_index = p - 11;
            refresh();
        }
        else if(p == 15 && palette_index == 3)
        {
            jump = 0;
            update(mode_editor);
        }
        else if(p >= 91 && p <= 94)
        {
            flip_index = p - 91;
            refresh();
        }
    }
}

void setup_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) { }