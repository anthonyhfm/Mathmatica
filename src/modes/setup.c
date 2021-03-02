#include "modes/setup.h"

u8 jump = 0;
u8 page = 0;

#define page_led 0
#define page_vel 1
#define page_aft 2
#define page_fad 3
#define page_inv 4

u8 led_letters[3][12] = 
{
    {81, 71, 61, 51, 52},
    {83, 84, 85, 73, 74, 63, 53, 54, 55},
    {86, 87, 76, 78, 66, 68, 56, 57}
};

u8 vel_letters[3][12] = 
{
    {81, 83, 71, 73, 61, 63, 52},
    {84, 85, 86, 74, 75, 64, 54, 55, 56},
    {87, 77, 67, 57, 58}
};

u8 aft_letters[3][12] = 
{
    {82, 71, 73, 61, 62, 63, 51, 53},
    {84, 85, 74, 64, 65, 54},
    {86, 87, 88, 77, 67, 57}
};

u8 fad_letters[3][12] = 
{
    {81, 82, 71, 61, 62, 51},
    {84, 73, 75, 63, 64, 65, 53, 55},
    {86, 87, 76, 78, 66, 68, 56, 57}
};

void fad_page_led()
{
    for(int i = 0; i < 12; i++) rgb_out(fad_letters[0][i], 0, 45, 63);
    for(int i = 0; i < 12; i++) rgb_out(fad_letters[1][i], 63, 63, 63);
    for(int i = 0; i < 12; i++) rgb_out(fad_letters[2][i], 0, 45, 63);

    if(fad_enabled) rgb_out(31, 0, 63, 0); 
    else rgb_out(31, 63 >> 2, 0, 0);

}

void fad_page_surface(u8 p, u8 v)
{
    if(v)
    {
        if(p == 31)
        {
            fad_enabled = (fad_enabled)? 0 : 1;
            refresh();
        }
    }
}

const u8 aft_colors[3][3] = 
{
    {63, 0, 0},
    {0, 63, 15},
    {0, 63, 15},
};

void aft_page_led()
{
    for(int i = 0; i < 12; i++) rgb_out(aft_letters[0][i], 32 >> 2, 0, 63);
    for(int i = 0; i < 12; i++) rgb_out(aft_letters[1][i], 63, 63, 63);
    for(int i = 0; i < 12; i++) rgb_out(aft_letters[2][i], 32 >> 2, 0, 63);

    

    for (int i = 0; i < 3; i++) rgb_out(31 + i, aft_colors[i][0] >> 2, aft_colors[i][1] >> 2, aft_colors[i][2] >> 2);


    rgb_out(31 + aftertouch_mode, aft_colors[aftertouch_mode][0], aft_colors[aftertouch_mode][1], aft_colors[aftertouch_mode][2]);

    if(aftertouch_mode != 0)
    {
        for(int i = 0; i < 3; i++) rgb_out(21 + i, 32 >> 2, 32 >> 2, 32 >> 2);
        rgb_out(aftertouch_int + 21, 32 >> 2, 0, 63);
    }

    
}

void aft_page_surface(u8 p, u8 v)
{
    if(v)
    {
        if(p >= 31 && p <= 33)
        {
            aftertouch_mode = p - 31;
            refresh();
        }
        else if(aftertouch_mode != 0 && p >= 21 && p <= 23)
        {
            aftertouch_int = p - 21;
            refresh();
        }
    }
}

void vel_page_led()
{
    for(int i = 0; i < 12; i++) rgb_out(vel_letters[0][i], 63, 16, 0);
    for(int i = 0; i < 12; i++) rgb_out(vel_letters[1][i], 63, 63, 63);
    for(int i = 0; i < 12; i++) rgb_out(vel_letters[2][i], 63, 16, 0);

    if(velocity)
    {
        rgb_out(31, 0, 63, 0);

        for(int i = 0; i < 3; i++) rgb_out(21 + i, 32 >> 2, 32 >> 2, 32 >> 2);
        rgb_out(velocity_int + 21, 63, 32 >> 2, 0);
    }
    else rgb_out(31, 63 >> 0, 0, 0);
}

void vel_page_surface(u8 p, u8 v)
{
    if(v)
    {
        if(p == 31)
        {
            velocity = (velocity)? 0 : 1;
            refresh();
        }
        else if(velocity && p >= 21 && p <= 23)
        {
            velocity_int = p - 21;
            refresh();
        }
    }
}

