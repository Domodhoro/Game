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
        void init(const std::string& file_path)
        {
            // Semente do mundo.
            const int world_seed = 1007;

            lua_config = std::make_unique<Lua_Config>(file_path);
            renderer = std::make_unique<Renderer>(window, SDL_Rect{0, 0, width, height});
            keyboard = std::make_unique<Keyboard>();
            mouse = std::make_unique<Mouse>();
            sound_mixer = std::make_unique<Sound_Mixer>();
            image = std::make_unique<Image>();
            text = std::make_unique<Text>(renderer.get(), image.get());
            camera = std::make_unique<Camera>(SDL_Point{0, 0});
            player = std::make_unique<Player>(SDL_Rect{width / 2 - Player::WIDTH / 2, height / 2 - Player::HEIGHT / 2, Player::WIDTH, Player::HEIGHT});
            world = std::make_unique<World>(world_seed);
            game_logic = std::make_unique<Game_Logic>(camera.get(), world.get(), player.get());
        }

        // Carrega todos os recursos (imagens, sons, arquivo de fonte de texto, etc...) do jogo.
        void load()
        {
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
            // Aplica a gravidade no jogador.
            game_logic->handle_gravity(7);
            // Movimenta o jogador.
            game_logic->move_player(3, keyboard.get(), get_ticks());
            // Atualiza a câmera
            game_logic->update_camera(width, height);
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

            // Exibe as coordenadas do jogador na tela.
            text->render_player_coordinates(renderer.get(), image.get(), camera->get_position());
            
            // Atualiza a tela com as alterações realizadas nos métodos de renderização presente.
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

        // Armazana a janela de visualização do jogo.
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
        std::unique_ptr<Game_Logic> game_logic;

        // Variável que armazena o estado do jogo.
        bool running;
    };
}

#endif // GAME_HPP