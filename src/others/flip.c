#include "others/flip.h"

u8 reverser[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

u8 flip_surface(u8 p)
{
    u8 x = p % 10;
    u8 y = p / 10;

    if(p == 99) return p;
    if(p == 0) return p;

    switch(flip_index)
    {
        case 0:
            return x + (y * 10);
            break;
        case 1:
            return reverser[x] + (reverser[y] * 10);
            break;
        case 2:
            return y + (reverser[x] * 10);
            break;
        case 3:
            return reverser[y] + (x * 10);
            break;
    }
}

u8 flip_led(u8 p)
{
    u8 x = p % 10;
    u8 y = p / 10;

    if(p == 99) return p;
    if(p == 0) return p;

    switch(flip_index)
    {
        case 0:
            return x + (y * 10);
            break;
        case 1:
            return reverser[x] + (reverser[y] * 10);
            break;
        case 2:
            return reverser[y] + (x * 10);
            break;
        case 3:
            return y + (reverser[x] * 10);
            break;
    }
}