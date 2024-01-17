#ifndef TOUCH_H
#define TOUCH_H

#include "../../structures/structures.h"
#include "../../functions/functions.h"
#include "../../file_functions/file_functions.h"

void touch_command(struct params *params, char command_name[25]) {
    char file_name[25];
    get_file_name(params->current_line, command_name, file_name);

    int length = get_length(file_name);
    if (length == 0) {
        move_to_next_line(params);
        println("specify the file name", 0xc, params);
    } else {
        int res = get_index_of_file(params, file_name);
        if (res == -1) {
            struct file file = create_new_file(file_name);
            int index = get_index_of_next_empty_file(params->arr_of_files);
            params->arr_of_files[index] = file;

            move_to_next_line(params);
            println("file was created", 0xa, params);
        } else {
            move_to_next_line(params);
            println("file already exists", 0xc, params);
        }
    }

    move_to_next_line(params);
    output_empty_new_line(params, 0xa);
}

#endif
