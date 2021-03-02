#ifndef MODE_H
#define MODE_H

#include "lighting/led.h"
#include "app_defs.h"
#include "memory/manager.h"

#define mode_boot 0
#include "modes/boot.h"

#define mode_setup 1
#include "modes/setup.h"

#define mode_legacy 2
#include "modes/legacy.h"

#define mode_programmer 3
#include "modes/programmer.h"

#define mode_drum 4
#include "modes/drum.h"

#define mode_editor 5
#include "modes/editpalette.h"


#define modecount 6
void mode_init();
void mode_timer_event();
void mode_surface_event(u8 p, u8 v, u8 x, u8 y);
void mode_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v);
void mode_aftertouch_event(u8 index, u8 value);
void mode_poly_event(u8 index, u8 value);

u8 mode;
u8 mode_default;

void refresh();
void update(u8 x);
void default_update(u8 x);

#endif