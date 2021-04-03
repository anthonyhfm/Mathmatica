#include "modes/legacy.h"

void legacy_init()
{
    rgb_out(98, legacy_r, legacy_g, legacy_b);
}

void legacy_surface_event(u8 p, u8 v, u8 x, u8 y)
{
    if(v)
    {
        if(p == 0)
        {
            update(mode_setup);
            return;
        }
    }

    midi_out(translate_to_drum(p), v);
}

void legacy_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v)
{  
    if(port == USBMIDI) return;
    if (t != 0x8 && t != 0x9) return;

    if(t == 0x8) v = 0;
    
    vel_out(translate_to_prog(p), v);
}

void legacy_timer_event() {}