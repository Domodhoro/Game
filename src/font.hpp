#ifndef FONT_HPP
#define FONT_HPP

namespace Domodhoro
{
    class Font final
    {
    public:
        Font()
        {
            if (TTF_Init() == -1)
            {
                throw Game_Exception("Falha ao iniciar o SDL_ttf.", __FILE__, __LINE__);
            }
        }

        ~Font()
        {
            for (const auto& it : fonts)
            {
                TTF_CloseFont(it.second);
            }

            TTF_Quit();
        }

        void load(const std::string& ID, const std::string& font_path, const int font_size)
        {
            TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);

            if (!font)
            {
                throw Game_Exception("Falha ao carregar arquivo fonte.", __FILE__, __LINE__);
            }

            fonts[ID] = font;
        }

        TTF_Font* get(const std::string& ID)
        {
            return fonts[ID];
        }
    private:
        std::map<std::string, TTF_Font*> fonts;
    };
}

#endif