#ifndef TEXT_HPP
#define TEXT_HPP

namespace Domodhoro
{
	// Classe responsável por exibir texto na tela usando uma fonte carregada.
	class Text final
	{
	public:
		// Construtor que inicializa a fonte e cria um objeto de texto padrão.
		Text(Renderer* renderer, Image* image) :
			font(std::make_unique<Font>())
		{
			// Carrega a fonte e dá o ID "DEFAULT".
			font->load("DEFAULT", "./font/04B_03__.TTF", 16);

			// Cria um objeto de texto inicial.
			text = std::make_unique<Game_Object>();
		}

		// Renderiza as coordenadas do jogador na tela.
		void render_player_coordinates(Renderer* renderer, Image* image, const SDL_Point player_position)
        {
        	// Gera uma string formatada com as coordenadas do jogador.
            std::string text_string = "(X : " + std::to_string(player_position.x) + ", Y : " + std::to_string(-1 * player_position.y) + ")";

            // Cria uma superfície de texto usando a fonte e a string gerada.
            SDL_Surface* text_surface = image->create_surface(font->get("DEFAULT"), text_string, {255, 255, 255});

            // Cria uma superfície de texto usando a fonte e a string gerada.
			text->set_destination_rect(SDL_Rect{16, 16, text_surface->w, text_surface->h});
			
			// Carrega a superfície de texto como uma textura chamada "PLAYER_COORDINATES".
			image->load(renderer->get(), text_surface, "PLAYER_COORDINATES");

			// Libera a memória da superfície de texto.
			SDL_FreeSurface(text_surface);

			// Renderiza a textura "PLAYER_COORDINATES" na posição do objeto de texto.
			renderer->render(image->get("PLAYER_COORDINATES"), text->get_destination_rect());
        }
	private:
		// Fonte usada para renderizar texto.
		std::unique_ptr<Font> font;
		
		// Armazena o objeto de texto.
		std::unique_ptr<Game_Object> text;
	};
}

#endif // TEXT_HPP