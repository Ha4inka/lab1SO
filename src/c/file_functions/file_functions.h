#ifndef FILE_FUNCTIONS_H
#define FILE_FUNCTIONS_H

#include "../structures/structures.h"
#include "../functions/functions.h"

extern int get_index_of_file(struct params *params, char file_name[25]);

extern void get_file_name(char string[80], char command_name[25], char file_name[25]);

extern struct file create_new_file(char file_name[25]);

extern int get_index_of_next_empty_file(struct file arr_of_files[100]);

extern void delete_file(char file_name[25], int index, struct file arr_of_files[100]);

#endif
