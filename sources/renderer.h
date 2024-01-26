#ifndef RENDERER_H
#define RENDERER_H

static void render_world(Game *game) {
    Chunk *current_chunk = game->world.first_chunk;

    while (current_chunk != NULL) {
    	int i, j;
    	
		for (i = 0; i != CHUNK_WIDTH; i++) {
			for (j = 0; j != CHUNK_HEIGHT; j++) {
				SDL_Rect dst = current_chunk->blocks[i][j].dst;

				dst.x -= game->camera_position.x;
				dst.y -= game->camera_position.y;

			    SDL_RenderCopy(game->renderer, game->texture_atlas.blocks, &current_chunk->blocks[i][j].src, &dst);
			}
		}

        current_chunk = current_chunk->next_chunk;
    }
}

static void render_player(Game *game) {
	int frame_duration = 50, num_frames = 14, frame_index = 2 + (SDL_GetTicks() / frame_duration) % num_frames;

	game->player.src.x = 0;

	if (game->keys.A) {
		game->player.src.x = frame_index * 64;
    	game->player.src.y = 960;
	}

	if (game->keys.D) {
		game->player.src.x = frame_index * 64;
    	game->player.src.y = 896;
	}

	SDL_Rect dst = game->player.dst;

	dst.x -= game->camera_position.x;
	dst.y -= game->camera_position.y;

    SDL_RenderCopy(game->renderer, game->texture_atlas.player, &game->player.src, &dst);
}

static void render_inventory_back(Game *game) {
	int i;

    for (i = 0; i != SLOT_MAX; i++) {
    	SDL_Rect dst = {
			5 + (1.2 * i * INVENTORY_BACK_SIZE), 
			5, 
			INVENTORY_BACK_SIZE,
			INVENTORY_BACK_SIZE
		};

		if (game->inventory.slot[i]) {
			set_texture_transparency(game->texture_atlas.inventory_back, 255);
		}
		else {
			set_texture_transparency(game->texture_atlas.inventory_back, 127);
		}

		SDL_RenderCopy(game->renderer, game->texture_atlas.inventory_back, NULL, &dst);
    }
}

static void render_map_frame(Game *game) {
	if (game->map.show_map_frame) {
		SDL_Rect dst = {
			WINDOW_WIDTH - MAP_FRAME_SIZE, 0, MAP_FRAME_SIZE, MAP_FRAME_SIZE
		};

		SDL_RenderCopy(game->renderer, game->texture_atlas.map_frame, NULL, &dst);
	}
}

void create_renderer(Game *game) {
	game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (game->renderer == NULL) {
		custom_error(SDL_GetError(), __FILE__, __LINE__);
	}

	game->viewport.x = 0;
	game->viewport.y = 0;
	game->viewport.w = WINDOW_WIDTH;
	game->viewport.h = WINDOW_HEIGHT;
}

void render(Game *game) {
	SDL_SetRenderDrawColor(game->renderer, 127, 127, 255, 255);
    SDL_RenderClear(game->renderer);

    render_world(game);
    render_player(game);
    render_inventory_back(game);
    render_map_frame(game);

    SDL_RenderSetViewport(game->renderer, &game->viewport);

    SDL_RenderPresent(game->renderer);
}

#endif