void led_page_led()
{
    for(int i = 0; i < 12; i++) rgb_out(led_letters[0][i], 10, 10, 63);
    for(int i = 0; i < 12; i++) rgb_out(led_letters[1][i], 63, 63, 63);
    for(int i = 0; i < 12; i++) rgb_out(led_letters[2][i], 10, 10, 63);

    for(int i = 0; i < 8; i++)
        rgb_out(31 + i, 17, 17, 60);

    rgb_out(31 + brightness, 63, 63, 63);

    for(int i = 0; i < 4; i++)
        rgb_out(11 + i, 63 >> 2, 20 >> 2, 63 >> 2);

    rgb_out(11 + palette_index, 63, 20, 63);
    if(palette_index == 3) rgb_out(15, 63, 63, 0);

    rgb_out(18, 10, 10, 63);
}

void led_page_surface(u8 p, u8 v)
{
    if(v)
    {
        if(p >= 31 && p <= 38)
        {
            brightness = p - 31;
            refresh();
        }
        else if(p >= 11 && p <= 14)
        {
            palette_index = p - 11;
            refresh();
        }
        else if(p == 18)
        {
            page = page_inv;
            refresh();
        }
        else if(p == 15 && palette_index == 3)
        {
            jump = 0;
            update(mode_editor);
        }
    }
}

void setup_init()
{
    if(page == page_inv) return;

    for(int i = 0; i < 4; i++) rgb_out(89 - (10 * i), 63 >> 2, 63 >> 2, 63 >> 2);

    switch(page)
    {
        case page_led:
            led_page_led();
            rgb_out(89, 10, 10, 63);
            break;
        case page_vel:
            vel_page_led();
            rgb_out(79, 63, 16, 0);
            break;
        case page_aft:
            aft_page_led();
            rgb_out(69, 32 >> 2, 0, 63);
            break;
        case page_fad:
            fad_page_led();
            rgb_out(59, 0, 45, 63);
            break;
        default:
            page = page_led;
            refresh();
            break;
    }

    rgb_out(39, legacy_r >> 2, legacy_g >> 2, legacy_b >> 2);
    rgb_out(29, live_r >> 2, live_g >> 2, live_b >> 2);
    rgb_out(19, programmer_r >> 2, programmer_g >> 2, programmer_b >> 2);

    for(int i = 0; i < 4; i++) rgb_out(91 + i, 63 >> 2, 0, 0);
    rgb_out(91 + flip_index, 63, 0, 0);

    switch(mode_default)
    {
        case mode_legacy:
            rgb_out(39, legacy_r, legacy_g, legacy_b);
            break;
        case mode_live:
            rgb_out(29, live_r, live_g, live_b);
            break;
        case mode_programmer:
            rgb_out(19, programmer_r, programmer_g, programmer_b);
            break;
        default:
            mode_default = mode_legacy;
            refresh();
            break;
        
    }
}

void setup_timer_event()
{

}

void setup_surface_event(u8 p, u8 v, u8 x, u8 y)
{
    if(v)
    {
        jump = 1;
        
        if(p == 0 && jump)
        {
            jump = 0;
            update(mode_default);
        }

        if(page != page_inv)
        {
            if(p == 89)
            {
                page = page_led;
                refresh();
            }
            else if(p == 79)
            {
                page = page_vel;
                refresh();
            }
            else if(p == 69)
            {
                page = page_aft;
                refresh();
            }
            else if(p == 59)
            {
                page = page_fad;
                refresh();
            }
            else if(p == 39)
            {
                mode_default = mode_legacy;
                refresh();
            }
            else if(p == 29)
            {
                mode_default = mode_live;
                refresh();
            }
            else if(p == 19)
            {
                mode_default = mode_programmer;
                refresh();
            }
            else if(p >= 91 && p <= 94)
            {
                flip_index = p - 91;
                refresh();
            }
        }
    }

    switch(page)
    {
        case page_led:
            led_page_surface(p, v);
            break;
        case page_vel:
            vel_page_surface(p, v);
            break;
        case page_aft:
            aft_page_surface(p, v);
            break;
        case page_fad:
            fad_page_surface(p, v);
            break;
        case page_inv:
            if(v)
            {
                page = page_led;
                refresh();
            }
            break;
    }
}

void setup_midi_event(u8 port, u8 t, u8 ch, u8 p, u8 v) { }