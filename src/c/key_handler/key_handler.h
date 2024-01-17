#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

#include "../functions/functions.h"
#include "../drivers/keyboard/keyboard.h"
#include "../structures/structures.h"

extern void handle_other_keys(struct keyboard_event event, struct params *params);

extern void handle_backspace_key(struct params *params);

extern void handle_enter_key(struct params *params, struct command *arr_of_commands);

extern void handle_escape_key(struct params *params);

extern void process_the_command(struct command *arr_of_commands, struct params *params);

extern void handle_arrow_key(struct params *params, int offset);

#endif