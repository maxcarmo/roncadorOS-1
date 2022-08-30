#include "../types.h"
#include "../defs.h"
#include "../virtio/keyboard.h"
#include "../virtio/rng.h"
#include "../libs/input-event-codes.h"
#include "../libs/time.h"
#include "game.h"




//define o intervalo de atualizacao em que a peca se move
#define UPDATE_TIME 1000

//cada frame fica FRAME_TIME ms na tela
#define FRAME_TIME 50

//define o loop em que a peca vai ser atualizada
#define UPDATE_LOOP (UPDATE_TIME/FRAME_TIME)

//para pegar a proxima peca disponivel
piece get_next_piece();

//estados que o jogo pode ter
typedef enum states {RUNNING, PAUSED, OVER, MENU} STATE;

//variaveis do jogo
struct GAME{
    uint8 has_switched; //se o jogar mudou de peca, ele nao pode mudar de novo ate a atual se encaixar
    STATE state; //estado do jogo
    uint8 loop_counter; //loop counter 0 - UPDATE LOOP
    uint8 *field; //campo de blocos do jogo
    piece current_piece, next_piece[NEXT_MAX], shadow_piece, hold_piece; //pecas disponiveis no jogo
    uint32 next_idx; //indice da proxima peca a ser escolhida
    uint32 score; //score do jogo
    uint64 dt; //tempo que o ultimo frame levou
}game;






//IZSOTLJ
extern uint8 tetrominoes[NUM_OF_TETROMINOS][BLOCKS_PER_TETROMINO] = {
    {
        0,0,0,0,
        1,1,1,1,
        0,0,0,0,
        0,0,0,0
    },
    {
        1,1,0,0,
        0,1,1,0,
        0,0,0,0,
        0,0,0,0
    },
    {
        0,1,1,0,
        1,1,0,0,
        0,0,0,0,
        0,0,0,0
    },
    {
        0,0,0,0,
        0,1,1,0,
        0,1,1,0,
        0,0,0,0
    },
    {
        0,1,0,0,
        1,1,1,0,
        0,0,0,0,
        0,0,0,0
    },
    {
        0,0,1,0,
        1,1,1,0,
        0,0,0,0,
        0,0,0,0
    },
    {
        1,0,0,0,
        1,1,1,0,
        0,0,0,0,
        0,0,0,0
    }

};


/*
*Função que dado uma posição de um bloco do tetromino, retorna a posição deste rotacionado
*@param x: Posição x do bloco 0<=x<4
*@param y: Posição y do bloco 0<=y<4
*@param rotation: Rotação do tetromino 0,1,2,...,2^32 -1
*@returns Posição do bloco rotacionado
*/
uint32 rotate(uint32 x, uint32 y, uint32 rotation, piece_shape shape){
    /*      0 graus         90 graus        180 graus       270 graus
    *       00 01 02 03     12 08 04 00     15 14 13 12     03 07 11 15
    *       04 05 06 07     13 09 05 01     11 10 09 08     02 06 10 14
    *       08 09 10 11     14 10 06 02     07 06 05 04     01 05 09 13
    *       12 13 14 15     15 11 07 03     03 02 01 00     00 04 08 12
    */
   rotation = rotation % 4; //existem 4 rotações disponiveis
    switch (shape){
        case Z:
        case S:
        case L:
        case J:
        case T:
        //essas pecas so usam um grid 3x3, assim o calculo é diferente para rotacionar
            if (x == 3 || y == 3) return 3; //coluna 3 ou linha 3 eh vazio sempre, entao retorna uma posicao que esta vazia
            switch (rotation){
                case 0: return TETROMINO_SIZE*y + x;            //  0 graus
                case 1: return 8 + y - (x * TETROMINO_SIZE);   // 90 graus
                case 2: return 10 - (y * TETROMINO_SIZE) - x;   //180 graus
                case 3: return 2 - y + (x*TETROMINO_SIZE);      //270 graus
            }
        case I:
        case O:
        //ja essas usam 4x4
            switch (rotation){ 
                case 0: return TETROMINO_SIZE*y + x;            //  0 graus
                case 1: return 12 + y - (x * TETROMINO_SIZE);   // 90 graus
                case 2: return 15 - (y * TETROMINO_SIZE) - x;   //180 graus
                case 3: return 3 - y + (x*TETROMINO_SIZE);      //270 graus
            }
            
    }

    return 0;
}

