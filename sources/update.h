#ifndef UPDATE_H
#define UPDATE_H

void update(Game *game) {
	do_player(game);
	do_world(game);
    do_camera(game);
    do_inventory(game);
    do_map(game);
}

#endif