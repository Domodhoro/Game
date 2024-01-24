#ifndef INPUTS_H
#define INPUTS_H

// Trata o evento de pressionamento de tecla.
void handle_key_down(SDL_KeyboardEvent *event, Keys *keys) {
	// Verifica se a tecla não está sendo repetida e atualiza o estado da tecla correspondente.
    if (event->repeat == 0) {
		if (event->keysym.scancode == SDL_SCANCODE_W) keys->W = true;
		if (event->keysym.scancode == SDL_SCANCODE_A) keys->A = true;
		if (event->keysym.scancode == SDL_SCANCODE_S) keys->S = true;
		if (event->keysym.scancode == SDL_SCANCODE_D) keys->D = true;
	}
}

// Trata o evento de soltura de tecla.
void handle_key_up(SDL_KeyboardEvent *event, Keys *keys) {
	// Verifica se a tecla não está sendo repetida e atualiza o estado da tecla correspondente.
    if (event->repeat == 0) {
		if (event->keysym.scancode == SDL_SCANCODE_W) keys->W = false;
		if (event->keysym.scancode == SDL_SCANCODE_A) keys->A = false;
		if (event->keysym.scancode == SDL_SCANCODE_S) keys->S = false;
		if (event->keysym.scancode == SDL_SCANCODE_D) keys->D = false;
	}
}

// Trata eventos gerais, como fechamento de janela e eventos de teclado.
void handle_events(Game *game) {
	SDL_Event event;

	// Processa todos os eventos na fila.
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			// Encerramento da janela.
	        case SDL_QUIT:
	            game->running = false;

	            break;
	        // Tecla pressionada.
	        case SDL_KEYDOWN:
	            handle_key_down(&event.key, &game->keys);

	            break;
	        // Tecla solta.
	        case SDL_KEYUP:
	            handle_key_up(&event.key, &game->keys);

	            break;
        }
	}
}

#endif // INPUTS_H