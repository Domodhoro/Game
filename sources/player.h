#ifndef PLAYER_H
#define PLAYER_H

static void move_player(Game *game, const DIRECTION direction) {
	switch (direction) {
	case UP:
		game->player.dst.y -= 1;
		break;
	case LEFT:
		game->player.dst.x -= 1;
		break;
	case DOWN:
		game->player.dst.y += 1;
		break;
	case RIGHT:
		game->player.dst.x += 1;
		break;
	}
}

static DIRECTION reverse_direction(DIRECTION direction) {
    switch (direction) {
    case UP:
        return DOWN;
    case DOWN:
        return UP;
    case LEFT:
        return RIGHT;
    case RIGHT:
        return LEFT;
    }
}

static void move_entity_with_collision(Game *game, DIRECTION direction) {
	move_player(game, direction);

	Chunk *current_chunk = game->world.first_chunk;

	while (current_chunk != NULL) {
		int i, j;

		for (i = 0; i != CHUNK_WIDTH; i++) {
			for (j = 0; j != CHUNK_HEIGHT; j++) {
				if (current_chunk->blocks[i][j].type != AIR) {
					if (SDL_HasIntersection(&game->player.dst, &current_chunk->blocks[i][j].dst)) {
						move_player(game, reverse_direction(direction));
					}
				}
			}
		}

        current_chunk = current_chunk->next_chunk;
    }
}

static void handle_gravity(Game *game) {
	int step = 0;

	while (step != GRAVITY_INTENSITY) {
		move_entity_with_collision(game, DOWN);

		step++;
	}
}

void do_player(Game *game) {
	handle_gravity(game);

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
}

#endif