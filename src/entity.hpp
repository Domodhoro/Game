#ifndef ENTITY_HPP
#define ENTITY_HPP

namespace Domodhoro
{
    // A classe Entity representa um objeto móvel no jogo, derivado da classe Game_Object.
    class Entity : public Game_Object
    {
    public:
        // Enumeração que define direções possíveis para o movimento da entidade.
        enum class DIRECTION
        {
            DEFAULT,
            UP,
            DOWN, 
            LEFT, 
            RIGHT
        };

        // Construtor da classe Entity. Aceita um retângulo de destino.
        Entity(const SDL_Rect& destination_rect) :
            Game_Object(SDL_Rect{0, 0, 0, 0}, destination_rect)
        {

        }

        // Define a posição da entidade com base em uma SDL_Point.
        void set_position(const SDL_Point& position)
        {
            destination_rect.x = position.x;
            destination_rect.y = position.y;
        }

        // Obtém a posição da entidade como uma SDL_Point.
        SDL_Point get_position() const
        {
            return SDL_Point{destination_rect.x , destination_rect.y};
        }

        // Move a entidade na direção especificada.
        void move(DIRECTION direction)
        {
            switch (direction)
            {
                // Move a entidade para cima.
                case DIRECTION::UP:
                    move_up();

                    break;
                // Move a entidade para baixo.
                case DIRECTION::DOWN:
                    move_down();

                    break;
                // Move a entidade para esquerda.
                case DIRECTION::LEFT:
                    move_left();

                    break;
                // Move a entidade para direita.
                case DIRECTION::RIGHT:
                    move_right();

                    break;
            }
        }

        // Inverte a direção fornecida.
        static DIRECTION reverse_direction(DIRECTION direction)
        {
            switch (direction)
            {
                case DIRECTION::UP:
                    return DIRECTION::DOWN;
                case DIRECTION::DOWN:
                    return DIRECTION::UP;
                case DIRECTION::LEFT:
                    return DIRECTION::RIGHT;
                case DIRECTION::RIGHT:
                    return DIRECTION::LEFT;
            }

            return DIRECTION::UP;
        }
    protected:
        // Métodos de movimento protegidos para serem usados pelas subclasses.
        void move_right()
        {
            // Move a entidade para cima em 1 pixel.
            destination_rect.x += 1;
        }

        void move_left()
        {
            // Move a entidade para baixo em 1 pixel.
            destination_rect.x -= 1;
        }

        void move_up()
        {
            // Move a entidade para esquerda em 1 pixel.
            destination_rect.y -= 1;
        }

        void move_down()
        {
            // Move a entidade para direita em 1 pixel.
            destination_rect.y += 1;
        }
    };
}

#endif // ENTITY_HPP