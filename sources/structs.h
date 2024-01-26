#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
	SDL_Rect dst;
}
Background;

typedef struct {
	_Bool show_map_frame;
}
Map;

typedef struct {
	_Bool slot[SLOT_MAX];
}
Inventory;

typedef struct {
	SDL_Rect src, dst;

	int speed, hearts;
}
Player;

typedef struct {
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

typedef struct {
	Chunk *first_chunk;

	int seed;

	fnl_state noise;
}
World;

typedef struct {	
	_Bool W, A, S, D, M;
	_Bool numbers[NUM_KEYS];
}
Keys;

typedef struct {
	SDL_Texture *text, *player, *blocks, *heart;
	SDL_Texture *inventory_back, *map_frame, *background;
}
Texture_Atlas;

typedef struct {
	SDL_Rect dst;
	SDL_Color color;

	const char *string;
}
Text;

typedef struct {
	lua_State *L;

	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Rect viewport;

	Keys keys;

	_Bool running;

	Texture_Atlas texture_atlas;
	Text text;

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