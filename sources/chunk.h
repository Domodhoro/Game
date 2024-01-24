#ifndef CHUNK_H
#define CHUNK_H

// Cria um chunk em tempo de execução e aloca memória para segurar a estrutura.
Chunk *create_chunk(int x, int y) {
	// Aloca memória para o chunk e verifica se não houve erro.
	Chunk* new_chunk = malloc(sizeof(Chunk));

	if (new_chunk == NULL) custom_error("Failed to allocate memory.", __FILE__, __LINE__);

	// Preenche a matriz do chunk com blocos.
	int i, j;

	for (i = 0; i != CHUNK_WIDTH; i++) {
		for (j = 0; j != CHUNK_HEIGHT; j++) {
			// Define o tipo do bloco.
			new_chunk->blocks[i][j].type = DIRT;

			// Configura o retângulo de origem do bloco para a textura no atlas.
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

	// Atualiza as coordenadas mundiais do chunk.
	new_chunk->x = x;
	new_chunk->y = y;

	new_chunk->next_chunk = NULL;

	return new_chunk;
}

// Função para verificar se já existe um chunk na posição especificada
_Bool chunk_exists(World *world, int x, int y) {
    Chunk *current_chunk = world->first_chunk;

    while (current_chunk != NULL) {
        if (current_chunk->x == x && current_chunk->y == y) {
            // Já existe um chunk nesta posição
            return true;
        }

        current_chunk = current_chunk->next_chunk;
    }

    // Não existe um chunk nesta posição
    return false;
}

// Função para adicionar um chunk à lista encadeada de chunks.
void add_chunk(World *world, const int x, const int y) {
    // Verifica se o chunk do jogador não existe no mundo.
    if (!chunk_exists(world, x, y)) {
        Chunk *new_chunk = create_chunk(x, y);

        // Verifica se esta é a primeira adição de um chunk ao mundo.
        if (world->first_chunk == NULL) {
            // Se for o primeiro chunk, define-o como o primeiro chunk na lista.
            world->first_chunk = new_chunk;
        } 
        else {
            // Se não for o primeiro chunk, encontra o último chunk na lista.
            Chunk *current_chunk = world->first_chunk;

            while (current_chunk->next_chunk != NULL) current_chunk = current_chunk->next_chunk;

            // Adiciona o novo chunk ao final da lista.
            current_chunk->next_chunk = new_chunk;
        }   
    }
}

// Função para remover um chunk específico do mundo.
void remove_chunk(World *world, const int x, const int y) {
	// Inicializa o ponteiro para percorrer a lista de chunks.
	Chunk *current_chunk = world->first_chunk;

	// Inicializa um ponteiro para o chunk anterior na lista.
    Chunk *prev = NULL;

    // Percorre a lista de chunks até encontrar o chunk ou atingir o final.
    while (current_chunk != NULL && (current_chunk->x != x || current_chunk->y != y)) {
        prev = current_chunk;

        current_chunk = current_chunk->next_chunk;
    }

    // Verifica se o chunk foi encontrado.
    if (current_chunk != NULL) {
    	// Verifica se o chunk a ser removido é o primeiro na lista.
        if (prev == NULL) {
        	// Atualiza o ponteiro do primeiro chunk na lista.
            world->first_chunk = current_chunk->next_chunk;
        }
        else {
        	// Remove o chunk da lista atualizando o ponteiro do chunk anterior.
            prev->next_chunk = current_chunk->next_chunk;
        }

        // Libera a memória alocada para o chunk removido.
        free(current_chunk);
    }
}

#endif //  CHUNK_H