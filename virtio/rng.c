#include "rng.h"
#include "virtio.h"
#include "../defs.h"


rng_device RNG_DEVICE;

uint32 get_random_number(uint32 start, uint32 end){
    uint32 random_number;
    uint32 *buffer = (uint32*) alloc(1);
    VirtQDescriptor desc;

    //seta o endereco do buffer para o dispositivo enxergar
    set_descriptor(&desc, (uint64)buffer, sizeof(uint32), VIRTQ_DESC_F_WRITE, 0);

    //atualiza os indices da virtq
    uint32 head = RNG_DEVICE.idx;
    RNG_DEVICE.queue->desc[RNG_DEVICE.idx] = desc;
    RNG_DEVICE.idx = (RNG_DEVICE.idx +1) % QNUM;
    RNG_DEVICE.queue->av.ring[RNG_DEVICE.queue->av.index % QNUM] = head;
    RNG_DEVICE.queue->av.index = RNG_DEVICE.queue->av.index +1;

    //informa para o dispositivo que tem buffer na fila
    write_to_reg(RNG_DEVICE.address, QUEUE_NOTIFY, 0);

    //espera o dispositivo respondar em um while
    //talvez pode ser alterado por uma interrupção
    while (RNG_DEVICE.queue->av.index != RNG_DEVICE.queue->used.index);
    //recupero o que foi escrito no buffer
    random_number = *buffer;
    //desaloca buffer
    dealloc(buffer);
    //retorno um numero aleatorio dentro do range
    return (random_number % (end - start)) + start;
}

void setup_rng(uint64 addr){
    //reset the device
    write_to_reg(addr, STATUS, STATUS_RESET);
    //set ack status bit
    set_bit(addr, STATUS, STATUS_ACKNOWLEDGE); //ack
    //set driver status bit
    set_bit(addr, STATUS, STATUS_DRIVER);
    //read feat bits and write it on the device
    uint32 device_feat = read_from_reg(addr, HOST_FEATURES);
    write_to_reg(addr, GUEST_FEATURES, device_feat);
    //setup virtq - populate virtq - read conf - write confg
    uint32 num_pages = 1 + sizeof(VirtQ)/PAGE_SIZE;
    VirtQ *Q = (VirtQ*) alloc(num_pages);
    uint32 q_pfn = ((uint64)Q)/PAGE_SIZE; //physical page number
    write_to_reg(addr, QUEUE_SEL, 0); //select the queue number 0
    write_to_reg(addr, QUEUE_NUM, QNUM); //writing the ring size of the queue
    write_to_reg(addr, GUEST_PAGE_SIZE, PAGE_SIZE); //writing the page size so the device can calculate the physical address
    write_to_reg(addr, QUEUE_PFN,  q_pfn); //write the physical page number
    //set DRIVER_OK statsu bit
    set_bit(addr, STATUS, STATUS_DRIVER_OK);
    //now, our device is alive

    RNG_DEVICE.address = addr;
    RNG_DEVICE.idx = 0;
    RNG_DEVICE.queue = Q;
}