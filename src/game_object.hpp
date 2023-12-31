#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

namespace Domodhoro
{

class Game_Object
{
public:
    Game_Object(const SDL_Rect& source_rect, const SDL_Rect& destination_rect) :
        source_rect(source_rect),
        destination_rect(destination_rect)
    {
        
    }

    virtual ~Game_Object() = default;

    virtual SDL_Rect get_source_rect() const
    {
        return source_rect;
    }

    virtual SDL_Rect get_destination_rect() const
    {
        return destination_rect;
    }

    virtual void set_source_rect(const SDL_Rect& source_rect)
    {
        this->source_rect = source_rect;
    }

    virtual void set_destination_rect(const SDL_Rect& destination_rect)
    {
        this->destination_rect = destination_rect;
    }
protected:
    SDL_Rect source_rect;
    SDL_Rect destination_rect;
};

}

#endif