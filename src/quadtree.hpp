#ifndef QUADTREE_HPP
#define QUADTREE_HPP

namespace Domodhoro
{
    // Classe que representa uma árvore para otimização de busca espacial.
    class Quadtree final
    {
    public:
        // Construtor que inicializa a árvore com uma fronteira e capacidade especificadas.
        Quadtree(const SDL_Rect& boundary, const int capacity) :
            boundary(boundary),
            capacity(capacity),
            divided(false)
        {
            blocks.reserve(capacity);
        }

        // Insere um bloco na árvore.
        void insert(Block* block)
        {
            // Verifica se o bloco está dentro dos limites da fronteira da árvore.
            if (!is_within_bounds(block))
            {
                return;
            }

            // Se a capacidade ainda não foi atingida, adiciona o bloco à lista atual de blocos.
            if (blocks.size() < static_cast<size_t>(capacity))
            {
                blocks.push_back(block);
            }
            else
            {
                // Se a capacidade foi atingida e a árvore ainda não foi dividida, a divide.
                if (!divided)
                {
                    subdivide();
                }

                // Insere o bloco em todos os quadrantes filhos.
                northeast->insert(block);
                northwest->insert(block);
                southeast->insert(block);
                southwest->insert(block);
            }
        }

        // Realiza uma consulta na árvore dentro de uma determinada área.
        std::vector<Block*> query(const SDL_Rect& range)
        {
            std::vector<Block*> found_blocks;

            // Inicia o processo de consulta recursiva.
            query(range, found_blocks);

            return found_blocks;
        }
    private:
        // Lista de blocos dentro da fronteira da árvore.
        std::vector<Block*> blocks;
        // Fronteira da árvore.
        SDL_Rect boundary;

        // Quadrantes nordeste, noroeste, sudeste e sudoeste.
        std::unique_ptr<Quadtree> northeast;
        std::unique_ptr<Quadtree> northwest;
        std::unique_ptr<Quadtree> southeast;
        std::unique_ptr<Quadtree> southwest;

        // Capacidade máxima de blocos que podem ser armazenados antes da subdivisão.
        int capacity;

        // Indica se a árvore foi dividida.
        bool divided;

        // Subdivide a árvore em quadrantes filhos.
        void subdivide()
        {
            const int x = boundary.x;
            const int y = boundary.y;
            const int w = boundary.w / 2;
            const int h = boundary.h / 2;

            // Cria os quadrantes filhos.
            northeast = std::make_unique<Quadtree>(SDL_Rect{x + w, y, w, h}, capacity);
            northwest = std::make_unique<Quadtree>(SDL_Rect{x, y, w, h}, capacity);
            southeast = std::make_unique<Quadtree>(SDL_Rect{x + w, y + h, w, h}, capacity);
            southwest = std::make_unique<Quadtree>(SDL_Rect{x, y + h, w, h}, capacity);

            // Marca a árvore como dividida.
            divided = true;
        }

        // Verifica se um bloco está dentro dos limites da fronteira da árvore.
        bool is_within_bounds(Block* block)
        {
            const SDL_Rect rect = block->get_destination_rect();

            return SDL_HasIntersection(&boundary, &rect);
        }

        // Realiza uma consulta recursiva na árvore e coleta os blocos dentro da área especificada.
        void query(const SDL_Rect& range, std::vector<Block*>& found_blocks)
        {
            // Se a fronteira da árvore não tem interseção com a área de consulta, retorna.
            if (!SDL_HasIntersection(&boundary, &range))
            {
                return;
            }

            // Verifica os blocos dentro da fronteira da árvore que estão dentro da área de consulta.
            for (const auto& it : blocks)
            {
                const SDL_Rect rect = it->get_destination_rect();

                if (SDL_HasIntersection(&rect, &range))
                {
                    found_blocks.push_back(it);
                }
            }

            // Se a árvore foi dividida, realiza a consulta recursiva nos quadrantes filhos.
            if (divided)
            {
                northeast->query(range, found_blocks);
                northwest->query(range, found_blocks);
                southeast->query(range, found_blocks);
                southwest->query(range, found_blocks);
            }
        }
    };
}

#endif // QUADTREE_HPP