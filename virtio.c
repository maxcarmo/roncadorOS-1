#include "types.h"
#include "defs.h"
#include "virtio.h"
#include "memlayout.h"
#include "console.h"

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
            printf("\t");
            switch(deviceid) {
                // case 1:
                //     printf(LIGHT_SEA_GREEN "Disposivito de rede encontrado\n" CR);
                //     break;
                case 2:
                    // Cada dispositivo começa no início de uma nova página
                    idx = (addr - VIRTIO_START) / 4096; 
                    // virtio_devices[idx] = BLOCK;
                    printf(YELLOW_GREEN 
                           "Dispositivo de bloco (hd) encontrado (IRQ %d)\n" CR, idx+1);
                    // virtio_disk_init(addr);
                    // printf(SPRING_GREEN "Disco configurado com sucesso\n" CR);
                    break;
                // case 4:
                //     printf(LIGHT_SEA_GREEN 
                //         "Dispositivo entropia (Gerador de Número Aleatório) encontrado\n" CR);
                //     break;
                // case 16:
                //     printf(LIGHT_SEA_GREEN "Dispositivo GPU  encontrado\n" CR);
                //     break;
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