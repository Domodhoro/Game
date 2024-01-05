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
            keyboard = std::make_unique<Keyboard>();
            mouse = std::make_unique<Mouse>();
            sound_mixer = std::make_unique<Sound_Mixer>();
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
            keyboard->update(running);
            mouse->update();
        }

        void update()
        {  
            handle_gravity();
            move_player();
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

        std::unique_ptr<Lua_Config> lua_config;
        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<Keyboard> keyboard;
        std::unique_ptr<Mouse> mouse;
        std::unique_ptr<Sound_Mixer> sound_mixer;
        std::unique_ptr<Text> text;
        std::unique_ptr<Image> image;
        std::unique_ptr<Camera> camera;
        std::unique_ptr<Player> player;
        std::unique_ptr<World> world;

        bool running;

        void handle_gravity()
        {
#if GRAVITY
            static const int gravity_velocity = 7;

            move_entity_with_collision(player.get(), Entity::DIRECTION::DOWN, gravity_velocity);
#endif
        }

        void move_player()
        {
            static const int player_velocity = 2;
            static const int jump_velocity = 14;

            for (const auto& it : keyboard->get_keys())
            {
                auto DIRECTION = keyboard->get_key_mappings().find(static_cast<int>(it));

                if (DIRECTION != keyboard->get_key_mappings().end())
                {
                    auto direction = DIRECTION->second;

                    int velocity = (direction == Entity::DIRECTION::UP) ? jump_velocity : player_velocity;

                    move_entity_with_collision(player.get(), direction, velocity);
                
                    player->animation(direction, get_ticks());
                }
            }
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

        void move_entity_with_collision(Entity* entity, Entity::DIRECTION direction, const int velocity)
        {
            for (int step = 1; step <= velocity; step++)
            {
                entity->move(direction);

                if (world->check_collision(entity))
                {
                    entity->move(entity->reverse_direction(direction));

                    break;
                }
            }
        }
    };
}

#endif