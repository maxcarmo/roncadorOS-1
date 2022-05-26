#define VIRTIO_MAGIC 0x74726976 //"triv" em little endian

//Regitradores de controle virtio mapeados em memório
#define VIRTIO_MMIO_DEVICE_ID		0x008 // tipo de dispositivo. Disco = 2