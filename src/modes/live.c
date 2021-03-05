#include "modes/live.h"

u8 live_mode = 1;
u8 custom_mode = 0;

void live_init()
{
    for(int i = 0; i < 3; i++) rgb_out(95 + i, 63 >> 2, 63 >> 2, 63 >> 2);

    switch(live_mode)
    {
        case live_session:
            rgb_out(95, 0, 63, 0);
            break;

        case live_note:
            rgb_out(96, 0, 63, 0);
            note_init();
            break;

        case live_custom:
            for(int i = 0; i < 4; i++) rgb_out(89 - (i * 10), 63 >> 2, 63 >> 2, 63 >> 2);
            rgb_out(97, 0, 63, 0);
            switch(custom_mode)
            {
                case custom_drum:
                    rgb_out(89, 0, 63, 0);
                    drum_init();
                    break;

                case custom_piano:
                    rgb_out(79, 0, 63, 0);
                    piano_init();
                    break;

                case custom_user1:
                    rgb_out(69, 0, 63, 0);
                    break;

                case custom_user2:
                    rgb_out(59, 0, 63, 0);
                    break;
            }
            break;
    }
}

void live_surface_event(u8 p, u8 v, u8 x, u8 y)
{
    if(v)
    {
        if(p == 0)
        {
            update(mode_setup);
            return;
        }
        else if(p == 95 && live_mode == live_note || p == 95 && live_mode == live_note)
        {
            live_mode = live_session;
            refresh();
            return;
        }
        else if(p == 96)
        {
            live_mode = live_note;
            refresh();
        }
        else if(p == 97)
        {
            live_mode = live_custom;
            refresh();
        }
        else if(p == 89 && live_mode == live_custom)
        {
            custom_mode = custom_drum;
            refresh();
        }
        else if(p == 79 && live_mode == live_custom)
        {
            custom_mode = custom_piano;
            refresh();
        }
        else if(p == 69 && live_mode == live_custom)
        {
            custom_mode = custom_user1;
            refresh();
        }
        else if(p == 59 && live_mode == live_custom)
        {
            custom_mode = custom_user2;
            refresh();
        }
    }

    if(live_mode == live_session)
    {
        if(p >= 96 && p <= 98) return;

        if (x == 0 || x == 9 || y == 0 || y == 9) 
        {
			hal_send_midi(USBMIDI, 0xB0, p, v);
		} 
        else 
        {
			hal_send_midi(USBMIDI, (v == 0)? 0x80 : 0x90, p, v);
		}
        
    }

    if(x >= 1 && x <= 8 && y >= 1 && y <= 8)
    {
        switch(live_mode)
        {
            case live_note:
                note_surface_event(p, v, x, y);
                break;

            case live_custom:
                switch(custom_mode)
                {
                    case custom_drum:
                        drum_surface_event(p, v, x, y);
                        break;

                    case custom_piano:
                        piano_surface_event(p, v, x, y);
                        break;

                    case custom_user1:
                        midi_out(translate_to_drum(p), v);
                        break;

                    case custom_user2:
                        midi_out(p, v);
                        break;
                }
                break;
        }
    }

    
    
}

void live_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v)
{
    if(live_mode == live_session)
    {
        if(port != USBMIDI) return;
        if(p >= 96 && p <= 98) return;

        switch (t) {
			case 0x8:
				v = 0;
			
			case 0x9:
                rgb_out(p, palette[0][0][v], palette[0][1][v], palette[0][2][v]);
				break;
			
			case 0xB:
				rgb_out(p, palette[0][0][v], palette[0][1][v], palette[0][2][v]);
				break;
		}
        
        if(p == 0 && v == 0) rgb_out(95, 0, 63, 0);

        return;    
    }

    u8 x = p % 10;
    u8 y = p / 10;
    u8 x_t = translate_to_prog(p) % 10;
    u8 y_t = translate_to_prog(p) / 10;

    switch(live_mode)
    {
        case live_note:
            note_midi_event(port, t, ch, p, v);
            break;

        case live_custom:
            switch(custom_mode)
            {
                case custom_drum:
                    drum_midi_event(port, t, ch, p, v);
                    break;

                case custom_piano:
                    piano_midi_event(port, t, ch, p, v);
                    break;

                case custom_user1:
                    if(port == USBMIDI) return;

                    if(t == 0x8) v = 0;
                    
                    if(x_t >= 1 && x_t <= 8 && y_t >= 1 && y_t <= 8)vel_out(translate_to_prog(p), v);
                    break;
                    

                case custom_user2:
                    if(port == USBMIDI) return;

                    if(t == 0x8) v = 0;
                    
                    if(x >= 1 && x <= 8 && y >= 1 && y <= 8) vel_out(p, v);
                    break;

                    
            }
            break;
    }

    
}

void live_timer_event() { }