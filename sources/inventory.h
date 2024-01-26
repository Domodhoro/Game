#ifndef INVENTORY_H
#define INVENTORY_H

static void inventory_reset(Game *game) {
	int i;

	for (i = 0; i != SLOT_MAX; i++) {
		game->inventory.slot[i] = false;
	}
}

void init_inventory(Game *game) {
	inventory_reset(game);

	game->inventory.slot[0] = true;
}

void inventory_update(Game *game) {
    int i;

    for (i = 0; i != NUM_KEYS; i++) {
        if (game->keys.numbers[i]) {
            inventory_reset(game);

            game->inventory.slot[i] = true;
        }
    }
}

#endif