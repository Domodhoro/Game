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

Chunk *create_chunk(const int x, const int y) {
	Chunk *new_chunk = malloc(sizeof(Chunk));

	if (new_chunk == NULL) {
        custom_error("Failed to allocate memory.", __FILE__, __LINE__);
    }

	int i, j;

	for (i = 0; i != CHUNK_WIDTH; i++) {
		for (j = 0; j != CHUNK_HEIGHT; j++) {
			new_chunk->blocks[i][j].type = DIRT;

			new_chunk->blocks[i][j].src.x = 0;
			new_chunk->blocks[i][j].src.y = 496;
			new_chunk->blocks[i][j].src.w = 16;
			new_chunk->blocks[i][j].src.h = 16;

			new_chunk->blocks[i][j].dst.x = x + (i * BLOCK_SIZE);
			new_chunk->blocks[i][j].dst.y = y + (j * BLOCK_SIZE);
			new_chunk->blocks[i][j].dst.w = BLOCK_SIZE;
			new_chunk->blocks[i][j].dst.h = BLOCK_SIZE;
		}
	}

	new_chunk->position.x = x;
	new_chunk->position.y = y;
    
	new_chunk->next_chunk = NULL;

	return new_chunk;
}

void add_chunk(World *world, const int x, const int y) {
    if (!chunk_exists(world, x, y)) {
        Chunk *new_chunk = create_chunk(x, y);

        if (world->first_chunk == NULL) {
            world->first_chunk = new_chunk;
        } 
        else {
            Chunk *current_chunk = world->first_chunk;

            while (current_chunk->next_chunk != NULL) {
                current_chunk = current_chunk->next_chunk;
            }

            current_chunk->next_chunk = new_chunk;
        }   
    }
}

void remove_chunk(World *world, const int x, const int y) {
	Chunk *current_chunk = world->first_chunk, *prev = NULL;

    while (current_chunk != NULL && (current_chunk->position.x != x || current_chunk->position.y != y)) {
        prev = current_chunk;

        current_chunk = current_chunk->next_chunk;
    }

    if (current_chunk != NULL) {
        if (prev == NULL) {
            world->first_chunk = current_chunk->next_chunk;
        }
        else {
            prev->next_chunk = current_chunk->next_chunk;
        }

        free(current_chunk);
    }
}

#endif