#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include "app_defs.h"
#include "modes/mode.h"
#include "others/out.h"

#define programmer_r 63
#define programmer_g 20
#define programmer_b 0

void programmer_init();
void programmer_timer_event();
void programmer_surface_event(u8 p, u8 v, u8 x, u8 y);
void programmer_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v);
void programmer_aftertouch_event(u8 index, u8 value);
void programmer_poly_event(u8 p, u8 v);

#endif