#ifndef CANSM_CBK_H
#define CANSM_CBK_H

#include "CanSM_Cfg.hpp"
#include "CanIf.hpp"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.hpp"

extern FUNC(void, CANSM_CODE) CanSM_ControllerBusOff(VAR(uint8, AUTOMATIC) ControllerId);
extern FUNC(void, CANSM_CODE) CanSM_ControllerModeIndication(
      VAR(uint8, AUTOMATIC) ControllerId
   ,  VAR(Type_EcuabCanIf_eModeController, AUTOMATIC) ControllerMode
);

#if(CANSM_CFG_TRCV_CANIF_SUPPORT == STD_ON)
extern FUNC(void, CANSM_CODE) CanSM_TransceiverModeIndication(
      VAR(uint8, AUTOMATIC) TransceiverId
   ,  VAR(CanTrcv_TrcvModeType, AUTOMATIC) TransceiverMode
);
#endif

#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
extern FUNC(void, CANSM_CODE) CanSM_ClearTrcvWufFlagIndication         (VAR(uint8, AUTOMATIC) Transceiver);
extern FUNC(void, CANSM_CODE) CanSM_CheckTransceiverWakeFlagIndication (VAR(uint8, AUTOMATIC) Transceiver);
extern FUNC(void, CANSM_CODE) CanSM_ConfirmPnAvailability              (VAR(uint8, AUTOMATIC) TransceiverId);
#endif

#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.hpp"

#endif

