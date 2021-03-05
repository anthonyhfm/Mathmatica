ifeq ($(OS),Windows_NT)

define rmdir
	if exist "$(1)" rd /s /q "$(1)"
endef

define mkdir
	if not exist "$(1)" mkdir "$(1)"
endef

else

define rmdir
	rm -rf "$(1)"
endef

define mkdir
	mkdir -p "$(1)"
endef

endif

BUILDDIR = build

TOOLS = tools

SOURCES += src/app.c
SOURCES += src/modes/setup.c src/modes/legacy.c src/modes/programmer.c src/modes/drum.c src/modes/note.c src/modes/piano.c src/modes/editpalette.c src/modes/boot.c src/modes/live.c src/modes/chord.c src/modes/sequencer.c src/modes/scale.c src/modes/step.c
SOURCES += src/modes/mode.c src/lighting/led.c src/others/translate.c src/others/out.c src/lighting/palette.c src/memory/manager.c src/memory/data.c src/others/sysex.c src/others/flip.c



INCLUDES += -Iinclude -I

LIB = lib/launchpad_pro.a

OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))

# output files
SYX = $(BUILDDIR)/Mathmatica.syx
ELF = $(BUILDDIR)/Mathmatica.elf
BIN = $(BUILDDIR)/Mathmatica.bin
BINTOSYX = $(TOOLS)/bintosyx

# tools
HOST_GPP = g++
CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS  = -O2 -Wall -I.\
-D_STM32F103RBT6_  -D_STM3x_  -D_STM32x_ -mthumb -mcpu=cortex-m3 \
-fsigned-char  -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=6000000UL \
-DCMSIS -DUSE_GLOBAL_CONFIG -ffunction-sections -std=c99  -mlittle-endian \
$(INCLUDES) -o

LDSCRIPT = stm32_flash.ld

LDFLAGS += -T$(LDSCRIPT) -u _start -u _Minimum_Stack_Size  -mcpu=cortex-m3 -mthumb -specs=nano.specs -specs=nosys.specs -nostdlib -Wl,-static -N -nostartfiles -Wl,--gc-sections

all: $(SYX)

# Mathmatica Build Tools changes the name from "Launchpad Open" to "Launchpad Math"
# Bintosyx converting Binary CFW to SYX (SysEx) flashable file

$(SYX): $(BIN)
	./$(BINTOSYX) /pro 000 $(BIN) $(SYX)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(ELF): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(LIB)

DEPENDS := $(OBJECTS:.o=.d)

-include $(DEPENDS)

$(BUILDDIR)/%.o: %.c
	$(call mkdir,$(dir $@))
	$(CC) -c $(CFLAGS) -MMD -o $@ $<

clean:
	$(call rmdir,$(BUILDDIR))