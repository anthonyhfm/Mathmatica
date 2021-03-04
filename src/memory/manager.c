#include "memory/manager.h"

u8 mem[USER_AREA_SIZE] = {0};

void Check()
{
    u8 check_brightness[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    u8 check_palette[4] = {0, 1, 2, 3};

    if(velocity != 0 && velocity != 1) velocity = 0;
    
    u8 true_bright = 0;
    for(int i = 0; i < 7; i++) if(brightness != check_brightness[i]) true_bright = 0; else {true_bright = 1; i = 8; }
    u8 true_palette = 0;
    for(int i = 0; i < 4; i++) if(palette_index != check_palette[i]) true_palette = 0; else {true_palette = 1; i = 8; }

    if(!true_bright) brightness = 7; 
    if(!true_palette) palette_index = 0; 
    
    if(palette_index <= 0 && palette_index >= 3) palette_index = 0;

    velocity = 0;
    velocity_int = 1;
    aftertouch_mode = 0;
    aftertouch_int = 1;
    fad_enabled = 0;
}

void read_memory()
{
    hal_read_flash(0, &mem[0], USER_AREA_SIZE);
	u16 read = 0;

    for(int i = 0; i < 3; i++)
    {
        for(int x = 0; x < 128; x++)
        {
            palette[3][i][x] = mem[read++] << 2;
        }
    }

    velocity = mem[read++];
    velocity_int = mem[read++];
    aftertouch_mode = mem[read++];
    aftertouch_int = mem[read++];
    brightness = mem[read++];
    palette_index = mem[read++];
    fad_enabled = mem[read++];

    Check();
}

void write_memory()
{
    u16 write = 0;

    for(int i = 0; i < 3; i++)
    {
        for(int x = 0; x < 128; x++)
        {
            mem[write++] = palette[3][i][x] >> 2;
        }
    }

    mem[write++] = velocity;
    mem[write++] = velocity_int;
    mem[write++] = aftertouch_mode;
    mem[write++] = aftertouch_int;
    mem[write++] = brightness;
    mem[write++] = palette_index;
    mem[write++] = fad_enabled;

    hal_write_flash(0, &mem[0], USER_AREA_SIZE);
}