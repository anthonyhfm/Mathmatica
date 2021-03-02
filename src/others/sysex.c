#include "others/sysex.h"

const u8 check[6] = {0x7E, 0x7F, 0x06, 0x01, 0xF7};
const u8 check_response[17] = {240, 126, 0, 6, 2, 0, 32, 41, 81, 0, 0, 0, 0, 99, 102, 121, 247};

void DeviceCheck(u8 port, u8 * data, u16 count)
{
    for(int i = 0; i < count; i++)
    {
        if(check[i] != data[i + 1]) return;
    }

    hal_send_sysex(port, check_response, 17);
    
}

void LED(u8 p, u8 r, u8 g, u8 b)
{
    if(mode == mode_legacy || mode == mode_programmer)
    {
        if(p == 99)
        	hal_plot_led(TYPESETUP, flip_led(p), r, g, b);
		else
			hal_plot_led(TYPEPAD, flip_led(p), r, g, b);
    }
}

void ApolloLED(u8 port, u8 * data, u16 count)
{
    if (data[1] == 95) // Identifier for Apollo Fast LED
    {
		for (u8* idata = data + 2; idata < (data + (count - 2));) 
        {
			int color_data[3] = {*idata++, *idata++, *idata++};

			// BIT NN CALCULATION BY MAT1JACZYYY
			int nn = ((color_data[0] & 64) >> 4) | ((color_data[1] & 64) >> 5) | ((color_data[2] & 64) >> 6);
			if (nn == 0) nn = *idata++;

			for (int i = 0; i < nn; i++) 
			{
				int p = *idata++;
				if (p == 0) 
					for (int x = 0; x < 99; x++) LED(x, color_data[0], color_data[1], color_data[2]); // Fill
				else if (p <= 99) 
					LED(p, color_data[0], color_data[1], color_data[2]); // Single
				else if (p <= 109) 
				{
					p -= 100;
					p *= 10;
					p += 1;

					for (u8 x = p; x < p + 8; x++) LED(x, color_data[0], color_data[1], color_data[2]); // Row
				}
				else if (p <= 119) 
					for (u8 x = p - 100; x < 90; x = x + 10) LED(x, color_data[0], color_data[1], color_data[2]); // Column
			}
		}
	}
}

void PaletteUtil(u8 port, u8 * data, u16 count)
{
	if(data[1] == 42)
	{
		u8 p = data[2];
		u8 r = data[3];
		u8 g = data[4];
		u8 b = data[5];

		palette[3][0][p] = r;
		palette[3][1][p] = g;
		palette[3][2][p] = b;
	}
}

void NovationLED(u8 port, u8 * data, u16 count)
{
	if(data[1] == 0 && data[2] == 32 && data[3] == 41 && data[4] == 2&& data[5] == 16 && data[6] == 11)
	{
		u8 p = data[7];
		u8 r = data[8];
		u8 g = data[9];
		u8 b = data[10];

		if(mode == mode_legacy || mode == mode_programmer)
		{
			if(p == 99)
				hal_plot_led(TYPESETUP, flip_led(p), r, g, b);
			else
				hal_plot_led(TYPEPAD, flip_led(p), r, g, b);
		}
	}

	// Example: 240, 0, 32, 41, 2, 16, 11, <LED>, <Red>, <Green>, <Blue>, 247
}

void PluginLed(u8 port, u8 * data, u16 count) // Plugin RGB of SuperVelocity
{
	if(data[1] == 69)
	{
		u8 p = data[2];
		u8 r = data[3];
		u8 g = data[4];
		u8 b = data[5];

		if(mode == mode_legacy || mode == mode_programmer)
		{
			if(p == 99)
				hal_plot_led(TYPESETUP, flip_led(p), r, g, b);
			else
				hal_plot_led(TYPEPAD, flip_led(p), r, g, b);
		}
	}
}

void HandleSysEx(u8 port, u8 * data, u16 count)
{
    DeviceCheck(port, data, count);
	PaletteUtil(port, data, count);
	ApolloLED(port, data, count);
	PluginLed(port, data, count);
	NovationLED(port, data, count);
}