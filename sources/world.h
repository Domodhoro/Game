#ifndef WORLD_H
#define WORLD_H

// Função para criar o mundo.
void create_world(Game *game) {
	// Define a seed do mundo como um número pseudo-aleatório no intervalo de 1 a 10000.
	game->world.seed = 1 + rand() % 9999;
	
	game->world.first_chunk = NULL;
}

// Função para destruir todos os chunks e liberar a memória associada ao mundo.
void destroy_world(World *world) {
	// Enquanto houver chunks na lista.
    while (world->first_chunk != NULL) {
    	// Salva o ponteiro para o primeiro chunk.
        Chunk *temp = world->first_chunk;

        // Atualiza o ponteiro do primeiro chunk para o próximo na lista.
        world->first_chunk = world->first_chunk->next_chunk;

        // Libera a memória alocada para o chunk removido.
        if (temp != NULL) free(temp);
    }
}

// Função para atualizar o mundo com base na posição do jogador.
void update_world(Game *game) {
	// Calcula a posição atual do jogador em relação aos chunks.
    int player_chunk_x = game->player.dst.x / BLOCK_SIZE;

    // Verifica se o jogador está em uma posição não negativa.
    if (player_chunk_x >= 0) {
    	// Divide a posição do jogador pelo tamanho do chunk.
        player_chunk_x /= CHUNK_WIDTH;
    } else {
    	// Caso a posição do jogador seja negativa, ajusta a divisão.
        player_chunk_x = (player_chunk_x + 1) / CHUNK_WIDTH - 1;
    }

    // Adiciona o chunk ao mundo.
    add_chunk(&game->world, player_chunk_x * CHUNK_WIDTH * BLOCK_SIZE, 500);
}

#endif // WORLD_H