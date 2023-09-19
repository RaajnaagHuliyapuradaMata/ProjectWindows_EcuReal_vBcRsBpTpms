#include "Std_Types.hpp"

#include "CanIf_Prv.hpp"

#define CANIF_START_SEC_CODE
#include "CanIf_MemMap.hpp"
FUNC(void, CANIF_CODE) CanIf_RxIndication_Internal(
      P2CONST(Can_HwType,                   AUTOMATIC, CANIF_APPL_DATA) Mailbox
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
){
     P2VAR(CanIf_NotifStatusType,        AUTOMATIC, AUTOMATIC      ) RxNotifPtr_pen     = CanIf_Lok_RxNotification_taen;
       VAR(Can_IdType,                   AUTOMATIC                 ) CanIdNoIdType_t    = Mailbox->CanId & CANIF_PRV_MSB_BIT_RESET;
       VAR(uint8,                        AUTOMATIC                 ) CanIdPduType_u8    = (uint8)((Mailbox->CanId)>>CANIF_CANID_BIT_SHIFT);
   P2CONST(CanIf_Cfg_Hrhtype_tst,        AUTOMATIC, CANIF_CFG_CONST) HrhCfg_pcst        = CanIf_Lok_ConfigSet_tpst->HrhConfig_pcst + CanIf_Lok_ConfigSet_tpst->HrhPduIdTable_Ptr[Mailbox->Hoh];
     P2VAR(CanIf_ControllerStateType,    AUTOMATIC, AUTOMATIC      ) ControllerState_ps = CanIf_Lok_ControllerState_ast + Mailbox->ControllerId;
       VAR(uint8,                        AUTOMATIC                 ) ModeChkStatus      = CANIF_PRV_INVALID_CHANNEL_MODE;
       VAR(boolean,                      AUTOMATIC                 ) IdFound_b          = FALSE;
       VAR(uint8,                        AUTOMATIC                 ) Index_u8;
       VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC                 ) PduId_qu8;
   P2CONST(CanIf_Cfg_RxPduType_tst,      AUTOMATIC, CANIF_CFG_CONST) RxPduCfg_pcst;
       VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC                 ) PduInfoTemp_tst;
       VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC                 ) ULPduInfoTyp_tst;

   if(
         (uint8)CANIF_CS_STARTED
      == (
               (
                     ControllerState_ps->Ctrl_Pdu_mode
                  &  BIT_MASK_PDU_MODE
               )
            >> CANIF_Ctrl_BIT_SHIFT
         )
   ){
      if(
            ((uint8)CANIF_TX_OFFLINE == (ControllerState_ps->Ctrl_Pdu_mode & BIT_MASK_CTRL_MODE))
         || ((uint8)CANIF_ONLINE     == (ControllerState_ps->Ctrl_Pdu_mode & BIT_MASK_CTRL_MODE))
      ){
         ModeChkStatus = CANIF_PRV_VALID_CHANNEL_MODE;
         Index_u8 = 0;
         switch(
            HrhCfg_pcst->HrhInfo_e
         ){
            case CANIF_PRV_FULL_E:
               PduId_qu8 = HrhCfg_pcst->PduIdx_t;
               do{
                  RxPduCfg_pcst = CanIf_Lok_ConfigSet_tpst->RxPduConfig_pcst + PduId_qu8;
                  if(
                        (
                               (RxPduCfg_pcst->CanIdtype_u8 &  CANIF_PRV_CANID_TYPE_MASK)
                           == ((RxPduCfg_pcst->CanIdtype_u8 >> CANIF_PRV_FOUR) & CanIdPduType_u8)
                        )
                     && (CanIdNoIdType_t == RxPduCfg_pcst->RxPduCanId)
                  ){
                     IdFound_b = TRUE;
                     break;
                  }
                  PduId_qu8++;
                  Index_u8++;
               }while(
                     HrhCfg_pcst->NumRxPdus_u32
                  >= Index_u8
               );
               break;

            default:
               IdFound_b = FALSE;
               break;
         }
      }
   }
   if(
         IdFound_b
      == TRUE
   ){
      PduInfoTemp_tst.SduLength   = PduInfoPtr->SduLength;
      ULPduInfoTyp_tst.SduLength  = PduInfoTemp_tst.SduLength;
      PduInfoTemp_tst.SduDataPtr  = (uint8*)(PduInfoPtr->SduDataPtr);
      ULPduInfoTyp_tst.SduDataPtr = PduInfoTemp_tst.SduDataPtr;
      if(
            (CANIF_READ_NOTIFSTATUS_DATA == RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8)
         || (CANIF_READ_NOTIFSTATUS      == RxPduCfg_pcst->RxPduReadNotifyReadDataStatus_u8)
      ){
         *(RxNotifPtr_pen + PduId_qu8) = CANIF_TX_RX_NOTIFICATION;
      }
      if(
            RxPduCfg_pcst->IndexForUL_u8
         != CANIF_PRV_NO_UL
      ){
         (void)CanIf_XCore_LocalCore_RxIndication(
               RxPduCfg_pcst
            ,  &ULPduInfoTyp_tst
         );
      }
   }
}

FUNC(Std_ReturnType, CANIF_CODE)CanIf_XCore_LocalCore_RxIndication(
      P2CONST(CanIf_Cfg_RxPduType_tst,      AUTOMATIC, CANIF_CFG_CONST) CanIf_RXPduConfig_pst
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, CANIF_CFG_CONST) CanIf_ULPduinfo_pst
){
   CanIf_Lok_ConfigSet_tpst->RxAutosarUL_Ptr[CanIf_RXPduConfig_pst->IndexForUL_u8].CanIfRxPduIndicationName(
         CanIf_RXPduConfig_pst->RxPduTargetId_t
      ,  CanIf_ULPduinfo_pst
   );
   return E_OK;
}
#define CANIF_STOP_SEC_CODE
#include "CanIf_MemMap.hpp"

