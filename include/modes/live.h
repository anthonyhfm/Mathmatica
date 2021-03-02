#ifndef LIVE_H
#define LIVE_H

#include "app_defs.h"
#include "modes/mode.h"

#include "others/translate.h"
#include "others/out.h"

#include "modes/note.h"
#include "modes/drum.h"
#include "modes/piano.h"

#define live_r 0
#define live_g 63
#define live_b 0

u8 live_mode;
u8 custom_mode;

#define live_session 0
#define live_note 1
#define live_custom 2

#define custom_drum 0
#define custom_piano 1
#define custom_user1 2
#define custom_user2 3

void live_init();
void live_timer_event();
void live_surface_event(u8 p, u8 v, u8 x, u8 y);
void live_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v);
void live_aftertouch_event(u8 index, u8 value);
void live_poly_event(u8 p, u8 v);

#endif