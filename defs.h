//UART
void uartputc(int);
int uartgetc();
void uartinit();

//print*
void printlng(long, int);
void printptr(uint64 *);
void printf(char *, ...);

void puts(char *);

int perimetro(int, ...);  
void panic(char *);

// memória
void memory_init();
void kvminit();
void memory_test();
void *alloc(int);
void dealloc(void*);
uint64 *uvmcreate();
int mappages(uint64 *, uint64, uint64, uint64, int);
pte_t *walk(pte_t *, uint64, int);
uint64 pte2pa(pte_t);  

void main();
void get_mstatus_mpie();

// PLIC
uint32 plic_claim(void);
void plic_complete(uint32);
void plic_init(void); 

void console_handler(void);

//processo
uint64 process_init(void);
struct proc *scheduler(void);

//VIRTIO
void virtio_probe();
void wait(uint32 ms);
#define DEVICE_WIDTH 640
#define DEVICE_HEIGHT 800

//GAME
void init_game();
void clear();