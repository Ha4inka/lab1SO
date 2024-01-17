#ifndef FILE_FUNCTIONS_H
#define FILE_FUNCTIONS_H

#include "../structures/structures.h"
#include "../functions/functions.h"

int get_index_of_file(struct params *params, char file_name[25]) {
    for (int i = 0; i < 100; i++) {
        struct file file = params->arr_of_files[i];
        if (file.name[0] != '\0') {
            int res = check_if_equal(file.name, file_name);
            if (res == 1) return i;
        }
    }
    return -1;
}

void get_file_name(char string[80], char command_name[25], char file_name[25]) {
    int command_name_length = get_length(command_name);
    int start = command_name_length + 4;

    int index = start;
    while (string[index] != ' ' && string[index] != '\0') {
        file_name[index - start] = string[index];
        index++;
    }


    file_name[index] = '\0';
}

struct file create_new_file(char file_name[25]) {
    int file_name_length = get_length(file_name);

    struct file file = {
            .content = {0},
            .name = {0}
    };

    for (int i = 0; i < file_name_length; i++) {
        file.name[i] = file_name[i];
    }
    file.name[file_name_length] = '\0';
    return file;
}

void delete_file(char file_name[25], int index, struct file arr_of_files[100]) {
    struct file file = {
            .content = {0},
            .name = {0}
    };

    arr_of_files[index] = file;
}

int get_index_of_next_empty_file(struct file arr_of_files[100]) {
    for (int i = 0; i < 100; i++) {
        if (arr_of_files[i].name[0] == '\0') {
            return i;
        }
    }
    return 0;
}

#endif
