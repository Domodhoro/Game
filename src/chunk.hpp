#ifndef CHUNK_HPP
#define CHUNK_HPP

namespace Domodhoro
{
    class Chunk final
    {
    public:
        static const int WIDTH = 16;
        static const int HEIGHT = 256;

        Chunk(const int x, const int y, const int seed) :
            noise(std::make_unique<Noise>(seed))
        {
            blocks.reserve(static_cast<int>(WIDTH * HEIGHT));

            for (int i = 0; i < WIDTH; i++)
            {
                for (int j = 0; j < HEIGHT; j++)
                {
                    const int block_x = x + i * Block::WIDTH;
                    const int block_y = y + j * Block::HEIGHT;

                    if (noise->get(block_x, block_y) > 0.75f)
                    {
                        const SDL_Rect destination_rect =
                        {
                            block_x, block_y, Block::WIDTH, Block::HEIGHT
                        };

                        blocks.push_back(std::make_unique<Block>(destination_rect, Block::TYPE::DIRT));
                    }
                }
            }

            static const int quadtree_capacity = 4;

            update_quadtree(x, y, quadtree_capacity);
        }

        Block::TYPE get_block_type_at(const int x, const int y) const
        {
            return blocks.at(x + y * WIDTH)->get_type();
        }

        bool check_collision(const Entity* player) const
        {
            SDL_Rect rect_1 = player->get_destination_rect();

            for (const auto& it : quadtree->query(rect_1))
            {
                SDL_Rect rect_2 = it->get_destination_rect();

                if (SDL_HasIntersection(&rect_1, &rect_2))
                {
                    return true;
                }
            }

            return false;
        }

        void render(Renderer* renderer, Image* image, const SDL_Point& camera_position) const
        {
            for (const auto& it : blocks)
            {
                it->set_source_rect({0, 496, 16, 16});
                
                renderer->render(image->get("BLOCK"), camera_position, it->get_source_rect(), it->get_destination_rect());
            }
        }
    private:
        std::vector<std::unique_ptr<Block>> blocks;

        std::unique_ptr<Noise> noise;
        std::unique_ptr<Quadtree> quadtree;

        void update_quadtree(const int x, const int y, const int capacity)
        {
            const SDL_Rect chunk_bounds =
            {
                x, y, x + WIDTH * Block::WIDTH, y + HEIGHT * Block::HEIGHT
            };

            quadtree = std::make_unique<Quadtree>(chunk_bounds, capacity);

            for (const auto& block : blocks)
            {
                quadtree->insert(block.get());
            }
        }
    };
}

#endif