#ifndef FILE_EDITING_H
#define FILE_EDITING_H

#include "../functions/functions.h"
#include "../structures/structures.h"
#include "../file_functions/file_functions.h"

void input_one_line(struct old_data *old_data, int line_index, struct file *file) {
    for (int char_index = 0; char_index < 80; char_index++) {
        file->content[line_index][char_index] = old_data->framebuffer[line_index][char_index];
    }
}

void clone_file_content(struct params *params) {
    struct file_editing file_editing = params->file_editing;

    int index = get_index_of_file(params, file_editing.current_file_name);
    struct file file = params->arr_of_files[index];

    struct old_data old_data = {{0}, {0}, 0};
    copy_framebuffer(params, &old_data);

    for (int i = 0; i < 25; i++) {
        if (old_data.framebuffer[i][0] != '\0') {
            input_one_line(&old_data, i, &file);
        }
    }

    params->file_editing = file_editing;
    params->arr_of_files[index] = file;
}

void input_file_name(struct file_editing *file_editing, char file_name[25]) {
    int length = get_length(file_name);
    for (int i = 0; i < length; i++) {
        file_editing->current_file_name[i] = file_name[i];
    }
    file_editing->current_file_name[length] = '\0';
}

void input_file_content(struct params *params, struct file *file, char file_name[25]) {
    struct file_editing file_editing = params->file_editing;

    for (int i = 0; i < 25; i++) {
        if (file_editing.file_contant[i][0] == '\0') break;
        for (int k = 0; k < 80; k++) {
            if (file_editing.file_contant[i][k] == '\0') break;
            file->content[i][k] = file_editing.file_contant[i][k];
        }
    }

    for (int i = 0; i < 25; i++) {
        file->name[i] = file_name[i];
    }
}

void load_data_from_file(struct params *params, int index_of_file) {
    struct file file = params->arr_of_files[index_of_file];

    for(int i = 0; i< 25; i++){
        println(file.content[i], 0xa, params);
        if(file.content[i + 1][0] == '\0') {
            int length = get_length(file.content[i]);
            params->current_line_length = length;
            return;
        }
        move_to_next_line(params);
    }
}

#endif