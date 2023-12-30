#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer final
{
public:
    Renderer(SDL_Window* window, const SDL_Rect& viewport) :
        viewport(viewport)
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

        if (!renderer)
        {
            throw Game_Exception("Falha ao iniciar o renderizador.", __FILE__, __LINE__);
        }
    }

    ~Renderer()
    {
        if (renderer)
        {
            SDL_DestroyRenderer(renderer);
        }
    }

    void clear(const Uint8 red, const Uint8 green, const Uint8 blue) const
    {
        SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
        SDL_RenderClear(renderer);
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

#endif