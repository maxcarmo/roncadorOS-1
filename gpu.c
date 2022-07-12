#include "types.h"
#include "defs.h"
#include "gpu.h"
#include "virtio.h"
#include "game.h"

#define BG_COLOR 0x666666
#define FIELD_COLOR 0xeeeeee


gpu_device *GPU_DEVICE;

uint8 tetris_block_layout[] = 
{
0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,
1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,
1,1,2,1,4,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,4,1,2,1,1,
1,1,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,2,1,1,
1,1,2,1,2,2,2,2,2,2,2,2,2,2,5,5,5,5,5,5,5,5,5,2,2,2,2,2,1,2,1,1,
1,1,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,5,5,5,5,5,5,2,2,2,1,2,1,1,
1,1,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,5,5,5,5,5,2,2,1,2,1,1,
1,1,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,5,5,5,2,2,1,2,1,1,
1,1,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,5,5,2,2,1,2,1,1,
1,1,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,5,2,2,1,2,1,1,
1,1,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,5,2,2,1,2,1,1,
1,1,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,2,2,1,2,1,1,
1,1,2,1,2,2,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,2,2,1,2,1,1,
1,1,2,1,2,2,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,2,2,1,2,1,1,
1,1,2,1,2,2,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,2,2,1,2,1,1,
1,1,2,1,2,2,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,2,2,1,2,1,1,
1,1,2,1,2,2,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,
1,1,2,1,2,2,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,
1,1,2,1,2,2,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,
1,1,2,1,2,2,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,
1,1,2,1,2,2,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,
1,1,2,1,2,2,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,
1,1,2,1,2,2,2,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,
1,1,2,1,2,2,2,2,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,1,2,1,1,
1,1,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,2,1,1,
1,1,2,1,4,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,4,1,2,1,1,
1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,
1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0
};

uint32 block_colors [7][6]= {
	//alpha		dark out  inside    dark inside  4 points  light inside
	{ BG_COLOR, 0x0097a7, 0x00e5ff, 0x00838f, 	 0x90caf9, 0x84ffff }, //I light blue
	{ BG_COLOR, 0x880e4f, 0xe91e63, 0xb71c1c, 	 0x90caf9, 0xe57373 }, //Z red
	{ BG_COLOR, 0x2e7d32, 0x00e676, 0x1b5e20, 	 0x90caf9, 0x69f0ae }, //S green
	{ BG_COLOR, 0x9e9e3e, 0xd6d244, 0x838718, 	 0x90caf9, 0xf2f25f }, //O yellow
	{ BG_COLOR, 0x4527a0, 0x673ab7, 0x4a148c, 	 0x90caf9, 0x9575cd }, //T purple-pinkish
	{ BG_COLOR, 0xe64a19, 0xff8a65, 0xdd2c00, 	 0x90caf9, 0xffab91 }, //L orange
	{ BG_COLOR, 0x0000ff, 0x304ffe, 0x1a237e, 	 0x90caf9, 0x8c9eff }  //J blue
	//			0x283593
};


void draw_field(){
	pixel color;
	gpu_rect rect;
	set_color(&color, FIELD_COLOR);
	set_rect(&rect, FIELD_START, 0, FIELD_WIDTH*BLOCK_SIZE, FIELD_HEIGHT*BLOCK_SIZE);
	stroke_rect(rect, color, 2);
}

void draw_tetris_block(uint32 x, uint32 y, piece_name shape){
	pixel p;
	uint8 color;
	uint32 byte;
	uint32 block_pixel_x, block_pixel_y, pixel_index;
	for (uint32 line = y; line < y+BLOCK_SIZE; line++){
		for (uint32 col = x; col < x+BLOCK_SIZE; col++){
			block_pixel_x = col - x;
			block_pixel_y = line - y;
			pixel_index = block_pixel_y * BLOCK_SIZE + block_pixel_x;
			color = tetris_block_layout[pixel_index];
			set_color(&p, block_colors[shape][color]);
			byte = line * DEVICE_WIDTH + col;
			GPU_DEVICE->framebuffer[byte] = p;
		}
	}
}

void draw_piece(piece p){
	uint32 x_offset, y_offset;
	x_offset = FIELD_START + (p.x * BLOCK_SIZE);
	y_offset = p.y * BLOCK_SIZE;
	for (uint8 line = 0; line < TETROMINO_SIZE; line++){
		for (uint8 col = 0; col < TETROMINO_SIZE; col++){
			if (tetrominoes[p.name][rotate(col, line, p.rotation)]){ //se há um bloco nessa posicao
				draw_tetris_block(x_offset + col*BLOCK_SIZE, y_offset + line*BLOCK_SIZE, p.name);
			}
		}
	}
}

void clear(){
	pixel p;
	set_color(&p, BG_COLOR);
	uint32 size = DEVICE_HEIGHT*DEVICE_WIDTH;
	for (uint32 pos = 0; pos < size; pos++){
		GPU_DEVICE->framebuffer[pos] = p; 
	}
}


