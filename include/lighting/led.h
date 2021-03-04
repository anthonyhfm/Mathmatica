#ifndef LED_H
#define LED_H

#include "app_defs.h"
#include "app.h"

#include "lighting/palette.h"
#include "memory/data.h"

void rgb_out(u8 p, u8 r, u8 g, u8 b);

void vel_out(u8 p, u8 v);

#endif