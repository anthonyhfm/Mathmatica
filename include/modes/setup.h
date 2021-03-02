#ifndef SETUP_H
#define SETUP_H

#include "app_defs.h"
#include "modes/mode.h"

u8 jump;

void setup_init();
void setup_timer_event();
void setup_surface_event(u8 p, u8 v, u8 x, u8 y);
void setup_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v);
void setup_aftertouch_event(u8 index, u8 value);
void setup_poly_event(u8 p, u8 v);

#endif