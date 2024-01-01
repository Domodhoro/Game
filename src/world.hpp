#ifndef WORLD_HPP
#define WORLD_HPP

namespace Domodhoro
{
    class World final
    {
    public:
        World(const int seed)
        {
            const int gap = static_cast<int>(Block::WIDTH);

            for (int i = 0; i < 4; i++)
            {
                chunks.push_back(std::make_unique<Chunk>(i * Chunk::WIDTH * gap, 0, seed));
            }
        }

        bool check_collision(const Entity* player) const
        {
#if COLLISION
            for (const auto& it : chunks)
            {
                if (it->check_collision(player))
                {
                    return true;
                }
            }
#endif
            return false;
        }

        void render(Renderer* renderer, Image* image, const SDL_Point& camera_position) const
        {
            for (const auto& it : chunks)
            {
                it->render(renderer, image, camera_position);
            }
        }
    private:
        std::vector<std::unique_ptr<Chunk>> chunks;
    };
}

#endif