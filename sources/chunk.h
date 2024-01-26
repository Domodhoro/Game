#ifndef CHUNK_H
#define CHUNK_H

static _Bool chunk_exists(World *world, const int x, const int y) {
    Chunk *current_chunk = world->first_chunk;

    while (current_chunk != NULL) {
        if (current_chunk->position.x == x && current_chunk->position.y == y) {
            return true;
        }

        current_chunk = current_chunk->next_chunk;
    }

    return false;
}

static Chunk *create_chunk(Game *game, const int x, const int y) {
	Chunk *new_chunk = malloc(sizeof(Chunk));

	if (new_chunk == NULL) {
        custom_error("Failed to allocate memory.", __FILE__, __LINE__);
    }

	int i, j;

	for (i = 0; i != CHUNK_WIDTH; i++) {
		for (j = 0; j != CHUNK_HEIGHT; j++) {
            int block_x = x + (i * BLOCK_SIZE), block_y = y + (j * BLOCK_SIZE);

            if (fnlGetNoise2D(&game->world.noise, block_x, block_y) > 0.25) {
                new_chunk->blocks[i][j].type = DIRT;

                new_chunk->blocks[i][j].dst.x = block_x;
                new_chunk->blocks[i][j].dst.y = block_y;
                new_chunk->blocks[i][j].dst.w = BLOCK_SIZE;
                new_chunk->blocks[i][j].dst.h = BLOCK_SIZE;
            }
            else {
                new_chunk->blocks[i][j].type = AIR;

                new_chunk->blocks[i][j].dst.x = block_x;
                new_chunk->blocks[i][j].dst.y = block_y;
                new_chunk->blocks[i][j].dst.w = BLOCK_SIZE;
                new_chunk->blocks[i][j].dst.h = BLOCK_SIZE;
            }
		}
	}

	new_chunk->position.x = x;
	new_chunk->position.y = y;
    
	new_chunk->next_chunk = NULL;

	return new_chunk;
}

void add_chunk(Game *game, const int x, const int y) {
    if (!chunk_exists(&game->world, x, y)) {
        Chunk *new_chunk = create_chunk(game, x, y);

        if (game->world.first_chunk == NULL) {
            game->world.first_chunk = new_chunk;
        } 
        else {
            Chunk *current_chunk = game->world.first_chunk;

            while (current_chunk->next_chunk != NULL) {
                current_chunk = current_chunk->next_chunk;
            }

            current_chunk->next_chunk = new_chunk;
        }   
    }
}

void remove_chunk(Game *game, const int x, const int y) {
	Chunk *current_chunk = game->world.first_chunk, *prev = NULL;

    while (current_chunk != NULL && (current_chunk->position.x != x || current_chunk->position.y != y)) {
        prev = current_chunk;

        current_chunk = current_chunk->next_chunk;
    }

    if (current_chunk != NULL) {
        if (prev == NULL) {
            game->world.first_chunk = current_chunk->next_chunk;
        }
        else {
            prev->next_chunk = current_chunk->next_chunk;
        }

        free(current_chunk);
    }
}

#endif