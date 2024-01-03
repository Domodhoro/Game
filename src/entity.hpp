#ifndef ENTITY_HPP
#define ENTITY_HPP

namespace Domodhoro
{
    class Entity : public Game_Object
    {
    public:
        Entity(const SDL_Rect& destination_rect) :
            Game_Object(SDL_Rect{0, 0, 0, 0}, destination_rect)
        {

        }

        void set_position(const SDL_Point& position)
        {
            destination_rect.x = position.x;
            destination_rect.y = position.y;
        }

        SDL_Point get_position() const
        {
            return SDL_Point{destination_rect.x , destination_rect.y};
        }

        void move_right()
        {
            destination_rect.x += 1;
        }

        void move_left()
        {
            destination_rect.x -= 1;
        }

        void move_up()
        {
            destination_rect.y -= 1;
        }

        void move_down()
        {
            destination_rect.y += 1;
        }
    };
}

#endif