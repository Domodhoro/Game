#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

class Game_Object
{
public:
    Game_Object(const SDL_Rect& destination_rect) :
        source_rect({0, 0, 0, 0}),
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

    virtual void render(SDL_Renderer* renderer, SDL_Texture* texture, Camera* camera) const
    {
        const SDL_Rect temp =
        {
            destination_rect.x - camera->get_position().x,
            destination_rect.y - camera->get_position().y,
            destination_rect.w,
            destination_rect.h
        };

        SDL_RenderCopy(renderer, texture, &source_rect, &temp);
    }
protected:
    SDL_Rect source_rect;
    SDL_Rect destination_rect;
};

#endif