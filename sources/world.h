#ifndef WORLD_H
#define WORLD_H

// Função para criar o mundo.
void create_world(Game *game) {
	// Define a seed do mundo como um número pseudo-aleatório no intervalo de 1 a 10000.
	game->world.seed = 1 + rand() % 9999;
	
	// Preenche a estrutura chunk.
	int i, j, k;

	for (i = 0; i != CHUNK_MAX; i++) {
		for (j = 0; j != CHUNK_WIDTH; j++) {
			for (k = 0; k != CHUNK_HEIGHT; k++) {
				// Define o tipo do bloco.
				game->world.chunks[i].blocks[j][k].type = DIRT;

				// Configura o retângulo de origem do bloco para a textura no atlas.
				game->world.chunks[i].blocks[j][k].src.x = 0;
				game->world.chunks[i].blocks[j][k].src.y = 496;
				game->world.chunks[i].blocks[j][k].src.w = 16;
				game->world.chunks[i].blocks[j][k].src.h = 16;

				// Configura o retângulo de origem do bloco.
				int x = i * CHUNK_WIDTH * BLOCK_SIZE, y = 0;

				game->world.chunks[i].blocks[j][k].dst.x = x + (j * BLOCK_SIZE);
				game->world.chunks[i].blocks[j][k].dst.y = y + (k * BLOCK_SIZE);
				game->world.chunks[i].blocks[j][k].dst.w = BLOCK_SIZE;
				game->world.chunks[i].blocks[j][k].dst.h = BLOCK_SIZE;
			}
		}
	}
}

#endif // WORLD_H