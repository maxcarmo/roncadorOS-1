#include "types.h"

struct trap_frame {
    uint64 regs[32];
    // /*  40 */ uint64 ra;
    // /*  48 */ uint64 sp;
    // /*  56 */ uint64 gp;
    // /*  64 */ uint64 tp;
    // /*  72 */ uint64 t0;
    // /*  80 */ uint64 t1;
    // /*  88 */ uint64 t2;
    // /*  96 */ uint64 s0;
    // /* 104 */ uint64 s1;
    // /* 112 */ uint64 a0;
    // /* 120 */ uint64 a1;
    // /* 128 */ uint64 a2;
    // /* 136 */ uint64 a3;
    // /* 144 */ uint64 a4;
    // /* 152 */ uint64 a5;
    // /* 160 */ uint64 a6;
    // /* 168 */ uint64 a7;
    // /* 176 */ uint64 s2;
    // /* 184 */ uint64 s3;
    // /* 192 */ uint64 s4;
    // /* 200 */ uint64 s5;
    // /* 208 */ uint64 s6;
    // /* 216 */ uint64 s7;
    // /* 224 */ uint64 s8;
    // /* 232 */ uint64 s9;
    // /* 240 */ uint64 s10;
    // /* 248 */ uint64 s11;
    // /* 256 */ uint64 t3;
    // /* 264 */ uint64 t4;
    // /* 272 */ uint64 t5;
    // /* 280 */ uint64 t6; // 31 registradores
    // uint64 fregs[32];
    uint64 satp;
    // trap_stack aponta para a pilha usada pelo kernel para tratar o trap.  
    uint8 * trap_stack;
    uint64 hartid;
    uint64 epc;
};

typedef struct trap_frame TrapFrame;

// Definimos 4 constantes com valores 0, 1, 2 e 3 respectivamete. 
enum procstate {UNUSED, SLEEPING, RUNNING, WAITING};

struct proc {
    int pid;
    enum procstate state;
    // A pilha que o processo utiliza no espaço do usuário. 
    // O valor de stack vai ser guardado no TrapFrame.sp
    // A variável em si é acessada só na criação e destruição do processo 
    // (serve para o SO liberar a pilha alocada quando o processo for destruído). 
    // Após um trap, na restauração do contexto do processo, o endereço da pilha 
    // do processo é obtido do registrador de TrapFrame (regs[1])     
    uint8 * stack;
    TrapFrame tf;
	uint64 * pagetable;
    char name[32];
 };

uint64 get_pc(struct proc *p);

uint64 get_satp(struct proc *p);

TrapFrame * get_tf(struct proc *p);

struct proc * scheduler(void);