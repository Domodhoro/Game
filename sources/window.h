#ifndef WINDOW_H
#define WINDOW_H

// Cria a janela do jogo.
void create_window(Game *game) {
	// Centralizar a janela na tela.
	const int x = SDL_WINDOWPOS_UNDEFINED, y = SDL_WINDOWPOS_UNDEFINED;

	// Cria a janela com o título do jogo, largura e altura especificadas.
	game->window = SDL_CreateWindow(GAME_TITLE, x, y, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	// Verifica se a janela foi criada com sucesso.
	if (game->window == NULL) custom_error(SDL_GetError(), __FILE__, __LINE__);
}

#endif // WINDOW_H