#include "lighting/led.h"

double calc_bright(u8 value)
{
    double e = 0.1;
    double out = 0;

    out = e * (brightness + 2);

    if(brightness == 7) return value;

    return value * out;
}

void rgb_out(u8 p, u8 r, u8 g, u8 b)
{
    if(p == 99)
        hal_plot_led(TYPESETUP, flip_led(p), calc_bright(r), calc_bright(g), calc_bright(b));
    else
        hal_plot_led(TYPEPAD, flip_led(p), calc_bright(r), calc_bright(g), calc_bright(b));
}

void vel_out(u8 p, u8 v)
{
    rgb_out(p, palette[palette_index][0][v], palette[palette_index][1][v], palette[palette_index][2][v]);
}