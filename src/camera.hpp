#ifndef CAMERA_HPP
#define CAMERA_HPP

namespace Domodhoro
{
    // A classe Camera representa a câmera 2D no jogo, controlando a área de visualização.
    class Camera final
    {
    public:
        // Construtor da classe Camera. Aceita a posição inicial da câmera.
        Camera(const SDL_Point& position) :
            position(position)
        {

        }

        // Define a posição da câmera para a posição fornecida.
        void set_position(const SDL_Point& position)
        {
            this->position = position;
        }

        // Retorna a posição atual da câmera.
        SDL_Point get_position() const
        {
            return position;
        }
    private:
        // Posição atual da câmera no mundo do jogo.
        SDL_Point position;
    };
}

#endif // CAMERA_HPP