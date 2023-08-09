
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmCore_DslDsd_Inf.h"

// RST integration code start
#include "DcmManagerX.h"
#include "CanIf.h"
// RST integration code end

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)

 #define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetPermTxWarmResp(void)
{
    VAR(Std_ReturnType,AUTOMATIC)   retVal;

    // RST: function returns always 0 if not used - commented this
    //retVal = E_OK;

    //return (retVal);

    CanIf_ControllerModeType tCanIfControllerMode;
    retVal = E_NOT_OK;

    CanIf_GetControllerMode(0, &tCanIfControllerMode);
    if (tCanIfControllerMode == CANIF_CS_STARTED)
    {
      retVal = E_OK;
    }

    return (retVal);

}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

#endif
