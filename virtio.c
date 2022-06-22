#include "types.h"
#include "defs.h"
#include "virtio.h"
#include "memlayout.h"
#include "console.h"
#include "gpu.h"



void set_descriptor(VirtQDescriptor *desc, uint64 address, uint32 length, uint16 flags, uint16 next){
    desc->address = address;
    desc->length = length;
    desc->flags = flags;
    desc->next = next;
}


void set_bit(uint64 base, MMIOReg reg, uint32 mask){
    uint32 number = *(uint32*)(base + reg);
    number |= mask;
    *(uint32*)(base + reg) = number;
}

void write_to_reg(uint64 base, MMIOReg reg, uint32 value){
    *(uint32*)(base + reg) = value;
}

uint32 read_from_reg(uint64 base, MMIOReg reg){
    uint32 val = *(uint32*)(base + reg);
    return val;
}


int str_len(char *string){
    int count = 0;
    while(*string){
        count++;
        string++;
    }
    return count;
}



char strs[][50] = {
	"magic",
	"version",
	"device id",
	"vendor id",
	"device features",
	"QNumMax",
	"QPFN",
	"intStatus",
	"status",
	"config"
};

uint32 vector[] = {
	0x000,
	0x004,
	0x008,
	0x00c,
	0x010,
	0x034,
	0x040,
	0x060,
	0x070,
	0x100
};
void read_regs(uint32 *ptr){
    int num_of_regs = 0xa;
    int palavra_grande = 9;
    uint32 number;
    for (int i = 0; i < 0xa; i++){
        number = *(uint32*)(((uint64)ptr) + vector[i]);
        printf(PINK_RED "%x\t%s", vector[i], strs[i]);
        printf("\t\t");
        if (str_len(strs[i]) < palavra_grande) printf("\t");
        if (number) printf("%p\n" CR, number);
        else        printf("0x0\n" CR);
    }   
    printf("----------------------------------------------\n");
}

void setup_rng(uint64 addr){
    uint32 *ptr = (uint32*) addr;
    //reset the device
    write_to_reg(addr, STATUS, 0x0);
    //set ack status bit
    set_bit(addr, STATUS, 0X01); //ack
    //set driver status bit
    set_bit(addr, STATUS, 0x02);
    //read feat bits and write it on the device
    uint32 dev_feat = read_from_reg(addr, HOST_FEATURES);
    write_to_reg(addr, GUEST_FEATURES, dev_feat);
    //setup virtq - populate virtq - read conf - write confg
    VirtQ *Q = (VirtQ*) alloc(10);
    printf("Q: %p\n", Q);
    uint32 q_pfn = ((uint64)Q)/PAGE_SIZE;
    printf("qpfn: %d\n", q_pfn);
    write_to_reg(addr, QUEUE_SEL, 0);
    write_to_reg(addr, QUEUE_NUM, QNUM);
    write_to_reg(addr, GUEST_PAGE_SIZE, PAGE_SIZE);
    write_to_reg(addr, QUEUE_PFN,  q_pfn);
    //set DRIVER_OK statsu bit
    set_bit(addr, STATUS, 0x04);
    char *buffer = (char*) alloc(1);
    buffer[0] = 'o';
    buffer[1] = 'i';
    VirtQDescriptor desc;
    set_descriptor(&desc, (uint64)buffer, 32, VIRTQ_DESC_F_WRITE, 0);

    Q->desc[0] = desc;
    Q->av.ring[Q->av.index] = 0;
    Q->av.index = (Q->av.index + 1) % QNUM;


    write_to_reg(addr, QUEUE_NOTIFY, 0);
    printf("%s\n", buffer);
    read_regs(ptr);
    while(*buffer == 'o');
    printf("%s\n", buffer);
}





void virtio_probe() {
    uint64 addr;
    uint32 *ptr;
    uint32 magicvalue;
    uint32 deviceid;
    int idx; // idx + 1 = IRQ
    for(addr = VIRTIO_START; addr <= VIRTIO_END; addr += VIRTIO_STRIDE) {
        printf("Sondando endereço VIRTIO %p ...\n", (uint64*) addr);
        ptr = (uint32*)addr; 
        magicvalue = *ptr;
        // No deslocamento 8 temos o ID do disposito 
        //!!! definir e usar uma macro
        deviceid = *(uint32*)(addr + VIRTIO_MMIO_DEVICE_ID);
        
        // Se o dispositov está conectado o deslocamento 0x000 contém o número
        // 0x74_72_69_76
        if (magicvalue != VIRTIO_MAGIC) {
            printf("Dispositivo virtio não encontrado \n");
        }
        else if (deviceid == 0) {
            printf( INDIAN_RED "\tDispositivo não conectado\n" CR);
        }
        else {
            //read_regs(ptr);
            switch(deviceid) {
                // case 1:
                //     printf(LIGHT_SEA_GREEN "Disposivito de rede encontrado\n" CR);
                //     break;
                case 0x02:
                    // Cada dispositivo começa no início de uma nova página
                    idx = (addr - VIRTIO_START) / 4096; 
                    // virtio_devices[idx] = BLOCK;
                    printf(YELLOW_GREEN 
                           "Dispositivo de bloco (hd) encontrado (IRQ %d)\n" CR, idx+1);
                    // virtio_disk_init(addr);
                    // printf(SPRING_GREEN "Disco configurado com sucesso\n" CR);
             
                    break;
                case 0x04:
                    printf(
                        LIGHT_SEA_GREEN 
                        "Dispositivo entropia (Gerador de Número Aleatório) encontrado\n" 
                        CR
                    );
                    setup_rng(addr);
                    break;
                case 0x10:
                    printf(LIGHT_SEA_GREEN "Dispositivo GPU  encontrado\n" CR);
                    gpu_device* d = setup_gpu_device(addr);
                    init_gpu_device(d);
                    write_to_reg(addr, INTERRUPT_ACK, 1);
                    transfer(d, 0,0,DEVICE_WIDTH, DEVICE_HEIGHT);
                    read_regs(ptr);
                    break;
                //     //teclado?
                // case 18:
                //     printf(LIGHT_SEA_GREEN "Dispositivo de entrada encontrado\n" CR);
                //     break;            
                default:
                    printf("Dispositivo virtio não identificado foi encontrado\n");
                    break;        
            }
            printf(CR);
        }
    }
}