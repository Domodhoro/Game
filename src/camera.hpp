#ifndef CAMERA_HPP
#define CAMERA_HPP

namespace Domodhoro
{
    class Camera final
    {
    public:
        Camera(const SDL_Point& position) :
            position(position)
        {

        }

        void set_position(const SDL_Point& position)
        {
            this->position = position;
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