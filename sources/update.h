#ifndef UPDATE_H
#define UPDATE_H

static void player_update(Game *game) {
	int step = 0;

	while (step != game->player.speed) {
		if (game->keys.W) {
			move_entity_with_collision(game, UP);
		}

		if (game->keys.A) {
			move_entity_with_collision(game, LEFT);
		}

		if (game->keys.S) {
			move_entity_with_collision(game, DOWN);
		}

		if (game->keys.D) {
			move_entity_with_collision(game, RIGHT);
		}

		step++;
	}

	step = 0;

	while (step != GRAVITY_INTENSITY) {
		move_entity_with_collision(game, DOWN);

		step++;
	}
}

static void camera_update(Game *game) {
	game->camera_position.x = game->player.dst.x + (PLAYER_WIDTH - WINDOW_WIDTH) / 2;
    game->camera_position.y = game->player.dst.y + (PLAYER_HEIGHT - WINDOW_HEIGHT) / 2;
}

void update(Game *game) {
	world_update(game);
	player_update(game);
    camera_update(game);
    inventory_update(game);
    map_update(game);
}

#endif