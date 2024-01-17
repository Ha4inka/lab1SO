#ifndef CLEAR_H
#define CLEAR_H

#include "../../structures/structures.h"
#include "../../functions/functions.h"

void clear_command(struct params *params, char command_name[25]) {
    char clear_color = (0x0 << 4) | 0xA;
    clear_screen(clear_color, params);
    params->current_cursor_position = 3;

    put_cursor(params->current_cursor_position);
    output_empty_new_line(params, 0xa);
}

#endif