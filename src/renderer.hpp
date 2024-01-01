#ifndef RENDERER_HPP
#define RENDERER_HPP

namespace Domodhoro
{
    class Renderer final
    {
    public:
        Renderer(SDL_Window* window, const SDL_Rect& viewport) :
            viewport(viewport)
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

            if (!renderer)
            {
                throw Game_Exception(SDL_GetError(), __FILE__, __LINE__);
            }
        }

        ~Renderer()
        {
            if (renderer)
            {
                SDL_DestroyRenderer(renderer);
            }
        }

        void clear(const SDL_Color color, const Uint8 alpha) const
        {
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, alpha);
            SDL_RenderClear(renderer);
        }

        void render(SDL_Texture* texture, const SDL_Point position, const SDL_Rect source_rect, const SDL_Rect destination_rect) const
        {
            SDL_Rect temp_destination_rect = destination_rect;
            
            temp_destination_rect.x -= position.x;
            temp_destination_rect.y -= position.y;

            SDL_RenderCopy(renderer, texture, &source_rect, &temp_destination_rect);
        }

        void render(SDL_Texture* texture, const SDL_Point position, const SDL_Rect source_rect, const SDL_Rect destination_rect, const double angle) const
        {
            SDL_Rect temp_destination_rect = destination_rect;
            
            temp_destination_rect.x -= position.x;
            temp_destination_rect.y -= position.y;

            SDL_RenderCopyEx(renderer, texture, &source_rect, &temp_destination_rect, angle, nullptr, SDL_FLIP_NONE);
        }

        void render(SDL_Texture* texture, const SDL_Rect destination_rect) const
        {
            SDL_RenderCopy(renderer, texture, nullptr, &destination_rect);
        }

        void render(SDL_Texture* texture, const SDL_Rect destination_rect, const double angle) const
        {
            SDL_RenderCopyEx(renderer, texture, nullptr, &destination_rect, angle, nullptr, SDL_FLIP_NONE);
        }

        void present() const
        {
            SDL_RenderSetViewport(renderer, &viewport);
            SDL_RenderPresent(renderer);
        }

        SDL_Renderer* get() const
        {
            return renderer;
        }
    private:
        SDL_Renderer* renderer;

        SDL_Rect viewport;
    };
}

#endif