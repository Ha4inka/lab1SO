#ifndef LS_H
#define LS_H

#include "../../structures/structures.h"
#include "../../functions/functions.h"

void ls_command(struct params *params, char command_name[25]) {
    for (int i = 0; i < 100; i++) {
        struct file file = params->arr_of_files[i];
        if (file.name[0] != '\0') {
            move_to_next_line(params);
            println(file.name, 0xa, params);
        }
    }

    move_to_next_line(params);
    output_empty_new_line(params, 0xa);
}

#endif
