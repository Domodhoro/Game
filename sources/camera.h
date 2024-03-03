#ifndef CAMERA_H
#define CAMERA_H

void update_camera(Game *game) {
	game->camera_position.x = game->player.dst.x + (PLAYER_WIDTH - WINDOW_WIDTH) / 2;
    game->camera_position.y = game->player.dst.y + (PLAYER_HEIGHT - WINDOW_HEIGHT) / 2;
}

#endif