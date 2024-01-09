#ifndef WORLD_HPP
#define WORLD_HPP

namespace Domodhoro
{
    // Classe que representa o mundo do jogo, composto por chunks.
    class World final
    {
    public:
        // Construtor que inicializa o mundo com chunks baseados em uma semente.
        World(const int seed)
        {
            chunks.reserve(4);

            const int gap = static_cast<int>(Block::WIDTH);

            // Cria quatro chunks em uma linha horizontal.
            for (int i = 0; i < 4; i++)
            {
                chunks.push_back(std::make_unique<Chunk>(i * Chunk::WIDTH * gap, 0, seed));
            }
        }

        // Verifica se há colisão entre o jogador e os blocos no mundo.
        bool check_collision(const Entity* entity) const
        {
            for (const auto& it : chunks)
            {
                if (it->check_collision(entity))
                {
                    return true;
                }
            }

            return false;
        }

        // Limita o jogador aos limites do mundo.
        void handle_player_boundaries(Entity* player)
        {
            SDL_Rect player_position = player->get_destination_rect();

            static const int world_top = 0;
            static const int world_bottom = (static_cast<int>(Chunk::HEIGHT) * static_cast<int>(Block::HEIGHT)) - player_position.h;

            // Verifica e ajusta a posição do jogador para evitar que ultrapasse os limites do mundo.
            if (player_position.y < world_top)
            {
                player_position.y = world_top;
            }
            else if (player_position.y > world_bottom)
            {
                player_position.y = world_bottom;
            }

            player->set_destination_rect(player_position);
        }

        // Renderiza todos os chunks do mundo.
        void render(Renderer* renderer, Image* image, const SDL_Point& camera_position) const
        {
            for (const auto& it : chunks)
            {
                it->render(renderer, image, camera_position);
            }
        }
    private:
        // Vetor de chunks que compõem o mundo.
        std::vector<std::unique_ptr<Chunk>> chunks;
    };
}

#endif // WORLD_HPP