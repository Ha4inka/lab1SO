#include <stddef.h>
#include "kernel/kernel.h"
#include "drivers/keyboard/keyboard.h"
#include "drivers/timer/timer.h"
#include "drivers/serial_port/serial_port.h"
#include "structures/structures.h"
#include "functions/functions.h"
#include "commands/nano/nano.h"
#include "commands/clear/clear.h"
#include "commands/touch/touch.h"
#include "commands/cat/cat.h"
#include "commands/rm/rm.h"
#include "commands/ls/ls.h"
#include "commands/sleep/sleep.h"
#include "commands/pink/pink.h"
#include "key_handler/key_handler.h"
#include "screen_saver/screen_saver.h"

// resolve erasing issue in editing mode

struct params params = {0xB8000,
                        3,
                        " $ ",
                        4,
                        0,
                        {0},
                        0,
                        0,
                        (char *) 0xB8000,
                        {
                                {0},
                                {0},
                                0
                        },
                        {"", {0}}
};

struct command arr_of_commands[] = {
        {"touch", touch_command},
        {"cat",   cat_command},
        {"clear", clear_command},
        {"rm",    rm_command},
        {"ls",    ls_command},
        {"sleep", sleep_command},
        {"nano",  nano_command},
        {"pink", pink_command},
        {NULL, NULL}
};

struct screen_saver screen_saver = {
        0xB8000,
        DOWN_RIGHT,
        {0}
};

struct file_editing file_editing = {""};

void exception_handler(u32 interrupt, u32 error, char *message) {
    serial_log(LOG_ERROR, message);
}

void init_kernel() {
    init_gdt();
    init_idt();
    init_exception_handlers();
    init_interrupt_handlers();
    register_timer_interrupt_handler();
    register_keyboard_interrupt_handler();
    configure_default_serial_port();
    set_exception_handler(exception_handler);
    enable_interrupts();
}

/**
 * In order to avoid execution of arbitrary instructions by CPU we halt it.
 * Halt "pauses" CPU and puts it in low power mode until next interrupt occurs.
 */
_Noreturn void halt_loop() {
    while (1) {
        halt();
    }
}

void key_handler(struct keyboard_event event) {
    if (event.key_character && event.type == EVENT_KEY_PRESSED) {
        if (params.sleep_mode == 1) {
            params.sleep_mode = 0;
            load_old_data(&params);
            screen_saver.current_address = 0xB8000;
            screen_saver.direction = DOWN_RIGHT;
        } else if (event.key == KEY_ENTER) {
            handle_enter_key(&params, arr_of_commands);
        } else if (event.key == KEY_BACKSPACE) {
            handle_backspace_key(&params);
        } else if (event.key == KEY_ESC) {
            handle_escape_key(&params);
        } else if (event.key == KEY_KEYPAD_4 && params.edit_mode == 1) {
            handle_arrow_key(&params, -1);
        } else if (event.key == KEY_KEYPAD_6 && params.edit_mode == 1) {
            handle_arrow_key(&params, 1);
        } else {
            handle_other_keys(event, &params);
        }
    }
}

void timer_tick_handler() {
    if (params.sleep_mode == 1) {
        char clear_color = (0x0 << 4) | 0xA;
        clear_screen(clear_color, &params);

        handle_movement(&params, &screen_saver);
        handle_icon_bounce(&screen_saver);

        for (int i = 0; i < 5; i++) {
            println(screen_saver.icon[i], 0xa, &params);
            move_to_next_line(&params);
        }

        put_cursor(0);
    }
}

/**
 * This is where the bootloader transfers control to.
 */

void kernel_entry() {
    init_kernel();
    keyboard_set_handler(key_handler);
    timer_set_handler(timer_tick_handler);

    intialize_icon(&screen_saver);

    char clear_color = (0x0 << 4) | 0xA;
    clear_screen(clear_color, &params);
    params.current_cursor_position = 3;

    println("Shell 0.0.1", 0xa, &params);

    move_to_next_line(&params);
    println(params.current_line, 0xa, &params);
    halt_loop();
}
