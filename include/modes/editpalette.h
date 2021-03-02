#ifndef EDITPALETTE_H
#define EDITPALETTE_H


#include "modes/mode.h"

void editpalette_init();
void editpalette_surface_event(u8 p, u8 v, u8 x, u8 y);
void editpalette_timer_event();
void editpalette_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v);

#endif