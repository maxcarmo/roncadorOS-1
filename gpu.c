#include "types.h"
#include "defs.h"
#include "gpu.h"
#include "virtio.h"


void print_hdr(gpu_ctrl_hdr *hdr){
	printf("type: %d\n", hdr->type);
	printf("flags: %d\n", hdr->flags);
	printf("fence: %d\n", hdr->fence_id);
	printf("ctx_id: %d\n", hdr->ctx_id);
	printf("padding: %d\n", hdr->padding);
	printf("************************************************\n");
}

void set_resource_flush(resource_flush *flush, gpu_ctrl_hdr hdr, gpu_rect rect, uint32 res_id, uint32 padding){
	flush->hdr = hdr;
	flush->r = rect;
	flush->resource_id = res_id;
	flush->padding = padding;
}

void set_transfer_to_host(transfer_to_host_2d *t, gpu_ctrl_hdr hdr, gpu_rect rect, uint64 offset, uint32 res_id, uint32 padding){
	t->hdr = hdr;
	t->r = rect;
	t->offset = offset;
	t->resource_id = res_id;
	t->padding = padding;
}

void set_setscanout(set_scanout *scanout, gpu_ctrl_hdr hdr, gpu_rect rect, uint32 scanout_id, uint32 res_id){
	scanout->hdr = hdr;
	scanout->r = rect;
	scanout->scanout_id = scanout_id;
	scanout->resource_id = res_id;
}

void set_mem_entry(mem_entry *mem, uint64 addr, uint32 length, uint32 padding){
	mem->addr = addr;
	mem->length = length;
	mem->padding = padding;
}

void set_header(gpu_ctrl_hdr *hdr, gpu_ctrl_type type, uint32 flags, uint64 fence_id, uint32 ctx_id, uint32 pad){
	hdr->type = type;
	hdr->flags = flags;
	hdr->fence_id = fence_id;
	hdr->ctx_id = ctx_id;
	hdr->padding = pad;
}

void set_res_create_2d(resource_create_2d *res, gpu_ctrl_hdr hdr, uint32 res_id, uint32 format, uint32 width, uint32 height){
	res->hdr = hdr;
	res->resource_id = res_id;
	res->formats = format;
	res->width = width;
	res->height = height;
}

void set_attach_backing(attach_backing *at, gpu_ctrl_hdr hdr, uint32 res_id, uint32 n_entries){
	at->hdr = hdr;
	at->resource_id = res_id;
	at->nr_entries = n_entries;
}

void set_color(pixel *p, uint8 r, uint8 g, uint8 b, uint8 a){
	p->r = r;
	p->g = g;
	p->b = b;
	p->a = a;
}

void set_rect(gpu_rect *rect, uint32 x, uint32 y, uint32 w, uint32 h){
	rect->x = x;
	rect->y = y;
	rect->height = h;
	rect->width = w;
}

void fill_rect(gpu_device *dev, gpu_rect rect, pixel color){
	uint32 byte;
	for (uint32 row = rect.y; row < rect.y + rect.height; row++){
		for (uint32 col = rect.x; col < rect.x + rect.width; col++){
			byte = row * dev->width + col;
			dev->framebuffer[byte] = color;
		}
	}
}

void stroke_rect(gpu_device *dev, gpu_rect rect, pixel color, uint32 size){
	gpu_rect new_rect;

	//top
	set_rect(&new_rect, rect.x, rect.y, rect.width, size);
	fill_rect(dev,new_rect,color);

	//bot
	set_rect(&new_rect, rect.x, rect.y+rect.height, rect.width, size);
	fill_rect(dev, new_rect, color);

	//left
	set_rect(&new_rect, rect.x, rect.y, size, rect.height);
	fill_rect(dev, new_rect, color);

	//right
	set_rect(&new_rect, rect.x+rect.width, rect.y, size, rect.height+size);
	fill_rect(dev, new_rect, color);
}

/*
*	funcao que inicializa o dispositivo
*	@param dev: ponteiro para o dispositivo
*/

