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
            throw Game_Exception("Falha ao iniciar o SDL_image.", __FILE__, __LINE__);
        }
    }

    ~Image()
    {
        for (const auto& it : textures)
        {
            SDL_DestroyTexture(it.second);
        }
    }

    void load(SDL_Renderer* renderer, const std::string& ID, const std::string& texture_path)
    {
        SDL_Surface* surface = create_surface(texture_path);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        if (!texture)
        {
            throw Game_Exception("Falha ao criar textura: " + texture_path, __FILE__, __LINE__);
        }

        SDL_FreeSurface(surface);

        textures[ID] = texture;
    }

    void load(SDL_Renderer* renderer, const std::string& ID, TTF_Font* font, const std::string& text, const SDL_Color& color)
    {
        SDL_Surface* surface = create_surface(font, text, color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        if (!texture)
        {
            throw Game_Exception("Falha ao criar textura (texto).", __FILE__, __LINE__);
        }

        SDL_FreeSurface(surface);

        textures[ID] = texture;
    }

    SDL_Texture* use(const std::string& ID)
    {
        return textures[ID];
    }
private:
    std::map<std::string, SDL_Texture*> textures;

    SDL_Surface* create_surface(const std::string& texture_path)
    {
        SDL_Surface* surface = IMG_Load(texture_path.c_str());

        if (!surface)
        {
            throw Game_Exception("Falha ao carregar textura: " + texture_path, __FILE__, __LINE__);
        }

        return surface;
    }

    SDL_Surface* create_surface(TTF_Font* font, const std::string& text, const SDL_Color& color)
    {
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

        if (!surface)
        {
            throw Game_Exception("Falha ao carregar textura (texto):", __FILE__, __LINE__);
        }

        return surface;
    }
};

}

#endif