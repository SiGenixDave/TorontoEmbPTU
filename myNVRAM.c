#include "myWrapper.h"
#include "nvram_api.h"

int32_t nvram_clear(nvram_handle handle) {

}

int32_t nvram_get_dirty_flag(nvram_handle handle) {

}

int32_t nvram_read(nvram_handle handle, unsigned char* buffer, size_t length,
		int32_t offset) {

}
int32_t nvram_write(nvram_handle handle, const unsigned char* buffer,
		size_t length, int32_t offset)

{

}

nvram_handle nvram_malloc(const char* name, int32_t version, size_t size) {

}

nvram_handle nvram_realloc(nvram_handle handle, int32_t version, size_t size) {

}

nvram_handle nvram_segment_info(const char* name, nvram_seg_info_t* seg_info) {

}

