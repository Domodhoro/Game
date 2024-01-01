#ifndef QUADTREE_HPP
#define QUADTREE_HPP

namespace Domodhoro
{
    class Quadtree final
    {
    public:
        Quadtree(const SDL_Rect& boundary, const int capacity) :
            boundary(boundary),
            capacity(capacity),
            divided(false)
        {
            blocks.reserve(capacity);
        }

        void insert(Block* block)
        {
            if (!is_within_bounds(block))
            {
                return;
            }

            if (blocks.size() < static_cast<size_t>(capacity))
            {
                blocks.push_back(block);
            }
            else
            {
                if (!divided)
                {
                    subdivide();
                }

                northeast->insert(block);
                northwest->insert(block);
                southeast->insert(block);
                southwest->insert(block);
            }
        }

        std::vector<Block*> query(const SDL_Rect& range)
        {
            std::vector<Block*> found_blocks;

            query(range, found_blocks);

            return found_blocks;
        }
    private:
        std::vector<Block*> blocks;

        SDL_Rect boundary;

        std::unique_ptr<Quadtree> northeast;
        std::unique_ptr<Quadtree> northwest;
        std::unique_ptr<Quadtree> southeast;
        std::unique_ptr<Quadtree> southwest;

        int capacity;

        bool divided;

        void subdivide()
        {
            const int x = boundary.x;
            const int y = boundary.y;
            const int w = boundary.w / 2;
            const int h = boundary.h / 2;

            northeast = std::make_unique<Quadtree>(SDL_Rect{x + w, y, w, h}, capacity);
            northwest = std::make_unique<Quadtree>(SDL_Rect{x, y, w, h}, capacity);
            southeast = std::make_unique<Quadtree>(SDL_Rect{x + w, y + h, w, h}, capacity);
            southwest = std::make_unique<Quadtree>(SDL_Rect{x, y + h, w, h}, capacity);

            divided = true;
        }

        bool is_within_bounds(Block* block)
        {
            const SDL_Rect rect = block->get_destination_rect();

            return SDL_HasIntersection(&boundary, &rect);
        }

        void query(const SDL_Rect& range, std::vector<Block*>& found_blocks)
        {
            if (!SDL_HasIntersection(&boundary, &range))
            {
                return;
            }

            for (const auto& it : blocks)
            {
                const SDL_Rect rect = it->get_destination_rect();

                if (SDL_HasIntersection(&rect, &range))
                {
                    found_blocks.push_back(it);
                }
            }

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

#endif