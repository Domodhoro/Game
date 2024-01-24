#ifndef UPDATE_H
#define UPDATE_H

// Atualiza o estado do jogo, movendo o jogador com base nas teclas pressionadas e em colisões.
void player_update(Game *game) {
	// Loop para mover o jogador com base na velocidade.
	int step = 0;

	while (step != game->player.speed) {
		// Verifica se a tecla está pressionada.
		if (game->keys.W) move_entity_with_collision(game, UP);
		if (game->keys.A) move_entity_with_collision(game, LEFT);
		if (game->keys.S) move_entity_with_collision(game, DOWN);
		if (game->keys.D) move_entity_with_collision(game, RIGHT);

		step++;
	}
}

// Atualiza a posição da câmera para centrar o jogador na tela.
void camera_update(Game *game) {
	// Calcula a posição da câmera para centrar o jogador na tela.
	game->camera_position.x = game->player.dst.x + (PLAYER_WIDTH - WINDOW_WIDTH) / 2;
    game->camera_position.y = game->player.dst.y + (PLAYER_HEIGHT - WINDOW_HEIGHT) / 2;
}

// Atualiza o estado do jogo, movendo o jogador com base nas teclas pressionadas e em colisões.
void update(Game *game) {
	update_world(game);

	// Atualiza a posição do jogador.
	player_update(game);

	// Atualiza a posição da câmera para seguir o jogador.
    camera_update(game);
}

#endif // UPDATE_H