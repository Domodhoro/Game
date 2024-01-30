#ifndef TEXTURE_H
#define TEXTURE_H

SDL_Surface *create_surface_IMG(const char *file_path) {
    SDL_Surface *surface = IMG_Load(file_path);

    if (surface == NULL) {
        custom_error(IMG_GetError(), __FILE__, __LINE__);
    }

    return surface;
}

SDL_Texture *get_texture(SDL_Renderer *renderer, const char *file_path) {
	SDL_Surface *surface = create_surface_IMG(file_path);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture == NULL) {
        custom_error(IMG_GetError(), __FILE__, __LINE__);
    }

    if (surface != NULL) {
        SDL_FreeSurface(surface);
    }

	return texture;
}

void set_texture_transparency(SDL_Texture *texture, const Uint8 alpha) {
    SDL_SetTextureAlphaMod(texture, alpha);
}

#endif