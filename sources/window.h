#ifndef WINDOW_H
#define WINDOW_H

void create_window(Game *game) {
	int x = SDL_WINDOWPOS_UNDEFINED, y = SDL_WINDOWPOS_UNDEFINED;

	game->window = SDL_CreateWindow(GAME_TITLE, x, y, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	if (game->window == NULL) {
		custom_error(SDL_GetError(), __FILE__, __LINE__);
	}
}

#endif