
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#define DEM_MEMMAP_ERROR

#if defined DEM_START_SEC_VAR_CLEARED
#if defined DEM_WAS_STARTED_SEC_VAR_CLEARED
        #error DEM_WAS_STARTED_SEC_VAR_CLEARED already defined
#endif
#define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef DEM_MEMMAP_ERROR
    #undef DEM_START_SEC_VAR_CLEARED
#define DEM_WAS_STARTED_SEC_VAR_CLEARED

#elif defined DEM_STOP_SEC_VAR_CLEARED
#if ! defined DEM_WAS_STARTED_SEC_VAR_CLEARED
        #error DEM_STOP_SEC_VAR_CLEARED without START_SEC
#else
        #undef DEM_WAS_STARTED_SEC_VAR_CLEARED
#endif
#define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef DEM_MEMMAP_ERROR
    #undef DEM_STOP_SEC_VAR_CLEARED

#elif defined DEM_START_SEC_VAR_INIT
#if defined DEM_WAS_STARTED_SEC_VAR_INIT
        #error DEM_WAS_STARTED_SEC_VAR_INIT already defined
#endif
#define BSW_START_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef BSW_START_SEC_VAR_INIT_UNSPECIFIED
    #undef DEM_MEMMAP_ERROR
    #undef DEM_START_SEC_VAR_INIT
#define DEM_WAS_STARTED_SEC_VAR_INIT

#elif defined DEM_STOP_SEC_VAR_INIT
#if ! defined DEM_WAS_STARTED_SEC_VAR_INIT
        #error DEM_STOP_SEC_VAR_INIT without START_SEC
#else
        #undef DEM_WAS_STARTED_SEC_VAR_INIT
#endif
#define BSW_STOP_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef BSW_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef DEM_MEMMAP_ERROR
    #undef DEM_STOP_SEC_VAR_INIT

#elif defined DEM_START_SEC_CONST
#if defined DEM_WAS_STARTED_SEC_CONST
        #error DEM_WAS_STARTED_SEC_CONST already defined
#endif
#define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef BSW_START_SEC_CONST_UNSPECIFIED
    #undef DEM_MEMMAP_ERROR
    #undef DEM_START_SEC_CONST
#define DEM_WAS_STARTED_SEC_CONST

#elif defined DEM_STOP_SEC_CONST
#if ! defined DEM_WAS_STARTED_SEC_CONST
        #error DEM_STOP_SEC_CONST without START_SEC
#else
        #undef DEM_WAS_STARTED_SEC_CONST
#endif
#define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef BSW_STOP_SEC_CONST_UNSPECIFIED
    #undef DEM_MEMMAP_ERROR
    #undef DEM_STOP_SEC_CONST

#elif defined DEM_START_SEC_CODE
#if defined DEM_WAS_STARTED_SEC_CODE
        #error DEM_WAS_STARTED_SEC_CODE already defined
#endif
#define BSW_START_SEC_CODE
    #include "Bsw_MemMap.hpp"
    #undef BSW_START_SEC_CODE
    #undef DEM_MEMMAP_ERROR
    #undef DEM_START_SEC_CODE
#define DEM_WAS_STARTED_SEC_CODE

#elif defined DEM_STOP_SEC_CODE
#if ! defined DEM_WAS_STARTED_SEC_CODE
        #error DEM_STOP_SEC_CODE without START_SEC
#else
        #undef DEM_WAS_STARTED_SEC_CODE
#endif
#define BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.hpp"
    #undef BSW_STOP_SEC_CODE
    #undef DEM_MEMMAP_ERROR
    #undef DEM_STOP_SEC_CODE

#elif defined DEM_START_SEC_CODE
#if defined Dem_WAS_STARTED_SEC_CODE
        #error Dem_WAS_STARTED_SEC_CODE already defined
#endif
#define BSW_START_SEC_CODE
    #include "Bsw_MemMap.hpp"
    #undef BSW_START_SEC_CODE
    #undef DEM_MEMMAP_ERROR
    #undef DEM_START_SEC_CODE
#define Dem_WAS_STARTED_SEC_CODE

#elif defined DEM_STOP_SEC_CODE
#if ! defined Dem_WAS_STARTED_SEC_CODE
        #error Dem_WAS_STARTED_SEC_CODE without START_SEC
#else
        #undef Dem_WAS_STARTED_SEC_CODE
#endif
#define BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.hpp"
    #undef BSW_STOP_SEC_CODE
    #undef DEM_MEMMAP_ERROR
    #undef DEM_STOP_SEC_CODE

#elif defined Dem_START_SEC_CODE
#if defined Dem_WAS_STARTED_SEC_CODE
        #error Dem_WAS_STARTED_SEC_CODE already defined
#endif
#define BSW_START_SEC_CODE
    #include "Bsw_MemMap.hpp"
    #undef BSW_START_SEC_CODE
    #undef DEM_MEMMAP_ERROR
    #undef Dem_START_SEC_CODE
#define Dem_WAS_STARTED_SEC_CODE

#elif defined Dem_STOP_SEC_CODE
#if ! defined Dem_WAS_STARTED_SEC_CODE
        #error Dem_WAS_STARTED_SEC_CODE without START_SEC
#else
        #undef Dem_WAS_STARTED_SEC_CODE
#endif
#define BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.hpp"
    #undef BSW_STOP_SEC_CODE
    #undef DEM_MEMMAP_ERROR
    #undef Dem_STOP_SEC_CODE

#elif defined DEM_START_SEC_VAR_SAVED_ZONE
#if defined DEM_WAS_STARTED_SEC_VAR_SAVED_ZONE
        #error DEM_WAS_STARTED_SEC_VAR_SAVED_ZONE already defined
#endif
#define BSW_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef BSW_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
    #undef DEM_MEMMAP_ERROR
    #undef DEM_START_SEC_VAR_SAVED_ZONE
#define DEM_WAS_STARTED_SEC_VAR_SAVED_ZONE

#elif defined DEM_STOP_SEC_VAR_SAVED_ZONE
#if ! defined DEM_WAS_STARTED_SEC_VAR_SAVED_ZONE
        #error DEM_WAS_STARTED_SEC_VAR_SAVED_ZONE without START_SEC
#else
        #undef DEM_WAS_STARTED_SEC_VAR_SAVED_ZONE
#endif
#define BSW_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
    #include "Bsw_MemMap.hpp"
    #undef BSW_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
    #undef DEM_MEMMAP_ERROR
    #undef DEM_STOP_SEC_VAR_SAVED_ZONE

#elif defined DEM_MEMMAP_ERROR
    #error "Dem_MemMap.h, wrong #pragma command"
#endif

