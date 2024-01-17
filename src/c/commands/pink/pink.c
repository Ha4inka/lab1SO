#ifndef PINK_H
#define PINK_H

#include <stdbool.h>
#include "../../structures/structures.h"
#include "../../functions/functions.h"
#include "../../file_functions/file_functions.h"
#include "../../file_editing/file_editing.h"

void pink_command(struct params *params, char command_name[25]){
    params->isPink = 1;

    move_to_next_line(params);
    output_empty_new_line(params, 0xd);
}

#endif