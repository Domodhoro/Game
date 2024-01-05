#ifndef RENDERER_HPP
#define RENDERER_HPP

namespace Domodhoro
{
    // Classe responsável por gerenciar a renderização gráfica usando a SDL.
    class Renderer final
    {
    public:
        Renderer(SDL_Window* window, const SDL_Rect& viewport) :
            viewport(viewport)
        {
            // Inicializa o renderizador.
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

            if (!renderer)
            {
                // Em caso de falha na inicialização.
                throw Game_Exception(SDL_GetError(), __FILE__, __LINE__);
            }
        }

        // Destrutor que libera recursos associados ao renderer.
        ~Renderer()
        {
            if (renderer)
            {
                SDL_DestroyRenderer(renderer);
            }
        }

        // Limpa a tela com uma cor específica e nível de transparência.
        void clear(const SDL_Color color, const Uint8 alpha) const
        {
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, alpha);
            SDL_RenderClear(renderer);
        }

        // Renderiza uma textura na posição especificada com uma origem e destino retangulares.
        void render(SDL_Texture* texture, const SDL_Point position, const SDL_Rect source_rect, const SDL_Rect destination_rect) const
        {
            SDL_Rect temp_destination_rect = destination_rect;
            
            // Ajusta a posição da textura em relação à câmera.
            temp_destination_rect.x -= position.x;
            temp_destination_rect.y -= position.y;

            SDL_RenderCopy(renderer, texture, &source_rect, &temp_destination_rect);
        }

        // Renderiza uma textura na posição especificada com uma origem e destino retangulares e um ângulo de rotação.
        void render(SDL_Texture* texture, const SDL_Point position, const SDL_Rect source_rect, const SDL_Rect destination_rect, const double angle) const
        {
            SDL_Rect temp_destination_rect = destination_rect;
            
            // Ajusta a posição da textura em relação à câmera.
            temp_destination_rect.x -= position.x;
            temp_destination_rect.y -= position.y;

            // Renderiza a textura com rotação.
            SDL_RenderCopyEx(renderer, texture, &source_rect, &temp_destination_rect, angle, nullptr, SDL_FLIP_NONE);
        }

        // Renderiza uma textura na posição especificada com um retângulo de destino.
        void render(SDL_Texture* texture, const SDL_Rect destination_rect) const
        {
            SDL_RenderCopy(renderer, texture, nullptr, &destination_rect);
        }

        // Renderiza uma textura na posição especificada com um retângulo de destino e um ângulo de rotação.
        void render(SDL_Texture* texture, const SDL_Rect destination_rect, const double angle) const
        {
            // Renderiza a textura com rotação.
            SDL_RenderCopyEx(renderer, texture, nullptr, &destination_rect, angle, nullptr, SDL_FLIP_NONE);
        }

        // Atualiza a tela com as alterações realizadas nos métodos de renderização presente.
        void present() const
        {
            // Define a viewport antes de apresentar o renderer.
            SDL_RenderSetViewport(renderer, &viewport);
            SDL_RenderPresent(renderer);
        }

        // Obtém o ponteiro para o SDL_Renderer associado.
        SDL_Renderer* get() const
        {
            return renderer;
        }
    private:
        // Ponteiro para o SDL_Renderer.
        SDL_Renderer* renderer;
        // Viewport que define a área de renderização na janela.
        SDL_Rect viewport;
    };
}

#endif // RENDERER_HPP