void print_hdr(gpu_ctrl_hdr *hdr){
	printf("HEADER: \n");
	printf("\ttype: %d\n", hdr->type);
	printf("\tflags: %d\n", hdr->flags);
	printf("\tfence: %d\n", hdr->fence_id);
	printf("\tctx_id: %d\n", hdr->ctx_id);
	printf("\tpadding: %d\n", hdr->padding);
}

void print_rect(gpu_rect rect){
	printf("RECTANGLE:\n");
	printf("\tx: %d\n", rect.x);
	printf("\ty: %d\n", rect.y);
	printf("\th: %d\n", rect.height);
	printf("\tw: %d\n", rect.width);
}

void print_gpu_display_one(gpu_display_one display){
	printf("DISPLAY ONE:\n");
	printf("\tenabled: %d\n", display.enabled);
	printf("\tflags: %d\n",display.flags);
	print_rect(display.r);
}

void print_display_info(gpu_resp_display_info *info){
	printf("DISPLAY INFO: \n");
	print_hdr(&(info->hdr));
	for (int i = 0; i < MAX_SCANOUTS; i++){
		print_gpu_display_one(info->pmodes[i]);
	}
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

void set_color(pixel *p, uint32 color){
	p->r = color >> 16;
	p->g = (color >> 8) & 0x00ff;
	p->b = color & 0x0000ff;
	p->a = 0xff;
}

void set_rect(gpu_rect *rect, uint32 x, uint32 y, uint32 w, uint32 h){
	rect->x = x;
	rect->y = y;
	rect->height = h;
	rect->width = w;
}

void fill_rect_tetris(gpu_device *dev, gpu_rect rect, pixel color){
	uint32 byte;
	pixel preto;
	set_color(&preto, 0x000000);
	for (uint32 row = rect.y; row < rect.y + rect.height; row++){
		for (uint32 col = rect.x; col < rect.x + rect.width; col++){
			byte = row * dev->width + col;
			if (row == rect.y ||
				col == rect.x ||
				row == rect.y + rect.height -1 ||
				col == rect.x + rect.width  -1
			){
				dev->framebuffer[byte] = preto;
			}else{
				dev->framebuffer[byte] = color;
			}
		}
	}
}

void fill_rect(gpu_rect rect, pixel color){
	uint32 byte;
	for (uint32 row = rect.y; row < rect.y + rect.height; row++){
		for (uint32 col = rect.x; col < rect.x + rect.width; col++){
			byte = row * GPU_DEVICE->width + col;
			GPU_DEVICE->framebuffer[byte] = color;
		}
	}
}

void stroke_rect(gpu_rect rect, pixel color, uint32 size){
	gpu_rect new_rect;

	//top
	set_rect(&new_rect, rect.x, rect.y, rect.width, size);
	fill_rect(new_rect,color);

	//bot
	set_rect(&new_rect, rect.x, rect.y+rect.height, rect.width, size);
	fill_rect(new_rect, color);

	//left
	set_rect(&new_rect, rect.x, rect.y, size, rect.height);
	fill_rect(new_rect, color);

	//right
	set_rect(&new_rect, rect.x+rect.width, rect.y, size, rect.height+size);
	fill_rect(new_rect, color);
}

/*
*	funcao que inicializa o dispositivo
*	@param dev: ponteiro para o dispositivo
*/

void init_gpu_device(gpu_device *device){
	uint16 head;
	pixel color;
	gpu_rect rect;
	gpu_ctrl_hdr hdr;

	set_rect(&rect, 0, 0, DEVICE_WIDTH, DEVICE_HEIGHT);
	set_color(&color, 0xEEeeEE); //0xEB3E1B
	fill_rect(rect, color);


	set_header(&hdr, VIRTIO_GPU_CMD_RESOURCE_CREATE_2D, 0, 0, 0, 0);
	resource_create_2d *res = (resource_create_2d*) alloc(1);
	set_res_create_2d(
		res,
		hdr,
		RESOURCE_ID,
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


	head = device->idx;
	device->queue->desc[device->idx] = c2d;
	device->idx = (device->idx + 1) % QNUM;
	device->queue->desc[device->idx] = c2d_response;
	device->idx = (device->idx + 1) % QNUM;
	device->queue->av.ring[device->queue->av.index % QNUM] = head;
	device->queue->av.index = (device->queue->av.index + 1); //wrapping_add(1) ???



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
	set_attach_backing(attach, hdr, RESOURCE_ID, 1);
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
	set_setscanout(scanout, hdr, rect, 0, RESOURCE_ID);
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
	set_transfer_to_host(transfer, hdr, rect, 0, RESOURCE_ID, 0);
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
	set_resource_flush(flush, hdr, rect, RESOURCE_ID, 0);

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
	while(device->queue->av.index != device->queue->used.index);
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
	set_bit(ptr, STATUS, STATUS_ACKNOWLEDGE);
	//set driver status bit
	set_bit(ptr, STATUS, STATUS_DRIVER);
	uint32 host_feat = read_from_reg(ptr, HOST_FEATURES);
	write_to_reg(ptr, GUEST_FEATURES, host_feat);

	//setup device specific
	write_to_reg(ptr, QUEUE_NUM, QNUM);
	uint32 num_pages = 1+ ((sizeof(VirtQ))/ PAGE_SIZE);

	//SELECT THE QUEUE
	write_to_reg(ptr, QUEUE_SEL, 0X0);
	
	VirtQ *queue = alloc(num_pages);
	uint32 q_pfn = ((uint64)queue)/PAGE_SIZE;

	//INFORM PAGE_SIZE
	write_to_reg(ptr, GUEST_PAGE_SIZE, PAGE_SIZE);
	//INFORM THE PAGE WHERE THE FIRST QUEUE IS
	write_to_reg(ptr, QUEUE_PFN, q_pfn);
	//INFORM THAT EVERYTHING IS OK
	set_bit(ptr, STATUS, STATUS_DRIVER_OK);

	num_pages = 1 + ((DEVICE_WIDTH*DEVICE_HEIGHT*sizeof(pixel))/PAGE_SIZE);
	pixel *fb = alloc(num_pages*2);
	gpu_device *device = (gpu_device*)alloc(1);
	device->queue = queue;
	device->dev = ptr;
	device->idx = 0;
	device->ack_used_idx = 0;
	device->framebuffer = fb ;//(pixel*)((uint64)fb + num_pages*PAGE_SIZE);
	device->width = DEVICE_WIDTH;
	device->height = DEVICE_HEIGHT;

	GPU_DEVICE = device;
	return device;
}

void transfer(uint32 x, uint32 y, uint32 width, uint32 height){
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
	set_rect(&rect, x, y, width+x, height+y);
	set_transfer_to_host(transfer, hdr, rect, 0, 1, 0);
	VirtQDescriptor desc_t2h, desc_t2h_response;
	gpu_ctrl_hdr *response4 = (gpu_ctrl_hdr*)alloc(1);
	set_descriptor(
		&desc_t2h,
		(uint64)transfer,
		sizeof(transfer_to_host_2d),
		VIRTQ_DESC_F_NEXT,
		(GPU_DEVICE->idx + 1)%QNUM
	);
	set_descriptor(
		&desc_t2h_response,
		(uint64)response4,
		sizeof(gpu_ctrl_hdr),
		VIRTQ_DESC_F_WRITE,
		0
	);
	head = GPU_DEVICE->idx;
	GPU_DEVICE->queue->desc[GPU_DEVICE->idx] = desc_t2h;
	GPU_DEVICE->idx = (GPU_DEVICE->idx + 1) % QNUM;
	GPU_DEVICE->queue->desc[GPU_DEVICE->idx] = desc_t2h_response;
	GPU_DEVICE->idx = (GPU_DEVICE->idx + 1) % QNUM;
	GPU_DEVICE->queue->av.ring[GPU_DEVICE->queue->av.index % QNUM] = head;
	GPU_DEVICE->queue->av.index = (GPU_DEVICE->queue->av.index + 1) ; 

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
	set_rect(&rect, x, y, width+x, height+y);
	set_resource_flush(flush, hdr, rect, 1, 0);

	VirtQDescriptor desc_rf, desc_rf_resp;
	gpu_ctrl_hdr *response5 = (gpu_ctrl_hdr*)alloc(1);
	set_descriptor(
		&desc_rf,
		(uint64)flush,
		sizeof(resource_flush),
		VIRTQ_DESC_F_NEXT,
		(GPU_DEVICE->idx + 1) % QNUM
	);
	set_descriptor(
		&desc_rf_resp,
		(uint64)response5,
		sizeof(gpu_ctrl_hdr),
		VIRTQ_DESC_F_WRITE,
		0
	);
	head = GPU_DEVICE->idx;
	GPU_DEVICE->queue->desc[GPU_DEVICE->idx] = desc_rf;
	GPU_DEVICE->idx = (GPU_DEVICE->idx + 1) % QNUM;
	GPU_DEVICE->queue->desc[GPU_DEVICE->idx] = desc_rf_resp;
	GPU_DEVICE->idx = (GPU_DEVICE->idx + 1) % QNUM;
	GPU_DEVICE->queue->av.ring[GPU_DEVICE->queue->av.index % QNUM] = head;
	GPU_DEVICE->queue->av.index = (GPU_DEVICE->queue->av.index + 1); 


	//RUN THE QUEUE
	write_to_reg(GPU_DEVICE->dev, QUEUE_NOTIFY, 0);
	while (GPU_DEVICE->queue->av.index != GPU_DEVICE->queue->used.index);
	dealloc(transfer);
	dealloc(response4);
	dealloc(response5);
	dealloc(flush);
}