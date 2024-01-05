#ifndef BLOCK_HPP
#define BLOCK_HPP

namespace Domodhoro
{ 
    // A classe Block herda de Game_Object e representa blocos no jogo.
    class Block final : public Game_Object
    {
    public:
        // Largura e altura (em pixels) padrão para instâncias da classe Block.
        static const int WIDTH = 10;
        static const int HEIGHT = 10;

        // Enumeração que define os tipos de blocos.
        enum class TYPE
        {
            DIRT
        };

        // Construtor da classe Block. Aceita um retângulo de destino e um tipo de bloco.
        Block(const SDL_Rect& destination_rect, const TYPE type) :
            Game_Object(SDL_Rect{0, 0, 0, 0}, destination_rect),
            type(type)
        {

        }

        // Retorna o tipo do bloco.
        TYPE get_type() const
        {
            return type;
        }
    private:
        // Tipo do bloco representado pela instância da classe.
        TYPE type;
    };
}

#endif // BLOCK_HPP