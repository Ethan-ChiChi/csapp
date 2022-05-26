#ifndef DEBUG_GUARD
#define DEBUG_GUARD

#include<stdint.h>

#define DEBUG_INSTRUCTIONCYCLE      0x1
#define DEBUG_REGISTERS             0x2
#define DEBUG_PRINTSTACK            0x4
#define DEBUG_CACHEDETAILS          0x8
#define DEBUG_PRINTCACHESET         0x10
#define DEBUG_MMU                   0x20
#define DEBUG_LINKER                0x40
#define DEBUG_LOADER                0x80
#define DEBUG_PARSEINST             0x100

#define DEBUG_VERBOSE_SET           0x041

//do page walk
#define DEBUG_ENABLE_PAGE_WALK      0

//use sram cache for memory acess
#define DEBUG_ENABLE_SRAM_CACHE     0

// printf wrapper
uint64_t debug_printf(uint64_t open_set, const char *format, ...);
#endif