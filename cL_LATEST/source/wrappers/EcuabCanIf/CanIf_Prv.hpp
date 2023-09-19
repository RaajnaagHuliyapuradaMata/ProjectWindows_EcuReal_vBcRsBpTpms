#ifndef CANIF_PRV_H
#define CANIF_PRV_H

#include "CanIf.hpp"
#include "CanIf_Cbk.hpp"
#include "PduR.hpp"
#include "PduR_CanIf.hpp"
#include "CanTp.hpp"
#include "CanTp_Cbk.hpp"
#include "EcuM.hpp"
#include "CanIf_Cfg_SchM.hpp"
#include "CanSM_Cbk.hpp"

#define CANIF_PRV_INVALID_CHANNEL_MODE                                        0u
#define CANIF_PRV_VALID_CHANNEL_MODE                                          1u
#define CANIF_PRV_WAKEUP_MODE                                                 2u
#define CANIF_PRV_CANID_TYPE_MASK                                          0x0fu
#define CANIF_PRV_FOUR                                                        4u
#define CANIF_PRV_SIX                                                         6u
#define CANIF_PRV_SEVEN                                                       7u
#define CANIF_PRV_EIGHT                                                       8u
#define CANIF_INVALID_ID                                                 0xffffu
#define CANIF_CAN_STD_VAL                                                 0x7FFu
#define CANIF_CAN_XTD_VAL                                            0x1FFFFFFFu
#define CANIF_SET                                                           TRUE
#define CANIF_PRV_NO_UL                                                       0u
#define CANIF_PRV_MAX_BUFFER_SIZE                                             8u
#define CANIF_RESET                                                        FALSE
#define CANIF_READ_NOTIFSTATUS                                              0x10
#define CANIF_READ_DATA                                                     0x01
#define CANIF_READ_NOTIFSTATUS_DATA                                         0x11
#define CANIF_READ_NONE                                                     0x00
#define CANIF_STATIC (Type_SwcServiceCom_tIdPdu)(((uint32)1u << (uint8)((uint8)8u * (uint8)sizeof(Type_SwcServiceCom_tIdPdu)))-1u)
#define CANIF_MSB_BIT_RESET                                          0x3FFFFFFFu
#define CANIF_CANID_BIT_SHIFT                                                30u
#define CANIF_Ctrl_BIT_SHIFT                                                  4u
#define BIT_MASK_CTRL_MODE                                                 0X0Fu
#define BIT_MASK_PDU_MODE                                                  0XF0u
#define CANIF_ZERO                                                            0u
#define CANIF_ONE                                                             1u
#define CANIF_TWO                                                             2u
#define CANIF_THREE                                                           3u
#define CANIF_FOUR                                                            4u
#define CANID_MASK_DEFAULT                                           0x1FFFFFFFU
#define CANIF_PRV_CANIF_2MSB_MASK                                    0xC0000000u
#define CANIF_PRV_MSB_BIT_RESET                                      0x3FFFFFFFu
#define CANIF_MSB_BIT_RESET_STD                                          0x3FFFu
#define CANIF_GET_ONE_BYTE                                               0x00ffu
#define CANIF_DET_REPORT_ERROR_NOT_OK(CONDITION, API, ERROR)
#define CANIF_DET_REPORT_ERROR_VOID_RET(CONDITION, API, ERROR)
#define CANIF_DET_REPORT_ERROR(CONDITION, API, ERROR)
#define CANIF_DET_REPORT_ERROR_NOK(CONDITION, API, ERROR)
#define CANIF_DET_REPORT_ERROR_SCHM_EXIT_NOK(CONDITION, API, ERROR, SCHM_EXIT_FUNC)

typedef struct{
   uint8 Ctrl_Pdu_mode;
}CanIf_ControllerStateType;

extern   CONST(CanIf_CallbackFuncType,    CANIF_CONST         ) CanIf_Callback;
extern     VAR(CanIf_ControllerStateType, CANIF_VAR           ) CanIf_Lok_ControllerState_ast[];
extern     VAR(CanIf_NotifStatusType,     CANIF_VAR           ) CanIf_Lok_TxNotification_aen[];
extern     VAR(CanIf_NotifStatusType,     CANIF_VAR           ) CanIf_Lok_RxNotification_taen[CANIF_CFG_NUM_CANRXPDUIDS];
extern     VAR(boolean,                   CANIF_VAR           ) CanIf_Lok_InitStatus_b;

FUNC(void, CANIF_CODE) CanIf_Lok_ReadRxBuffer(
        P2VAR(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr
   ,  P2CONST(CanIf_Cfg_RxPduType_tst,      AUTOMATIC, CANIF_CFG_CONST)  RxPduCfgPtr
);

FUNC(Std_ReturnType, CANIF_CODE) CanIf_XCore_LocalCore_Transmit(
          VAR(Type_SwcServiceCom_tIdPdu,    AUTOMATIC                  ) CanIfTxSduId
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, CANIF_APPL_CONST) CanIfTxInfoPtr
);

extern FUNC(Std_ReturnType, CANIF_CODE)CanIf_XCore_LocalCore_TxConfirmation(
   P2CONST(CanIf_Cfg_TxPduConfig_tst, AUTOMATIC, CANIF_CFG_CONST) CanIf_TxPduConfig_pst
);

extern FUNC(Std_ReturnType, CANIF_CODE)CanIf_XCore_LocalCore_RxIndication(
      P2CONST(CanIf_Cfg_RxPduType_tst,      AUTOMATIC, CANIF_CFG_CONST) CanIf_RXPduConfig_pst
   ,  P2CONST(Type_SwcServiceCom_stInfoPdu, AUTOMATIC, CANIF_CFG_CONST) CanIf_ULPduinfo_pst
);

#endif