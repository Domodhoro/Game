#ifndef GAME_HPP
#define GAME_HPP

class Game final
{
public:
    Game(const std::string& title, const int window_width, const int window_height) :
        width(window_width),
        height(window_height),
        running(true)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            throw Game_Exception("Falha ao iniciar o SDL.", __FILE__, __LINE__);
        }

        const int x = SDL_WINDOWPOS_UNDEFINED;
        const int y = SDL_WINDOWPOS_UNDEFINED;

        window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

        if (!window)
        {
            throw Game_Exception("Falha ao criar janela de visualização.", __FILE__, __LINE__);
        }

        init();
    }

    ~Game()
    {
        if (window)
        {
            SDL_DestroyWindow(window);
        }

        SDL_Quit();
    }

    Uint32 get_ticks() const
    {
        return SDL_GetTicks();
    }

    bool is_running() const
    {
        return running;
    }

    void handle_events()
    {
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYDOWN:
                keys.insert(event.key.keysym.scancode);
                break;

            case SDL_KEYUP:
                keys.erase(event.key.keysym.scancode);
                break;
            }
        }
    }

    void update()
    {
        static const int player_velocity = 3;

        for (const auto& it : keys)
        {
            switch (static_cast<int>(it))
            {
            case SDL_SCANCODE_ESCAPE:
                running = false;
                break;

            case SDL_SCANCODE_G:
                handle_gravity();
                break;

            case SDL_SCANCODE_W:
                for (int step = 1; step <= player_velocity; step++)
                {
                    player->move_up();

                    if (world->check_collision(player.get()))
                    {
                        player->move_down();
                    }
                }

                player->set_source_rect({0, 960, 64, 64});
                break;

            case SDL_SCANCODE_A:
                for (int step = 1; step <= player_velocity; step++)
                {
                    player->move_left();

                    if (world->check_collision(player.get()))
                    {
                        player->move_right();
                    }
                }

                player->set_source_rect({0, 960, 64, 64});
                break;

            case SDL_SCANCODE_S:
                for (int step = 1; step <= player_velocity; step++)
                {
                    player->move_down();

                    if (world->check_collision(player.get()))
                    {
                        player->move_up();
                    }
                }

                player->set_source_rect({0, 896, 64, 64});
                break;

            case SDL_SCANCODE_D:
                for (int step = 1; step <= player_velocity; step++)
                {
                    player->move_right();

                    if (world->check_collision(player.get()))
                    {
                        player->move_left();
                    }
                }

                player->set_source_rect({0, 896, 64, 64});
                break;
            }
        }

        handle_player_boundaries();
        update_camera();
    }

    void render() const
    {
        renderer->clear(127, 127, 255);

        world->render(renderer->get(), image.get(), camera.get());
        player->render(renderer->get(), image->use("PLAYER"), camera.get());

        renderer->present();
    }

    void set_FPS(const Uint32 FPS, const Uint32 frame_time) const
    {
        static const Uint32 delay = 1000 / FPS;

        if (frame_time < delay)
        {
            SDL_Delay(delay - frame_time);
        }
    }
private:
    int width;
    int height;

    SDL_Window* window;

    SDL_Event event;

    std::unordered_set<SDL_Scancode> keys;

    bool running;

    std::unique_ptr<Lua_Config> lua_config;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<Sound> sound;
    std::unique_ptr<Text> text;
    std::unique_ptr<Image> image;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Entity> player;
    std::unique_ptr<World> world;

    void init()
    {
        lua_config = std::make_unique<Lua_Config>();
        renderer = std::make_unique<Renderer>(window, SDL_Rect{0, 0, width, height});
        sound = std::make_unique<Sound>();
        text = std::make_unique<Text>();
        image = std::make_unique<Image>();
        camera = std::make_unique<Camera>(SDL_Point{0, 0});
        player = std::make_unique<Entity>(SDL_Rect{width / 2 - 50 / 2, height / 2 - 50 / 2, 50, 50});
        world = std::make_unique<World>(1007);

        lua_config->load("./config.lua");
        image->load(renderer->get(), "PLAYER", "./img/player.png");
        image->load(renderer->get(), "BLOCK", "./img/block.png");
        player->set_source_rect({0, 960, 64, 64});
    }

    void handle_gravity()
    {
        static const int gravity_velocity = 7;

        for (int step = 1; step <= gravity_velocity; step++)
        {
            player->apply_gravity();

            if (world->check_collision(player.get()))
            {
                player->move_up();
            }
        }
    }

    void handle_player_boundaries()
    {
        SDL_Rect player_position = player->get_destination_rect();

        static const int world_bottom = (static_cast<int>(Chunk::HEIGHT) * static_cast<int>(Block::SIZE)) - player_position.h;

        if (player_position.y < 0)
        {
            player_position.y = 0;
        }
        else if (player_position.y > world_bottom)
        {
            player_position.y = world_bottom;
        }

        player->set_destination_rect(player_position);
    }

    void update_camera()
    {
        const SDL_Point camera_position =
        {
            player->get_destination_rect().x + player->get_destination_rect().w / 2 - width / 2,
            player->get_destination_rect().y + player->get_destination_rect().h / 2 - height / 2
        };

        camera->set_position(camera_position);
    }
};

#endif