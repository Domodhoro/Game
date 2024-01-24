#ifndef ENUMS_H
#define ENUMS_H

// Enum para representar os tipos de blocos.
typedef enum BLOCK_TYPE {
	AIR = 0,
	DIRT
}
BLOCK_TYPE;

// Enum para representar as direções do jogador.
typedef enum DIRECTION {
	NONE = 0,
	UP,
	LEFT,
	DOWN,
	RIGHT
}
DIRECTION;

#endif // ENUMS_H