void init_gpu_device(gpu_device *device){
	pixel black_graysh;
	gpu_rect rect;
	set_rect(&rect, 0, 0, DEVICE_WIDTH, DEVICE_HEIGHT);
	set_color(&black_graysh, 2,2,2,255);
	fill_rect(device, rect, black_graysh);

	gpu_ctrl_hdr hdr;
	set_header(&hdr, VIRTIO_GPU_CMD_RESOURCE_CREATE_2D, 0, 0, 0, 0);
	resource_create_2d *res = (resource_create_2d*) alloc(1);
	set_res_create_2d(
		res,
		hdr,
		1,
		VIRTIO_GPU_FORMAT_R8G8B8A8_UNORM,
		device->width,
		device->height
	);
	VirtQDescriptor c2d, c2d_response;
	set_descriptor(
		&c2d,
		(uint64)res,
		sizeof(resource_create_2d),
		VIRTQ_DESC_F_NEXT,
		(device->idx + 1) % QNUM
	);
	gpu_ctrl_hdr *response1 = (gpu_ctrl_hdr*) alloc(1);
	set_descriptor(
		&c2d_response,
		(uint64)response1,
		sizeof(gpu_ctrl_hdr),
		VIRTQ_DESC_F_WRITE,
		0
	);
	//device->idx++;
	//device->queue->av.index;
	uint16 head = device->idx;
	device->queue->desc[device->idx] = c2d;
	device->idx = (device->idx + 1) % QNUM;
	device->queue->desc[device->idx] = c2d_response;
	device->idx = (device->idx + 1) % QNUM;
	device->queue->av.ring[device->queue->av.index % QNUM] = head;
	device->queue->av.index = (device->queue->av.index + 1) % QNUM; //wrapping_add(1) ???

	//--------------------------------------------------------------//
	//passo 2
	//attach backing

	attach_backing *attach  = (attach_backing*) alloc(1);
	mem_entry *memory_entry = (mem_entry*) alloc(1);
	set_header(
		&hdr,
		VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING,
		0,
		0,
		0,
		0
	);
	set_attach_backing(attach, hdr, 1, 1);
	set_mem_entry(
		memory_entry,
		(uint64)device->framebuffer,
		device->height * device->width * sizeof(pixel),
		0
	);
	VirtQDescriptor desc_ab, desc_ab_mem, desc_ab_resp;
	set_descriptor(
		&desc_ab,
		(uint64)attach,
		sizeof(attach_backing),
		VIRTQ_DESC_F_NEXT,
		(device->idx + 1) % QNUM
	);
	set_descriptor(
		&desc_ab_mem,
		(uint64)memory_entry,
		sizeof(mem_entry),
		VIRTQ_DESC_F_NEXT,
		(device->idx + 2) % QNUM
	);
	gpu_ctrl_hdr *response2 = (gpu_ctrl_hdr*)alloc(1);
	set_descriptor(
		&desc_ab_resp,
		(uint64)response2,
		sizeof(gpu_ctrl_hdr),
		VIRTQ_DESC_F_WRITE,
		0
	);
	head = device->idx;
	device->queue->desc[device->idx] = desc_ab;
	device->idx = (device->idx + 1) % QNUM;
	device->queue->desc[device->idx] = desc_ab_mem;
	device->idx = (device->idx + 1) % QNUM;
	device->queue->desc[device->idx] = desc_ab_resp;
	device->idx = (device->idx + 1) % QNUM;
	device->queue->av.ring[device->queue->av.index % QNUM] = head;
	device->queue->av.index = (device->queue->av.index + 1) % QNUM; //wrapping_add(1) ???

	//*****************************************************************************************//
	//step 3
	set_scanout *scanout = (set_scanout*) alloc(1);
	gpu_ctrl_hdr *response3 = (gpu_ctrl_hdr*) alloc(1);
	set_header(
		&hdr,
		VIRTIO_GPU_CMD_SET_SCANOUT,
		0,
		0,
		0,
		0
	);
	set_rect(&rect, 0, 0, device->width, device->height);
	set_setscanout(scanout, hdr, rect, 0, 1);
	VirtQDescriptor desc_sso, desc_sso_resp;
	set_descriptor(
		&desc_sso,
		(uint64)scanout,
		sizeof(set_scanout),
		VIRTQ_DESC_F_NEXT,
		(device->idx + 1) % QNUM
	);
	set_descriptor(
		&desc_sso_resp,
		(uint64)response3,
		sizeof(gpu_ctrl_hdr),
		VIRTQ_DESC_F_WRITE,
		0
	);
	head = device->idx;
	device->queue->desc[device->idx] = desc_sso;
	device->idx = (device->idx + 1) % QNUM;
	device->queue->desc[device->idx] = desc_sso_resp;
	device->idx = (device->idx + 1) % QNUM;
	device->queue->av.ring[device->queue->av.index % QNUM] = head;
	device->queue->av.index = (device->queue->av.index + 1) % QNUM; //wrapping_add(1) ???

	//*******************************************************************************************//
	//step 4
	//transfer to host
	transfer_to_host_2d *transfer = (transfer_to_host_2d*)alloc(1);
	set_header(
		&hdr,
		VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D,
		0,
		0,
		0,
		0
	);
	set_rect(&rect, 0, 0, device->width, device->height);
	set_transfer_to_host(transfer, hdr, rect, 0, 1, 0);
	VirtQDescriptor desc_t2h, desc_t2h_response;
	gpu_ctrl_hdr *response4 = (gpu_ctrl_hdr*)alloc(1);
	set_descriptor(
		&desc_t2h,
		(uint64)transfer,
		sizeof(transfer_to_host_2d),
		VIRTQ_DESC_F_NEXT,
		(device->idx + 1)%QNUM
	);
	set_descriptor(
		&desc_t2h_response,
		(uint64)response4,
		sizeof(gpu_ctrl_hdr),
		VIRTQ_DESC_F_WRITE,
		0
	);
	head = device->idx;
	device->queue->desc[device->idx] = desc_t2h;
	device->idx = (device->idx + 1) % QNUM;
	device->queue->desc[device->idx] = desc_t2h_response;
	device->idx = (device->idx + 1) % QNUM;
	device->queue->av.ring[device->queue->av.index % QNUM] = head;
	device->queue->av.index = (device->queue->av.index + 1) % QNUM; //wrapping_add(1) ???

	//****************************************************************************************//
	//STEP 5 
	//FLUSH
	resource_flush *flush = (resource_flush*) alloc(1);
	set_header(
		&hdr,
		VIRTIO_GPU_CMD_RESOURCE_FLUSH,
		0,
		0,
		0,
		0
	);
	set_rect(&rect, 0, 0, device->width, device->height);
	set_resource_flush(flush, hdr, rect, 1, 0);

	VirtQDescriptor desc_rf, desc_rf_resp;
	gpu_ctrl_hdr *response5 = (gpu_ctrl_hdr*)alloc(1);
	set_descriptor(
		&desc_rf,
		(uint64)flush,
		sizeof(resource_flush),
		VIRTQ_DESC_F_NEXT,
		(device->idx + 1) % QNUM
	);
	set_descriptor(
		&desc_rf_resp,
		(uint64)response5,
		sizeof(gpu_ctrl_hdr),
		VIRTQ_DESC_F_WRITE,
		0
	);
	head = device->idx;
	device->queue->desc[device->idx] = desc_rf;
	device->idx = (device->idx + 1) % QNUM;
	device->queue->desc[device->idx] = desc_rf_resp;
	device->idx = (device->idx + 1) % QNUM;
	device->queue->av.ring[device->queue->av.index % QNUM] = head;
	device->queue->av.index = (device->queue->av.index + 1) % QNUM; //wrapping_add(1) ???


	//RUN THE QUEUE
	write_to_reg(device->dev, QUEUE_NOTIFY, 0);
	while(response1->type == 0);
	print_hdr(response1);
	print_hdr(response2);
	print_hdr(response3);
	print_hdr(response4);
	print_hdr(response5);
}



