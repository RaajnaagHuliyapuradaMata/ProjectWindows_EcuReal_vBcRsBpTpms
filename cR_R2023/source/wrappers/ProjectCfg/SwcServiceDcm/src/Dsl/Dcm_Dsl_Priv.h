
#ifndef DCM_DSL_PRIV_H
#define DCM_DSL_PRIV_H

#define DCM_OBDSERVICEID_0x01                        (0x01u)
#define DCM_OBDSERVICEID_0x0A                        (0x0Au)
#define DCM_SERVICEID_DEFAULT_VALUE                  (0xFFu)
#define DCM_PDUID_DEFAULT_VALUE                      (0xFFu)
#define DCM_NEGATIVE_RESPONSE_LENGTH                 (0x03u)
#define DCM_SERVICEID_ADDEND                         (0x40u)

#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF) )
#define  DCM_SID_DIAGNOSTICSESSIONCONTROL            (0x10u)
#endif

#define Dcm_Lok_GetDslState()           (Dcm_DslState_u8)
#define Dcm_Lok_GetDslSubState()        (Dcm_DslSubState_u8)
#define Dcm_Lok_GetDslNextState()       (Dcm_DslNextState_u8)
#define Dcm_Lok_GetDslNextSubState()    (Dcm_DslNextSubState_u8)

#define Dcm_Lok_SetDslState(NewDslState_u8)                 (Dcm_DslState_u8 = NewDslState_u8)
#define Dcm_Lok_SetDslSubState(NewDslSubState_u8)           (Dcm_DslSubState_u8 = NewDslSubState_u8)
#define Dcm_Lok_SetDslNextState(NewDslNextState_u8)         (Dcm_DslNextState_u8 = NewDslNextState_u8)
#define Dcm_Lok_SetDslNextSubState(NewDslNextSubState_u8)   (Dcm_DslNextSubState_u8 = NewDslNextSubState_u8)

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
#define Dcm_Lok_GetDslPreemptionState()   (Dcm_DslPreemptionState_u8)
#define Dcm_Lok_SetDslPreemptionState(NewDslPreemptionState_u8)  (Dcm_DslPreemptionState_u8 = NewDslPreemptionState_u8)
#endif

#define Dcm_isRequestTobeProcessedByDSP(DcmRxPduId)    (Dcm_DslRxPduArray_ast[DcmRxPduId].Dcm_DslCopyRxData_b)

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"
extern VAR(uint8,AUTOMATIC) Dcm_DslState_u8;
extern VAR(uint8,AUTOMATIC) Dcm_DslSubState_u8;
extern VAR(uint8,AUTOMATIC) Dcm_DslNextState_u8;
extern VAR(uint8,AUTOMATIC) Dcm_DslNextSubState_u8;
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
extern VAR(uint8,AUTOMATIC) Dcm_DslPreemptionState_u8;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isForcePendingResponse(void)
{
    return (Dcm_DslTransmit_st.isForceResponsePendRequested_b);
}

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isProtocolStarted(void)
{
    return (Dcm_DsldGlobal_st.flgCommActive_b);
}

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isPagedBufferTxStarted(void)
{
    return (Dcm_DsldGlobal_st.flgPagedBufferTxOn_b);
}
#endif

#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isRxPduShared(VAR(PduIdType, AUTOMATIC) DcmRxPduId,
        VAR(uint8, AUTOMATIC) ServiceId)
{
    return((DcmRxPduId < (DCM_CFG_NUM_RX_PDUID-1u)) && (DcmRxPduId == DCM_CFG_SHARED_RX_PDUID) && \
            (ServiceId >= DCM_OBDSERVICEID_0x01) && (ServiceId <= DCM_OBDSERVICEID_0x0A));

}
#endif

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_Check_PendingResponseForKWP(void)
{
    VAR(boolean,AUTOMATIC) RetVal_b = TRUE;

#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF) && (DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))

    if((DCM_IS_KWPPROT_ACTIVE() != FALSE) && (Dcm_isFirstReponseSent_b != FALSE))
    {
        Dcm_KWPConfirmationForSplitResp(DCM_RES_POS_NOT_OK);
        Dcm_isFirstReponseSent_b = FALSE;
    }
    else
#endif
    {
        RetVal_b = FALSE;
    }

    return RetVal_b;
}

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE FUNC(boolean,DCM_CODE) Dcm_Lok_isProtocolPreemptionInitiated(void)
{
    return ((Dcm_Lok_GetDslPreemptionState() == DSL_SUBSTATE_STOP_PROTOCOL) || \
            (Dcm_Lok_GetDslPreemptionState() == DSL_SUBSTATE_STOP_ROE));
}
#endif

#endif
