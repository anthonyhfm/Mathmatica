#ifndef LEGACY_H
#define LEGACY_H

#include "app_defs.h"
#include "modes/mode.h"

#include "others/translate.h"
#include "others/out.h"

#define legacy_r 20
#define legacy_g 0
#define legacy_b 63

void legacy_init();
void legacy_timer_event();
void legacy_surface_event(u8 p, u8 v, u8 x, u8 y);
void legacy_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v);
void legacy_aftertouch_event(u8 index, u8 value);
void legacy_poly_event(u8 p, u8 v);

#endif