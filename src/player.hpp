#ifndef PLAYER_HPP
#define PLAYER_HPP

namespace Domodhoro
{
    // Classe que representa o jogador no jogo, derivada da classe Entity.
	class Player final : public Entity
	{
	public:
        // Construtor que inicializa o jogador com a posição especificada.
		Player(const SDL_Rect& destination_rect) :
			Entity(destination_rect)
		{

		}

        // Método para animar o jogador com base na direção e nos ticks.
		void animation(DIRECTION direction, const Uint32 ticks)
        {
            // Configurações para animação.
        	static const int frame_duration = 50;
    		static const int num_frames = 14;

            // Calcula o índice do quadro com base nos ticks.
    		const int frame_index = 2 + (ticks / frame_duration) % num_frames;

            // Define a região da folha de sprites com base na direção.
            switch (direction)
            {
                case DIRECTION::UP:
                    set_source_rect({frame_index * 64, 960, 64, 64});

                    break;
                case DIRECTION::LEFT:
                    set_source_rect({frame_index * 64, 960, 64, 64});

                    break;
                case DIRECTION::RIGHT:
                    set_source_rect({frame_index * 64, 896, 64, 64});

                    break;
            }
        }
	};
}

#endif // PLAYER_HPP