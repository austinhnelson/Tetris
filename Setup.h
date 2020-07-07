#pragma once

#define CUBE_SIZE_X 30
#define CUBE_SIZE_Y 30

#define INITIAL_PLAYER_X 55
#define INITIAL_PLAYER_Y 55

#define NUM_OF_ROWS 20
#define NUM_OF_COLUMNS 10

#define PLAY_ARENA_X (CUBE_SIZE_X * NUM_OF_COLUMNS)
#define PLAY_ARENA_Y (CUBE_SIZE_Y * NUM_OF_ROWS)

#define WINDOW_X_OFFSET_SIZE 250
#define WINDOW_Y_OFFSET_SIZE 100
#define WINDOW_X (PLAY_ARENA_X + WINDOW_X_OFFSET_SIZE)
#define WINDOW_Y (PLAY_ARENA_Y + WINDOW_Y_OFFSET_SIZE)

#define NUM_OF_LEVELS 10

#define GRID_IMAGE_START_X 50
#define GRID_IMAGE_START_Y 50

#define TEXT_BOX_ALLIGN_X (INITIAL_PLAYER_X + PLAY_ARENA_X + CUBE_SIZE_X)

#define TEXT_SIZE 30
#define TEXT_BOX_COORD_OFFSET_Y 79 //taken from Map.cpp sprite size in the y direction plus character size

enum block {
	I_BLOCK,
	O_BLOCK,
	L_BLOCK,
	J_BLOCK,
	S_BLOCK,
	Z_BLOCK,
	T_BLOCK,
	BLOCK_SIZE
};