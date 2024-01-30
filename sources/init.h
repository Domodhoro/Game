#ifndef INIT_H
#define INIT_H

static void init_SDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		custom_error(SDL_GetError(), __FILE__, __LINE__);
	}
}

static void init_lua(Game* game) {
	game->L = luaL_newstate();

	if (game->L == NULL) {
		custom_error("Failed to create Lua state.", __FILE__, __LINE__);
	}

    luaL_openlibs(game->L);

    if (luaL_dofile(game->L, "./scripts/script.lua") < 0) {
    	custom_error(lua_tostring(game->L, -1), __FILE__, __LINE__);
    }
}

static void init_keys(Game *game) {
	game->keys.W = false;
    game->keys.A = false;
    game->keys.S = false;
    game->keys.D = false;

    int i;

    for (i = 0; i != NUM_KEYS; i++) {
        game->keys.numbers[i] = false;
    }
}

static void init_SDL_image(Game *game) {
	if (IMG_Init(IMG_INIT_PNG) < 0) {
		custom_error(SDL_GetError(), __FILE__, __LINE__);
	}
}

static void init_SDL_ttf(Game *game) {
	if (TTF_Init() < 0) {
		custom_error(SDL_GetError(), __FILE__, __LINE__);
	}

	game->font = TTF_OpenFont("./fonts/04B_03__.TTF", FONT_SIZE);

    if (game->font == NULL) {
    	custom_error(TTF_GetError(), __FILE__, __LINE__);
    }
}

static void init_SDL_mixer(Game *game) {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		custom_error(Mix_GetError(), __FILE__, __LINE__);
	}

	game->music = NULL;
}

static void init_camera(Game *game) {
	game->camera_position.x = 0;
	game->camera_position.y = 0;
}

static void init_map(Game *game) {
	game->map.show_map_frame = true;
}

static void init_inventory(Game *game) {
	inventory_reset(game);

	game->inventory.slot[0] = true;
}

static void init_world(Game *game) {
    game->world.seed = 1 + rand() % 9999;

    game->world.noise = fnlCreateState();
    
    game->world.noise.noise_type = FNL_NOISE_OPENSIMPLEX2;
    game->world.noise.seed = game->world.seed;
    
    game->world.first_chunk = NULL;
}

static void init_player(Game *game) {
	game->player.speed = 5;
	game->player.hearts = 10;

	game->player.src.x = 0;
	game->player.src.y = 960;
	game->player.src.w = 64;
	game->player.src.h = 64;

	game->player.dst.x = (WINDOW_WIDTH - PLAYER_WIDTH) / 2;
	game->player.dst.y = (WINDOW_HEIGHT - PLAYER_HEIGHT) / 2;
	game->player.dst.w = PLAYER_WIDTH;
	game->player.dst.h = PLAYER_HEIGHT;
}

void init(Game *game) {
	init_SDL();
	
	create_window(game);
	create_renderer(game);

	set_window_icon(game, "./textures/icon.png");
	
	init_lua(game);
	init_keys(game);
	init_SDL_image(game);
	init_SDL_ttf(game);
	init_SDL_mixer(game);
	init_camera(game);
	init_map(game);
	init_inventory(game);
	init_world(game);
	init_player(game);

	game->running = true;
}

void load(Game *game) {
	game->player.texture = get_texture(game->renderer, "./textures/player.png");
	game->world.block_texture = get_texture(game->renderer, "./textures/blocks.png");
	game->inventory.texture = get_texture(game->renderer, "./textures/inventory_back.png");
	game->map.frame_texture = get_texture(game->renderer, "./textures/map_frame.png");
	game->background.texture = get_texture(game->renderer, "./textures/background.png");
}

#endif