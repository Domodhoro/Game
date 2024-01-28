#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define SDL_HANDLED_MAIN

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "./lua54/lua.h"
#include "./lua54/lualib.h"
#include "./lua54/lauxlib.h"

#define FNL_IMPL

#include "./FastNoiseLite/FastNoiseLite.h"

#define GAME_TITLE "Game"
#define WINDOW_WIDTH 2000
#define WINDOW_HEIGHT 900
#define FPS 60
#define WORLD_SIZE 2
#define FONT_SIZE 16
#define NUM_KEYS 10
#define SLOT_MAX 10
#define INVENTORY_BACK_SIZE 25
#define MAP_FRAME_SIZE 200
#define BLOCK_SIZE 10
#define CHUNK_MAX 8
#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 128
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50
#define HEART_SIZE 15
#define GRAVITY_INTENSITY 3

#include "./sources/custom_error.h"
#include "./sources/enums.h"
#include "./sources/structs.h"
#include "./sources/colors.h"
#include "./sources/world.h"
#include "./sources/map.h"
#include "./sources/inventory.h"
#include "./sources/camera.h"
#include "./sources/player.h"
#include "./sources/texture.h"
#include "./sources/inputs.h"
#include "./sources/update.h"
#include "./sources/window.h"
#include "./sources/renderer.h"
#include "./sources/init.h"
#include "./sources/terminate.h"

int main() {
    srand((unsigned int)time(NULL));

	Game game;

    init(&game);
    load(&game);

    Uint32 frame_start = 0, frame_end = 0, elapsed_time = 0;
    const Uint32 delay = 1000 / FPS;

    while (game.running) {
        frame_start = SDL_GetTicks();

        handle_events(&game);
        update(&game);
        render(&game);

        frame_end = SDL_GetTicks();

        elapsed_time = frame_end - frame_start;

        if (elapsed_time < delay) {
            SDL_Delay(delay - elapsed_time);
        }
    }

    terminate(&game);

    return 0;
}