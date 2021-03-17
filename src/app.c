/******************************************************************************
 
 Copyright (c) 2015, Focusrite Audio Engineering Ltd.
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 * Neither the name of Focusrite Audio Engineering Ltd., nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 *****************************************************************************/

//______________________________________________________________________________
//
// MATHMATICA BY AZOR (314DRAGON)
//______________________________________________________________________________

#include "app.h"

// store ADC frame pointer
static const u16 *g_ADC = 0;

// buffer to store pad states for flash save
#define BUTTON_COUNT 100

u8 g_Buttons[BUTTON_COUNT] = {0};

//______________________________________________________________________________

u8 mod[3] = {1, 2, 3};

u8 GET_VELOCITY(void)
{
  return *(u8 *)(velocity_int + 3) & 0x7f;
}

void app_surface_event(u8 t, u8 p, u8 v)
{
    
    p = flip_surface(p);

    if(mode == mode_setup)
    {
        mode_surface_event(p, (v == 0)? 0 : 127, p % 10, p / 10);
        return;
    }

    if(p == 0)
    {
        mode_surface_event(p, (v == 0)? 0 : 127, p % 10, p / 10);
    }
    else
    {
        // I dont even know if this shit works lmao dont judge me
        u8 out_v = 0;
        
        if (!velocity) 
		    out_v = (v == 0)? 0 : 127;
        else if(velocity && mode != mode_setup)
        {
            out_v = v / mod[velocity_int];
        }

        mode_surface_event(p, out_v, p % 10, p / 10);
    }

	
}

//______________________________________________________________________________

void app_midi_event(u8 port, u8 t, u8 p, u8 v)
{
	mode_midi_event(port, t >>= 4, t % 16, p, v);
}

//______________________________________________________________________________

void app_sysex_event(u8 port, u8 * data, u16 count)
{
    HandleSysEx(port, data, count);
}

//______________________________________________________________________________

void app_aftertouch_event(u8 index, u8 value)
{
    // I dont even know if this shit works lmao dont judge me

    u8 out_a = 0;
    out_a = value / mod[aftertouch_int];
    index = out_a;

    switch(aftertouch_mode)
    {
        case 1:
            index = mod[aftertouch_int] * (aftertouch_int + 1);
            if(index >= 127) index = 127;
            mode_aftertouch_event(index, value);
            break;

        case 2:
            index = mod[aftertouch_int] * (aftertouch_int + 1);
            if(index >= 127) index = 127;
            mode_poly_event(index, value);
            break;
    }
}

//______________________________________________________________________________

void app_cable_event(u8 type, u8 value)
{

}

//______________________________________________________________________________

void app_timer_event()
{
    mode_timer_event();
}

//______________________________________________________________________________

void app_init(const u16 *adc_raw)
{
    read_memory();
    update(mode_boot);
}
