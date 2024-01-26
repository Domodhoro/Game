#ifndef INPUTS_H
#define INPUTS_H

static void handle_key(SDL_KeyboardEvent *event, Keys *keys, const _Bool is_key_pressed) {
	if (event->repeat == 0) {
    	switch (event->keysym.scancode) {
    	case SDL_SCANCODE_W:
    		keys->W = is_key_pressed;
    		break;
    	case SDL_SCANCODE_A:
    		keys->A = is_key_pressed;
    		break;
    	case SDL_SCANCODE_S:
    		keys->S = is_key_pressed;
    		break;
    	case SDL_SCANCODE_D:
    		keys->D = is_key_pressed;
    		break;
        case SDL_SCANCODE_M:
            keys->M = is_key_pressed;
            break;
    	case SDL_SCANCODE_1 ... SDL_SCANCODE_0:
            keys->numbers[event->keysym.scancode - SDL_SCANCODE_1] = is_key_pressed;
            break;
        }
	}
}

static void handle_key_down(SDL_KeyboardEvent *event, Keys *keys) {
    handle_key(event, keys, true);
}

static void handle_key_up(SDL_KeyboardEvent *event, Keys *keys) {
    handle_key(event, keys, false);
}

void init_keys(Game *game) {
	game->keys.W = false;
    game->keys.A = false;
    game->keys.S = false;
    game->keys.D = false;

    int i;

    for (i = 0; i != NUM_KEYS; i++) {
        game->keys.numbers[i] = false;
    }
}

void handle_events(Game *game) {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
        case SDL_QUIT:
            game->running = false;

            break;
        case SDL_KEYDOWN:
            handle_key_down(&event.key, &game->keys);

            break;
        case SDL_KEYUP:
            handle_key_up(&event.key, &game->keys);

            break;
        }
	}
}

#endif