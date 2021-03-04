#include "modes/live.h"

u8 live_mode = 1;
u8 custom_mode = 0;

void live_init()
{
    
}

void live_surface_event(u8 p, u8 v, u8 x, u8 y)
{
    if(v)
    {
        if(p == 0)
        {
            update(mode_setup);
            return;
        }
    }

    if (x == 0 || x == 9 || y == 0 || y == 9) {
		hal_send_midi(USBMIDI, 0xB0, p, v);
	} else {
		hal_send_midi(USBMIDI, (v == 0)? 0x80 : 0x90, p, v);
	}
}

void live_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v)
{
    if(port == USBSTANDALONE) return;

    if(t == 0x8) v = 0;
    
    vel_out(p, v);
}

void live_timer_event() { }