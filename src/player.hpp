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
        	static const int frame_duration = 50;
    		static const int num_frames = 14;

    		const int frame_index = 2 + (ticks / frame_duration) % num_frames;

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

#endif