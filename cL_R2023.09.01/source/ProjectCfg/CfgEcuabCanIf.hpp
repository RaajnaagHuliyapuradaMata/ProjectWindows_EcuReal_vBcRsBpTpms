#pragma once
/******************************************************************************/
/* File   : CfgEcuabCanIf.h                                                   */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "ComStack_Cfg.hpp"
#include "Can_GeneralTypes.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define CANIF_XCORE_CFG_ENABLED                                        (STD_OFF)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef enum{
      CANIF_PRV_FULL_E
   ,  CANIF_PRV_BASIC_RANGE_E
   ,  CANIF_PRV_BASIC_LIST_E
}CanIf_Lok_HrhType_ten;

typedef struct{
   CanIf_Lok_HrhType_ten HrhInfo_e;
   PduIdType             PduIdx_t;
   uint32                NumRxPdus_u32;
   boolean               HrhRangeMask_b;
   uint8                 ControllerId_u8;
}CanIf_Cfg_Hrhtype_tst;

typedef struct{
   uint8       RxPduReadNotifyReadDataStatus_u8;
   uint8_least IndexForUL_u8;
   uint8       CanIdtype_u8;
   uint8       RxPduDlc_u8;
   Can_IdType  RxPduCanId;
   PduIdType   Hrhref_t;
   PduIdType   RxPduTargetId_t;
}CanIf_Cfg_RxPduType_tst;

typedef struct{
   uint8   CtrlId;
   uint8   CtrlCanCtrlRef;
   boolean CtrlWakeupSupport;
}CanIf_Cfg_CtrlConfig_tst;

typedef struct{
   const CanIf_Cfg_CtrlConfig_tst*   CanIf_CtrlConfigPtr;
         Can_HwHandleType            CanObjectId;
}CanIf_Cfg_HthConfig_tst;

typedef struct{
   const CanIf_Cfg_HthConfig_tst* CanIf_HthConfigPtr;
}CanIf_Cfg_TxBufferConfig_tst;

typedef enum{
      STANDARD_CAN
   ,  STANDARD_FD_CAN
   ,  EXTENDED_CAN
   ,  EXTENDED_FD_CAN
}CanIf_Cfg_TxPduCanIdType_ten;

typedef enum{
      CANIF_NO_UL
   ,  CAN_NM
   ,  CAN_TP
   ,  CAN_TSYN
   ,  J1939NM
   ,  J1939TP
   ,  PDUR
   ,  XCP
   ,  CDD
   ,  USER
   ,  MAX_USER_TYPE
}CanIf_Cfg_UserType_ten;

typedef struct{
   const CanIf_Cfg_TxBufferConfig_tst* CanIf_TxBufferConfigPtr;
   PduIdType                           TxPduId;
   PduIdType                           TxPduTargetPduId;
   PduIdType                           TxPduType;
   CanIf_Cfg_TxPduCanIdType_ten        TxPduCanIdType;
   CanIf_Cfg_UserType_ten              TxPduTxUserUL;
   void (*UserTxConfirmation) (PduIdType TxPduTargetPduId);
   Can_IdType                          TxPduCanId;
   boolean                             TxPduReadNotifyStatus;
   boolean                             TxTruncEnabled_b;
   uint8                               TxPduLength_u8;
}CanIf_Cfg_TxPduConfig_tst;

typedef struct{
   void (*CanIfRxPduIndicationName) (PduIdType RxPduTargetId_t, const PduInfoType * CanIf_ULPduinfo_pst );
}CanIf_RxCbk_Prototype;

typedef struct{
   P2CONST(CanIf_Cfg_Hrhtype_tst,   TYPEDEF, CANIF_CFG_CONST) HrhConfig_pcst;
   P2CONST(CanIf_Cfg_RxPduType_tst, TYPEDEF, CANIF_CFG_CONST) RxPduConfig_pcst;
   VAR(PduIdType,                   TYPEDEF)                  NumCanRxPduId_t;
   VAR(uint8,                       TYPEDEF)                  NumCanCtrl_u8;
   VAR(PduIdType,                   TYPEDEF)                  NumCddRxPdus_t;
   const uint16*                                              RxPduIdTable_Ptr;
   const uint16*                                              HrhPduIdTable_Ptr;
   VAR(uint8,                       TYPEDEF)                  CfgSetIndex_u8;
   const CanIf_Cfg_TxPduConfig_tst*                           CanIf_TxPduConfigPtr;
   const CanIf_Cfg_TxBufferConfig_tst*                        CanIf_TxBufferConfigPtr;
   const CanIf_Cfg_CtrlConfig_tst*                            CanIf_CtrlConfigPtr;
         uint32                                               NumOfTxPdus;
         uint32                                               NumOfTxBuffers;
   const uint16*                                              TxPduIdTable_Ptr;
   const uint8*                                               CtrlIdTable_Ptr;
   const CanIf_RxCbk_Prototype*                               RxAutosarUL_Ptr;
}Type_CfgEcuabCanIf_st;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/
#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.hpp"
extern const Type_CfgEcuabCanIf_st CfgEcuabCanIf_st;
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.hpp"

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
