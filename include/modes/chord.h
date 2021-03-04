#ifndef CHORD_H
#define CHORD_H

#include "app_defs.h"
#include "modes/mode.h"

#include "others/translate.h"
#include "others/out.h"

#define chord_r 63
#define chord_g 63
#define chord_b 0

void chord_init();
void chord_timer_event();
void chord_surface_event(u8 p, u8 v, u8 x, u8 y);
void chord_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v);
void chord_aftertouch_event(u8 index, u8 value);
void chord_poly_event(u8 p, u8 v);

#endif