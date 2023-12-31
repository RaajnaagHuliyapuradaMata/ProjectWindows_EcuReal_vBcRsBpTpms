

#include "ComM_Priv.hpp"

#if(COMM_INHIBITION_ENABLED)

#define COMM_START_SEC_CODE
#include "ComM_MemMap.hpp"

Std_ReturnType ComM_ResetInhibitCounter(void){

#if(COMM_DEV_ERROR_DETECT != STD_OFF)

   if(ComM_GlobalStruct.ComM_InitStatus_en != COMM_INIT)
   {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_RESET_INHIBIT_COUNTER_APIID,COMM_E_NOT_INITED);
        return COMM_E_NOT_INITIALIZED;
   }
#endif

   ComM_GlobalStruct.ComM_InhibitCounter_u16 = C_ZERO;
    return E_OK;
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.hpp"

#endif

