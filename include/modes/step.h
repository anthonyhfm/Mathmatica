#ifndef STEP_H
#define STEP_H

#include "app_defs.h"
#include "modes/mode.h"

#include "others/translate.h"
#include "others/out.h"

#define step_r 63
#define step_g 0
#define step_b 16

void step_init();
void step_timer_event();
void step_surface_event(u8 p, u8 v, u8 x, u8 y);
void step_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v);
void step_aftertouch_event(u8 index, u8 value);
void step_poly_event(u8 p, u8 v);

#endif