//deixa todos os blocos do campo como empty
void reset_field(){
    for (uint32 i = 0; i < FIELD_HEIGHT*FIELD_WIDTH; i++){
        game.field[i] = EMPTY;
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

            block_index = rotate(x,y, p.rotation + rot, p.shape);
            field_index = cy * FIELD_WIDTH + cx;

            if (tetrominoes[p.shape][block_index]){ //se ha um bloco de tetris
                // e este bloco está 
                if (cx < 0 || cx >= FIELD_WIDTH) return 0; // fora dos limites no x
                if (cy < -4 || cy >= FIELD_HEIGHT) return 0; // fora dos limites no y
                if (cy >= 0 && game.field[field_index] != EMPTY) return 0; //ou está em cima de outro bloco
                // então retorno falso

            }

            if (
                cy >= 0 &&
                tetrominoes[p.shape][block_index] && //se ha um bloco de tetris
                game.field[field_index] != EMPTY    //em cima de outro bloco
            ) return 0; //entao retorno falso, pois a peça não se encaixa
            
        }
    }
    return 1;
}

//funcao para rotacionar um peca
int rotate_piece(piece *p){
    if (piece_fit(*p, 0,0,1)){
        (p->rotation)++;
        return 1;
    }
    return 0;
}

//funcao para mover uma peca para baixo
int move_piece_down(piece *p){
    if (piece_fit(*p, 0, 1, 0)){
        (p->y)++;
        return 1;
    }
    return 0;
}

/*
* funcao para mover uma peca para esquerda ou direta
* @param *p: ponteiro para a peca
* @param direction: direcao que a peca vai, -1 esquerda, 1 direita
* @return true ou false para se a peca moveu ou nao
*/
int move_piece_left_or_right(piece *p, int direction){
    if (direction != -1 && direction != 1) return 0;
    if (piece_fit(*p, direction, 0, 0)){
        p->x += direction;
        return 1;
    }
    return 0;
}

//realiza um hard drop na peca
//isto é, move a peca para baixo ate onde der
int hard_drop(piece *p){
    int dropped = 0;
    while(move_piece_down(p)) dropped++;
    return dropped;
}


//funcao que marca uma certa peca no campo
//quando a peca eh encaixada ela tem que ser marcada no campo
//essa funcao eh responsavel por isso
void mark_piece_in_field(piece p){
    uint32 piece_offset = p.y * FIELD_WIDTH + p.x;
    uint32 piece_index;
    uint32 field_offset, field_index;
    for (uint8 x = 0; x < TETROMINO_SIZE; x++){
        for (uint8 y = 0; y < TETROMINO_SIZE; y++){
            piece_index = rotate(x, y, p.rotation, p.shape);
            if (tetrominoes[p.shape][piece_index]){ //se há um bloco nessa rotacao
                field_offset = y * FIELD_WIDTH  + x;
                field_index = piece_offset + field_offset;
                game.field[field_index] = p.shape; //marco no field
            }
        }
    }
}


//essa funcao é responsavel por trocar a peca atual do usuario
//por uma peca que esta no hold
//se nenhuma peca estiver no hold
//entao é pego a proxima peca disponivel
//e a peca atual vai para o hold
void switch_hold(){
    if (game.has_switched) return; //se o usuario acabou de trocar
    piece temp = game.current_piece;
    if (game.hold_piece.shape == EMPTY){
        game.current_piece = get_next_piece();
    }else{
        game.current_piece = game.hold_piece;
    }
    game.hold_piece = temp;
    game.hold_piece.x = PIECE_START;
    game.hold_piece.y = 0;
    game.hold_piece.rotation = 0;
    //a peca O é a unica que comeca ocupando a terceira linha
    //como todas as outras comecam ocupando a segunda linha
    //entao soma-se 1 na posicao delas
    if (game.hold_piece.shape != O){
        game.hold_piece.y++;
    }
    game.has_switched = true;
}

//funcao que devolve uma nova peca aleatoria
piece new_piece(){
    piece p;
    p.shape = get_random_number(0, NUM_OF_TETROMINOS);
    p.x = PIECE_START;
    p.y = 0;
    p.rotation = 0;
    if (p.shape != O){
        p.y++;
    }
    return p;
}


