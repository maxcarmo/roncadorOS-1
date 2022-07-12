#ifndef GAME_H
#define GAME_H

#define FPS 30
#define FRAME_TIME 1/FPS

#define FIELD_WIDTH 12
#define FIELD_HEIGHT 20
#define FIELD_START ((DEVICE_WIDTH/2) - (FIELD_WIDTH*16))
#define BLOCK_SIZE 32 //32x32 pixels
#define TETROMINO_SIZE 4 //4x4 blocks
#define BLOCKS_PER_TETROMINO 16
#define NUM_OF_TETROMINOS 7

uint8 *game_field;

uint8 tetrominoes[NUM_OF_TETROMINOS][BLOCKS_PER_TETROMINO];
typedef enum pieces{ I, Z, S, O, T, L, J, EMPTY }piece_name;

typedef struct piece {
    uint32 x, y, rotation;
    piece_name name;
} piece;




void draw_tetris_block(uint32 x, uint32 y, piece_name index);
void draw_piece(piece p);
uint32 rotate(uint32 x, uint32 y, uint32 rotation);
void draw_field();

#endif