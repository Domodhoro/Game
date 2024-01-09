#ifndef GAME_LOGIC
#define GAME_LOGIC

namespace Domodhoro
{
	// Classe responsável por toda a lógica do jogo.
	class Game_Logic final
	{
	public:
		// Construtor da classe Game_Logic.
		Game_Logic(Camera* camera, World* world, Player* player) :
			camera(camera),
			world(world),
			player(player),
			player_is_jumping(false)
		{

		}

		// Trata a aplicação da gravidade no jogo.
        void handle_gravity(const int gravity_velocity)
        {
            move_entity_with_collision(player, Entity::DIRECTION::DOWN, gravity_velocity);
        }

		// Move o jogador com base nas teclas pressionadas.
        void move_player(const int player_velocity, Keyboard* keyboard, const Uint32 ticks)
        {
            // Lógica do pulo do jogador.
            player_jump(player_is_jumping);
    
            // Itera sobre as teclas pressionadas no momento.
            for (const auto& key : keyboard->get_keys())
            {
                auto direction = keyboard->get_direction_from_key(key);

                // Inicia o pulo se o jogador estiver no chão e se tecla de pulo estiver pressionada.
                if (player->is_on_ground() && direction == Entity::DIRECTION::UP)
                {
                    player_is_jumping = true;
                }

                // Movimenta o jogador na horizontal.
                if (direction != Entity::DIRECTION::UP)
                {
                    move_entity_with_collision(player, direction, player_velocity);
                }

                // Ativa a animação do jogador na direção especificada e com o tempo atual do jogo.
                player->animation(direction, ticks);
            }

            // Impede do jogador sair do mundo.
            world->handle_player_boundaries(player);
        }

        // Atualiza a posição da câmera com base na posição do jogador.
        void update_camera(const int window_width, const int window_height)
        {
            // Calcula a posição central da câmera com base na posição central do jogador.
            const SDL_Point camera_position =
            {
                player->get_destination_rect().x + player->get_destination_rect().w / 2 - window_width / 2,
                player->get_destination_rect().y + player->get_destination_rect().h / 2 - window_height / 2
            };

            // Define a posição da câmera usando a posição calculada.
            camera->set_position(camera_position);
        }
    private:
    	// Armazenza a câmera do jogo.
    	Camera* camera;

    	// Armazena o mundo do jogo.
    	World* world;

    	// Armazena o jogador.
    	Player* player;

    	// Armazena o estado do pulo.
    	bool player_is_jumping;

        // Lógica do pulo do jogador.
        void player_jump(bool& player_is_jumping)
        {
            // Velocidade de salto do jogador.
            static const int jump_velocity = 14;
            // Contador do pulo.
            static int jump_counter = 0;
            // Limite do contador de pulo.
            static int jump_counter_limit = 10;

            // Verifica se o jogador está pulando.
            if (player_is_jumping)
            {
                // Reseta a variável.
                player->set_on_ground_status(false);

                // Movimenta o jogador para cima.
                move_entity_with_collision(player, Entity::DIRECTION::UP, jump_velocity);

                // Incrementa o contador do pulo.
                jump_counter++;

                // Verifica se o pulo atingiu o limite.
                if (jump_counter >= jump_counter_limit)
                {
                    // Reseta as variáveis do pulo.
                    player_is_jumping = false;
                    jump_counter = 0;
                }
            }
        }

        // Move uma entidade com detecção de colisão.
        void move_entity_with_collision(Entity* entity, Entity::DIRECTION direction, const int velocity)
        {
            // Loop que movimenta a entidade em incrementos.
            for (int step = 1; step <= velocity; step++)
            {
                // Move a entidade na direção especificada.
                entity->move(direction);

                // Verifica se há colisão com o mundo.
                if (world->check_collision(entity))
                {
                    // Verifica se há colisão com o chão.
                    if (direction == Entity::DIRECTION::DOWN)
                    {
                        entity->set_on_ground_status(true);
                    }

                    // Em caso de colisão, reverte o movimento para a posição anterior.
                    entity->move(entity->reverse_direction(direction));

                    break;
                }
            }
        }
	};
}

#endif // GAME_LOGIC