
#ifndef PDUR_DCM_UP_H
#define PDUR_DCM_UP_H

#include "PduR_Prv.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

#if defined(PDUR_CONFIG_SINGLE_TPTX_LO)
#define PduR_iDcmTransmitID(id)           (id)
#define PduR_iDcmTransmitFunc(id)           (PDUR_CONFIG_SINGLE_TPTX_LO(Transmit))
#else
#define PduR_iDcmTransmitID(id)           (PDUR_DCM_TX_BASE[(id)].loId)
#define PduR_iDcmTransmitFunc(id)           (PduR_loTransmitTable[(PDUR_DCM_TX_BASE[(id)].loTransmitID)].PduR_loTransmitFunc)

#endif

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
 #define PduR_aDcmTransmit(id, ptr)        PduR_dDcmTransmit((id), (ptr))
#else

 #define PduR_aDcmTransmit(id, ptr)        PduR_iDcmTransmitFunc(id)(PduR_iDcmTransmitID(id), (ptr))
#endif

#define PduR_rDcmTransmit(id, ptr)         PduR_aDcmTransmit((id), (ptr))

extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_MF_Dcm_Transmit_Func( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info );

#define PDUR_IH_Dcm_Transmit_Func    PDUR_DET_API(PduR_invId_UpTransmit)

#if defined(PDUR_CONFIG_SINGLE_TPCANCELTX_LO)
#define PduR_iDcmCancelTransmitID(id)           (id)
#define PduR_iDcmCancelTransmitFunc(id)         (PDUR_CONFIG_SINGLE_TPCANCELTX_LO(CancelTransmit))
#else
#define PduR_iDcmCancelTransmitID(id)           (PDUR_DCM_TX_BASE[(id)].loId)
#define PduR_iDcmCancelTransmitFunc(id)         (PduR_loCancelTransmitTable[(PDUR_DCM_TX_BASE[(id)].loCancelTransmitID)].PduR_loCancelTransmitFunc)
#endif

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif
