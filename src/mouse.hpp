#ifndef MOUSE_HPP
#define MOUSE_HPP

namespace Domodhoro
{
	class Mouse final
    {
    public:
        Mouse() :
            position({0, 0})
        {

        }

        void update()
        {
            SDL_GetMouseState(&position.x, &position.y);
        }

        SDL_Point get_position() const
        {
            return position;
        }
    private:
        SDL_Point position;
    };
}

#endif