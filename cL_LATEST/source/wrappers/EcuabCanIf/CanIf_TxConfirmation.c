#include "Std_Types.hpp"

#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
void CanIf_TxConfirmation(
   Type_SwcServiceCom_tIdPdu CanTxPduId
){
       VAR(uint16,                    AUTOMATIC                 ) ltxPduCustId_t     = CanIf_Lok_ConfigSet_tpst->TxPduIdTable_Ptr[CanTxPduId];
   P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) lTxPduConfig_pst   = (CanIf_Lok_ConfigSet_tpst->CanIf_TxPduConfigPtr) + ltxPduCustId_t;
   P2CONST(CanIf_Cfg_CtrlConfig_tst,  AUTOMATIC, CANIF_CFG_CONST) lCtrlConfig_pst    = lTxPduConfig_pst->CanIf_TxBufferConfigPtr->CanIf_HthConfigPtr->CanIf_CtrlConfigPtr;
       VAR(uint8,                     AUTOMATIC                 ) lControllerId_u8   = lCtrlConfig_pst->CtrlId;
     P2VAR(CanIf_ControllerStateType, AUTOMATIC, AUTOMATIC      ) lControllerState_p = CanIf_Lok_ControllerState_ast + lControllerId_u8;
     P2VAR(CanIf_NotifStatusType,     AUTOMATIC, AUTOMATIC      ) lTxNotifPtr        = CanIf_Lok_TxNotification_aen;

   if(
         FALSE
      != lTxPduConfig_pst->TxPduReadNotifyStatus
   ){
      *(lTxNotifPtr + CanTxPduId) = CANIF_TX_RX_NOTIFICATION;
   }

   if(
         (
               NULL_PTR
            != lTxPduConfig_pst->UserTxConfirmation
         )
      && (
               (
                     lControllerState_p->Ctrl_Pdu_mode
                  &  BIT_MASK_CTRL_MODE
               )
            == (uint8)CANIF_ONLINE
         )
   ){
      (void)CanIf_XCore_LocalCore_TxConfirmation(
         lTxPduConfig_pst
      );
   }
}

FUNC(Std_ReturnType, CANIF_CODE)CanIf_XCore_LocalCore_TxConfirmation(
   P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) CanIf_TxPduConfig_pst
){
   CanIf_TxPduConfig_pst->UserTxConfirmation(
      CanIf_TxPduConfig_pst->TxPduTargetPduId
   );
   return E_OK;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"
