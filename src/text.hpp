#ifndef TEXT_HPP
#define TEXT_HPP

namespace Domodhoro
{
	class Text final
	{
	public:
		Text(Renderer* renderer, Image* image) :
			font(std::make_unique<Font>())
		{
			font->load("DEFAULT", "./font/04B_03__.TTF", 16);

			texts.push_back(std::make_unique<Game_Object>());

			show_player_coordinates(renderer, image, {0, 0});
		}

		void show_player_coordinates(Renderer* renderer, Image* image, const SDL_Point player_position)
        {
            text_string = "(X : " + std::to_string(player_position.x) + ", Y : " + std::to_string(player_position.y) + ")";

            SDL_Surface* text_surface = image->create_surface(font->get("DEFAULT"), text_string, {255, 255, 255});

			texts.back()->set_destination_rect(SDL_Rect{16, 16, text_surface->w, text_surface->h});
			
			image->load(renderer->get(), text_surface, "PLAYER_COORDINATES");

			SDL_FreeSurface(text_surface);
        }

		void render(Renderer* renderer, Image* image) const
		{
			for (const auto& it : texts)
			{
				renderer->render(image->get("PLAYER_COORDINATES"), it->get_destination_rect());
			}
		}
	private:
		std::unique_ptr<Font> font;
		
		std::vector<std::unique_ptr<Game_Object>> texts;

		std::string text_string;
	};
}

#endif