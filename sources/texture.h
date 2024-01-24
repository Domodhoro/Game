#ifndef TEXTURE_H
#define TEXTURE_H

// Cria uma textura a partir de um arquivo.
SDL_Texture *get_texture(SDL_Renderer *renderer, const char *file_path) {
    // Cria uma superfície a partir do arquivo de textura.
	SDL_Surface *surface = IMG_Load(file_path);

    // Verifica se a superfície foi carregada com sucesso.
    if (surface == NULL) custom_error(IMG_GetError(), __FILE__, __LINE__);

    // Cria uma textura a partir da superfície usando o renderizador.
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Verifica se a textura foi criada com sucesso.
    if (texture == NULL) custom_error(IMG_GetError(), __FILE__, __LINE__);

    // Libera a superfície, pois a textura já foi criada.
    SDL_FreeSurface(surface);

	return texture;
}

// Define a transparência de uma textura.
void set_texture_transparency(SDL_Texture *texture, const Uint8 alpha) {
    // Define o valor de alpha da textura.
    SDL_SetTextureAlphaMod(texture, alpha);
}

// Cria uma textura a partir de um texto.
SDL_Texture *get_text_texture(SDL_Renderer *renderer, TTF_Font *font, Text *text) {
    // Cria uma superfície a partir do arquivo de textura.
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text->string, text->color);

    // Verifica se a superfície foi carregada com sucesso.
    if (surface == NULL) custom_error(IMG_GetError(), __FILE__, __LINE__);

    // Obtém as dimensões da superfície.
    text->dst.w = surface->w;
    text->dst.h = surface->h;

    // Cria uma textura a partir da superfície usando o renderizador.
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Verifica se a textura foi criada com sucesso.
    if (texture == NULL) custom_error(IMG_GetError(), __FILE__, __LINE__);

    // Libera a superfície, pois a textura já foi criada.
    SDL_FreeSurface(surface);

    return texture;
}

#endif // TEXTURE_H