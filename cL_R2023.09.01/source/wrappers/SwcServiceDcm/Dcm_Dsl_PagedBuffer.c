

#include "DcmCore_DslDsd_Inf.hpp"
#include "Rte_Dcm.hpp"

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
StatusType Dcm_PagedBufferTimerStatus_uchr;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
void (*Dcm_adrUpdatePage_pfct) (Dcm_MsgType PageBufPtr,Dcm_MsgLenType PageLen);
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

LOCAL_INLINE boolean Dcm_Lok_isPageLengthValid(Dcm_MsgLenType FilledPageLen)
{
   boolean isPageLenValid_b = FALSE;
    Dcm_DsdStatesType_ten stDsdStateTemp_en  = Dcm_Lok_GetDsdState();

   if((FilledPageLen <= (Dcm_DsldMsgContext_st.resMaxDataLen+1uL)) && \
            (stDsdStateTemp_en == DSD_CALL_SERVICE))
   {
        isPageLenValid_b = TRUE;
   }

    return isPageLenValid_b;
}

LOCAL_INLINE void DCM_Lok_PagedBufferTimerStart(void){
    DCM_TimerStart(Dcm_DsldGlobal_st.dataPagedBufferTimeout_u32, 0x00u
   ,                  Dcm_PagedBufferStartTick_u32, Dcm_PagedBufferTimerStatus_uchr)
}

LOCAL_INLINE void DCM_Lok_PagedBufferTimerProcess(void){
    DCM_TimerProcess(Dcm_DsldGlobal_st.dataPagedBufferTimeout_u32,Dcm_PagedBufferStartTick_u32
   ,           Dcm_PagedBufferTimerStatus_uchr)
}

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

static void Dcm_Lok_ProcessFirstPositiveResponse(void){

    Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[2] = Dcm_DsldGlobal_st.dataSid_u8 | DCM_SERVICEID_ADDEND;

    Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8 = &Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[2];

    Dcm_DsldGlobal_st.dataCurrentPageRespLength_u32++;

    Dcm_DsldGlobal_st.flgPagedBufferTxOn_b = TRUE;

    Dcm_Lok_SetDsdState(DSD_WAITFORTXCONF);

    Dcm_Lok_SetDslNextState((DSL_STATE_RESPONSE_TRANSMISSION));
    Dcm_Lok_SetDslNextSubState((DSL_SUBSTATE_SEND_FINAL_RESPONSE));

   if(Dcm_Lok_GetDslState() == DSL_STATE_WAITING_FOR_TXCONFIRMATION)
   {

   }

   else if((Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse !=FALSE) &&
        (Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 == 0))
   {

        DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32, 0x00u, Dcm_P2OrS3StartTick_u32
   ,               Dcm_P2OrS3TimerStatus_uchr)
   }
   else{

        Dcm_DsldPduInfo_st.SduDataPtr = &Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[0];
        Dcm_DsldPduInfo_st.SduLength  = (PduLengthType) Dcm_DslTransmit_st.TxResponseLength_u32;

        Dcm_Lok_SetDslState((DSL_STATE_PAGEDBUFFER_TRANSMISSION));
        Dcm_Lok_SetDslSubState((DSL_SUBSTATE_DATA_READY));
        Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 = 0x0u;

        Dcm_Lok_SetDslNextState((DSL_STATE_IDLE));
        Dcm_Lok_SetDslNextSubState((DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING));

        Dcm_Lok_SendResponse(&Dcm_DsldPduInfo_st);
   }
}

void Dcm_StartPagedProcessing (const Dcm_MsgContextType * pMsgContext )
{

   if( (FALSE != Dcm_Lok_CheckTotalResponseLength(pMsgContext->resDataLen)) && \
                                                                (Dcm_DslTransmit_st.TxResponseLength_u32 == 0x00uL))
   {

        Dcm_DslTransmit_st.TxResponseLength_u32 = pMsgContext->resDataLen+1uL;

        if(Dcm_adrUpdatePage_pfct != NULL_PTR)
        {
            (*Dcm_adrUpdatePage_pfct)(&Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].tx_buffer_pa[3]
   ,                            Dcm_DsldMsgContext_st.resMaxDataLen);
        }
   }
   else{
        DCM_DET_ERROR(DCM_PROCESSINGDONE_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)
   }
}

void Dcm_ProcessPage(Dcm_MsgLenType FilledPageLen )
{
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
   if(FALSE == Dcm_Lok_isProtocolPreemptionInitiated())
#endif
   {
        if(FALSE != Dcm_Lok_isPageLengthValid(FilledPageLen))
        {
            Dcm_DsldGlobal_st.dataCurrentPageRespLength_u32 = FilledPageLen;

            if(FALSE != Dcm_Lok_isPagedBufferTxStarted())
            {
                if(FilledPageLen != 0u)
                {

                    Dcm_Lok_SetDsdState(DSD_WAITFORTXCONF);

                    Dcm_Lok_SetDslState((DSL_STATE_PAGEDBUFFER_TRANSMISSION));
                    Dcm_Lok_SetDslSubState((DSL_SUBSTATE_DATA_READY));
                }
                else{

                    DCM_Lok_PagedBufferTimerStart();
                    Dcm_Lok_PagedBufferTimeout();
                }
            }
            else{
                Dcm_Lok_ProcessFirstPositiveResponse();
            }
        }
   }
}

void Dcm_Lok_PagedBufferTimeout(void){
   if(FALSE != Dcm_Lok_isPagedBufferTxStarted())
   {

        DCM_Lok_PagedBufferTimerProcess();

        if(FALSE != DCM_TimerElapsed(Dcm_DsldGlobal_st.dataPagedBufferTimeout_u32))
        {
            DCM_DET_ERROR(DCM_PAGEDBUFFER_ID , DCM_E_INTERFACE_TIMEOUT)

            SchM_Enter_Dcm_Global_NoNest();
            Dcm_Lok_SetDsdState(DSD_IDLE);
            Dcm_Lok_SetDslState((DSL_STATE_IDLE));
            Dcm_Lok_SetDslSubState((DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING));
            SchM_Exit_Dcm_Global_NoNest();

            DcmAppl_DcmCancelPagedBufferProcessing(Dcm_DsldGlobal_st.dataSid_u8);

            Dcm_DsldGlobal_st.flgPagedBufferTxOn_b = FALSE;
        }
   }
}

boolean Dcm_Lok_CheckTotalResponseLength(Dcm_MsgLenType TotalResLen_u32)
{
   boolean isRespLenValid_b = FALSE;

   if(TotalResLen_u32 <= ((Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].maxResponseLength_u32)-1uL))
   {
        isRespLenValid_b = TRUE;
   }

    return (isRespLenValid_b);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
