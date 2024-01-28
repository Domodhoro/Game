#ifndef TERMINATE_H
#define TERMINATE_H

void terminate(Game *game) {
	while (game->world.first_chunk != NULL) {
        Chunk *temp = game->world.first_chunk;

        game->world.first_chunk = game->world.first_chunk->next_chunk;

        if (temp != NULL) {
            free(temp);
        }
    }

	if (game->player.texture != NULL) {
		SDL_DestroyTexture(game->player.texture);
	}

	if (game->world.block_texture != NULL) {
		SDL_DestroyTexture(game->world.block_texture);
	}

	if (game->inventory.texture != NULL) {
		SDL_DestroyTexture(game->inventory.texture);
	}

	if (game->map.frame_texture != NULL) {
		SDL_DestroyTexture(game->map.frame_texture);
	}

	if (game->background.texture != NULL) {
		SDL_DestroyTexture(game->background.texture);
	}

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