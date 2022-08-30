#ifndef GPU_H
#define GPU_H
#include "types.h"
#include "virtio.h"
//5.7.4 Device configuration layout



#define VIRTIO_GPU_EVENT_DISPLAY (1 << 0)
#define F_VIRGL 0
#define F_EDID 	1
#define FLAG_FENCE (1 << 0)
#define MAX_SCANOUTS 1
#define RESOURCE_ID 1

typedef struct virtio_gpu_config { 
	uint32 events_read; 
	uint32 events_clear; 
	uint32 num_scanouts;
	uint32 reserved;
}gpu_config;


//5.7.6.7 Device Operation: Request header
typedef enum virtio_gpu_ctrl_type { 
	/* 2d commands */ 
	VIRTIO_GPU_CMD_GET_DISPLAY_INFO = 0x0100, 
	VIRTIO_GPU_CMD_RESOURCE_CREATE_2D, 
	VIRTIO_GPU_CMD_RESOURCE_UNREF, 
	VIRTIO_GPU_CMD_SET_SCANOUT, 
	VIRTIO_GPU_CMD_RESOURCE_FLUSH, 
	VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D, 
	VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING, 
	VIRTIO_GPU_CMD_RESOURCE_DETACH_BACKING, 
	VIRTIO_GPU_CMD_GET_CAPSET_INFO, 
	VIRTIO_GPU_CMD_GET_CAPSET, 
	VIRTIO_GPU_CMD_GET_EDID, 

	/* cursor commands */ 
	VIRTIO_GPU_CMD_UPDATE_CURSOR = 0x0300, 
	VIRTIO_GPU_CMD_MOVE_CURSOR, 

	/* success responses */ 
	VIRTIO_GPU_RESP_OK_NODATA = 0x1100, 
	VIRTIO_GPU_RESP_OK_DISPLAY_INFO, 
	VIRTIO_GPU_RESP_OK_CAPSET_INFO, 
	VIRTIO_GPU_RESP_OK_CAPSET, 
	VIRTIO_GPU_RESP_OK_EDID, 

	/* error responses */ 
	VIRTIO_GPU_RESP_ERR_UNSPEC = 0x1200, 
	VIRTIO_GPU_RESP_ERR_OUT_OF_MEMORY, 
	VIRTIO_GPU_RESP_ERR_INVALID_SCANOUT_ID, 
	VIRTIO_GPU_RESP_ERR_INVALID_RESOURCE_ID, 
	VIRTIO_GPU_RESP_ERR_INVALID_CONTEXT_ID, 
	VIRTIO_GPU_RESP_ERR_INVALID_PARAMETER, 
}gpu_ctrl_type;
 
#define VIRTIO_GPU_FLAG_FENCE (1 << 0) 
 
typedef struct virtio_gpu_ctrl_hdr { 
	gpu_ctrl_type type; 
	uint32 flags; 
	uint64 fence_id; 
	uint32 ctx_id; 
	uint32 padding;
}gpu_ctrl_hdr;

//5.7.6.8 Device Operation: controlq

 
typedef struct virtio_gpu_rect { 
	uint32 x; 
	uint32 y; 
	uint32 width; 
	uint32 height; 
}gpu_rect; 


typedef struct virtio_gpu_display_one { 
	gpu_rect r; 
	uint32 enabled; 
	uint32 flags; 
}gpu_display_one;


typedef struct virtio_gpu_resp_display_info { 
	gpu_ctrl_hdr hdr; 
	gpu_display_one pmodes[MAX_SCANOUTS]; 
}gpu_resp_display_info;

typedef struct get_ed_id{
	gpu_ctrl_hdr hdr;
	uint32 scanout;
	uint32 paddind;
}get_ed_id;

typedef struct resp_ed_id {
	gpu_ctrl_hdr hdr;
	uint32 size;
	uint32 paddind;
	uint8 edid[1024];
}resp_ed_id;

typedef enum virtio_gpu_formats { 
	VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM  = 1, 
	VIRTIO_GPU_FORMAT_B8G8R8X8_UNORM  = 2, 
	VIRTIO_GPU_FORMAT_A8R8G8B8_UNORM  = 3, 
	VIRTIO_GPU_FORMAT_X8R8G8B8_UNORM  = 4, 

	VIRTIO_GPU_FORMAT_R8G8B8A8_UNORM  = 67, 
	VIRTIO_GPU_FORMAT_X8B8G8R8_UNORM  = 68, 

	VIRTIO_GPU_FORMAT_A8B8G8R8_UNORM  = 121, 
	VIRTIO_GPU_FORMAT_R8G8B8X8_UNORM  = 134, 
}virtio_gpu_format;


typedef struct resource_create_2d {
	gpu_ctrl_hdr hdr;
	uint32 resource_id;
	uint32 formats;
	uint32 width;
	uint32 height;
}resource_create_2d;


typedef struct resource_unref {
	gpu_ctrl_hdr hdr;
	uint32 resource_id;
	uint32 padding;
}resource_unref;


typedef struct set_scanout {
	gpu_ctrl_hdr hdr;
	gpu_rect r;
	uint32 scanout_id;
	uint32 resource_id;
}set_scanout;


typedef struct resource_flush {
	gpu_ctrl_hdr hdr;
	gpu_rect r;
	uint32 resource_id;
	uint32 padding;
}resource_flush;



typedef struct transfer_to_host_2d {
	gpu_ctrl_hdr hdr;
	gpu_rect r;
	uint64 offset;
	uint32 resource_id;
	uint32 padding;
}transfer_to_host_2d;


typedef struct attach_backing {
	gpu_ctrl_hdr hdr;
	uint32 resource_id;
	uint32 nr_entries;
}attach_backing;



typedef struct mem_entry {
	uint64 addr;
	uint32 length;
	uint32 padding;
}mem_entry;



typedef struct detach_backing {
	gpu_ctrl_hdr hdr;
	uint32 resource_id;
	uint32 padding;
}detach_backing;


typedef struct cursor_pos {
	uint32 scanout_id;
	uint32 x;
	uint32 y;
	uint32 padding;
}cursor_pos;



typedef struct update_cursor {
	gpu_ctrl_hdr hdr;
	cursor_pos pos;
	uint32 resource_id;
	uint32 hot_x;
	uint32 hot_y;
	uint32 padding;
}update_cursor;



// typedef struct pixel {
// 	uint8 r;
// 	uint8 g;
// 	uint8 b;
// 	uint8 a;
// }pixel;




typedef struct gpu_device{
	VirtQ *queue;
	uint64 dev;
	uint16 idx;
	uint16 ack_used_idx;
	uint32 *framebuffer;
	uint32 width;
	uint32 height;
}gpu_device;

/*
*	funcao que seta o dispositivo
*	@param ptr: ponteiro para o dispositivo na memoria
*	@return 0 ou o endereco do device para caso o dispositivo falhe ou não na inicialização
*/
gpu_device *setup_gpu_device(uint64 ptr);
void init_gpu_device(gpu_device *device);
void transfer(uint32 x, uint32 y, uint32 width, uint32 height);
// void set_color(pixel*, uint32 color);
void set_rect(gpu_rect *rect, uint32 x, uint32 y, uint32 width, uint32 height);
void draw_line(int x1, int y1, int x2, int y2);
void bg_color(uint32 color);
void fill_color(uint32 color);
void stroke_color(uint32 color);
void stroke_weigth(uint32 weight);
void draw_rect(int x, int y, int w, int h);
void draw_circle(int x, int y, int r);
void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3);




#endif