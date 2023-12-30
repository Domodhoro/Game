#ifndef CHUNK_HPP
#define CHUNK_HPP

class Chunk final
{
public:
    static const int WIDTH = 16;
    static const int HEIGHT = 256;

    Chunk(const int x, const int y, const int seed) :
        noise(std::make_unique<Noise>(seed))
    {
        for (int i = 0; i < WIDTH; i++)
        {
            for (int j = 0; j < HEIGHT; j++)
            {
                const int block_x = x + i * Block::SIZE;
                const int block_y = y + j * Block::SIZE;

                if (noise->get(block_x, block_y) > 0.75f)
                {
                    const SDL_Rect destination_rect =
                    {
                        block_x, block_y, Block::SIZE, Block::SIZE
                    };

                    blocks.push_back(std::make_unique<Block>(destination_rect, static_cast<int>(Block::TYPE::DIRT)));
                }
            }
        }

        update_quadtree(x, y);
    }

    bool check_collision(const Entity* player) const
    {
        SDL_Rect rect_1 = player->get_destination_rect();

        for (const Block* block : quadtree->query(rect_1))
        {
            SDL_Rect rect_2 = block->get_destination_rect();

            if (SDL_HasIntersection(&rect_1, &rect_2))
            {
                return true;
            }
        }

        return false;
    }

    void render(SDL_Renderer* renderer, Image* image, Camera* camera) const
    {
        for (const auto& it : blocks)
        {
            it->set_source_rect({0, 496, 16, 16});
            it->render(renderer, image->use("BLOCK"), camera);
        }
    }
private:
    std::vector<std::unique_ptr<Block>> blocks;

    std::unique_ptr<Noise> noise;
    std::unique_ptr<Quadtree> quadtree;

    void update_quadtree(const int x, const int y)
    {
        const SDL_Rect chunk_bounds =
        {
            x, y, x + WIDTH * Block::SIZE, y + HEIGHT * Block::SIZE
        };

        quadtree = std::make_unique<Quadtree>(chunk_bounds, 4);

        for (const auto& block : blocks)
        {
            quadtree->insert(block.get());
        }
    }
};

#endif