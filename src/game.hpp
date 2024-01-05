#ifndef GAME_HPP
#define GAME_HPP

namespace Domodhoro
{
    // A classe Game é responsável pela gestão geral do jogo, incluindo a inicialização, manipulação de eventos, atualização e renderização.
    class Game final
    {
    public:
        // Construtor da classe Game. Inicializa a biblioteca SDL e cria a janela do jogo.
        Game(const std::string& title, const int window_width, const int window_height) :
            width(window_width),
            height(window_height),
            running(true)
        {
            // Inicializa a biblioteca SDL.
            if (SDL_Init(SDL_INIT_VIDEO) < 0)
            {
                // Em caso de falha na inicialização.
                throw Game_Exception(SDL_GetError(), __FILE__, __LINE__);
            }

            // Define a janela do jogo centralizada na tela.
            static const int x = SDL_WINDOWPOS_UNDEFINED;
            static const int y = SDL_WINDOWPOS_UNDEFINED;

            // Cria a janela do jogo.
            window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

            if (!window)
            {
                // Em caso de falha.
                throw Game_Exception(SDL_GetError(), __FILE__, __LINE__);
            }
        }

        // Destrutor da classe Game. Libera recursos e finaliza a biblioteca SDL.
        ~Game()
        {
            // Libera a janela do jogo se existir.
            if (window)
            {
                SDL_DestroyWindow(window);
            }

            // Finaliza a biblioteca SDL.
            SDL_Quit();
        }

        // Inicializa diversos componentes do jogo.
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

            // Carrega os sprites do objetos do jogo.
            SDL_Surface* player_surface = image->create_surface("./img/player.png");
            SDL_Surface* block_surface = image->create_surface("./img/block.png");

            image->load(renderer->get(), player_surface, "PLAYER");
            image->load(renderer->get(), block_surface, "BLOCK");

            // Libera recursos.
            SDL_FreeSurface(player_surface);
            SDL_FreeSurface(block_surface);

            // Define o sprite inicial do jogador.
            player->set_source_rect({0, 960, 64, 64});
        }

        // Obtém o tempo decorrido desde o início do jogo em milissegundos.
        Uint32 get_ticks() const
        {
            return SDL_GetTicks();
        }

        // Verifica se o jogo está em execução.
        bool is_running() const
        {
            return running;
        }

        // Lida com eventos de entrada do usuário (teclado e mouse).
        void handle_events()
        {
            keyboard->update(running);
            mouse->update();
        }

        // Atualiza a lógica do jogo.
        void update()
        {  
            // Aplica a gravidade.
            handle_gravity();
            // Movimenta o jogador.
            move_player(get_ticks());
            // Impede do jogador sair do mundo.
            world->handle_player_boundaries(player.get());
            // Atualiza a câmera
            update_camera();
#if SHOW_TEXTS
            // Exibe os textos na tela.
            text->show_player_coordinates(renderer.get(), image.get(), camera->get_position());
#endif // SHOW_TEXTS
        }

        // Renderiza o estado atual do jogo.
        void render() const
        {
            // Limpa a tela com uma cor padrão.
            renderer->clear({127, 127, 255}, 255);

            // Renderiza o mundo.
            world->render(renderer.get(), image.get(), camera->get_position());

            // Renderiza o jogador.
            renderer->render(image->get("PLAYER"), camera->get_position(), player->get_source_rect(), player->get_destination_rect());

            // Renderiza o texto.
            text->render(renderer.get(), image.get());
            
            renderer->present();
        }

        // Define a taxa de quadros por segundo (FPS) e controla o atraso para manter a taxa desejada.
        void set_FPS(const Uint32 FPS, const Uint32 frame_time) const
        {
            static const Uint32 delay = 1000 / FPS;

            if (frame_time < delay)
            {
                SDL_Delay(delay - frame_time);
            }
        }
private:
        // Dimensões (largura e altura) da janela.
        int width;
        int height;

        SDL_Window* window;

        // Componentes do jogo.
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

        // Variável que armazena o estado do jogo.
        bool running;

        // Trata a aplicação da gravidade no jogo.
        void handle_gravity()
        {
#if GRAVITY
            static const int gravity_velocity = 7;

            move_entity_with_collision(player.get(), Entity::DIRECTION::DOWN, gravity_velocity);
#endif // GRAVITY
        }

        // Move o jogador com base nas teclas pressionadas.
        void move_player(const Uint32 ticks)
        {
            // Velocidade padrão de movimento horizontal do jogador.
            static const int player_velocity = 2;
            // Velocidade de salto do jogador.
            static const int jump_velocity = 14;

            // Itera sobre as teclas pressionadas no momento.
            for (const auto& it : keyboard->get_keys())
            {
                // Procura a direção correspondente à tecla no mapeamento de teclas.
                auto DIRECTION = keyboard->get_key_mappings().find(static_cast<int>(it));

                // Verifica se a tecla corresponde a uma direção válida.
                if (DIRECTION != keyboard->get_key_mappings().end())
                {
                    // Obtém a direção correspondente à tecla.
                    auto direction = DIRECTION->second;

                    // Define a velocidade com base na direção (velocidade padrão ou velocidade de salto).
                    int velocity = (direction == Entity::DIRECTION::UP) ? jump_velocity : player_velocity;

                    // Move o jogador com detecção de colisão usando a velocidade e direção calculadas.
                    move_entity_with_collision(player.get(), direction, velocity);

                    // Ativa a animação do jogador na direção especificada e com o tempo atual do jogo.
                    player->animation(direction, ticks);
                }
            }
        }

        // Atualiza a posição da câmera com base na posição do jogador.
        void update_camera()
        {
            // Calcula a posição central da câmera com base na posição central do jogador.
            const SDL_Point camera_position =
            {
                player->get_destination_rect().x + player->get_destination_rect().w / 2 - width / 2,
                player->get_destination_rect().y + player->get_destination_rect().h / 2 - height / 2
            };

            // Define a posição da câmera usando a posição calculada.
            camera->set_position(camera_position);
        }

        // Move uma entidade com detecção de colisão.
        void move_entity_with_collision(Entity* entity, Entity::DIRECTION direction, const int velocity)
        {
            // Loop que movimenta a entidade (jogador, por exemplo) em incrementos, controlados pela variável 'velocity'.
            for (int step = 1; step <= velocity; step++)
            {
                // Move a entidade na direção especificada.
                entity->move(direction);

                // Verifica se há colisão com o mundo (ou outros objetos).
                if (world->check_collision(entity))
                {
                    // Em caso de colisão, reverte o movimento para a posição anterior.
                    entity->move(entity->reverse_direction(direction));

                    // Encerra o loop para evitar movimentos adicionais após a colisão.
                    break;
                }
            }
        }
    };
}

#endif // GAME_HPP