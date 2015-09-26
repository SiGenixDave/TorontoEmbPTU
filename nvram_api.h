/**
 * @file	nvram_api.h
 * @brief	NVRAM API definition
 * @author  Mario Scondo (mario.scondo@linux-support.com)
 *
 * This header file defines the API of the NVRAM library. It is the only
 * header file necessary for using the library.
 */

#ifndef NVRAM_API_H
#define NVRAM_API_H

#ifdef __cplusplus
extern "C" {
#endif

/*
  The following complicated declarations are needed to be able to use
  the same file in several targets.
 */
#if defined (_WIN32)
 typedef int int32_t;
 typedef unsigned int uint32_t;
 typedef long int int64_t;
 #ifdef NVRAM_MAKEDLL
  #define NVRAM_EXPORT __declspec(dllexport)
 #else
  #define NVRAM_EXPORT __declspec(dllimport)
 #endif
#elif defined (O_CSS)
 #ifndef O_C99_TYPES
  #ifndef __INCvxTypesh
   #include "css.h"
   #include "ansi_api.h"
  #endif
 #endif
#else
 #include <linux/types.h>
 #include <stdint.h>
#endif

#ifndef NVRAM_EXPORT
 #define NVRAM_EXPORT
#endif

/*
  The following defines are names of the system counters supported by CSS.
  These are predefined and updated by CSS.
 */
#define NVRAM_SC_UPTIME        "uptime"
#define NVRAM_SC_UPTIME_TOTAL  "uptime_total"
#define NVRAM_SC_POWER_ON_CNT  "power_on_cnt"
#define NVRAM_SC_RESTART_CNT   "restart_cnt"

/**
 * maximum length for segment names
 */
#define NVRAM_MAX_NAME_LEN	 31

/**
 * max number of memory segments to be managed
 */
#define NVRAM_MAX_NUM_SEGS	100

/*
 * result codes
 */
#define NVRAM_RESET			 1		/**< init OK, but NVRAM had to be reset */
#define NVRAM_OK			 0		/**< everything OK */
#define NVRAM_ERR_OPEN		-1		/**< opening the NVRAM device failed */
#define NVRAM_ERR_INIT		-2		/**< could not initialize NVRAM device */
#define NVRAM_ERR_SEGMENT	-3		/**< segmentation error */
#define NVRAM_ERR_CHECKSUM	-4		/**< checksum error */
#define NVRAM_ERR_NOMEM		-5		/**< not enough memory available */
#define NVRAM_ERR_MMAP		-6		/**< mapping of device file failed */
#define NVRAM_ERR_HANDLE	-7		/**< invalid handle */
#define NVRAM_ERR_VERSION	-8		/**< version mismatch */
#define NVRAM_ERR_SIZE		-9		/**< size mismatch */
#define NVRAM_ERR_NAME		-10		/**< invalid name */

/**
 * Determines if the specified \a handle is valid
 */
#define NVRAM_HANDLE_VALID(handle) \
	(((handle) >= 0) && ((handle) < NVRAM_MAX_NUM_SEGS))

/**
 * handle to be used to access NVRAM memory
 */
typedef int32_t nvram_handle;

/**
 * General information about the NVRAM device
 */
typedef struct
{
	size_t		size;			/**< total size of the available NVRAM */
	size_t  	free;			/**< number of available bytes */
	size_t  	cfree;			/**< max. number of bytes available consecutively */
	int32_t 	num_segments;	/**< max. number of managed memory segments */
	int32_t 	status;			/**< global NVRAM status/error code */
	int32_t 	mm_version;		/**< NVRAM management API version */
} nvram_dev_info_t;


/**
 * Information about a memory segment
 */
typedef struct
{
	char		name[NVRAM_MAX_NAME_LEN+1];	/**< segment name */
	int32_t 	version;			  		/**< segment version */
	size_t 		size;				  		/**< segment size */
} nvram_seg_info_t;

#ifndef TEST_ON_PC
NVRAM_EXPORT int32_t nvram_init(
	void
);
NVRAM_EXPORT int32_t nvram_reset(
	void
);
NVRAM_EXPORT int32_t nvram_check(
	void
);
NVRAM_EXPORT nvram_handle nvram_malloc(
	const char*			 	name,
    int32_t				 	version,
    size_t				 	size
);
NVRAM_EXPORT nvram_handle nvram_realloc(
	nvram_handle		 	handle,
	int32_t				 	version,
	size_t				 	size
);
NVRAM_EXPORT int32_t nvram_free(
	nvram_handle		 	handle
);
NVRAM_EXPORT int32_t nvram_clear(
	nvram_handle		 	handle
);
NVRAM_EXPORT void *nvram_get_pointer(
	nvram_handle		 	handle
);
NVRAM_EXPORT int32_t nvram_get_dirty_flag(
	nvram_handle		 	handle
);
NVRAM_EXPORT int32_t nvram_read(
	nvram_handle		 	handle,
    unsigned char*		 	buffer,
    size_t				 	length,
    int32_t				 	offset
);
NVRAM_EXPORT int32_t nvram_write(
	nvram_handle		 	handle,
    const unsigned char*	buffer,
    size_t					length,
    int32_t					offset
);
NVRAM_EXPORT int32_t nvram_info(
	nvram_dev_info_t*		dev_info,
    nvram_seg_info_t*		seg_info_array
);
NVRAM_EXPORT nvram_handle nvram_segment_info(
	const char*				name,
    nvram_seg_info_t*		seg_info
);

NVRAM_EXPORT int32_t nvram_sc_get(
    const char *name,
    int64_t    *p_ctr );
#endif

#ifdef __cplusplus
}
#endif

#endif /* NVRAM_API_H */

