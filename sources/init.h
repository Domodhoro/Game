#ifndef INIT_H
#define INIT_H

// Inicializa a biblioteca SDL para suporte de vídeo.
void init_SDL() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) custom_error(SDL_GetError(), __FILE__, __LINE__);
}

// Inicializa a biblioteca SDL_image para manipulação de imagens PNG e carrega texturas iniciais.
void init_SDL_image(Game *game) {
	if (IMG_Init(IMG_INIT_PNG) == 0) custom_error(SDL_GetError(), __FILE__, __LINE__);
}

// Inicializa a biblioteca SDL_ttf para renderização de texto.
void init_SDL_ttf(Game *game) {
	if (TTF_Init() != 0) custom_error(SDL_GetError(), __FILE__, __LINE__);
}

// Inicializa a biblioteca SDL_mixer para reprodução de áudio.
void init_SDL_mixer(Game *game) {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) custom_error(Mix_GetError(), __FILE__, __LINE__);
}

// Inicializa o interpretador Lua, cria um novo estado Lua e carrega arquivos Lua.
void init_lua(Game* game) {
	game->L = luaL_newstate();

	if (game->L == NULL) custom_error("Failed to create Lua state.", __FILE__, __LINE__);

    // Abre as bibliotecas padrão do Lua.
    luaL_openlibs(game->L);

    // Abre o arquivo Lua que define os níveis.
    if (luaL_dofile(game->L, "./scripts/script.lua") != 0) custom_error(lua_tostring(game->L, -1), __FILE__, __LINE__);
}

// Função para inicializar o jogo.
void init(Game *game) {
	// Inicializa a biblioteca SDL.
	init_SDL();
	
	// Cria a janela e o renderizador.
	create_window(game);
	create_renderer(game);

	// Inicializa a manipulação de imagens, fontes e áudio.
	init_SDL_image(game);
	init_SDL_ttf(game);
	init_SDL_mixer(game);

	// Inicializa o interpretador Lua.
	init_lua(game);

	// Abre a fonte para renderização de texto e verifica se a fonte foi carregada corretamente.
    game->font = TTF_OpenFont("./fonts/04B_03__.TTF", FONT_SIZE);

    if (game->font == NULL) custom_error(TTF_GetError(), __FILE__, __LINE__);

    // Cria um texto definindo a cor e a posição na tela.
    game->text.string = "Hello, world!";
    game->text.color = GREEN;
    game->text.dst.x = 16;
	game->text.dst.y = 50;

	// Carrega texturas iniciais a partir dos arquivos de imagem.
	game->texture_atlas.text = get_text_texture(game->renderer, game->font, &game->text);
	game->texture_atlas.player = get_texture(game->renderer, "./textures/player.png");
	game->texture_atlas.blocks = get_texture(game->renderer, "./textures/blocks.png");
	game->texture_atlas.heart = get_texture(game->renderer, "./textures/heart.png");
	game->texture_atlas.inventory_back = get_texture(game->renderer, "./textures/inventory_back.png");

	// Define a transparência da textura do inventário.
	set_texture_transparency(game->texture_atlas.inventory_back, 127);

	// Inicializa o estado de execução do jogo.
	game->running = true;

	// Inicializa a posição da câmera.
	game->camera_position.x = 0;
	game->camera_position.y = 0;

	// Cria o mundo.
	create_world(game);

	// Cria o jogador.
	create_player(game);

	// Fecha o interpretador Lua se estiver aberto.
	if (game->L != NULL) lua_close(game->L);
}

#endif // INIT_H