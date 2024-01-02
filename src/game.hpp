#ifndef GAME_HPP
#define GAME_HPP

namespace Domodhoro
{
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
                throw Game_Exception(SDL_GetError(), __FILE__, __LINE__);
            }

            static const int x = SDL_WINDOWPOS_UNDEFINED;
            static const int y = SDL_WINDOWPOS_UNDEFINED;

            window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

            if (!window)
            {
                throw Game_Exception(SDL_GetError(), __FILE__, __LINE__);
            }
        }

        ~Game()
        {
            if (window)
            {
                SDL_DestroyWindow(window);
            }

            SDL_Quit();
        }

        void init()
        {
            lua_config = std::make_unique<Lua_Config>("./config.lua");
            renderer = std::make_unique<Renderer>(window, SDL_Rect{0, 0, width, height});
            sound = std::make_unique<Sound>();
            image = std::make_unique<Image>();
            text = std::make_unique<Text>(renderer.get(), image.get());
            camera = std::make_unique<Camera>(SDL_Point{0, 0});
            player = std::make_unique<Player>(SDL_Rect{width / 2 - 50 / 2, height / 2 - 50 / 2, 50, 50});
            world = std::make_unique<World>(1007);

            SDL_Surface* player_surface = image->create_surface("./img/player.png");
            SDL_Surface* block_surface = image->create_surface("./img/block.png");

            image->load(renderer->get(), player_surface, "PLAYER");
            image->load(renderer->get(), block_surface, "BLOCK");

            SDL_FreeSurface(player_surface);
            SDL_FreeSurface(block_surface);

            player->set_source_rect({0, 960, 64, 64});
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
        	static const int player_velocity = 2;
            static const int jump_velocity = 14;
        	static const int gravity_velocity = 7;
  
            handle_gravity(gravity_velocity);
            move_player(player_velocity, jump_velocity);
            handle_player_boundaries();
            update_camera();
#if SHOW_TEXTS
            text->show_player_coordinates(renderer.get(), image.get(), camera->get_position());
#endif
        }

        void render() const
        {
            renderer->clear({127, 127, 255}, 255);

            world->render(renderer.get(), image.get(), camera->get_position());

            renderer->render(image->get("PLAYER"), camera->get_position(), player->get_source_rect(), player->get_destination_rect());

            text->render(renderer.get(), image.get());
            
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
        std::unique_ptr<Player> player;
        std::unique_ptr<World> world;

        bool player_is_floor = false;

        void move_player(const int player_velocity, const int jump_velocity)
        {
            for (const auto& it : keys)
            {
                switch (static_cast<int>(it))
                {
                case SDL_SCANCODE_W:
                    for (int step = 1; step <= jump_velocity; step++)
                    {
                        player->move_up();

                        if (world->check_collision(player.get()))
                        {
                            player->move_down();

                            break;
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

                            break;
                        }
                    }

                    player->set_source_rect({0, 960, 64, 64});
                    break;

                case SDL_SCANCODE_D:
                    for (int step = 1; step <= player_velocity; step++)
                    {
                        player->move_right();

                        if (world->check_collision(player.get()))
                        {
                            player->move_left();

                            break;
                        }
                    }

                    player->set_source_rect({0, 896, 64, 64});
                    break;
                }
            }
        }

        void handle_gravity(const int gravity_velocity)
        {
#if GRAVITY
            for (int step = 1; step <= gravity_velocity; step++)
            {
                player->apply_gravity();

                if (world->check_collision(player.get()))
                {
                    player->move_up();

                    player_is_floor = true;

                    break;
                }
            }
#endif
            player_is_floor = false;
        }

        void handle_player_boundaries()
        {
#if WORLD_BORDER
            SDL_Rect player_position = player->get_destination_rect();

            static const int world_bottom = (static_cast<int>(Chunk::HEIGHT) * static_cast<int>(Block::HEIGHT)) - player_position.h;

            if (player_position.y < 0)
            {
                player_position.y = 0;
            }
            else if (player_position.y > world_bottom)
            {
                player_position.y = world_bottom;
            }

            player->set_destination_rect(player_position);
#endif
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
}

#endif