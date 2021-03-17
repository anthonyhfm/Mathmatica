#include "modes/note.h"

u8 note_colors[100][3] = {};
u8 octaves[5][6] = 
{
	{11, 25, 41, 55, 71, 85},
	{},
	{},
	{11, 35, 41, 65, 71},
	{11, 28, 33, 55, 77, 82}
};
u8 finger_grid[5][100] = 
{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 0, 9, 10, 11, 12, 1, 2, 3, 4, 0, 0, 5, 6, 7, 8, 9, 10, 11, 12, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 0, 9, 10, 11, 12, 1, 2, 3, 4, 5, 0, 0, 6, 7, 8, 9, 10, 11, 12, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 0, 9, 10, 11, 12, 1, 2, 3, 4},
	{},
	{},
	{},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 0, 6, 7, 8, 9, 10, 11, 12, 1, 0, 0, 11, 12, 1, 2, 3, 4, 5, 6, 0, 0, 4, 5, 6, 7, 8, 9, 10, 11, 0, 0, 9, 10, 11, 12, 1, 2, 3, 4, 0, 0, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 7, 8, 9, 10, 11, 12, 1, 2, 0, 0, 12, 1, 2, 3, 4, 5, 6, 7}
};

void setNoteLed(u8 p, u8 r, u8 g, u8 b)
{
	note_colors[p][0] = r;
	note_colors[p][1] = g;
	note_colors[p][2] = b;
}

void DrawNotes()
{
	if(chromatic) // Chromatic Mode LED
	{
		for(int i = 0; i < 100; i++)
		{
			for(int x = 0; x < 8; x++)
			{
				if(finger_grid[finger_set][i] == scale_scales[scale][x] + 1)
				{
					setNoteLed(i, note_r, note_g, note_b);	
				}
			}
		}

		for(int i = 0; i < 6; i++) setNoteLed(octaves[finger_set][i], 63, 0, 63);
	}
	else // Scale Mode LED
	{

	}


}

void note_init() 
{
	for(int i = 0; i < 100; i++) setNoteLed(i, 0, 0, 0);

	DrawNotes();


	for(int i = 0; i < 64; i++) rgb_out(translate_to_prog(i + 36), note_colors[translate_to_prog(i + 36)][0], note_colors[translate_to_prog(i + 36)][1], note_colors[translate_to_prog(i + 36)][2]);
}

void note_down(u8 p, u8 v)
{
	if(v) rgb_out(p, 0, 63, 0);
		else rgb_out(p, note_colors[p][0], note_colors[p][1], note_colors[p][2]);
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



	if(x >= 1 && x <= 3 && y >= 2 && y <= 8) note_down(p - 5 , v);
	
	if(x >= 6 && x <= 8 && y >= 0 && y <= 7) note_down(p + 5 , v);

	note_down(p, v);
}

void note_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) 
{
	
}

void note_timer_event() {}