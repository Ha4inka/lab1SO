#ifndef SLEEP_H
#define SLEEP_H

#include "../../structures/structures.h"
#include "../../functions/functions.h"
#include "../../file_functions/file_functions.h"

void sleep_command(struct params *params, char command_name[25]) {
    struct old_data old_data = {{0}, {0}, 0};
    copy_framebuffer(params, &old_data);
    copy_row_colors(params, &old_data);
    params->old_data = old_data;
    params->old_data.number_of_lines = params->number_of_lines;

    params->sleep_mode = 1;

    char clear_color = (0x0 << 4) | 0xA;
    clear_screen(clear_color, params);

    clear_arr(params->current_line, 80);
    params->current_line_length = 1;
    params->current_cursor_position = 0;

    put_cursor(params->current_cursor_position);
}

#endif
