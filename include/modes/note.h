#ifndef NOTE_H
#define NOTE_H

#include "app_defs.h"
#include "modes/mode.h"

#include "others/translate.h"
#include "others/out.h"

#define note_r 0
#define note_g 45
#define note_b 63

void note_init();
void note_timer_event();
void note_surface_event(u8 p, u8 v, u8 x, u8 y);
void note_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v);
void note_aftertouch_event(u8 index, u8 value);
void note_poly_event(u8 p, u8 v);

#endif