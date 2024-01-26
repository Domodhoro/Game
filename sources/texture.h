#ifndef TEXTURE_H
#define TEXTURE_H

SDL_Texture *get_texture(SDL_Renderer *renderer, const char *file_path) {
	SDL_Surface *surface = IMG_Load(file_path);

    if (surface == NULL) {
        custom_error(IMG_GetError(), __FILE__, __LINE__);
    }

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture == NULL) {
        custom_error(IMG_GetError(), __FILE__, __LINE__);
    }

    SDL_FreeSurface(surface);

	return texture;
}

void set_texture_transparency(SDL_Texture *texture, const Uint8 alpha) {
    SDL_SetTextureAlphaMod(texture, alpha);
}

SDL_Texture *get_text_texture(SDL_Renderer *renderer, TTF_Font *font, Text *text) {
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text->string, text->color);

    if (surface == NULL) {
        custom_error(IMG_GetError(), __FILE__, __LINE__);
    }

    text->dst.w = surface->w;
    text->dst.h = surface->h;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture == NULL) {
        custom_error(IMG_GetError(), __FILE__, __LINE__);
    }

    SDL_FreeSurface(surface);

    return texture;
}

#endif