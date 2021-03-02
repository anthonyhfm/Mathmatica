#include "others/out.h"

void midi_out(u8 p, u8 v) 
{
    hal_send_midi(USBSTANDALONE, 144 + 15, p, v);
}

void aft_out(u8 p, u8 v) 
{
    if(aftertouch_mode == 1)
        hal_send_midi(USBSTANDALONE, 208, p, v);
    else if(aftertouch_mode == 2)
        hal_send_midi(USBSTANDALONE, 160, p, v);
}