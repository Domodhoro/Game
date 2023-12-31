#ifndef BLOCK_HPP
#define BLOCK_HPP

namespace Domodhoro
{

class Block final : public Game_Object
{
public:
    static const int SIZE = 10;

    enum class TYPE : int
    {
        DIRT = 1
    };

    Block(const SDL_Rect& destination_rect, const int type) :
        Game_Object(SDL_Rect{0, 0, 0, 0}, destination_rect),
        type(type)
    {

    }
private:
    int type;
};

}

#endif