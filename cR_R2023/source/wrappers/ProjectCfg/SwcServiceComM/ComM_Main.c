

#include "ComM_Priv.h"

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

FUNC(void,COMM_CODE) ComM_MainFunction_ComMChannel_Can_Network_Channel(void)
{
    ComM_LChannelMainFunction(0) ;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#if (COMM_PNC_GW_ENABLED == STD_ON)

#endif

#if (COMM_PNC_ENABLED == STD_ON)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

extern FUNC(void,COMM_CODE) ComM_EIRACallBack_COMM_BUS_TYPE_CAN(void);

FUNC(void,COMM_CODE) ComM_EIRACallBack_COMM_BUS_TYPE_CAN(void)
{
    ComM_EIRA_CallBack(0);
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif

