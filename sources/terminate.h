#ifndef TERMINATE_H
#define TERMINATE_H

static void destroy_textures(Game *game) {
	if (game->texture_atlas.text != NULL) {
		SDL_DestroyTexture(game->texture_atlas.text);
	}

	if (game->texture_atlas.player != NULL) {
		SDL_DestroyTexture(game->texture_atlas.player);
	}

	if (game->texture_atlas.blocks != NULL) {
		SDL_DestroyTexture(game->texture_atlas.blocks);
	}

	if (game->texture_atlas.heart != NULL) {
		SDL_DestroyTexture(game->texture_atlas.heart);
	}

	if (game->texture_atlas.inventory_back != NULL) {
		SDL_DestroyTexture(game->texture_atlas.inventory_back);
	}

	if (game->texture_atlas.map_frame != NULL) {
		SDL_DestroyTexture(game->texture_atlas.map_frame);
	}
}

void terminate(Game *game) {
	destroy_world(game);
	destroy_textures(game);

	if (game->L != NULL) {
		lua_close(game->L);
	}

	if (game->font != NULL) {
		TTF_CloseFont(game->font);
	}

	if (game->music != NULL) {
		Mix_FreeMusic(game->music);
	}

	if (game->renderer != NULL) {
		SDL_DestroyRenderer(game->renderer);
	}

	if (game->window != NULL) {
		SDL_DestroyWindow(game->window);
	}
	
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

#endif