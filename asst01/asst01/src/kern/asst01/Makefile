CC=arm-none-eabi-gcc
FPU = -mfloat-abi=hard -mfpu=fpv4-sp-d16
MACH=cortex-m4
TARGET = target
OBJECT = object
MAPDIR = mapfiles
CFLAGS=-c -mcpu=$(MACH) -mthumb $(FPU) -Wall -std=gnu11 -O0
LDFLAGS= -nostdlib -nostartfiles -nodefaultlibs -fno-exceptions -mcpu=$(MACH) -mthumb  $(FPU) -T stm32_ls.ld -Wl,-Map=$(MAPDIR)/asst01.map -O0

all: sys.o scb.o clock.o usart.o gpio.o timer.o kmain.o kstdio.o stm32_startup.o sys_init.o asst01.elf


sys.o: ..\arch\stm32f446re\sys\sys.c
	$(CC) $(CFLAGS) $^ -o $(OBJECT)\$@

scb.o: ..\arch\stm32f446re\dev\scb.c
	$(CC) $(CFLAGS) $^ -o $(OBJECT)\$@

kstdio.o: ..\kstdio\kstdio.c
	$(CC) $(CFLAGS) $^ -o $(OBJECT)\$@
	
kmain.o: ..\kmain\kmain.c
	$(CC) $(CFLAGS) $^ -o $(OBJECT)\$@
	
sys_init.o: ..\kmain\sys_init.c
	$(CC) $(CFLAGS) $^ -o $(OBJECT)\$@

clock.o: ..\arch\stm32f446re\dev\clock.c
	$(CC) $(CFLAGS) $^ -o $(OBJECT)\$@

gpio.o: ..\arch\stm32f446re\dev\gpio.c
	$(CC) $(CFLAGS) $^ -o $(OBJECT)\$@
	
usart.o: ..\arch\stm32f446re\dev\usart.c
	$(CC) $(CFLAGS) $^ -o $(OBJECT)\$@
	
timer.o: ..\arch\stm32f446re\dev\timer.c
	$(CC) $(CFLAGS) $^ -o $(OBJECT)\$@
	
stm32_startup.o: ..\arch\stm32f446re\sys\stm32_startup.c
	$(CC) $(CFLAGS) $^ -o $(OBJECT)\$@
	
asst01.elf: $(OBJECT)\kmain.o $(OBJECT)\stm32_startup.o $(OBJECT)\scb.o $(OBJECT)\clock.o $(OBJECT)\usart.o $(OBJECT)\gpio.o $(OBJECT)\timer.o $(OBJECT)\kstdio.o $(OBJECT)\sys_init.o $(OBJECT)\sys.o
	$(CC) $(LDFLAGS) $^ -o $(TARGET)\$@
clean:
	del $(OBJECT)\*.o $(MAPDIR)\*.map $(TARGET)\*


load:
	openocd -f board/stm32f4discovery.cfg


