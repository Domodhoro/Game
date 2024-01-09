#ifndef PLAYER_HPP
#define PLAYER_HPP

namespace Domodhoro
{
    // Classe que representa o jogador no jogo, derivada da classe Entity.
	class Player final : public Entity
	{
	public:
        static const int WIDTH = 50;
        static const int HEIGHT = 50;

        // Construtor que inicializa o jogador com a posição especificada.
		Player(const SDL_Rect& destination_rect) :
			Entity(destination_rect),
            frame_duration(1),
            num_frames(1)
		{

		}

        // Método para animar o jogador com base na direção e nos ticks.
		void animation(DIRECTION direction, const Uint32 ticks)
        {
            // Configurações para animação.
        	frame_duration = 50;
    		num_frames = 14;

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
    private:
        // Configurações para animação.
        int frame_duration;
        int num_frames;
	};
}

#endif // PLAYER_HPP