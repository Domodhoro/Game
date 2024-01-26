#ifndef WORLD_H
#define WORLD_H

void create_world(Game *game) {
	game->world.seed = 1 + rand() % 9999;
	
	game->world.first_chunk = NULL;
}

void destroy_world(Game *game) {
    while (game->world.first_chunk != NULL) {
        Chunk *temp = game->world.first_chunk;

        game->world.first_chunk = game->world.first_chunk->next_chunk;

        if (temp != NULL) {
            free(temp);
        }
    }
}

void world_update(Game *game) {
    int player_chunk_x = game->player.dst.x / BLOCK_SIZE;

    if (player_chunk_x >= 0) {
        player_chunk_x /= CHUNK_WIDTH;
    }
    else {
        player_chunk_x = ((player_chunk_x + 1) / CHUNK_WIDTH) - 1;
    }

    int i;

    for (i = -WORLD_SIZE; i != WORLD_SIZE + 1; i++) {
    	add_chunk(&game->world, (player_chunk_x + i) * CHUNK_WIDTH * BLOCK_SIZE, 700);
    }
}

#endif