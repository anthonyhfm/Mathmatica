# Mathmatica
### The performance-optimized, custom firmware. 
This repository contains the source code of Mathmatica, a custom firmware for the Launchpad Pro [MK2]. The firmware includes the new, MK3 setup menu, and adds a few other Launchpad cover optimized modes. It brings faster light updating speed, and the new keyboard mode. The firmware is easy to install, free to use and works with every project and DAW.

![GitHub language count](https://img.shields.io/github/languages/count/anthonyhfm/Mathmatica) 
![Website status](https://img.shields.io/website?down_message=offline&up_color=blueviolet&up_message=online&url=https%3A%2F%2Fwww.314dragon.com%2F)
![Discord](https://img.shields.io/discord/760499946792157215?color=4e5d94&label=discord)
![GitHub issues](https://img.shields.io/github/issues/anthonyhfm/Mathmatica)

## Install
The simplest way to install is via the flasher tool. Simply download the contents of the [flasher folder](https://github.com/anthonyhfm/Mathmatica/tree/performance/flasher). While not necessary to do so, it is recommended for you to close all apps using the Launchpad Pro.

An alternative way to do it is using [mat1jaczyyy's Launchpad Utility](https://fw.mat1jaczyyy.com/). To upload the Mathmatica firmware to [mat1jaczyyy's Launchpad Utility](https://fw.mat1jaczyyy.com/), press the following keys in the following sequence. [Up Arrow], [Up Arrow], [Down Arrow], [Down Arrow], [Left Arrow], [Right Arrow], [Left Arrow], [Right Arrow]. An option to use a custom SysEx file should appear. Upload the Mathmatica firmware file from the pop-up.

## Usage
The legacy mode is optimized for Launchpad covers. It includes built-in top lights eliminating the need of a top lights plugin. This also allows you to put samples on the top row. Also included is a new boot animation, which can be skipped by pressing the Setup button while it is displaying. The Live mode allows you to use Ableton Live integration. The modes in Live mode is a port from the new MK3 series. If you want to use any of the other modes (legacy and programmer), all you need to do is set the track inputs/outputs to the standalone port and the appropriate channel for the mode. Note that on Windows, the standalone port displays itself as "Launchpad Open" or "x- Launchpad Open" and the MIDI port displays itself as "Launchpad Open (Port 2)" or "MIDIIN2 (x- Launchpad Open)". 

| Mode        | Port        |
| ----------- | ----------- |
| Legacy      | Standalone  |
| Live        | MIDI        |
| Programmer  | Standalone  |

## Guide
You can click [here](https://drive.google.com/file/d/19jlDuHY_tf0r4qOTz5fD8Y76C6XeIqXa/view?usp=sharing) for the full guide.

## Build
The Launchpad Pro uses SysEx messages embedded into `.syx` files in order to update its firmware. In case you are lazy to build the firmware yourself, you can find the latest firmware build in this repository at `build/mathmatica.syx` or you can click [here](https://raw.githubusercontent.com/anthonyhfm/Mathmatica/performance/build/Mathmatica.syx) to download the latest build.

### On Windows
First, install `make` (preferably using Chocolatey):
```
choco install make
```

Next, install the [GCC ARM toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads). Make sure your PATH contains `arm-none-eabi-gcc\bin` (the installer can do this for you) and you can invoke `arm-none-eabi-gcc.exe` from the command line. Then, to directly compile the code:
```
make
```

### On macOS
First, install `make`:
```
xcode-select --install
```

You can easily install the GCC ARM toolchain using the [Homebrew package manager](https://brew.sh). The EABI tools are maintained in an external repository which you need to put on tap first.
```
brew tap PX4/homebrew-px4
```
```
brew install gcc-arm-none-eabi
```

Then to compile,
```
make
```

### On Debian Linux/Debian-based (Ubuntu, Pop!-OS, etc)
First, install `make`:
```
sudo apt-get install build-essential
```

Next, install the GCC ARM Toolchain
```
sudo apt-get install gcc-arm-none-eabi binutils-arm-none-eabi gdb-arm-none-eabi openocd
```

Then to compile,
```
make
```

### On Arch Linux/Arch-based (Manjaro, EndeavourOS, etc)
First, install `make`:
```
sudo pacman -Qg base-devel
```

Next, install the GCC ARM Toolchain
```
sudo pacman -S arm-none-eabi-gcc arm-none-eabi-binutils libmpc zlib arm-none-eabi-newlib gmp mpfr
```

Then to compile,
```
make
```

## Issues
`¯\_(ツ)_/¯` You tell me.

- Want a feature or report an issue? Submit an issue report on [GitHub's issue tracker](https://github.com/anthonyhfm/Mathmatica/issues)!
- Don't like the firmware? You can simply reflash Novation's stock firmware over at [mat1jaczyyy's Launchpad Utility](https://fw.mat1jaczyyy.com) or you can use [Novation's firmware flasher](https://customer.novationmusic.com/en/support/downloads?brand=Novation&product_by_range=527&download_type=software).

## Credits
- [anthonyhfm](https://github.com/anthonyhfm) ~ The Mathmatica Project.
- [EmilyLP](https://github.com/EmilyLPad) ~ Boot animation.
- [Pix3l_](https://github.com/WhosPix3l) ~ Making README file.

### People who didn't directly commit:
- [203Null](https://github.com/203Null) ~ Inspiration for the spreadsheets guide.
- [mat1jaczyyy](https://github.com/mat1jaczyyy) ~ Inspiration for README file.
- [Novation](https://github.com/Focusrite-Novation) ~ Launchpad Pro open-source firmware.

## Find us!
- [Discord](https://discord.com/invite/n7KHW5H)
- [Instagram](https://instagram.com/314dragon)
- [Website](https://314dragon.com)
