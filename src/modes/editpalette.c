#include "modes/editpalette.h"

u8 scroll = 0;
u8 index = 3;
u8 selected = 0;
u8 shift = 0;
u8 sel_col = 0;



void editpalette_init()
{
	for(int i = 0; i < 4; i++) rgb_out(3 + i, 63 >> 2, 63 >> 2, 63 >> 2);
	rgb_out(scroll + 3, 10, 63, 10);

	rgb_out(91, 10, 63, 10);
	rgb_out(92, 10, 63, 10);

	rgb_out(89, 63 >> 2, 0, 0);
	rgb_out(79, 0, 63 >> 2, 0);
	rgb_out(69, 0, 0, 63 >> 2);

	if(sel_col == 0)
		rgb_out(89, 63, 0, 0);
	else if(sel_col == 1)
		rgb_out(79, 0, 63, 0);
	else if(sel_col == 2)
		rgb_out(69, 0, 0, 63);

	

	if(scroll == 3)
	{
		for(int i = 0; i < 32; i++)
		{
			if(shift)
			{
				rgb_out(translate_to_prog(36 + i), palette[index][0][i + 96] >> 2, palette[index][1][i + 96] >> 2, palette[index][2][i + 96] >> 2);

				if(selected == i + (32 * scroll)) rgb_out(translate_to_prog(36 + i), palette[index][0][i + 96], palette[index][1][i + 96], palette[index][2][i + 96]);
			}
			else rgb_out(translate_to_prog(36 + i), palette[index][0][i + 96], palette[index][1][i + 96], palette[index][2][i + 96]);
		}
	}
	else
	{
		for(int i = 0; i < 64; i++)
		{
			if(shift)
			{
				rgb_out(translate_to_prog(36 + i), palette[index][0][i + (32 * scroll)] >> 2, palette[index][1][i + (32 * scroll)] >> 2, palette[index][2][i + (32 * scroll)] >> 2);

				if(selected == i + (32 * scroll)) rgb_out(translate_to_prog(36 + i), palette[index][0][i + (32 * scroll)], palette[index][1][i + (32 * scroll)], palette[index][2][i + (32 * scroll)]);
			}
			else rgb_out(translate_to_prog(36 + i), palette[index][0][i + (32 * scroll)], palette[index][1][i + (32 * scroll)], palette[index][2][i + (32 * scroll)]);
		}
	}

	if(selected >= 128) selected = 128;
	rgb_out(80, palette[index][0][selected], palette[index][1][selected], palette[index][2][selected]);
	


}

void editpalette_surface_event(u8 p, u8 v, u8 x, u8 y)
{
	if(v)
    {
        if(p == 0)
        {
            update(mode_setup);
            return;
        }
    }

	if(v)
	{
		if(p >= 3 && p <= 6)
		{
			scroll = p - 3;
			refresh();
		}
		else if(translate_to_drum(p) >= 36 && translate_to_drum(p) <= (36 + 63))
		{
			u8 x = translate_to_drum(p);

			switch(scroll)
			{
				case 0:
					selected = x - 36;
					break;

				case 1:
					selected = x - 4;
					break;

				case 2:
					selected = x + 28;
					break;

				case 3:
					selected = (x - 36) + 96;
					break;
			}

			refresh();
		}
		else if(p == 89)
		{
			sel_col = 0;
			refresh();
		}
		else if(p == 79)
		{
			sel_col = 1;
			refresh();
		}
		else if(p == 69)
		{
			sel_col = 2;
			refresh();
		}
		else if(p == 91)
		{
			palette[index][sel_col][selected] += 3;
			refresh();
			
		}
		else if(p == 92)
		{
			palette[index][sel_col][selected] -= 3;
			refresh();
		}

	}

	if(p == 80)
	{
		if(v) shift = 1;
		else shift = 0;
		refresh();
	}
}

void editpalette_timer_event() {}
void editpalette_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) {}