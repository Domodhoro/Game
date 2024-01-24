#ifndef PLAYER_H
#define PLAYER_H

// Função para criar o jogador, inicializando seus atributos e posição.
void create_player(Game *game) {
	// Define a velocidade inicial do jogador e quantidade inicial de corações do jogador.
	game->player.speed = 3;
	game->player.hearts = 10;

	// Configura o retângulo de origem do jogador para a textura no atlas.
	game->player.src.x = 0;
	game->player.src.y = 960;
	game->player.src.w = 64;
	game->player.src.h = 64;

	// Posiciona o jogador no centro da janela.
	game->player.dst.x = (WINDOW_WIDTH - PLAYER_WIDTH) / 2;
	game->player.dst.y = (WINDOW_HEIGHT - PLAYER_HEIGHT) / 2;
	game->player.dst.w = PLAYER_WIDTH;
	game->player.dst.h = PLAYER_HEIGHT;
}

// Função para mover o jogador.
void move_player(Game *game, const DIRECTION direction) {
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

// Inverte a direção.
DIRECTION reverse_direction(DIRECTION direction) {
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

// Move o jogador com detecção de colisão.
void move_entity_with_collision(Game *game, DIRECTION direction) {
	move_player(game, direction);

	Chunk *current_chunk = game->world.first_chunk;

	while (current_chunk != NULL) {
        // Loop para mover o jogador verificando a colisão.
		int i, j;

		for (i = 0; i != CHUNK_WIDTH; i++) {
			for (j = 0; j != CHUNK_HEIGHT; j++) {
				if (SDL_HasIntersection(&game->player.dst, &current_chunk->blocks[i][j].dst)) move_player(game, reverse_direction(direction));
			}
		}

        current_chunk = current_chunk->next_chunk;
    }
}

#endif // PLAYER_H