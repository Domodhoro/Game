#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

namespace Domodhoro
{
	class Keyboard final
    {
    public:
       	void update(bool& running)
    	{
    		while (SDL_PollEvent(&event) != 0)
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    running = false;

                    break;

                case SDL_KEYDOWN:
                    keys.insert(event.key.keysym.scancode);

                    break;

                case SDL_KEYUP:
                    keys.erase(event.key.keysym.scancode);

                    break;
                }
            }
    	}

    	const std::unordered_set<SDL_Scancode>& get_keys() const
    	{
    		return keys;
    	}

    	const std::map<int, Entity::DIRECTION>& get_key_mappings() const
    	{
    		return key_mappings;
    	}
    private:
    	SDL_Event event;

    	std::unordered_set<SDL_Scancode> keys;

    	std::map<int, Entity::DIRECTION> key_mappings = 
        {
            {SDL_SCANCODE_SPACE, Entity::DIRECTION::UP},
            {SDL_SCANCODE_A, Entity::DIRECTION::LEFT},
            {SDL_SCANCODE_D, Entity::DIRECTION::RIGHT}
        };
    };
}

#endif