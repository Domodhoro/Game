#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Incluindo os cabeçalhos da biblioteca SDL.
#define SDL_HANDLED_MAIN

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// Incluindo os cabeçalhos da biblioteca Lua.
#include "./lua54/lua.h"
#include "./lua54/lualib.h"
#include "./lua54/lauxlib.h"

// Definindo o nome do jogo.
#define GAME_TITLE "Game"

// Definindo as dimensões da janela de visualização.
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

// Definindo o FPS.
#define FPS 60

// Definindo o tamanho dos elementos do jogo.
#define BLOCK_SIZE 10
#define INVENTORY_BACK_SIZE 25
#define HEART_SIZE 15
#define CHUNK_MAX 4
#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50

// Define o tamanho da fonte de texto.
#define FONT_SIZE 16

// Incluindo outros cabeçalhos.
#include "./sources/custom_error.h"
#include "./sources/enums.h"
#include "./sources/structs.h"
#include "./sources/colors.h"
#include "./sources/world.h"
#include "./sources/player.h"
#include "./sources/texture.h"
#include "./sources/inputs.h"
#include "./sources/update.h"
#include "./sources/window.h"
#include "./sources/renderer.h"
#include "./sources/init.h"
#include "./sources/terminate.h"

int main() {
    // Inicializa a semente do gerador de números pseudo-aleatórios.
    srand((unsigned int)time(NULL));

    // Cria a estrutura do jogo.
	Game game;

    // Inicializa o jogo.
    init(&game);

    Uint32 frame_start = 0;
    Uint32 frame_end = 0;
    Uint32 elapsed_time = 0;

    const Uint32 delay = 1000 / FPS;

    // Loop principal do jogo.
    while (game.running) {
        frame_start = SDL_GetTicks();

        // Lida com eventos, atualiza e renderiza o jogo.
        handle_events(&game);
        update(&game);
        render(&game);

        frame_end = SDL_GetTicks();

        // Calcula o tempo decorrido e atrasa se necessário para manter o FPS desejado.
        elapsed_time = frame_end - frame_start;

        if (elapsed_time < delay) SDL_Delay(delay - elapsed_time);
    }

    // Encerra o jogo.
    terminate(&game);

    return 0;
}