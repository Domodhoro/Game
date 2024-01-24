#ifndef WORLD_H
#define WORLD_H

// Função para criar um pedaço gerenciável do mundo.
void create_chunk(Game *game, const int x, const int y) {
	// Aloca dinamicamente a estrutura do chunk e verifica se houve erro na alocação de memória.
	game->world.chunk = malloc(sizeof(Chunk));

	if (game->world.chunk == NULL) custom_error("Error allocating memory.\n", __FILE__, __LINE__);

	// Preenche a estrutura chunk.
	int i, j;

	for (i = 0; i != CHUNK_WIDTH; i++) {
		for (j = 0; j != CHUNK_HEIGHT; j++) {
			// Define o tipo do bloco.
			game->world.chunk->blocks[i][j].type = DIRT;

			// Configura o retângulo de origem do bloco para a textura no atlas.
			game->world.chunk->blocks[i][j].src.x = 0;
			game->world.chunk->blocks[i][j].src.y = 496;
			game->world.chunk->blocks[i][j].src.w = 16;
			game->world.chunk->blocks[i][j].src.h = 16;

			// Configura o retângulo de origem do bloco.
			game->world.chunk->blocks[i][j].dst.x = x + (i * BLOCK_SIZE);
			game->world.chunk->blocks[i][j].dst.y = y + (j * BLOCK_SIZE);
			game->world.chunk->blocks[i][j].dst.w = BLOCK_SIZE;
			game->world.chunk->blocks[i][j].dst.h = BLOCK_SIZE;
		}
	}
}

// Função para criar o mundo.
void create_world(Game *game) {
	// Define a seed do mundo como um número pseudo-aleatório no intervalo de 1 a 10000.
	game->world.seed = 1 + rand() % 9999;
	
	create_chunk(game, 0, 0);
}

#endif // WORLD_H