#include "modes/boot.h"

#define note_length 0.03
#define notes_total 200
#define colors 10
#define notes_per_frame 10

const u8 color_array[colors] = {13, 17, 21, 37, 45, 44, 48, 49, 0};

int boot_color_tn = 0;
double boot_color_de = 0;

int boot_tn = 0;
double boot_de = 0;
int boot_tn2 = 0;
u8 finished = 0;

u8 notes[notes_total][notes_per_frame] = 
{
    {0, 0, 0, 0},
    {98, 1},
    {11, 88, 22, 77, 55, 66, 33, 44, 97, 2},
    {12, 87, 23, 76, 44, 34, 55, 65, 96, 3},
    {13, 86, 24, 75, 45, 35, 54, 64, 95, 4},
    {14, 85, 25, 74, 63, 54, 45, 36, 94, 5},
    {15, 84, 26, 73, 53, 54, 45, 46, 93, 6},
    {16, 83, 27, 72, 43, 44, 55, 56, 92, 7},
    {17, 82, 37, 62, 55, 66, 33, 44, 91, 8},
    {81, 18, 47, 52, 44, 34, 55, 65, 80, 19},
    {71, 28, 57, 42, 45, 35, 54, 64, 70, 29},
    {61, 38, 67, 32, 63, 54, 45, 36, 60, 39},
    {51, 48, 77, 22, 53, 54, 45, 46, 50, 49},
    {41, 58, 22, 77, 43, 44, 55, 56, 40, 59},
    {31, 68, 23, 76, 55, 66, 33, 44, 30, 69},
    {21, 78, 24, 75, 20, 79},
    {11, 88, 25, 74, 10, 89},
    {12, 87, 26, 73, 98, 1},
    {13, 86, 27, 72, 97, 2},
    {14, 85, 37, 62, 96, 3},
    {15, 84, 47, 52, 95, 4},
    {16, 83, 57, 42, 94, 5},
    {17, 82, 67, 32, 93, 6},
    {81, 18, 77, 22, 92, 7},
    {71, 28, 91, 8},
    {61, 38, 80, 19},
    {51, 48, 70, 29},
    {41, 58, 60, 39},
    {31, 68, 50, 49},
    {21, 78, 40, 59},
    {11, 88, 30, 69},
    {20, 79},
    {10, 89},
    {98, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

void boot_init()
{
    
}

void boot_timer_event()
{
    boot_de = boot_de + note_length;
    boot_tn = boot_de;

    boot_color_de = boot_color_de + 0.02;
    boot_color_tn = boot_color_de;

    if(boot_tn >= 1) boot_tn2 = boot_tn - 1;

    for(int x; x < notes_per_frame; x++)
    {
        for(int i = 0; i < colors; i++)
        {
            if(boot_tn - i >= 0)
            {
                rgb_out(notes[boot_tn - i][x], palette[0][0][color_array[i]], palette[0][1][color_array[i]], palette[0][2][color_array[i]]);
            }
        }
    }

    if(boot_color_tn >= 28)
    {
        update(mode_legacy);
    }

    
}

void boot_surface_event(u8 p, u8 v, u8 x, u8 y) 
{
    if(v)
    {
        if(p == 0)
        {
            update(mode_setup);
        }
    }
}

void boot_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) {}