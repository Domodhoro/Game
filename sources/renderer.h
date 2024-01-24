#ifndef RENDERER_H
#define RENDERER_H

// Cria o renderizador associado à janela do jogo.
void create_renderer(Game *game) {
	// Cria o renderizador com aceleração de hardware e sincronização vertical.
	game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Verifica se o renderizador foi criado com sucesso.
	if (game->renderer == NULL) custom_error(SDL_GetError(), __FILE__, __LINE__);

	// Inicializa a estrutura viewport para abranger toda a janela.
	game->viewport.x = 0;
	game->viewport.y = 0;
	game->viewport.w = WINDOW_WIDTH;
	game->viewport.h = WINDOW_HEIGHT;
}

// Renderiza texto.
void render_text(Game *game) {
	// Renderiza o mundo no renderizador SDL.
	SDL_RenderCopy(game->renderer, game->texture_atlas.text, NULL, &game->text.dst);
}

// Renderiza o mundo.
void render_world(Game *game) {
	int i, j;

	for (i = 0; i != CHUNK_WIDTH; i++) {
		for (j = 0; j != CHUNK_HEIGHT; j++) {
			// Calcula a posição de destino considerando a câmera.
			SDL_Rect dst = game->world.chunk->blocks[i][j].dst;

			dst.x -= game->camera_position.x;
			dst.y -= game->camera_position.y;

			// Renderiza o mundo no renderizador SDL.
		    SDL_RenderCopy(game->renderer, game->texture_atlas.blocks, &game->world.chunk->blocks[i][j].src, &dst);
		}
	}
}

// Renderiza o jogador com animação de movimento.
void render_player(Game *game) {
	int frame_duration = 50, num_frames = 14, frame_index = 2 + (SDL_GetTicks() / frame_duration) % num_frames;

	// Define a posição inicial no atlas de texturas.
	game->player.src.x = 0;

	// Atualiza a posição e animação baseada nas teclas pressionadas.
	if (game->keys.A) {
		game->player.src.x = frame_index * 64;
    	game->player.src.y = 960;
	}

	if (game->keys.D) {
		game->player.src.x = frame_index * 64;
    	game->player.src.y = 896;
	}

	// Calcula a posição de destino considerando a câmera.
	SDL_Rect dst = game->player.dst;

	dst.x -= game->camera_position.x;
	dst.y -= game->camera_position.y;

	// Renderiza o jogador no renderizador SDL.
    SDL_RenderCopy(game->renderer, game->texture_atlas.player, &game->player.src, &dst);
}

// Renderiza o fundo do inventário.
void render_inventory_back(Game *game) {
	int i = 0;

	// Itera sobre as posições no inventário.
    for (i = 0; i != 10; i++) {
    	// Calcula a posição de destino considerando o índice e o tamanho do fundo do inventário.
    	SDL_Rect dst = {
			5 + (1.2 * i * INVENTORY_BACK_SIZE), 
			5, 
			INVENTORY_BACK_SIZE,
			INVENTORY_BACK_SIZE
		};

		// Renderiza o fundo do inventário no renderizador SDL.
		SDL_RenderCopy(game->renderer, game->texture_atlas.inventory_back, NULL, &dst);
    }
}

// Função principal para renderizar os elementos do jogo.
void render(Game *game) {
	// Define a cor de limpeza do renderizador.
	SDL_SetRenderDrawColor(game->renderer, 127, 127, 255, 255);
    SDL_RenderClear(game->renderer);

    // Renderiza os elementos do jogo.
    render_world(game);
    render_player(game);
    render_inventory_back(game);
    render_text(game);

    // Define a viewport do renderizador para cobrir toda a janela.
    SDL_RenderSetViewport(game->renderer, &game->viewport);

    // Atualiza a tela exibindo o renderizador.
    SDL_RenderPresent(game->renderer);
}

#endif // RENDERER_H