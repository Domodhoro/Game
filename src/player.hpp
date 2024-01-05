#ifndef PLAYER_HPP
#define PLAYER_HPP

namespace Domodhoro
{
	class Player final : public Entity
	{
	public:
		Player(const SDL_Rect& destination_rect) :
			Entity(destination_rect)
		{

		}

		void set_animation(DIRECTION direction, const Uint32 ticks)
        {
            switch (direction)
            {
                case DIRECTION::UP:
                    set_source_rect({0, 960, 64, 64});

                    break;
                case DIRECTION::LEFT:
                    set_source_rect({0, 960, 64, 64});

                    break;
                case DIRECTION::RIGHT:
                    set_source_rect({0, 896, 64, 64});

                    break;
            }
        }
	};
}

#endif