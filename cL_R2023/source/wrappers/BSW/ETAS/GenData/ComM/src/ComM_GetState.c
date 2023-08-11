

#include "ComM_Priv.h"

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h"

Std_ReturnType ComM_GetState(NetworkHandleType Channel, ComM_StateType *  State)
{

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    if (ComM_GlobalStruct.ComM_InitStatus_en != COMM_INIT)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_STATE_APIID,COMM_E_NOT_INITED);
        return COMM_E_NOT_INITIALIZED;
    }

    if (Channel >= COMM_NO_OF_CHANNELS)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_STATE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
    }

    if (State == NULL_PTR)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_STATE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
    }
    #endif

    *State = ComM_ChannelStruct[Channel].ChannelState_e;
    return E_OK;
}

#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h"