/*
*	funcao que seta o dispositivo
*	@param ptr: ponteiro para o dispositivo na memoria
*	@return 0 ou o endereco do device para caso o dispositivo falhe ou não na inicialização
*/
gpu_device* setup_gpu_device(uint64 ptr){

	uint32 idx = (ptr - VIRTIO_START) >> 12;

	//reset device -- writing 0 to status register
	write_to_reg(ptr, STATUS, 0);
	//set ack bit
	set_bit(ptr, STATUS, (1 << 0));
	//set driver status bit
	set_bit(ptr, STATUS, (1 << 1));
	uint32 host_feat = read_from_reg(ptr, HOST_FEATURES);
	write_to_reg(ptr, GUEST_FEATURES, host_feat);

	//setup device specific
	write_to_reg(ptr, QUEUE_NUM, QNUM);
	uint32 num_pages = (sizeof(VirtQ) + PAGE_SIZE - 1)/ PAGE_SIZE;

	//SELECT THE QUEUE
	write_to_reg(ptr, QUEUE_SEL, 0X0);
	
	VirtQ *queue = alloc(num_pages);
	printf("numpages: %d\n", num_pages);
	printf("queue: %p\n", queue);
	uint32 q_pfn = ((uint64)queue)/PAGE_SIZE;

	//INFORM PAGE_SIZE
	write_to_reg(ptr, GUEST_PAGE_SIZE, PAGE_SIZE);
	//INFORM THE PAGE WHERE THE FIRST QUEUE IS
	write_to_reg(ptr, QUEUE_PFN, q_pfn);
	//INFORM THAT EVERYTHING IS OK
	set_bit(ptr, STATUS, (1<<2));

	num_pages = (PAGE_SIZE*2+DEVICE_WIDTH*DEVICE_HEIGHT*sizeof(pixel))/PAGE_SIZE;
	pixel *fb = alloc(num_pages);
	gpu_device *device = (gpu_device*)alloc(1);
	device->queue = queue;
	device->dev = ptr;
	device->idx = 0;
	device->ack_used_idx = 0;
	device->framebuffer = fb;
	device->width = DEVICE_WIDTH;
	device->height = DEVICE_HEIGHT;
	return device;
}

