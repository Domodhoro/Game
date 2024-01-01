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
	};
}

#endif