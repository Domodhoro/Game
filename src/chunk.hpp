#ifndef CHUNK_HPP
#define CHUNK_HPP

namespace Domodhoro
{
    // A classe Chunk representa um pedaço gerenciável do mundo do jogo, gerando e armazenando blocos.
    class Chunk final
    {
    public:
        // Largura e altura padrão do Chunk, em número de blocos.
        static const int WIDTH = 16;
        static const int HEIGHT = 256; 

        // Construtor da classe Chunk. Gera blocos com base em um ruído, atualiza um quadtree e inicializa membros.
        Chunk(const int x, const int y, const int seed) :
            noise(std::make_unique<Noise>(seed))
        {
            // Reserva espaço no vetor para armazenar os blocos do Chunk.
            blocks.reserve(static_cast<int>(WIDTH * HEIGHT));

            // Loop para gerar blocos dentro do Chunk.
            for (int i = 0; i < WIDTH; i++)
            {
                for (int j = 0; j < HEIGHT; j++)
                {
                    // Calcula as coordenadas x e y do bloco no mundo do jogo.
                    const int block_x = x + i * Block::WIDTH;
                    const int block_y = y + j * Block::HEIGHT;

                    // Verifica se a posição do bloco possui um valor de ruído suficientemente alto.
                    if (noise->get(block_x, block_y) > 0.75f)
                    {
                        // Cria um retângulo de destino para o bloco.
                        const SDL_Rect destination_rect =
                        {
                            block_x, block_y, Block::WIDTH, Block::HEIGHT
                        };

                        // Adiciona um bloco ao vetor, usando o tipo de bloco.
                        blocks.push_back(std::make_unique<Block>(destination_rect, Block::TYPE::DIRT));
                    }
                }
            }

            // Define a capacidade máxima de elementos no quadtree para otimizar consultas.
            static const int quadtree_capacity = 4;

            // Atualiza o quadtree com base nos blocos gerados no Chunk.
            update_quadtree(x, y, quadtree_capacity);
        }

        // Retorna o tipo de bloco na posição (x, y) dentro do Chunk.
        Block::TYPE get_block_type_at(const int x, const int y) const
        {
            return blocks.at(x + y * WIDTH)->get_type();
        }

        // Verifica colisões entre o jogador e os blocos do Chunk usando um quadtree.
        bool check_collision(const Entity* player) const
        {
            // Obtém o retângulo de destino do jogador.
            SDL_Rect rect_1 = player->get_destination_rect();

            // Loop através dos blocos no quadtree que podem colidir com o jogador.
            for (const auto& it : quadtree->query(rect_1))
            {
                // Obtém o retângulo de destino do bloco atual.
                SDL_Rect rect_2 = it->get_destination_rect();

                // Verifica se há interseção entre os retângulos do jogador e do bloco.
                if (SDL_HasIntersection(&rect_1, &rect_2))
                {   
                    // Colisão detectada, retorna true.
                    return true;
                }
            }

            // Nenhuma colisão detectada, retorna false.
            return false;
        }

        // Renderiza os blocos do Chunk usando um renderer e uma imagem, considerando a posição da câmera.
        void render(Renderer* renderer, Image* image, const SDL_Point& camera_position) const
        {
            // Itera sobre cada bloco no vetor de blocos do Chunk.
            for (const auto& it : blocks)
            {
                // Define o retângulo de origem do bloco para renderização.
                it->set_source_rect({0, 496, 16, 16});
                
                // Renderiza o bloco usando o renderer, a imagem "BLOCK" e a posição da câmera.
                renderer->render(image->get("BLOCK"), camera_position, it->get_source_rect(), it->get_destination_rect());
            }
        }
    private:
        // Armazena os blocos presentes no Chunk.
        std::vector<std::unique_ptr<Block>> blocks;
        // Gerador de ruído usado para gerar a distribuição dos blocos no Chunk.
        std::unique_ptr<Noise> noise;
        // Quadtree para otimizar consultas de colisão.
        std::unique_ptr<Quadtree> quadtree; 

        // Atualiza o quadtree com base nos blocos presentes no Chunk.
        void update_quadtree(const int x, const int y, const int capacity)
        {
            // Cria um retângulo que representa os limites do Chunk no mundo do jogo.
            const SDL_Rect chunk_bounds =
            {
                x, y, x + WIDTH * Block::WIDTH, y + HEIGHT * Block::HEIGHT
            };

            // Inicializa o quadtree para otimizar consultas de colisão dentro dos limites do Chunk.
            quadtree = std::make_unique<Quadtree>(chunk_bounds, capacity);

            // Insere cada bloco do Chunk no quadtree para otimizar futuras consultas de colisão.
            for (const auto& block : blocks)
            {
                quadtree->insert(block.get());
            }
        }
    };
}

#endif // CHUNK_HPP