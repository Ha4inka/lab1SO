SRC_ASM := \
	src/asm/boot.asm \
	src/asm/low_level_functions.asm \
	src/asm/ex_handlers.asm src/asm/int_handlers.asm
SRC_C   := \
	src/c/entry.c \
	src/c/kernel/idt.c \
	src/c/kernel/gdt.c \
	src/c/kernel/exception_handler.c \
	src/c/kernel/interrupt_handler.c \
	src/c/drivers/keyboard/keyboard.c \
	src/c/drivers/timer/timer.c \
	src/c/drivers/serial_port/serial_port.c \
	src/c/structures/structures.c \
	src/c/functions/functions.c \
	src/c/commands/clear/clear.c \
	src/c/commands/touch/touch.c \
	src/c/commands/rm/rm.c \
	src/c/commands/ls/ls.c \
	src/c/commands/nano/nano.c \
	src/c/commands/cat/cat.c \
	src/c/commands/sleep/sleep.c \
	src/c/file_functions/file_functions.c \
	src/c/screen_saver/screen_saver.c \
	src/c/file_editing/file_editing.c \
	src/c/key_handler/key_handler.c \
	src/c/commands/pink/pink.c

OBJ_ASM := $(patsubst src/asm/%.asm, build/asm/%.o, $(SRC_ASM))
OBJ_C   := $(patsubst %.c, build/kernel/%.o, $(SRC_C))

all: kernel.bin

kernel.bin: $(OBJ_ASM) $(OBJ_C)
	@echo "Linking..."
	@mkdir -p $(@D)
	ld -m elf_i386 -T link.ld -Lbuild $(OBJ_ASM) $(OBJ_C) -o build/kernel.bin

build/asm/%.o: src/asm/%.asm
	@echo "Assembling $<..."
	@mkdir -p $(@D)
	nasm -f elf32 $< -o $@

build/kernel/%.o: %.c
	@echo "Compiling $<..."
	@mkdir -p $(@D)
	gcc -ffreestanding -m32 -fno-pie -Wall -Wextra -c $< -o $@

clean:
	rm -rf build

kernel.iso: kernel.bin
	cp build/kernel.bin iso/boot/kernel.bin
	grub-mkrescue -o build/kernel.iso iso

boot: clean kernel.bin
	qemu-system-i386 -kernel build/kernel.bin

boot_stdio: clean kernel.bin
	qemu-system-i386 -monitor stdio -kernel build/kernel.bin

boot_iso: clean kernel.iso
	qemu-system-i386 -cdrom build/kernel.iso

.PHONY: all clean
