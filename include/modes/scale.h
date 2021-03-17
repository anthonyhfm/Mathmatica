#ifndef SCALE_H
#define SCALE_H

#include "app_defs.h"
#include "modes/mode.h"

#include "others/translate.h"
#include "others/out.h"

void scale_init();
void scale_timer_event();
void scale_surface_event(u8 p, u8 v, u8 x, u8 y);
void scale_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v);
void scale_aftertouch_event(u8 index, u8 value);
void scale_poly_event(u8 p, u8 v);

u8 scale_scales[16][8];

u8 scale_returnto, scale_root, finger_set, scale, chromatic;

#endif