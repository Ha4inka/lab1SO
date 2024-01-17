#ifndef FILE_EDITING_H
#define FILE_EDITING_H

#include "../structures/structures.h"

extern void input_one_line(struct old_data *old_data, int line_index, struct file *file);

extern void clone_file_content(struct params *params);

extern void input_file_name(struct file_editing *file_editing, char file_name[25]);

extern void input_file_content(struct params *params, struct file *file, char file_name[25]);

extern void load_data_from_file(struct params *params, int index_of_file);

#endif