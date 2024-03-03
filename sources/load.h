#ifndef LOAD_H
#define LOAD_H

void load(Game *game) {
	game->player.texture = get_texture(game->renderer, "./textures/player.png");
	game->world.block_texture = get_texture(game->renderer, "./textures/blocks.png");
	game->inventory.texture = get_texture(game->renderer, "./textures/inventory_back.png");
	game->map.frame_texture = get_texture(game->renderer, "./textures/map_frame.png");
	game->background.texture = get_texture(game->renderer, "./textures/background.png");
}

#endif