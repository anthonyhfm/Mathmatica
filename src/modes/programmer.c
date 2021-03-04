#include "modes/programmer.h"

void programmer_init()
{
    rgb_out(99, programmer_r, programmer_g, programmer_b);
}

void programmer_surface_event(u8 p, u8 v, u8 x, u8 y)
{
    if(v)
    {
        if(p == 0)
        {
            update(mode_setup);
            return;
        }

    }

    midi_out(p, v);
}

void programmer_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v)
{
    if(port == USBMIDI) return;

    if(t == 0x8) v = 0;
    
    vel_out(p, v);
}

void programmer_timer_event() {}