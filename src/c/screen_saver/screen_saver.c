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

void intialize_icon(struct screen_saver *screen_saver){
    screen_saver->icon[0] = "xxx xxx";
    screen_saver->icon[1] = "x x x  ";
    screen_saver->icon[2] = "x x xxx";
    screen_saver->icon[3] = "x x   x";
    screen_saver->icon[4] = "xxx xxx";
}

void handle_movement(struct params *params, struct screen_saver *screen_saver) {
    params->current_address = screen_saver->current_address;
    switch (screen_saver->direction) {
        case DOWN_RIGHT:
            screen_saver->current_address += 162;
            break;
        case UP_RIGHT:
            screen_saver->current_address -= 158;
            break;
        case UP_LEFT:
            screen_saver->current_address -= 162;
            break;
        case DOWN_LEFT:
            screen_saver->current_address += 158;
            break;
    }
}

void handle_icon_bounce(struct screen_saver *screen_saver) {
    if (screen_saver->current_address > 0xB8000 + 160 * 20 && screen_saver->direction == DOWN_RIGHT) {
        screen_saver->direction = UP_RIGHT;
    } else if ((screen_saver->current_address - 0xB8000) % 160 == 0 && screen_saver->direction == UP_LEFT) {
        screen_saver->direction = UP_RIGHT;
    } else if ((screen_saver->current_address - 0xB8000) % 160 == 0 && screen_saver->direction == DOWN_LEFT) {
        screen_saver->direction = DOWN_RIGHT;
    } else if (screen_saver->current_address > 0xB8000 + 160 * 20 && screen_saver->direction == DOWN_LEFT) {
        screen_saver->direction = UP_LEFT;
    } else if (screen_saver->current_address < 0xB8000 + 160 && screen_saver->direction == UP_LEFT) {
        screen_saver->direction = DOWN_LEFT;
    } else if ((screen_saver->current_address - 0xB8000 + 4) % 160 == 150 && screen_saver->direction == UP_RIGHT) {
        screen_saver->direction = UP_LEFT;
    } else if ((screen_saver->current_address - 0xB8000 + 4) % 160 == 150 && screen_saver->direction == DOWN_RIGHT) {
        screen_saver->direction = DOWN_LEFT;
    } else if (screen_saver->current_address < 0xB8000 + 160 && screen_saver->direction == UP_RIGHT) {
        screen_saver->direction = DOWN_RIGHT;
    }
}

#endif
