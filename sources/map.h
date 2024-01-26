#ifndef MAP_H
#define MAP_H

void do_map(Game *game) {
	static _Bool previous_state = false;

    if (game->keys.M && !previous_state) {
        game->map.show_map_frame = !game->map.show_map_frame;
    }

    previous_state = game->keys.M;
}

#endif