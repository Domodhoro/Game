extern "C"
{
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "./lib/lua54/lua.h"
#include "./lib/lua54/lualib.h"
#include "./lib/lua54/lauxlib.h"

#define FNL_IMPL

#include "lib/FastNoiseLite/FastNoiseLite.h"
}

#include <iostream>
#include <exception>
#include <cstring>
#include <memory>
#include <vector>
#include <map>
#include <unordered_set>

#define GRAVITY false
#define COLLISION true
#define WORLD_BORDER true

#include "./src/game_exception.hpp"
#include "./src/lua_config.hpp"
#include "./src/sound.hpp"
#include "./src/font.hpp"
#include "./src/image.hpp"
#include "./src/camera.hpp"
#include "./src/game_object.hpp"
#include "./src/block.hpp"
#include "./src/entity.hpp"
#include "./src/player.hpp"
#include "./src/renderer.hpp"
#include "./src/text.hpp"
#include "./src/noise.hpp"
#include "./src/quadtree.hpp"
#include "./src/chunk.hpp"
#include "./src/world.hpp"
#include "./src/game.hpp"

int main(int argc, char* argv[])
{
    static const Uint32 FPS = 60;

    try
    {
        Domodhoro::Game game("Game", 640, 480);

        game.init();

        static Uint32 frame_start = 0;
        static Uint32 frame_end = 0;

        while (game.is_running())
        {
            frame_start = game.get_ticks();

            game.handle_events();
            game.update();
            game.render();

            frame_end = game.get_ticks();

            game.set_FPS(FPS, frame_end - frame_start);
        }
    }
    catch (const Domodhoro::Game_Exception& e)
    {
        std::cerr << e.what() << std::endl;

        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Falha desconhecida!" << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}