piece get_next_piece(){
    piece p = game.next_piece[game.next_idx];
    game.next_piece[game.next_idx] = new_piece();
    game.next_idx = (game.next_idx + 1) % NEXT_MAX;
    return p;
}

void reset_game(){
    //reset all pieces
    game.current_piece = new_piece();
    for (int i = 0; i < NEXT_MAX; i++){
        game.next_piece[i] = new_piece();
    }
    game.hold_piece.shape = EMPTY;

    //reset score
    game.score = 0;

    //reset some other shit
    game.has_switched = false;
    game.loop_counter = 0;

    //change state for running
    game.state = RUNNING;

    //reset field
    reset_field();
}

void treat_keys(){
    virtio_input_event event;
    while(!av_events_queue.empty){
        event = av_events_queue.get_event(&av_events_queue);
        switch (game.state){
            case MENU:
                if (event.code == KEY_ENTER){
                    game.state = RUNNING;
                }
                break;
            case OVER:
                if (event.code == KEY_ENTER || event.code == KEY_R){
                    reset_game();
                }
                break;
            case PAUSED:
                if (event.code == KEY_P){
                    game.state = RUNNING;
                }
                break;
            case RUNNING: 
                switch (event.code){
                    case KEY_SPACE:
                        hard_drop(&game.current_piece);
                        game.loop_counter += UPDATE_LOOP;
                        break;
                    case KEY_LEFT:
                        move_piece_left_or_right(&game.current_piece, -1);
                        break;
                    case KEY_RIGHT:
                        move_piece_left_or_right(&game.current_piece, 1);
                        break;
                    case KEY_DOWN:
                        move_piece_down(&game.current_piece);
                        break;
                    case KEY_UP:
                        rotate_piece(&game.current_piece);
                        break;
                    case KEY_P:
                        game.state = PAUSED;
                        break;
                    case KEY_C:
                        switch_hold();
                        break;
                    case KEY_R:
                        reset_game();
                        break;
                }
                break;
        }
    }
}

//funcao que atualiza se deu game over ou nao
void update_game_over_status(){
    //SE HÁ ALGUM BLOCO NO START_OFFSET
    uint32 range = START_OFFSET*FIELD_WIDTH;
    for (int field_index = 0; field_index < range; field_index++){
        if (game.field[field_index] != EMPTY){
            game.state = OVER;
            return;
        }
    }
}


