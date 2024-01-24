#ifndef TERMINATE_H
#define TERMINATE_H

// Libera os recursos alocados durante a execução do jogo.
void terminate(Game *game) {
	// Função para liberar a memória associada ao mundo.
	destroy_world(&game->world);

	// Libera as texturas do atlas de texturas.
	if (game->texture_atlas.text != NULL) SDL_DestroyTexture(game->texture_atlas.text);
	if (game->texture_atlas.player != NULL) SDL_DestroyTexture(game->texture_atlas.player);
	if (game->texture_atlas.blocks != NULL) SDL_DestroyTexture(game->texture_atlas.blocks);
	if (game->texture_atlas.heart != NULL) SDL_DestroyTexture(game->texture_atlas.heart);
	if (game->texture_atlas.inventory_back != NULL) SDL_DestroyTexture(game->texture_atlas.inventory_back);

	// Fecha a fonte.
	if (game->font != NULL) TTF_CloseFont(game->font);

	// Fecha o renderizador.
	if (game->renderer != NULL) SDL_DestroyRenderer(game->renderer);

	// Fecha a janela.
	if (game->window != NULL) SDL_DestroyWindow(game->window);
	
	// Encerra as bibliotecas SDL_image, SDL_ttf, SDL_mixer e SDL.
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

#endif // TERMINATE_H