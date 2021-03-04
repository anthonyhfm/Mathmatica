#ifndef SYSEX_H
#define SYSEX_H

#include "app_defs.h"
#include "modes/mode.h"
#include "others/out.h"

void HandleSysEx(u8 port, u8 * data, u16 count);

#endif