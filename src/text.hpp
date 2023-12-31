#ifndef TEXT_HPP
#define TEXT_HPP

namespace Domodhoro
{
	
class Text final
{
public:
	Text(Renderer* renderer, Image* image)
	{
		font = std::make_unique<Font>();
		text = std::make_unique<Game_Object>(SDL_Rect{0, 0, 0, 0}, SDL_Rect{10, 10, 138, 26});

		text->set_source_rect({0, 0, 128, 16});
		font->load("04B_03__", "./font/04B_03__.TTF", 16);
		image->load(renderer->get(), "TEXT_1", font->get("04B_03__"), "Hello, world!", {0, 255, 0});
	}

	void render(Renderer* renderer, Image* image)
	{
		renderer->render(image->use("TEXT_1"), SDL_Point{0, 0}, text->get_source_rect(), text->get_destination_rect());
	}
private:
	std::unique_ptr<Font> font;
	std::unique_ptr<Game_Object> text;
};

}

#endif