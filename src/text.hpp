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
			font->load("04B_03__", "./font/04B_03__.TTF", 8);

			texts.push_back(std::make_unique<Game_Object>(SDL_Rect{10, 10, 100, 16}));

			SDL_Surface* text_surface = image->create_surface(font->get("04B_03__"), "Hello, world!", {0, 0, 0});
			
			image->load(renderer->get(), text_surface, "TEXT_1");

			SDL_FreeSurface(text_surface);
		}

		void render(Renderer* renderer, Image* image) const
		{
			for (const auto& it : texts)
			{
				renderer->render(image->get("TEXT_1"), it->get_destination_rect());
			}
		}
	private:
		std::unique_ptr<Font> font;
		
		std::vector<std::unique_ptr<Game_Object>> texts;
	};
}

#endif