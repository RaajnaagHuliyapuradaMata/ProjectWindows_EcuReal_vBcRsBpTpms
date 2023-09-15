#include "Std_Types.hpp"

#include "CanSM_Prv.hpp"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"
FUNC(void, CANSM_CODE) CanSM_TxTimeoutException(VAR(NetworkHandleType, AUTOMATIC) Channel){
   VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CanSM_CurrNwMode_en;
   VAR(CanSM_BusOffRecoveryStateType_ten, AUTOMATIC) CanSM_CurrBORMode_en;
   CANSM_REPORT_ERROR((CanSM_Init_ab == (boolean)CANSM_UNINITED)
   ,                          ((uint8)CANSM_TXTIMEOUTEXCEPTION_SID)
   ,                          ((uint8)CANSM_E_UNINIT))
   Channel = CanSM_GetHandle(Channel);
   CANSM_REPORT_ERROR(((uint8)Channel >= (CfgSwcServiceCanSM_castConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8))
   ,                           ((uint8)CANSM_TXTIMEOUTEXCEPTION_SID)
   ,                           ((uint8)CANSM_E_INVALID_NETWORK_HANDLE))
   CanSM_CurrNwMode_en = CanSM_CurrNw_Mode_en[Channel];
   CanSM_CurrBORMode_en = CanSM_currBOR_State_en[Channel];
   if((CanSM_CurrNwMode_en==CANSM_BSM_S_FULLCOM) &&(CanSM_CurrBORMode_en==CANSM_S_NO_BUS_OFF)){
        CanSM_CurrNw_Mode_en[Channel] = CANSM_BSM_S_TX_TIMEOUT_EXCEPTION;

   	CanSM_TxTimeoutexception_Substates_en[Channel] = CANSM_TxTimeoutException_S_CC_STOPPED;
   }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"

