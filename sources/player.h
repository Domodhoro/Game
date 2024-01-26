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

void create_player(Game *game) {
	game->player.speed = 5;
	game->player.hearts = 10;

	game->player.src.x = 0;
	game->player.src.y = 960;
	game->player.src.w = 64;
	game->player.src.h = 64;

	game->player.dst.x = (WINDOW_WIDTH - PLAYER_WIDTH) / 2;
	game->player.dst.y = (WINDOW_HEIGHT - PLAYER_HEIGHT) / 2;
	game->player.dst.w = PLAYER_WIDTH;
	game->player.dst.h = PLAYER_HEIGHT;
}

void move_entity_with_collision(Game *game, DIRECTION direction) {
	move_player(game, direction);

	Chunk *current_chunk = game->world.first_chunk;

	while (current_chunk != NULL) {
		int i = 0, j = 0;

		for (i = 0; i != CHUNK_WIDTH; i++) {
			for (j = 0; j != CHUNK_HEIGHT; j++) {
				if (SDL_HasIntersection(&game->player.dst, &current_chunk->blocks[i][j].dst)) {
					move_player(game, reverse_direction(direction));
				}
			}
		}

        current_chunk = current_chunk->next_chunk;
    }
}

#endif