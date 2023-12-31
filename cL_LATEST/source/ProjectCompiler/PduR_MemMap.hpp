
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "PduR_Cfg_SymbolicNames.hpp"

#define MEMMAP_ERROR

#if( PDUR_CONFIGURATION_VARIANT == PDUR_VARIANT_PRE_COMPILE )

# if defined PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED

#  undef PDUR_START_SEC_CONFIG_DATA_UNSPECIFIED
#  define PDUR_START_SEC_CONST_UNSPECIFIED
# elif defined PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED

#  undef  PDUR_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#  define PDUR_STOP_SEC_CONST_UNSPECIFIED
# elif defined PDUR_START_SEC_CONFIG_DATA_8

#  undef PDUR_START_SEC_CONFIG_DATA_8
#  define PDUR_START_SEC_CONST_8
# elif defined PDUR_STOP_SEC_CONFIG_DATA_8

#  undef  PDUR_STOP_SEC_CONFIG_DATA_8
#  define PDUR_STOP_SEC_CONST_8
# elif defined PDUR_START_SEC_VAR_CLEARED_8

#  undef PDUR_START_SEC_VAR_CLEARED_8
#  define PDUR_START_SEC_VAR_CLEARED_PC_8
# elif defined PDUR_STOP_SEC_VAR_CLEARED_8

#  undef PDUR_STOP_SEC_VAR_CLEARED_8
#  define PDUR_STOP_SEC_VAR_CLEARED_PC_8
# elif defined PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED

#  undef PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#  define PDUR_START_SEC_VAR_CLEARED_PC_UNSPECIFIED
# elif defined PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED

#  undef PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#  define PDUR_STOP_SEC_VAR_CLEARED_PC_UNSPECIFIED
# endif
#endif

#if defined PDUR_START_SEC_CONST_UNSPECIFIED

#define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.hpp"

    #undef PDUR_START_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_CONST_UNSPECIFIED
#define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.hpp"

    #undef PDUR_STOP_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined PDUR_START_SEC_CONST_8

#define BSW_START_SEC_CONST_8
    #include "Bsw_MemMap.hpp"

    #undef PDUR_START_SEC_CONST_8
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_CONST_8
#define BSW_STOP_SEC_CONST_8
    #include "Bsw_MemMap.hpp"

    #undef PDUR_STOP_SEC_CONST_8
    #undef MEMMAP_ERROR

#elif defined PDUR_START_SEC_VAR_CLEARED_POSTBUILD_8

#define BSW_START_SEC_VAR_CLEARED_POSTBUILD_8
    #include "Bsw_MemMap.hpp"

    #undef PDUR_START_SEC_VAR_CLEARED_POSTBUILD_8
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#define BSW_STOP_SEC_VAR_CLEARED_POSTBUILD_8
    #include "Bsw_MemMap.hpp"

    #undef PDUR_STOP_SEC_VAR_CLEARED_POSTBUILD_8
    #undef MEMMAP_ERROR

#elif defined PDUR_START_SEC_VAR_CLEARED_PC_8

#define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.hpp"

    #undef PDUR_START_SEC_VAR_CLEARED_PC_8
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_VAR_CLEARED_PC_8
#define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.hpp"

    #undef PDUR_STOP_SEC_VAR_CLEARED_PC_8
    #undef MEMMAP_ERROR
#elif defined PDUR_START_SEC_VAR_CLEARED_PC_UNSPECIFIED

#define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.hpp"

    #undef PDUR_START_SEC_VAR_CLEARED_PC_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_VAR_CLEARED_PC_UNSPECIFIED
#define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.hpp"

    #undef PDUR_STOP_SEC_VAR_CLEARED_PC_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined PDUR_START_SEC_CODE
#define BSW_START_SEC_CODE
    #include "Bsw_MemMap.hpp"

    #undef PDUR_START_SEC_CODE
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_CODE
#define BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.hpp"

    #undef PDUR_STOP_SEC_CODE
    #undef MEMMAP_ERROR

#elif defined PDUR_START_SEC_CONFIG_DATA_POSTBUILD_8

#define BSW_START_SEC_CONFIG_DATA_POSTBUILD_8
    #include "Bsw_MemMap.hpp"

    #undef PDUR_START_SEC_CONFIG_DATA_POSTBUILD_8
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_8
#define BSW_STOP_SEC_CONFIG_DATA_POSTBUILD_8
    #include "Bsw_MemMap.hpp"

    #undef PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_8
    #undef MEMMAP_ERROR

#elif defined PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED

#define BSW_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.hpp"

    #undef PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#define BSW_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.hpp"

    #undef PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined PDUR_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED

#define BSW_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.hpp"

    #undef PDUR_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined PDUR_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#define BSW_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.hpp"

    #undef PDUR_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined MEMMAP_ERROR
    #error "PduR_MemMap.h, wrong #pragma command"
#endif

