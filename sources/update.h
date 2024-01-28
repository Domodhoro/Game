#ifndef UPDATE_H
#define UPDATE_H

void update(Game *game) {
	update_player(game);
	update_world(game);
    update_camera(game);
    update_inventory(game);
    update_map(game);
}

#endif