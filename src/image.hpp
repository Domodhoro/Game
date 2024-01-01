#ifndef IMAGE_HPP
#define IMAGE_HPP

namespace Domodhoro
{
    class Image final
    {
    public:
        Image()
        {
            if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
            {
                throw Game_Exception(IMG_GetError(), __FILE__, __LINE__);
            }
        }

        ~Image()
        {
            for (const auto& it : textures)
            {
                SDL_DestroyTexture(it.second);
            }
        }

        SDL_Surface* create_surface(const std::string& texture_path)
        {
            SDL_Surface* surface = IMG_Load(texture_path.c_str());

            if (!surface)
            {
                throw Game_Exception(IMG_GetError(), __FILE__, __LINE__);
            }

            return surface;
        }

        SDL_Surface* create_surface(TTF_Font* font, const std::string& text, const SDL_Color& color)
        {
            SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);

            if (!surface)
            {
                throw Game_Exception(IMG_GetError(), __FILE__, __LINE__);
            }

            return surface;
        }

        void load(SDL_Renderer* renderer, SDL_Surface* surface, const std::string& ID)
        {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

            if (!texture)
            {
                throw Game_Exception(IMG_GetError(), __FILE__, __LINE__);
            }

            textures[ID] = texture;
        }

        SDL_Texture* get(const std::string& ID)
        {
            return textures[ID];
        }
    private:
        std::map<std::string, SDL_Texture*> textures;
    };
}

#endif