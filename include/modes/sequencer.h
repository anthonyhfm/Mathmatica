#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "app_defs.h"
#include "modes/mode.h"

#include "others/translate.h"
#include "others/out.h"

#define sequencer_r 32
#define sequencer_g 63
#define sequencer_b 32

void sequencer_init();
void sequencer_timer_event();
void sequencer_surface_event(u8 p, u8 v, u8 x, u8 y);
void sequencer_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v);
void sequencer_aftertouch_event(u8 index, u8 value);
void sequencer_poly_event(u8 p, u8 v);

#endif