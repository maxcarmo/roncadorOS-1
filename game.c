#include "types.h"
#include "defs.h"
#include "game.h"
#include "keyboard.h"
#include "memlayout.h"


//IZSOTLJ
extern uint8 tetrominoes[NUM_OF_TETROMINOS][BLOCKS_PER_TETROMINO] = {
    {
        0,0,1,0,
        0,0,1,0,
        0,0,1,0,
        0,0,1,0
    },
    {
        0,0,1,0,
        0,1,1,0,
        0,1,0,0,
        0,0,0,0
    },
    {
        0,1,0,0,
        0,1,1,0,
        0,0,1,0,
        0,0,0,0
    },
    {
        0,0,0,0,
        0,1,1,0,
        0,1,1,0,
        0,0,0,0
    },
    {
        0,0,1,0,
        0,1,1,0,
        0,0,1,0,
        0,0,0,0
    },
    {
        0,0,0,0,
        0,1,1,0,
        0,0,1,0,
        0,0,1,0
    },
    {
        0,0,0,0,
        0,1,1,0,
        0,1,0,0,
        0,1,0,0
    }

};


/*
*Função que dado uma posição de um bloco do tetromino, retorna a posição deste rotacionado
*@param x: Posição x do bloco 0<=x<4
*@param y: Posição y do bloco 0<=y<4
*@param rotation: Rotação do tetromino 0,1,2,...,2^32 -1
*@returns Posição do bloco rotacionado
*/
uint32 rotate(uint32 x, uint32 y, uint32 rotation){
    /*      0 graus         90 graus        180 graus       270 graus
    *       00 01 02 03     12 08 04 00     15 14 13 12     03 07 11 15
    *       04 05 06 07     13 09 05 01     11 10 09 08     02 06 10 14
    *       08 09 10 11     14 10 06 02     07 06 05 04     01 05 09 13
    *       12 13 14 15     15 11 07 03     03 02 01 00     00 04 08 12
    */ 
    switch (rotation % 4){ //existem 4 rotações disponiveis
        case 0: return TETROMINO_SIZE*y + x;            //  0 graus
        case 1: return 12 + y - (x * TETROMINO_SIZE);   // 90 graus
        case 2: return 15 - (y * TETROMINO_SIZE) - x;   //180 graus
        case 3: return 3 - y + (x*TETROMINO_SIZE);      //270 graus
    }
    return 0;
}


void init_field(){
    for (uint32 i = 0; i < FIELD_HEIGHT*FIELD_WIDTH; i++){
        game_field[i] = EMPTY;
    }
}

/*
* função de colisão que retorna se uma peça se encaixa ou não
* @param p: Peça atual do jogo
* @param walk_x: Peça se move em x? -1 esquerda, 0 nao, 1 direita
* @param walk_y: Peça se move em y? -1 cima, 0 nao, 1 baixo
* @param rot: Peça rotaciona? 0 nao, 1 sim
* @return true ou false para se a peça se encaixa ou não
*/
uint8 piece_fit(piece p, int walk_x, int walk_y, int rot){
    uint32 block_index, field_index;
    int cx,cy;
    for (uint32 x = 0; x < TETROMINO_SIZE; x++){
        for (uint32 y = 0; y < TETROMINO_SIZE; y++){
            cx = p.x + x + walk_x;
            cy = p.y + y + walk_y;

            block_index = rotate(x,y, p.rotation + rot);
            field_index = cy * FIELD_WIDTH + cx;

            if (tetrominoes[p.name][block_index]){ //se ha um bloco de tetris
                // e este bloco está 
                if (cx < 0 || cx >= FIELD_WIDTH) return 0; // fora dos limites no x
                if (cy < 0 || cy >= FIELD_HEIGHT) return 0; // fora dos limites no y
                if (game_field[field_index] != EMPTY) return 0; //ou está em cima de outro bloco
                // então retorno falso

            }

            if (
                tetrominoes[p.name][block_index] && //se ha um bloco de tetris
                game_field[field_index] != EMPTY    //em cima de outro bloco
            ) return 0; //entao retorno falso, pois a peça não se encaixa
            
        }
    }
    return 1;
}

void rotate_piece(piece *p){
    if (piece_fit(*p, 0,0,1)){
        (p->rotation)++;
    }
}

void wait(uint32 ms){
    uint64 time = (*(uint64*) CLINT_MTIME) / 10000;
    uint64 new_time = time;
    while (new_time - time < ms){
        new_time = (*(uint64*) CLINT_MTIME) / 10000;
    }
}

#define REAL_LOOP 750

#define LOOP_TIME_MS 50

#define UPDATE_LOOP (REAL_LOOP/LOOP_TIME_MS)

void game_loop(){
    uint8 game_over = 0;
    piece p, p2, p3;

    p.name = Z;
    p.x = 3;
    p.y = 4;
    p.rotation = 0;


    uint64 t0, t1, t2;
    t0 = 0;
    int i = 0;
    while (!game_over){
        //frame calculation ======================
        t1 = (*(uint64*) CLINT_MTIME) / 10000; // 25
        //wait(400);
        if (t1 - t0 < LOOP_TIME_MS){
            wait(LOOP_TIME_MS-(t1-t0));
            //printf("t1-t0: %h\n", t1-t0);
        }else{
            printf("fodeu\n");
        }
        t0 = (*(uint64*) CLINT_MTIME) / 10000; //15
        //update
        if (!(i%UPDATE_LOOP)){
            rotate_piece(&p);
            if (!(i%(10*UPDATE_LOOP))){
                p.name = (p.name + 1) % 7;
                //keyboard_int();
            }
        }
        //draw
        
        clear();
        draw_field();
        draw_piece(p);
        t2 = (*(uint64*) CLINT_MTIME) / 10000; //15
        //printf("t2-t1: %h\n", t2-t1);
        //transfer(FIELD_START,0,FIELD_WIDTH*BLOCK_SIZE + FIELD_START,DEVICE_HEIGHT);
        transfer(0,0,DEVICE_WIDTH, DEVICE_HEIGHT);
        i++;
    }
}

void init_game(){
    uint8 num_pages = 1 + (FIELD_HEIGHT*FIELD_WIDTH)/PAGE_SIZE;
    game_field = (uint8*) alloc(num_pages);
    init_field();
    game_loop();
}