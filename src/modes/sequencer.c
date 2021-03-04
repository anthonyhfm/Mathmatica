#include "modes/sequencer.h"

void sequencer_init()
{
    rgb_out(99, sequencer_r, sequencer_g, sequencer_b);
}

void sequencer_timer_event()
{

}

void sequencer_surface_event(u8 p, u8 v, u8 x, u8 y)
{
    if(v)
    {
        if(p == 0)
        {
            update(mode_setup);
            return;
        }
    }

}

void sequencer_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v)
{

}