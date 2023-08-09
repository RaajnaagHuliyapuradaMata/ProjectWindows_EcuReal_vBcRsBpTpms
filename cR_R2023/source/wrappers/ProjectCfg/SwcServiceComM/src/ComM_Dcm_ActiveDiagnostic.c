

#include "ComM_Priv.h"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

FUNC(void,COMM_CODE) ComM_DCM_ActiveDiagnostic(VAR(NetworkHandleType, AUTOMATIC) Channel)

{

    P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;

    channelRamPtr_ps = &ComM_ChannelStruct[Channel];

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {

       (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_DCM_ACTIVEDIAG,COMM_E_NOT_INITED);
        return;
    }
    #endif

    channelRamPtr_ps->DiagnosticRequestState_b = COMM_ACTIVE_DIAGNOSTICS;

}
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

