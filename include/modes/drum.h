#ifndef DRUM_H
#define DRUM_H

#include "app_defs.h"
#include "modes/mode.h"

#include "others/translate.h"
#include "others/out.h"

#define drum_r 63
#define drum_g 63
#define drum_b 0

void drum_init();
void drum_timer_event();
void drum_surface_event(u8 p, u8 v, u8 x, u8 y);
void drum_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v);
void drum_aftertouch_event(u8 index, u8 value);
void drum_poly_event(u8 p, u8 v);

#endif