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
            position({0, 0}),
            left_button(false),
            right_button(false)
        {

        }

        // Atualiza a posição do mouse.
        void update()
        {
            // Lê a posição (x, y) do cursor do mouse na tela.
            SDL_GetMouseState(&position.x, &position.y);

            // Atualiza o estado dos botões
            left_button = (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT));
            right_button = (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_RIGHT));
        }

        // Obtém a posição atual do mouse.
        SDL_Point get_position() const
        {
            return position;
        }

        // Verifica se o botão esquerdo está pressionado.
        bool is_left_button_pressed() const
        {
            return left_button;
        }

        // Verifica se o botão direito está pressionado.
        bool is_right_button_pressed() const
        {
            return right_button;
        }
    private:
        // Estrutura que armazena a posição do mouse.
        SDL_Point position;

        // Estado dos botões do mouse.
        bool left_button;
        bool right_button;
    };
}

#endif // MOUSE_HPP