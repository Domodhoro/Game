extern "C"
{
// Inclusão dos cabeçalhos SDL.
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// Inclusão dos cabeçalhos Lua.
#include "./lib/lua54/lua.h"
#include "./lib/lua54/lualib.h"
#include "./lib/lua54/lauxlib.h"

// Inclusão do cabeçalho FastNoiseLite.
#define FNL_IMPL

#include "./lib/FastNoiseLite/FastNoiseLite.h"
}

// Inclusões de cabeçalhos padrão C++.
#include <iostream>
#include <exception>
#include <memory>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_set>

// Inclusões de cabeçalhos personalizados.
#include "./src/game_exception.hpp"
#include "./src/lua_config.hpp"
#include "./src/sound_mixer.hpp"
#include "./src/font.hpp"
#include "./src/image.hpp"
#include "./src/camera.hpp"
#include "./src/game_object.hpp"
#include "./src/block.hpp"
#include "./src/entity.hpp"
#include "./src/player.hpp"
#include "./src/renderer.hpp"
#include "./src/keyboard.hpp"
#include "./src/mouse.hpp"
#include "./src/text.hpp"
#include "./src/noise.hpp"
#include "./src/quadtree.hpp"
#include "./src/chunk.hpp"
#include "./src/world.hpp"
#include "./src/game_logic.hpp"
#include "./src/game.hpp"

int main(int argc, char* argv[])
{
    // Constante para controlar a taxa de quadros por segundo.
    const Uint32 FPS = 60;

    try
    {
        // Criação da instância do jogo.
        Domodhoro::Game game("Game", 640, 480);

        // Inicializa diversos componentes do jogo.
        game.init("./config.lua");

        // Carrega todos os recursos (imagens, sons, arquivo de fonte de texto, etc...) do jogo.
        game.load();

        // Variáveis para medir o tempo de execução de cada quadro.
        Uint32 frame_start = 0;
        Uint32 frame_end = 0;

        // Loop principal do jogo.
        while (game.is_running())
        {
            // Marca o início do quadro.
            frame_start = game.get_ticks();

            // Lida com eventos de entrada, atualiza a lógica e renderiza o jogo.
            game.handle_events();
            game.update();
            game.render();

            // Marca o final do quadro.
            frame_end = game.get_ticks();

            // Controla a taxa de quadros por segundo.
            game.set_FPS(FPS, frame_end - frame_start);
        }
    }
    catch (const Domodhoro::Game_Exception& e)
    {
        // Imprime a mensagem de erro e encerra o programa com código de saída de falha.
        std::cerr << e.what() << std::endl;

        return EXIT_FAILURE;
    }
    catch (...)
    {
        // Imprime uma mensagem de falha desconhecida e encerra o programa com código de saída de falha.
        std::cerr << "Falha desconhecida!" << std::endl;
        
        return EXIT_FAILURE;
    }

    // Se terminar sem problemas, retorna código de saída de sucesso.
    return EXIT_SUCCESS;
}
