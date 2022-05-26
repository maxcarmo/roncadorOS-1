#include "types.h"
#include "proc.h"
#include "defs.h"
#include "string.h"
#include "memlayout.h"
#include "param.h"
#include "riscv.h"
#include "programs.h"

// Na última pág. da memória virtual temos a pliha do processo no espaço do usuário
#define PROC_USTACK_VA (MAXVA - PAGE_SIZE)
extern void msg_syscall(int); // para mapear a página da syscal p/ o processo

int nextpid = 1;

struct proc proc[NPROC];

int 
allocpid() {
    int pid;
    //!!! Exemplo de condição de corrida
    pid = nextpid;
    nextpid = nextpid + 1;
    return pid;
}

struct proc * 
allocproc(void) {
    struct proc *p;
    // Condição de corrida: Se o thread é interrompido e um 
    // segundo tenta alocar outro processo teremos problemas,
    // mesmo com uma única CPU
 
    for( p = proc; p < &proc[NPROC]; p++) {
        if (p->state == UNUSED) {
            // O escalonador está à caça de um processo com state == RUNNING
            p->state = RUNNING; 
            return p;
        }
    }
    return 0;
}

void deallocproc(struct proc *p) {
    p->state = UNUSED;
    // Desaloca memória da pilha
    // ...
}

// Inicializa a estrutura do processo e retorna o endereço da primeira 
// instrução. Para o código do processo (mas não para as pilhas) fazemos 
// mapeamento de identidade (VA = AP)
uint64 
process_init() {
    // uint64 proc_start_addr = (uint64) code1;
    struct proc *p;
    
    // return 0;
    p = allocproc();
    if (p == 0) {
        printf("Lista de processos não comporta novo processo\n");
        return 0;
    }
    p->pid = allocpid();
    p->pagetable = uvmcreate();
    p->tf.satp = MAKE_SATP(p->pagetable);

    p->stack = alloc(1); // Pilha no espaço do usuário: 4096 bytes
    if (p->stack == 0) {
        printf("Não há memória disponível para novo processo\n");
        return 0;
    }
    memset(p->stack, 0 , PAGE_SIZE);
    p->tf.regs[1] = PROC_USTACK_VA + PAGE_SIZE; // tf.sp

    //Aloca pilha do processo no kernel
    if((p->tf.trap_stack = alloc(1)) == 0){
        printf("Não há memória disponível para novo processo\n");
        deallocproc(p);
        return 0;
    }
    // p->tf.epc = proc_start_addr;
    p->tf.epc = (uint64) code1;
    printf("<CRIAÇÃO de PROCESSO>:\n");
    printf("\t tp.epc:%p\n", p->tf.epc);
    //mapeia a pilha do usuário para PROC_USTACK_VA. Permite acesso do modo-U
    if (mappages(p->pagetable, PROC_USTACK_VA, 
             PAGE_SIZE, (uint64) p->stack, PTE_R | PTE_W | PTE_U) != 0) {
                 printf("Erro ao mapear memória do processo");
                 deallocproc(p);
                 return 0;
             }
    
    // Mapeia  código do processo. Assumimos aqui que o código não ocupa mais
    // que 1 página.
    if (mappages(p->pagetable, (uint64) code1, 
             PAGE_SIZE, (uint64) code1, PTE_R | PTE_X |PTE_U) != 0) {
                 printf("Erro ao mapear memória do processo");
                 deallocproc(p);
                 return 0;
             } 
    // É preciso mapear também a página que contém a syscall         
    if (mappages(p->pagetable, (uint64) msg_syscall, 
             PAGE_SIZE, (uint64) msg_syscall, PTE_R | PTE_X |PTE_U) != 0) {
                 printf("Erro ao mapear memória do processo");
                 deallocproc(p);
                 return 0;
             }          

    // Testes
    pte_t *pte;
    pte = (uint64*) walk(p->pagetable, PROC_USTACK_VA, 0);
    printf("\t USER_STACK (processo) - VA: \t%p PA:%p\n", 
           PROC_USTACK_VA, (uint64*)pte2pa(*pte));      
    printf("\t KERNEL_STACK (processo) - PA:\t%p\n", 
            p->tf.trap_stack);       
    pte = (uint64*) walk(p->pagetable, p->tf.epc, 0);
    printf("\t End. de início do processo(VA): \t%p PA(PN):%p\n", 
           p->tf.epc, (uint64*)pte2pa(*pte));
    pte = (uint64*) walk(p->pagetable, (uint64) msg_syscall, 0); //um 
    printf("\t PN de msg_syscall:%p\n", pte2pa(*pte));

    printf("\t pagetable:%p\n", p->pagetable);
    printf("\t satp:%p\n", p->tf.satp);
    printf("\t Endereço (VA) da syscall 'msg_syscall':%p\n", msg_syscall);
    
    return p->tf.epc;
}

struct proc* scheduler(void) {
    struct proc *p;
    int found = 0;

    for(p = proc; p < &proc[NPROC]; p++) {
        if(p->state == RUNNING) {
            found = 1;
            break;
        }
    }
    if(found) {
        printf("Processo com PID#%d escalonado\n", p->pid);
        return p; 
    }
    return 0;
}
