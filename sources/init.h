#ifndef INIT_H
#define INIT_H

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

static void init_SDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		custom_error(SDL_GetError(), __FILE__, __LINE__);
	}
}

static void create_window(Game *game) {
	int x = SDL_WINDOWPOS_UNDEFINED, y = SDL_WINDOWPOS_UNDEFINED;

	game->window = SDL_CreateWindow(GAME_TITLE, x, y, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	if (game->window == NULL) {
		custom_error(SDL_GetError(), __FILE__, __LINE__);
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

void init(Game *game) {
	init_lua(game);

	init_SDL();
	
	create_window(game);
	create_renderer(game);
	
	init_keys(game);

	init_SDL_image(game);
	init_SDL_ttf(game);
	init_SDL_mixer(game);

    game->text.dst.x = 16;
	game->text.dst.y = 50;
	game->text.dst.w = 0;
	game->text.dst.h = 0;

    game->text.color = GREEN;

	game->text.string = "Hello, world!";

	game->texture_atlas.text = get_text_texture(game->renderer, game->font, &game->text);

	game->texture_atlas.player = get_texture(game->renderer, "./textures/player.png");
	game->texture_atlas.blocks = get_texture(game->renderer, "./textures/blocks.png");
	game->texture_atlas.heart = get_texture(game->renderer, "./textures/heart.png");
	game->texture_atlas.inventory_back = get_texture(game->renderer, "./textures/inventory_back.png");
	game->texture_atlas.map_frame = get_texture(game->renderer, "./textures/map_frame.png");

	game->camera_position.x = 0;
	game->camera_position.y = 0;

	init_map(game);
	init_inventory(game);

	create_world(game);
	create_player(game);

	game->running = true;
}

#endif