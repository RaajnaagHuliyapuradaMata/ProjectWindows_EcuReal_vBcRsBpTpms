#ifndef CANTP_CFG_H
#define CANTP_CFG_H

#include "ComStack_Types.h"
#if (!defined(COMTYPE_AR_RELEASE_MAJOR_VERSION) || (COMTYPE_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(COMTYPE_AR_RELEASE_MINOR_VERSION) || (COMTYPE_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#define CANTP_VENDOR_ID                     (6u)
#define CANTP_MODULE_ID                     (35u)
#define CANTP_INSTANCE_ID                   (0u)

#define CANTP_AR_RELEASE_MAJOR_VERSION      (4u)
#define CANTP_AR_RELEASE_MINOR_VERSION      (2u)
#define CANTP_AR_RELEASE_REVISION_VERSION   (2u)
#define CANTP_SW_MAJOR_VERSION              (8u)
#define CANTP_SW_MINOR_VERSION              (0u)
#define CANTP_SW_PATCH_VERSION              (0u)

#define CANTP_ON                            (1u)
#define CANTP_OFF                           (0u)
#define CANTP_DEV_ERROR_DETECT              CANTP_OFF
#define CANTP_VERSION_INFO_API 				CANTP_ON
#define CANTP_READ_PARAMETER_API     	   	CANTP_OFF
#define CANTP_CHANGE_PARAMETER_API          CANTP_OFF
#define CANTP_TRIGGER_TRANSMIT_API          CANTP_OFF
#define CANTP_TX_BURST_MODE                 CANTP_OFF
#define CANTP_STRICT_BSCRTIMEOUT_CHECK      CANTP_OFF
#define CANTP_STRICTDLCCHECK				CANTP_OFF
#define CANTP_PAGE_CONFIRMATION             CANTP_OFF
#define CANTP_LEGACY_SHARED_FC_SUPPORT      CANTP_OFF
#define CANTP_FD_CALLOUT_SUPPORT            CANTP_OFF
#define CANTP_CANFD_SUPPORT                 CANTP_ON
#define CANTP_SCHM_SUPPORT                  CANTP_OFF
#define CANTP_FC_DISABLE_SUPPORT            CANTP_OFF
#define CANTP_CANTPLITE_SUPPORT             CANTP_OFF
#define CANTP_DYNAMIC_FC_SUPPORT            CANTP_OFF
#define CANTP_CYCLE_COUNTER                 CANTP_ON
#define CanTp_FdCallOut
#define CANTP_PRE_COMPILE                   (0u)
#define CANTP_POST_BUILD_SELECTABLE         (1u)
#define CANTP_POST_BUILD_LOADABLE           (2u)
#define CANTP_VARIANT                       CANTP_PRE_COMPILE
#define CANTP_NO_OF_CANTPCONFIGSETS         (1u)
#define CANTP_BURST_QUEUE_SIZE              (1u)
#define CANTP_MAX_RX_CONNECTION_SIZE        (2u)
#define CANTP_MAX_TX_CONNECTION_SIZE        (1u)
#define CANTP_MAX_NO_OF_TX_NPDU                 (1u)
#define CANTP_MAX_CHANNEL_SIZE              (2u)
#define CANTP_MAX_NPDU_LENGTH               (64u)
#define CANTP_DEFAULT_STMIN_TICKS           (0u)
#define CANTP_INVALID_STMIN_TICKS           (14u)
#define CANTP_PADDING_BYTE                  (0xAAu)

#define CanTpConf_CanTpTxNSdu_UdsOnCan_Tx_Phy_PduR2CanTp                        ((PduIdType)0)
#define CanTpConf_CanTpRxNSdu_UdsOnCan_Rx_Func_CanTp2PduR                       ((PduIdType)0)
#define CanTpConf_CanTpRxNSdu_UdsOnCan_Rx_Phys_CanTp2PduR                       ((PduIdType)1)
#define CanTpConf_CanTpRxNPdu_Func_CanIf2CanTP                                  ((PduIdType)0)
#define CanTpConf_CanTpRxNPdu_Phys_CanIf2CanTp                                  ((PduIdType)1)
#define CanTpConf_CanTpRxFcNPdu_Phys_CanIf2CanTp                                ((PduIdType)1)
#define CanTpConf_CanTpTxNPdu_Phys_CanTp2CanIf                                  ((PduIdType)0)
#define CanTpConf_CanTpTxFcNPdu_Phys_CanTp2CanIf                                ((PduIdType)0)

extern const Type_CfgSwcServiceCanTp_st CanTp_Config;

#define CanTp_Cfg_DlcCheck(SduLength, ExpectedLength) (((SduLength) >= (ExpectedLength)) ? (E_OK) : (E_NOT_OK))
#define CanTp_Cfg_GetUsToTicks(Us)                    (((Us) * 100u)/1000000u)

#endif
