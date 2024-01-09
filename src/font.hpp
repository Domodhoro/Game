#ifndef FONT_HPP
#define FONT_HPP

namespace Domodhoro
{
    // A classe Font é responsável pela carregamento e gerenciamento de fontes de texto no jogo.
    class Font final
    {
    public:
        // Construtor da classe Font. Inicializa a biblioteca SDL_ttf.
        Font()
        {
            if (TTF_Init() == -1)
            {
                // Em caso de falha na inicialização.
                throw Game_Exception(TTF_GetError(), __FILE__, __LINE__);
            }
        }

        // Destrutor da classe Font. Libera todas as fontes e finaliza a biblioteca SDL_ttf.
        ~Font()
        {
            // Libera cada fonte armazenada no mapa.
            for (const auto& it : fonts)
            {
                TTF_CloseFont(it.second);
            }

            // Finaliza a biblioteca SDL_ttf.
            TTF_Quit();
        }

        // Carrega uma fonte identificada por um ID no mapa de fontes.
        void load(const std::string& ID, const std::string& font_path, const int font_size)
        {
            // Abre a fonte e verifica se a operação foi bem-sucedida.
            TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);

            if (!font)
            {
                // Em caso de falha.
                throw Game_Exception(TTF_GetError(), __FILE__, __LINE__);
            }

            // Armazena a fonte no mapa usando o ID fornecido.
            fonts[ID] = font;
        }

        // Obtém a fonte associada a um ID específico.
        TTF_Font* get(const std::string& ID)
        {
            return fonts[ID];
        }
    private:
        // Mapa que associa IDs de fontes a ponteiros para as fontes carregadas.
        std::map<std::string, TTF_Font*> fonts;
    };
}

#endif // FONT_HPP