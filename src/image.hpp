#ifndef IMAGE_HPP
#define IMAGE_HPP

namespace Domodhoro
{
    // Classe responsável por gerenciar imagens do jogo.
    class Image final
    {
    public:
        // Construtor que inicializa a biblioteca SDL_image.
        Image()
        {
            if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
            {
                // Em caso de falha na inicialização.
                throw Game_Exception(IMG_GetError(), __FILE__, __LINE__);
            }
        }

        // Destrutor que libera todas as texturas carregadas.
        ~Image()
        {
            // Libera as texturas.
            for (const auto& it : textures)
            {
                SDL_DestroyTexture(it.second);
            }
        }

        // Cria uma superfície a partir do caminho de um arquivo de textura.
        SDL_Surface* create_surface(const std::string& texture_path)
        {
            SDL_Surface* surface = IMG_Load(texture_path.c_str());

            if (!surface)
            {
                // Em caso de falha.
                throw Game_Exception(IMG_GetError(), __FILE__, __LINE__);
            }

            return surface;
        }

        // Cria uma superfície a partir de um texto renderizado com uma fonte de texto e cor especificadas.
        SDL_Surface* create_surface(TTF_Font* font, const std::string& text, const SDL_Color& color)
        {
            SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);

            if (!surface)
            {
                // Em caso de falha.
                throw Game_Exception(IMG_GetError(), __FILE__, __LINE__);
            }

            return surface;
        }

        // Carrega uma textura a partir de uma superfície e associa-a a um ID.
        void load(SDL_Renderer* renderer, SDL_Surface* surface, const std::string& ID)
        {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

            if (!texture)
            {
                throw Game_Exception(IMG_GetError(), __FILE__, __LINE__);
            }

            textures[ID] = texture;
        }

        // Obtém a textura associada a um ID específico.
        SDL_Texture* get(const std::string& ID)
        {
            return textures[ID];
        }
    private:
        // Mapeamento de IDs para texturas.
        std::map<std::string, SDL_Texture*> textures;
    };
}

#endif // IMAGE_HPP