//Essa funcao eh responsavel por checar se fez pontos ou nao.
//Ela eh chamada toda vez que uma peca eh encaixada no gamefield
// @param piece_height: altura da peca
// @return retorna a quantidade de pontos feito
int check_line(int piece_height){
    int marked_offset, unmarked_offset;
    int lines_marked = 0;   //linhas marcadas como ponto
    int lines_unmarked = 0; //linhas marcadas como nao ponto
    int marked; //usado para saber se a linha do loop anterior foi marcada como ponto
    int field_index; 
    int line_start_check = TETROMINO_SIZE - 1; //de qual linha do tetromino comecara o check
    if (piece_height + TETROMINO_SIZE > FIELD_HEIGHT){ //se o bloco do tetromino passar o field
        line_start_check = FIELD_HEIGHT - piece_height - 1; //entao atualiza para um numero compativel
    }
    //em termos do game field, piece bottom guarda o comeco da ultima linha do tetromino
    int piece_bottom = (piece_height + line_start_check) * FIELD_WIDTH;



    /*  o = pecas
        * = vazio
        x = peca atual
    0|*******|
    1|*******|
    2|*******|
    3|*oo*o**|
    4|x**oo*o|
    5|xoooooo|
    6|x*ooooo|
    7|xoooooo|
    */
    //no exemplo acima, as linhas que marcam pontos sao a 7 e 5
    //e as que nao marcam sao as 6 e 4
    //apos a funcao ser executada, o field ficara assim
    /*
    0|*******|              0|*******|
    1|*******|              1|*******|
    2|*******|              2|*******|
    3|*oo*o**|      ==>     3|*******|
    4|x**oo*o|              4|*******|
                            5|*oo*o**|
    6|x*ooooo|              6|x**oo*o|
                            7|x*ooooo|
    */


    //faco um for de baixo para cima
    //no exemplo seria do 7 -> 4, ou melhor de 3 a 0
    for (int line = line_start_check; line >= 0; line--){
        field_index = (piece_height + line) * FIELD_WIDTH; //comeco da linha
        marked = 1;
        //utilizo esse for interno para ver se a linha esta
        //preenchida com blocos de tetrominoes
        for (int col = 0; col < FIELD_WIDTH; col++){
            if (game.field[field_index+col] == EMPTY){
                marked = 0; //se tem algum bloco vazio, entao a linha nao faz um ponto
                break;
            }
        }
        //aqui para baixo que aconte uma parte da magia
        //para mover as pecas de cima para baixo sem percorrer o game field mais de 1 vez

        //se encontrou uma linha nao marcada
        if (!marked){
            // e se encontrou linhas marcadas anteriormente
            if (lines_marked > 0){
                //entao quer dizer que eu tenho que mover a linha nao marcada
                //para baixo
                //quem vai me dizer quantas linhas para baixo
                //vai ser um pequeno calculo
                //as linhas nao marcadas vai dar o offset qual linha vai receber os blocos
                //as linhas marcadas + linhas nao marcadas vai dar o offset de qual linha vai dar os blocos
                /*


                1 instancia, linhas marcadas = 1, linhas nao marcadas = 0
                o contador de linhas nao marcadas so eh incrementado depois desse if

                0|*******|      0|*******|
                1|*******|      1|*******|
                2|*******|      2|*******|
                3|*oo*o**| ==>  3|*oo*o**| 
                4|x**oo*o|      4|x**oo*o|
                5|xoooooo|      5|xoooooo|
linha atual ->  6|x*ooooo|      6|x*ooooo| <- este doa
                7|xoooooo|      7|x*ooooo| <- este recebe

---------------------------------------------------------------------------------------------------------
                2 instacia, linhas marcadas = 2, linhas nao marcadas = 1

                0|*******|      0|*******|
                1|*******|      1|*******|
                2|*******|      2|*******|
                3|*oo*o**| ==>  3|*oo*o**| 
linha atual ->  4|x**oo*o|      4|x**oo*o| <- este doa
                5|xoooooo|      5|xoooooo|
                6|x*ooooo|      6|x**oo*o| <- este recebe
                7|x*ooooo|      7|x*ooooo| 
                */
                for (int col = 0; col < FIELD_WIDTH; col++){
                    unmarked_offset = lines_unmarked * FIELD_WIDTH;
                    marked_offset = lines_marked * FIELD_WIDTH;
                    game.field[(piece_bottom - unmarked_offset)+col] = game.field[(piece_bottom - (unmarked_offset + marked_offset)) + col];
                }
            }
            lines_unmarked++;
        }else{
            lines_marked++;
        }
    }
    //depois de percorrer as linhas do tetromino encaixado
    //temos que reposicionar os blocos acima se houve algum ponto
    //entao para continuar de onde parou, utilizamos a variavel
    //que guarda o valor das linhas nao marcadas como ponto
    if (lines_marked > 0){

        //seguindo o exemplo
        //linhas nao marcadas = 2
        //linhas marcadas = 2
        //piece height = 4
        //line start check = 3
        //4+3-2 = 5
        //entao nesse loop vou de 5 ate 2
        //pegando os blocos exatamente 2 linhas acima
        for (int line = (piece_height + line_start_check - lines_unmarked); line >= lines_marked; line--){
            for (int col = 0; col < FIELD_WIDTH; col++){
                game.field[line*FIELD_WIDTH + col] = game.field[(line-lines_marked)*FIELD_WIDTH + col];
            }
        }
        //e nesse loop eu vou nas linhas de 0 a 1 e preencho com vazio
        for (int line = 0; line < lines_marked; line++){
            for (int col = 0; col < FIELD_WIDTH; col++){
                game.field[line*FIELD_WIDTH + col] = EMPTY;
            }
        }
    }
    //dou return no score
    switch (lines_marked){
        case 0:
            return 0;
        case 1:
            return 2;
        case 2:
            return 5;
        case 3:
            return 15;
        case 4:
            return 60;
    }
}

