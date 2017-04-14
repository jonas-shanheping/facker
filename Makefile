CC=arm-none-eabi-gcc
CXX=arm-none-eabi-gcc
LD=arm-none-eabi-ld
AR=arm-none-eabi-ar
AS=arm-none-eabi-as
CP=arm-none-eabi-objcopy
OD=arm-none-eabi-objdump
NM=arm-none-eabi-nm
SIZE=arm-none-eabi-size
A2L=arm-none-eabi-addr2line

BINDIR=bin
BINELF=facker.elf
BIN=facker.bin

INCLUDES= \
   -Iinc \
   -Ilib/BSP/STM32F411E-Discovery \
   -Ilib/STM32F4xx_HAL_Driver/Inc \
   -Ilib/CMSIS/Include \
   -Ilib/CMSIS/Device/ST/STM32F4xx/Include \

ASOURCES= \
	src/startup_stm32f411xe.s

CSOURCES= \
	src/stm32f4xx_it.c \
	src/system_stm32f4xx.c \
	src/stm32f4xx_hal_msp.c \
	lib/BSP/STM32F411E-Discovery/stm32f411e_discovery.c \
	lib/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
	lib/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
	lib/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
	lib/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
	lib/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
	lib/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
	lib/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
	lib/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c

CSOURCES+=	\
	src/main.c src/ft_send.c src/ft_manager.c \
	src/ft_init.c src/ft_timer.c\

INCLUDES_LIBS=
LINK_LIBS=

OBJECTS=$(ASOURCES:%.s=%.o)
OBJECTS+=$(CSOURCES:%.c=%.o)
OBJECTS+=$(CXXSOURCES:%.c=%.o)

CFLAGS=-c -g -Wall -mcpu=cortex-m4 -mlittle-endian -mthumb -DSTM32F411xE \
    -Os -flto -ffunction-sections -fdata-sections -fno-builtin -fno-exceptions $(INCLUDES) 

LDFLAGS=-mcpu=cortex-m4 -mlittle-endian -mthumb -DSTM32F411xE -TSTM32F411VETx_FLASH.ld -Wl,--gc-sections -g -Wl,-Map=facker.map

all: $(SOURCES) $(BINDIR)/$(BIN)
    
flash: $(BINDIR)/$(BIN)
	st-flash --reset write $(BINDIR)/$(BIN) 0x8000000 
   
$(BINDIR)/$(BIN): $(BINDIR)/$(BINELF)
	$(CP) -O binary $< $@
    
$(BINDIR)/$(BINELF): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@
	@echo "Linking complete!\n"
	$(SIZE) $(BINDIR)/$(BINELF)
	rm -f $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo "Compiled "$<"!\n"

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	@echo "Compiled "$<"!\n"

%.o: %.s
	$(CC) $(CFLAGS) $< -o $@
	@echo "Assembled "$<"!\n"

clean:
	rm -f $(OBJECTS) $(BINDIR)/$(BINELF) $(BINDIR)/$(BIN) $(BINDIR)/output.map
