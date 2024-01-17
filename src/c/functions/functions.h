#ifndef FUNCTIONS_H
#define FUNCTIONS_H

extern int check_if_equal(char *first_string, char *second_string);

extern int get_length(char *msg);

extern void substring(char *string, int start, int end, char inputed_command_name[80]);

extern void remove_char_from_string(struct params *params);

extern void add_char_to_string(char pressed_char, struct params *params);

extern void put_cursor(unsigned short pos);

extern void move_cursor(int offset, struct params *params);

extern void move_to_next_line(struct params *params);

extern void clear_screen(char color, struct params *params);

extern void clear_arr(char *arr, int n);

extern void output_empty_new_line(struct params *params, int color);

extern void clear_one_line(struct params *params);

extern void copy_row_colors(struct params *params, struct old_data *old_data);

extern void copy_framebuffer(struct params *params, struct old_data *old_data);

extern void move_framebuffer(struct params *params);

extern void
print_data_from_old_framebuffer(struct params *params, int offset);

extern void println(char *msg, int color, struct params *params);

extern void load_old_data(struct params *params);

extern void process_data_clearing(struct params *params);

#endif