//funcao para sincronizar o frame
void frame_sync(){
    static uint64 t0 = 0;
    static uint64 t1 = 0;

    t1 = (*(uint64*) CLINT_MTIME) / 10000;

    game.dt = t1 - t0;
    if (game.dt < FRAME_TIME){
        wait(FRAME_TIME - game.dt);
        game.dt = FRAME_TIME;
    }
    t0 = t1;
}

//funcao que atualiza o jogo
void update(){
    if (game.state != RUNNING) return;
    uint8 piece_moved;
    //update ==================================
    if (game.loop_counter >= UPDATE_LOOP){
        piece_moved = move_piece_down(&game.current_piece);
        if (!piece_moved){
            mark_piece_in_field(game.current_piece);
            game.score += check_line(game.current_piece.y);
            game.current_piece = get_next_piece();
            update_game_over_status();
            game.has_switched = false;
        }
        game.loop_counter = 0xff;
    }
    game.shadow_piece = game.current_piece;
    while(move_piece_down(&game.shadow_piece));
    game.loop_counter++;
}


//funcao responsavel por desenhar o jogo
void draw(){
    //draw =======================================
    if (game.state == MENU){
        clear();
        uint32 commands_title_size = 5;
        uint32 commands_size = 3;
        uint32 diff = (commands_size + 1)*10;
        uint32 commands_start = 220;
        draw_string("TETRIS", DEVICE_WIDTH/2, 90, 10, 0xFFEB3E1B, true);
        draw_string("Commands", 20, 200, commands_title_size, 0xffff9040, false);
        draw_string("ARROW UP:    rotate", 20, commands_start + diff*1, commands_size, 0xffff0000, false);
        draw_string("ARROW DOWN:  move down", 20, commands_start+diff*2, commands_size, 0xffff0000, false);
        draw_string("ARROW LEFT:  move left", 20, commands_start+diff*3, commands_size, 0xffff0000, false);
        draw_string("ARROW RIGHT: move right", 20, commands_start+diff*4, commands_size, 0xffff0000, false);
        draw_string("C:           hold", 20, commands_start+diff*5, commands_size, 0xffff0000, false);
        draw_string("R:           reset", 20, commands_start+diff*6, commands_size, 0xffff0000, false);
        draw_string("P:           pause", 20, commands_start+diff*7, commands_size, 0xffff0000, false);
        draw_string("SPACE:       hard drop", 20, commands_start+diff*8, commands_size, 0xffff0000, false);
        draw_string("PRESSIONE ENTER PARA COMECAR", DEVICE_WIDTH/2, DEVICE_HEIGHT/2 + DEVICE_HEIGHT/4, 4, 0xff00ff00, true);
    }else{
        clear();
        draw_field(game.field);
        draw_score(game.score);
        draw_next(game.next_piece, game.next_idx);
        draw_hold(game.hold_piece, game.has_switched);
        if (game.state == RUNNING){
            draw_piece(game.shadow_piece, true);
            draw_piece(game.current_piece, false);
        }else{
            if (game.state == OVER){
                draw_string("GAME OVER", DEVICE_WIDTH/2, DEVICE_HEIGHT/2, 10, 0xffff0000, true);
            }else if (game.state == PAUSED){
                draw_string("PAUSED", DEVICE_WIDTH/2, DEVICE_HEIGHT/2, 8, 0xFFEB3E1B, true);
            }
        }
    }
    transfer(0,0,DEVICE_WIDTH, DEVICE_HEIGHT);
}


void game_loop(){
    while (true){
        frame_sync();
        treat_keys();
        update();
        draw();
    }
}


//funcao responsavel por inicializar as variaveis do jogo
void init_game(){
    uint8 num_pages = 1 + (FIELD_HEIGHT*FIELD_WIDTH)/PAGE_SIZE;

    game.state = MENU;
    game.has_switched = false;
    game.loop_counter = 0;
    game.current_piece = new_piece();
    for (int i = 0; i < NEXT_MAX; i++){
        game.next_piece[i] = new_piece();
    }
    game.hold_piece.shape = EMPTY;
    game.next_idx = 0;
    game.score = 0;
    game.field = (uint8*) alloc(num_pages);
    game.dt = 0;
    reset_field();
    game_loop();
}