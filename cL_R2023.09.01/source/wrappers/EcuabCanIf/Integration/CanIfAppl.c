
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "CanIf_Prv.hpp"

#if(CANIF_CONFIGURATION_VARIANT > 1)

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"

void CanIfAppl_IncompatibleGenerator(void){
    // User can report DET error / DEM error etc here
}

#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

#endif
