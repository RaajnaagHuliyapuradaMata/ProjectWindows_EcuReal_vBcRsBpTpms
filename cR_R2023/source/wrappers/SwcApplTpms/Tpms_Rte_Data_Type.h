#ifndef HUF_RTE_DATA_TYPE_HEADER_
#define HUF_RTE_DATA_TYPE_HEADER_

#include "Types.h"

#ifndef TRUE
#define TRUE          1U
#endif

#ifndef FALSE
#define FALSE         0U
#endif

#define PRODUCTION_SW   0x0
#define DEVELOPMENT_SW  0x1
#define SW_CATEGORY  PRODUCTION_SW
//#define SW_CATEGORY  DEVELOPMENT_SW

#if (SW_CATEGORY == DEVELOPMENT_SW)
#define DEBUG_AUTOLOCATION
#ifdef DEBUG_AUTOLOCATION
#define DEBUG_LOST_TELEGRAMS
#endif
#endif

typedef unsigned int          bitfield;
typedef unsigned long         uintptr;

#endif

