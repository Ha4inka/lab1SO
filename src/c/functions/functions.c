#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../structures/structures.h"
#include "../kernel/kernel.h"

void println(char *msg, int color, struct params *params) {
    if (params->isPink == 1) {
        color = 0xd;
    }

    char *message = msg;
    char *framebuffer = (char *) params->current_address;

    while (*message != '\0') {
        *framebuffer = *message;
        *(framebuffer + 1) = (0x0 << 4) | color;
        framebuffer += 2;
        message++;
    }
}

void put_cursor(unsigned short pos) {
    out(0x3D4, 14);
    out(0x3D5, ((pos >> 8) & 0x00FF));
    out(0x3D4, 15);
    out(0x3D5, pos & 0x00FF);
}

void clear_screen(char color, struct params *params) {
    char *framebuffer = params->framebuffer;
    for (int i = 0; i < (80 * 25); i++) {
        *framebuffer = '\0';
        *(framebuffer + 1) = color;
        framebuffer += 2;
    }

    params->number_of_lines = 0;
    params->current_address = 0xB8000;
}


void clear_arr(char *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = '\0';
    }
}

void output_empty_new_line(struct params *params, int color) {
    if (params->isPink == 1) {
        color = 0xd;
    }

    params->current_line[0] = ' ';
    params->current_line[1] = '$';
    params->current_line[2] = ' ';
    params->current_line[3] = '\0';
    params->current_line_length = 4;
    println(params->current_line, color, params);
}

int get_length(char *msg) {
    char *message = msg;

    int length = 0;

    while (*message != '\0') {
        length++;
        message++;
    }

    return length;
}

int check_if_equal(char *first_string, char *second_string) {
    int first_string_length = get_length(first_string);
    int second_string_length = get_length(second_string);

    if (first_string_length != second_string_length) return 0;

    for (int i = 0; i < second_string_length; i++) {
        if (first_string[i] != second_string[i])
            return 0;
    }
    return 1;
}

void substring(char *string, int start, int end, char inputed_command_name[80]) {
    int len = get_length(string);

    for (int i = start; i < len; i++) {
        if (i == end) {
            break;
        } else {
            inputed_command_name[i - start] = string[i];
        }
    }
    inputed_command_name[end - start] = '\0';
}

void remove_char_from_string(struct params *params) {
    int length = params->current_line_length;
    params->current_line[length - 2] = '\0';
    params->current_line_length--;
}

void add_char_to_string(char pressed_char, struct params *params) {
    int length = params->current_line_length;
    params->current_line[length - 1] = pressed_char;
    params->current_line[length + 1] = '\0';
    params->current_line_length++;
}

void move_cursor(int offset, struct params *params) {
    (params->current_cursor_position) += offset;
    put_cursor(params->current_cursor_position);
}

void clear_one_line(struct params *params) {
    char *framebuffer = (char *) 0xB8000;
    char clear_color = (0x0 << 4) | 0xa;

    if(params->isPink == 1){
        clear_color = (0x0 << 4) | 0xd;
    }


    for (int i = 0; i < (80); i++) {
        *(framebuffer + params->number_of_lines * 160) = ' ';
        *(framebuffer + params->number_of_lines * 160 + 1) = clear_color;
        framebuffer += 2;
    }
}

void copy_framebuffer(struct params *params, struct old_data *old_data) {
    for (int k = 0; k < 25; k++) {
        for (int i = 0; i < 160; i += 2) {
            old_data->framebuffer[k][i / 2] = params->framebuffer[i + 160 * k];
        }
        old_data->framebuffer[k][79] = '\0';
    }
}

void copy_row_colors(struct params *params, struct old_data *old_data) {
    for (int k = 0; k < 25; k++) {
        old_data->row_colors[k] = params->framebuffer[3 + k * 160];
    }
}

void
print_data_from_old_framebuffer(struct params *params, int offset) {
    for (int i = offset; i < 25; i++) {
        println(params->old_data.framebuffer[i], params->old_data.row_colors[i], params);
        params->number_of_lines++;

        params->current_cursor_position = params->number_of_lines * 80 + 3;
        put_cursor(params->current_cursor_position);
        params->current_address += 160;
    }
}

void move_framebuffer(struct params *params) {
    struct old_data old_data = {{0}, {0}, 0};
    copy_framebuffer(params, &old_data);
    copy_row_colors(params, &old_data);
    params->old_data = old_data;


    char clear_color = (0x0 << 4) | 0xa;
    clear_screen(clear_color, params);

    print_data_from_old_framebuffer(params, 1);

    params->current_cursor_position = 3 + 24 * 80;
    put_cursor(params->current_cursor_position);
//    output_empty_new_line(params, 0xd);
}

void move_to_next_line(struct params *params) {
    if (params->number_of_lines > 23) {
        move_framebuffer(params);
    } else {
        params->number_of_lines++;
        params->current_cursor_position = params->number_of_lines * 80 + 3;
        put_cursor(params->current_cursor_position);
        params->current_address += 160;
    }
}

void load_old_data(struct params *params) {
    char clear_color = (0x0 << 4) | 0xa;
    if (params->isPink == 1) {
        clear_color = (0x0 << 4) | 0xd;
    }
    clear_screen(clear_color, params);

    print_data_from_old_framebuffer(params, 0);

    params->number_of_lines = params->old_data.number_of_lines + 1;
    params->current_address = 0xB8000 + params->number_of_lines * 160;
    params->current_cursor_position = 3 + params->number_of_lines * 80;
    put_cursor(params->current_cursor_position);
    if (params->number_of_lines > 23) {
        move_framebuffer(params);
    }
    output_empty_new_line(params, 0xa);
}

void process_data_clearing(struct params *params) {
    clear_one_line(params);

    remove_char_from_string(params);
    println(params->current_line, 0xa, params);

    move_cursor(-1, params);
}

#endif
