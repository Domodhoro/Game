#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Background {
	SDL_Texture *texture;
	SDL_Rect dst;
}
Background;

typedef struct Map {
	SDL_Texture *frame_texture;

	_Bool show_map_frame;
}
Map;

typedef struct Inventory {
	SDL_Texture *texture;

	_Bool slot[SLOT_MAX];
}
Inventory;

typedef struct Player {
	SDL_Texture *texture;
	SDL_Rect src, dst;

	int speed, hearts;
}
Player;

typedef struct Block {
	SDL_Rect dst;

	BLOCK_TYPE type;
}
Block;

typedef struct Chunk {
	Block blocks[CHUNK_WIDTH][CHUNK_HEIGHT];
	SDL_Point position;
	
	struct Chunk *next_chunk;
}
Chunk;

typedef struct World {
	SDL_Texture *block_texture;

	Chunk *first_chunk;

	int seed;

	fnl_state noise;
}
World;

typedef struct Keys {	
	_Bool W, A, S, D, M;
	_Bool numbers[NUM_KEYS];
}
Keys;


typedef struct Game {
	lua_State *L;

	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Rect viewport;

	Keys keys;

	_Bool running;

	TTF_Font *font;
	Mix_Music *music;

	SDL_Point camera_position;

	Map map;
	Inventory inventory;
	Player player;
	World world;
	Background background;
}
Game;

#endif