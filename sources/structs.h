#ifndef STRUCTS_H
#define STRUCTS_H

// Struct para representar o jogador.
typedef struct Player {
	SDL_Rect src;
	SDL_Rect dst;

	int speed;
	int hearts;
}
Player;

// Struct para representar um bloco.
typedef struct Block {
	SDL_Rect src;
	SDL_Rect dst;

	BLOCK_TYPE type;
}
Block;

// Struct para representar um pedaço gerenciável do mundo.
typedef struct Chunk {
	Block blocks[CHUNK_WIDTH][CHUNK_HEIGHT];
}
Chunk;

// Struct para representar o mundo.
typedef struct World {
	Chunk *chunk;

	int seed;
}
World;

// Struct para armazenar as teclas pressionadas.
typedef struct Keys {	
	_Bool W, A, S, D;
}
Keys;
// Struct para armazenar texturas.
typedef struct Texture_Atlas {
	SDL_Texture *text, *player, *blocks, *heart, *inventory_back;
}
Texture_Atlas;

// Struct para representar texto.
typedef struct Text {
	SDL_Rect dst;
	SDL_Color color;

	const char* string;
}
Text;

// Struct principal do jogo que contém todas as informações necessárias.
typedef struct Game {
	lua_State *L;
	SDL_Window *window;
	SDL_Renderer *renderer;
	TTF_Font *font;
	Mix_Music *music;

	_Bool running;

	SDL_Rect viewport;
	Keys keys;
	Texture_Atlas texture_atlas;
	Text text;
	SDL_Point camera_position;
	Player player;
	World world;
}
Game;

#endif // STRUCTS_H