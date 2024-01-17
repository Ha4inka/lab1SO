#ifndef NANO_H
#define NANO_H

#include "../../structures/structures.h"
#include "../../functions/functions.h"
#include "../../file_functions/file_functions.h"
#include "../../file_editing/file_editing.h"

void copy_terminal_framebuffer(struct params *params) {
    struct old_data old_data = {{0}, {0}, 0};
    copy_framebuffer(params, &old_data);
    copy_row_colors(params, &old_data);
    params->old_data = old_data;
    params->old_data.number_of_lines = params->number_of_lines;
}

void nano_command(struct params *params, char command_name[25]) {
    char file_name[25];
    get_file_name(params->current_line, command_name, file_name);

    int file_name_length = get_length(file_name);
    if (file_name_length == 0) {
        move_to_next_line(params);
        println("specify the file name", 0xc, params);
    } else {
        int index_of_file = get_index_of_file(params, file_name);
        if (index_of_file != -1) {
            struct file_editing file_editing;
            input_file_name(&file_editing, file_name);
            params->file_editing = file_editing;

            copy_terminal_framebuffer(params);

            params->edit_mode = 1;

            char clear_color = (0x0 << 4) | 0xA;
            clear_screen(clear_color, params);

            params->current_cursor_position = 0;
            put_cursor(params->current_cursor_position);
            if (params->arr_of_files[index_of_file].content[0][0] != '\0') {
                load_data_from_file(params, index_of_file);
                params->current_address =
                        0xB8000 + params->number_of_lines * 160 + params->current_line_length * 2;
                params->current_cursor_position =
                        params->number_of_lines * 80 + params->current_line_length;
                put_cursor(params->current_cursor_position);
            }


            clear_arr(params->current_line, 80);
            params->current_line_length = 1;

            struct file file = params->arr_of_files[index_of_file];
            input_file_content(params, &file, file_name);

            params->arr_of_files[index_of_file] = file;
        } else {
            move_to_next_line(params);
            println("file does not exist", 0xc, params);

            move_to_next_line(params);
            output_empty_new_line(params, 0xa);
        }
    }

}

#endif