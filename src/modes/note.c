#include "modes/note.h"

u8 note_midi[100] = {0, 1, 2, 3, 4, 5, 7, 8, 9, 10, 36, 37, 38, 39, 40, 41, 42, 43, 19, 20, 41, 42, 43, 44, 45, 46, 47, 48, 29, 30, 46, 47, 48, 49, 50, 51, 52, 53, 39, 40, 51, 52, 53, 54, 55, 56, 57, 58, 49, 50, 59, 56, 57, 58, 59, 60, 61, 62, 63, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 66, 67, 68, 69, 70, 71, 72, 73, 79, 80, 71, 72, 73, 74, 75, 76, 77, 78, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99};

u8 blue_blocks[30] = {13, 15, 16, 18, 21, 23, 25, 27, 32, 35, 37, 38, 42, 43, 45, 47, 52, 54, 57, 62, 64, 65, 67, 72, 74, 76, 81, 84, 86, 87};
u8 pink_blocks[6] = {11, 28, 33, 55, 77, 82};

void note_init() 
{
	for(int i = 0; i < 30; i++) rgb_out(blue_blocks[i], note_r, note_g, note_b);
	for(int i = 0; i < 6; i++) rgb_out(pink_blocks[i], 63, 0, 63);
}

void note_down(u8 p, u8 v)
{
	if(v)
	{
		for(int i = 0; i < 100; i++)
		{
			u8 x = note_midi[i];

			if(p == i)
			{
				rgb_out(p, 0, 63, 0);
			}
		}
	}
	else
	{
		for(int i = 0; i < 30; i++)
		{
			if(p == blue_blocks[i])
			{
				rgb_out(p, note_r, note_g, note_b);
				return;
			}
		}

		for(int i = 0; i < 6; i++)
		{
			if(p == pink_blocks[i])
			{
				rgb_out(p, 63, 0, 63);
				return;
			}
		}

		rgb_out(p, 0, 0, 0);
	}

}

void note_surface_event(u8 p, u8 v, u8 x, u8 y) 
{
	if(v)
    {
        if(p == 0)
        {
            update(mode_setup);
            return;
        }
    }

	if(x >= 1 && x <= 3 && y >= 2 && y <= 8) 
	{
		midi_out(note_midi[p - 5], v);
		note_down(p - 5 , v);
	}
	
	if(x >= 6 && x <= 8 && y >= 0 && y <= 7) 
	{
		midi_out(note_midi[p + 5], v);
		note_down(p + 5 , v);
	}

	note_down(p, v);

	midi_out(note_midi[p], v);
}

void note_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) 
{
	
}

void note_timer_event() {}