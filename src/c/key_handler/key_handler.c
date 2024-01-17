#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

#include <stddef.h>
#include "../functions/functions.h"
#include "../drivers/keyboard/keyboard.h"
#include "../structures/structures.h"
#include "../file_editing/file_editing.h"

void handle_other_keys(struct keyboard_event event, struct params *params) {
    add_char_to_string(event.key_character, params);
    println(params->current_line, 0xa, params);
    move_cursor(1, params);
}

void handle_backspace_key(struct params *params) {
    if (params->edit_mode == 1 && params->current_line_length > 1) {
        process_data_clearing(params);
    } else if (params->current_line_length > 4) {
        process_data_clearing(params);
    }

    if (params->sleep_mode == 1) {
        params->sleep_mode = 0;
        load_old_data(params);
    }
}

void process_the_command(struct command *arr_of_commands, struct params *params) {
    int length = 0;
    while (arr_of_commands[length].name != NULL) {
        length++;
    }

    int isFound = 0;
    for (int i = 0; i < length; i++) {
        char *actual_command_name = arr_of_commands[i].name;
        int actual_command_name_length = get_length(actual_command_name);

        char inputed_command_name[80];
        substring(params->current_line, 3, actual_command_name_length + 3, inputed_command_name);
        int res = check_if_equal(inputed_command_name, actual_command_name);
        if (res == 1) {
            isFound = 1;
            arr_of_commands[i].execute(params, arr_of_commands[i].name);
        }
    }
    if (isFound == 0) {
        move_to_next_line(params);
        println("command not found", 0xc, params);

        move_to_next_line(params);
        output_empty_new_line(params, 0xa);
    }
}

void handle_enter_key(struct params *params, struct command *arr_of_commands) {
    if (params->edit_mode == 0) {
        process_the_command(arr_of_commands, params);
    } else {
        params->number_of_lines++;
        params->current_cursor_position = params->number_of_lines * 80;
        put_cursor(params->current_cursor_position);
        params->current_address = 0xB8000 + params->number_of_lines * 160;
        params->current_line_length = 1;
        println(" ", 0xa, params);
    }
}

void handle_escape_key(struct params *params) {
    if (params->edit_mode == 0) return;

    params->edit_mode = 0;
    clone_file_content(params);
    load_old_data(params);
}

void handle_arrow_key(struct params *params, int offset) {
    params->current_cursor_position += offset;
    params->current_address += offset * 2;
    put_cursor(params->current_cursor_position);
}

#endif