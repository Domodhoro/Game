#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

namespace Domodhoro
{
    // Classe base para objetos do jogo.
    class Game_Object
    {
    public:
        // Construtor padrão.
        Game_Object() :
            source_rect({0, 0, 0, 0}),
            destination_rect({0, 0, 0, 0})
        {

        }

        // Construtor que aceita apenas a posição de destino.
        Game_Object(const SDL_Rect& destination_rect) :
            source_rect({0, 0, 0, 0}),
            destination_rect(destination_rect)
        {

        }

        // Construtor que aceita ambas as posições de origem e destino.
        Game_Object(const SDL_Rect& source_rect, const SDL_Rect& destination_rect) :
            source_rect(source_rect),
            destination_rect(destination_rect)
        {
            
        }

        // Destrutor virtual padrão.
        virtual ~Game_Object() = default;

        // Função virtual para obter a posição de origem.
        virtual SDL_Rect get_source_rect() const
        {
            return source_rect;
        }

        // Função virtual para obter a posição de destino.
        virtual SDL_Rect get_destination_rect() const
        {
            return destination_rect;
        }

        // Função virtual para definir a posição de origem.
        virtual void set_source_rect(const SDL_Rect& source_rect)
        {
            this->source_rect = source_rect;
        }

        // Função virtual para definir a posição de destino.
        virtual void set_destination_rect(const SDL_Rect& destination_rect)
        {
            this->destination_rect = destination_rect;
        }
    protected:
        // Variáveis membros para a posição de origem e destino.
        SDL_Rect source_rect;
        SDL_Rect destination_rect;
    };
}

#endif // GAME_OBJECT_HPP