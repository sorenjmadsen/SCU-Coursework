PREFIX=~/Documents/Programs/COEN20/workspace/tools/bin/
CC=$(PREFIX)arm-none-eabi-gcc
AS=$(PREFIX)arm-none-eabi-as
OBJCOPY=$(PREFIX)arm-none-eabi-objcopy
SIZE=$(PREFIX)arm-none-eabi-size

AFLAGS=-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS=-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -std=c99 -O3 -Wall -ffunction-sections -fdata-sections -fno-strict-aliasing
LFLAGS=-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 $(LIB) -lc -lnosys -lc -u _printf_float -Wl,-gc-sections -T linker.ld -Wl,-Map,$(MAP)

CFILES=$(wildcard src/*.c)
SFILES=$(wildcard src/*.s)
OFILES=$(patsubst src/%.c,obj/%.o,$(CFILES)) $(patsubst src/%.s,obj/%.o,$(SFILES))

LIB	=	library.a
ELF	=	output.elf
BIN	=	output.bin
MAP	=	output.map

all:		$(BIN)

$(BIN):	$(ELF)
		$(OBJCOPY) -O binary $(ELF) $(BIN)
		$(SIZE) --target=binary $(BIN)

$(ELF):	$(OFILES) $(LIB)
		$(CC) -o $(ELF) $(OFILES) $(LIB) $(LFLAGS)

obj/%.o:	src/%.c
		$(CC) $(CFLAGS) -Iinc -c -o $@ $<

obj/%.o:	src/%.s
		$(AS) $(AFLAGS) -o $@ $<
