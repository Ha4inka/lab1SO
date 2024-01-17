#ifndef STRUCTURES_H
#define STRUCTURES_H

struct old_data {
    char framebuffer[25][80];
    char row_colors[25];
    int number_of_lines;
};

struct file_editing {
    char current_file_name[25];
    char file_contant[25][80];
};

struct file {
    char content[25][80];
    char name[25];
};

struct command {
    char *name;

    void (*execute)(struct params *, char name[25]);
};


struct params {
    int current_address;
    int current_cursor_position;
    char current_line[80];
    int current_line_length;
    int number_of_lines;
    struct file arr_of_files[100];
    int edit_mode;
    int sleep_mode;
    char *framebuffer;
    struct old_data old_data;
    struct file_editing file_editing;
    int isPink;
};

#endif
