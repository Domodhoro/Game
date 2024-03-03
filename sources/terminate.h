#ifndef TERMINATE_H
#define TERMINATE_H

static void destroy_world(Game *game) {
	if (game->world.block_texture != NULL) {
		SDL_DestroyTexture(game->world.block_texture);
	}

	while (game->world.first_chunk != NULL) {
        Chunk *temp = game->world.first_chunk;

        game->world.first_chunk = game->world.first_chunk->next_chunk;

        if (temp != NULL) {
            free(temp);
        }
    }
}

static void destroy_player(Game *game) {
	if (game->player.texture != NULL) {
		SDL_DestroyTexture(game->player.texture);
	}
}

static void destroy_inventory(Game *game) {
	if (game->inventory.texture != NULL) {
		SDL_DestroyTexture(game->inventory.texture);
	}
}

static void destroy_map(Game *game) {
	if (game->map.frame_texture != NULL) {
		SDL_DestroyTexture(game->map.frame_texture);
	}
}

static void destroy_background(Game *game) {
	if (game->background.texture != NULL) {
		SDL_DestroyTexture(game->background.texture);
	}
}

static void destroy_font(Game *game) {
	if (game->font != NULL) {
		TTF_CloseFont(game->font);
	}
}

static void destroy_music(Game *game) {
	if (game->music != NULL) {
		Mix_FreeMusic(game->music);
	}
}

static void destroy_renderer(Game *game) {
	if (game->renderer != NULL) {
		SDL_DestroyRenderer(game->renderer);
	}
}

static void destroy_window(Game *game) {
	if (game->window != NULL) {
		SDL_DestroyWindow(game->window);
	}
}

static void destroy_lua(Game *game) {
	if (game->L != NULL) {
		lua_close(game->L);
	}
}

void terminate(Game *game) {
	destroy_world(game);
	destroy_player(game);
	destroy_inventory(game);
	destroy_map(game);
	destroy_background(game);
	destroy_font(game);
	destroy_music(game);
	destroy_renderer(game);
	destroy_window(game);
	destroy_lua(game);
	
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

#endif