#ifndef CAT_H
#define CAT_H

#include "../../structures/structures.h"
#include "../../functions/functions.h"
#include "../../file_functions/file_functions.h"
#include "../../file_editing/file_editing.h"

void cat_command(struct params *params, char command_name[25]) {
    char file_name[25];
    get_file_name(params->current_line, command_name, file_name);

    int length = get_length(file_name);
    if (length == 0) {
        move_to_next_line(params);
        println("specify the file name", 0xc, params);
    } else {
        int index_of_file = get_index_of_file(params, file_name);
//        struct file file = params->arr_of_files[index_of_file];
//
//        input_file_content(params, &file);
//        params->arr_of_files[index_of_file] = file;

        struct file file = params->arr_of_files[index_of_file];
        move_to_next_line(params);
        for (int i = 0; i < 25; i++) {
            if (file.content[i][0] == '\0') break;
            println(file.content[i], 0xa, params);
            move_to_next_line(params);
        }
    }

    output_empty_new_line(params, 0xa);
}

#endif
