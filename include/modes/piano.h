#ifndef PIANO_H
#define PIANO_H

#include "app_defs.h"
#include "modes/mode.h"

#include "others/translate.h"
#include "others/out.h"

#define piano_r 0
#define piano_g 0
#define piano_b 63

void piano_init();
void piano_timer_event();
void piano_surface_event(u8 p, u8 v, u8 x, u8 y);
void piano_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v);
void piano_aftertouch_event(u8 index, u8 value);
void piano_poly_event(u8 p, u8 v);

#endif