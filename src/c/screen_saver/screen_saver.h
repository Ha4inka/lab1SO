#ifndef SCREEN_SAVER_H
#define SCREEN_SAVER_H

#include "../structures/structures.h"

enum direction {
    DOWN_RIGHT,
    UP_RIGHT,
    UP_LEFT,
    DOWN_LEFT
};

struct screen_saver {
    int current_address;
    enum direction direction;
    char *icon[5];
};

void intialize_icon(struct screen_saver *screen_saver);

void handle_movement(struct params *params, struct screen_saver *screen_saver);

void handle_icon_bounce(struct screen_saver *screen_saver);

#endif
