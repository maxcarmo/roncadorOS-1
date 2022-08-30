#include "../types.h"
#include "../defs.h"
#include "virtio.h"
#include "../memlayout.h"
#include "../console.h"
#include "gpu.h"
#include "rng.h"
#include "keyboard.h"



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
	0x108
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



#define CPU_CLOCK   (10000000)
#define TIME_MS     10000





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
        deviceid = read_from_reg(addr, DEVICE_ID);
        
        // Se o dispositov está conectado o deslocamento 0x000 contém o número
        // 0x74_72_69_76
        if (magicvalue != VIRTIO_MAGIC) {
            printf("Dispositivo virtio não encontrado \n");
        }
        else if (deviceid == 0) {
            printf( INDIAN_RED "\tDispositivo não conectado\n" CR);
        }
        else {
            switch(deviceid) {
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
                    break;
                case 0x12:
                    printf(LIGHT_SEA_GREEN "Dispositivo de Entrada encontrado\n" CR);
                    setup_input_device(addr);
                    break;
                default:
                    printf("Dispositivo virtio não identificado foi encontrado\n");
                    break;        
            }
            printf(CR);
        }
    }
}


void handle_virt_int(int id){
    printf(PINK_RED);
    switch(id){
        case 6:
            keyboard_int();
            break;
        case 7:
            printf("GPU\n");
            break;
        default:
            printf("DISPOSITIVO VIRTIO DESCONHECIDO\n");
            break;
    }
    transfer(0,0,DEVICE_WIDTH, DEVICE_HEIGHT);
    printf(CR);
}