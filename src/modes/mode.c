#include "modes/mode.h"

u8 mode = 0;
u8 mode_default = 0;

void refresh() 
{
	for(int i = 0; i < 100; i++)
		rgb_out(i, 0, 0, 0);

	mode_init();
}

void update(u8 in) 
{
	mode = in;
	refresh();
	write_memory();
}

void default_update(u8 in) 
{
	mode_default = in;
	update(mode_default);
}

void mode_init()
{
	switch(mode)
	{
		case mode_boot:
			boot_init();
			break;
		case mode_setup:
			setup_init();
			break;
		case mode_legacy:
			legacy_init();
			break;
		case mode_programmer:
			programmer_init();
			break;
		case mode_drum:
			drum_init();
			break;
		case mode_editor:
			editpalette_init();
			break;
	}
}

void mode_timer_event()
{
	switch(mode)
	{
		case mode_boot:
			boot_timer_event();
			break;
		case mode_setup:
			setup_timer_event();
			break;
		case mode_legacy:
			legacy_timer_event();
			break;
		case mode_programmer:
			programmer_timer_event();
			break;
		case mode_drum:
			drum_timer_event();
			break;
		case mode_editor:
			editpalette_timer_event();
			break;
	}
};

void mode_surface_event(u8 p, u8 v, u8 x, u8 y)
{
	switch(mode)
	{
		case mode_boot:
			boot_surface_event(p, v, x, y);
			break;
		case mode_setup:
			setup_surface_event(p, v, x, y);
			break;
		case mode_legacy:
			legacy_surface_event(p, v, x, y);
			break;
		case mode_programmer:
			programmer_surface_event(p, v, x, y);
			break;
		case mode_drum:
			drum_surface_event(p, v, x, y);
			break;
		case mode_editor:
			editpalette_surface_event(p, v, x, y);
			break;
	}
}

void mode_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) 
{
	switch(mode)
	{
		case mode_boot:
			boot_midi_event(port, t, ch, p,  v);
			break;
		case mode_setup:
			setup_midi_event(port, t, ch, p,  v);
			break;
		case mode_legacy:
			legacy_midi_event(port, t, ch, p,  v);
			break;
		case mode_programmer:
			programmer_midi_event(port, t, ch, p,  v);
			break;
		case mode_drum:
			drum_midi_event(port, t, ch, p,  v);
			break;
		case mode_editor:
			editpalette_midi_event(port, t, ch, p, v);
			break;
	}
};

void mode_aftertouch_event(u8 index, u8 value)
{
	switch(mode)
	{

	}
}

void mode_poly_event(u8 index, u8 value)
{
	switch(mode)
	{
		
	}
}