void transfer(gpu_device *device, uint32 x, uint32 y, uint32 width, uint32 height){
	//*******************************************************************************************//
	//step 4
	//transfer to host
	uint16 head;
	gpu_ctrl_hdr hdr;
	gpu_rect rect;
	transfer_to_host_2d *transfer = (transfer_to_host_2d*)alloc(1);
	set_header(
		&hdr,
		VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D,
		0,
		0,
		0,
		0
	);
	set_rect(&rect, x, y, width, height);
	set_transfer_to_host(transfer, hdr, rect, 0, 1, 0);
	VirtQDescriptor desc_t2h, desc_t2h_response;
	gpu_ctrl_hdr *response4 = (gpu_ctrl_hdr*)alloc(1);
	set_descriptor(
		&desc_t2h,
		(uint64)transfer,
		sizeof(transfer_to_host_2d),
		VIRTQ_DESC_F_NEXT,
		(device->idx + 1)%QNUM
	);
	set_descriptor(
		&desc_t2h_response,
		(uint64)response4,
		sizeof(gpu_ctrl_hdr),
		VIRTQ_DESC_F_WRITE,
		0
	);
	head = device->idx;
	device->queue->desc[device->idx] = desc_t2h;
	device->idx = (device->idx + 1) % QNUM;
	device->queue->desc[device->idx] = desc_t2h_response;
	device->idx = (device->idx + 1) % QNUM;
	device->queue->av.ring[device->queue->av.index % QNUM] = head;
	device->queue->av.index = (device->queue->av.index + 1) % QNUM; //wrapping_add(1) ???

	//****************************************************************************************//
	//STEP 5 
	//FLUSH
	resource_flush *flush = (resource_flush*) alloc(1);
	set_header(
		&hdr,
		VIRTIO_GPU_CMD_RESOURCE_FLUSH,
		0,
		0,
		0,
		0
	);
	set_rect(&rect, x, y, width, height);
	set_resource_flush(flush, hdr, rect, 1, 0);

	VirtQDescriptor desc_rf, desc_rf_resp;
	gpu_ctrl_hdr *response5 = (gpu_ctrl_hdr*)alloc(1);
	set_descriptor(
		&desc_rf,
		(uint64)flush,
		sizeof(resource_flush),
		VIRTQ_DESC_F_NEXT,
		(device->idx + 1) % QNUM
	);
	set_descriptor(
		&desc_rf_resp,
		(uint64)response5,
		sizeof(gpu_ctrl_hdr),
		VIRTQ_DESC_F_WRITE,
		0
	);
	head = device->idx;
	device->queue->desc[device->idx] = desc_rf;
	device->idx = (device->idx + 1) % QNUM;
	device->queue->desc[device->idx] = desc_rf_resp;
	device->idx = (device->idx + 1) % QNUM;
	device->queue->av.ring[device->queue->av.index % QNUM] = head;
	device->queue->av.index = (device->queue->av.index + 1) % QNUM; //wrapping_add(1) ???


	//RUN THE QUEUE
	write_to_reg(device->dev, QUEUE_NOTIFY, 0);
}