#ifndef MOUSE_HPP
#define MOUSE_HPP

namespace Domodhoro
{
    // Classe responsável por gerenciar o mouse.
	class Mouse final
    {
    public:
        // Construtor que inicializa a posição do mouse.
        Mouse() :
            position({0, 0})
        {

        }

        // Atualiza a posição do mouse.
        void update()
        {
            SDL_GetMouseState(&position.x, &position.y);
        }

        // Obtém a posição atual do mouse.
        SDL_Point get_position() const
        {
            return position;
        }
    private:
        // Estrutura que armazena a posição do mouse.
        SDL_Point position;
    };
}

#endif // MOUSE_HPP