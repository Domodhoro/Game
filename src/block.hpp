#ifndef BLOCK_HPP
#define BLOCK_HPP

namespace Domodhoro
{
    class Block final : public Game_Object
    {
    public:
        static const int WIDTH = 10;
        static const int HEIGHT = 10;

        enum class TYPE
        {
            DIRT
        };

        Block(const SDL_Rect& destination_rect, const TYPE type) :
            Game_Object(SDL_Rect{0, 0, 0, 0}, destination_rect),
            type(type)
        {

        }

        TYPE get_type() const
        {
            return type;
        }
    private:
        TYPE type;
    };
}

#endif