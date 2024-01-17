#ifndef NANO_H
#define NANO_H
#include "../../structures/structures.h"

extern void copy_terminal_framebuffer(struct params *params);

extern void nano_command(struct params *params, char command_name[25]);

#endif
