
#include "Dcm_Cfg_Prot.h"
#include "DcmCore_Main_Inf.h"
#include "Rte_Dcm.h"
#include  "DcmDspUds_Seca_Prv.h"
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"
#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)

const Dcm_ConfigType Dcm_Config[DCM_PRV_MAXNUM_OF_CONFIG]={{DCM_CFG_CONFIGSET1},{DCM_CFG_CONFIGSET2},{DCM_CFG_CONFIGSET3},{DCM_CFG_CONFIGSET4},
                                      {DCM_CFG_CONFIGSET5},{DCM_CFG_CONFIGSET6},{DCM_CFG_CONFIGSET7},{DCM_CFG_CONFIGSET8}};
#endif
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

#if (DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)
static void Dcm_Lok_RestoreDddId(void)
{
    Dcm_RestoreDddiReturn_ten dataRetValFromNvMStorage_u8;
    uint32 nrNumOfDddIds;
    uint32 idxLoop_u32;

    nrNumOfDddIds = Dcm_DddiCalculateTableSize_u16();

    for(idxLoop_u32 = 0; idxLoop_u32<nrNumOfDddIds; idxLoop_u32++)
    {
        dataRetValFromNvMStorage_u8 = DcmAppl_DcmReadDddiFromNvM(&Dcm_DDDIBaseConfig_cast[idxLoop_u32],
                Dcm_DDDIBaseConfig_cast[idxLoop_u32].dataDddId_u16);
        if(dataRetValFromNvMStorage_u8 == DCM_DDDI_READ_NOT_OK)
        {

            DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_NO_READ_ACCESS )
        }
    }
}
#endif

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
static void Dcm_Lok_ROEInit(void)
{
    uint8_least idxIndex_qu8;
    const Dcm_Dsld_protocol_tableType * adrProtocol_pcst;

    adrProtocol_pcst = Dcm_DsldProtocol_pcst;

    for(idxIndex_qu8= DCM_CFG_NUM_PROTOCOL; idxIndex_qu8!=0x00u; idxIndex_qu8--)
    {

        if(adrProtocol_pcst->roe_info_pcs != NULL_PTR)
        {

            Dcm_Dsd_ServiceIni(adrProtocol_pcst->roe_info_pcs->servicetable_Id_u8);
        }

        adrProtocol_pcst++;
    }

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
    Dcm_RestoreROEDtcEvents();
#endif
#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)
    Dcm_RestoreROEDidEvents();
#endif
#endif

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
    Dcm_DsdRoe2State_en = DSD_IDLE;
#endif
}
#endif

#if (DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
static void Dcm_Lok_RdpiInit(void)
{
    const Dcm_Dsld_protocol_tableType * adrProtocol_pcst;

    adrProtocol_pcst = Dcm_DsldProtocol_pcst;

    if(adrProtocol_pcst->rdpi_info_pcs != NULL_PTR)
    {
        Dcm_DsldPeriodicSchedulerIni();
    }
}
#endif

#if (DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
static void Dcm_Lok_WarmStart(void)
{
    Dcm_EcuStartModeType dataRetGetProgCond_u8;

    dataRetGetProgCond_u8 = Dcm_GetProgConditions(&Dcm_ProgConditions_st);

    if(dataRetGetProgCond_u8 == DCM_WARM_START)
    {

        Dcm_ReadyForBoot_b = TRUE;

        if (( Dcm_ProgConditions_st.StoreType == DCM_WARMREQUEST_TYPE ) || ( Dcm_ProgConditions_st.StoreType == DCM_WARMRESPONSE_TYPE ))
        {

            Dcm_CheckActiveDiagnosticStatus(Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_GetActiveConnectionIdx_u8()].channel_idx_u8].ComMChannelId);
        }
    }
    else
    {

        Dcm_ReadyForBoot_b = FALSE;
        Dcm_ProgConditions_st.StoreType       = DCM_NOTVALID_TYPE;
    }
}
#endif

#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
static void Dcm_Lok_SecaInit(void)
{

#if (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

    Dcm_Dsp_SecaGlobaltimer_u32 = 0x0;
#endif

#if (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)

    Dcm_Dsp_RestoreDelayCount();
#if (DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
    Dcm_Dsp_SecaClearSeed();
#endif
#endif
#endif

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)

    Dcm_DslDsdRestoreSecaTimer();
#endif
}
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) && (DCM_CFG_NUM_IOCBI_DIDS != 0x00u))
static void Dcm_Lok_IOCBIIinit(void)
{
    uint16 idxDid_u16;
    uint16 idxSig_u16;
    uint16 cntrIocbiDid_u16 = 0;
    uint16 DIDTablesize;

    DIDTablesize = Dcm_DIDcalculateTableSize_u16();

    for(idxDid_u16=0; idxDid_u16<DIDTablesize; idxDid_u16++)
    {
        for(idxSig_u16=0; idxSig_u16<Dcm_DIDConfig[idxDid_u16].nrSig_u16; idxSig_u16++)
        {

            if((Dcm_DIDConfig[idxDid_u16].adrExtendedConfig_pcst->dataSessBitMask_u32!=0x00u) && (Dcm_DspDid_ControlInfo_st[Dcm_DspDataInfo_st[Dcm_DIDConfig[idxDid_u16].adrDidSignalConfig_pcst[idxSig_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16].idxDcmDspIocbiInfo_u16>0))
            {
                break;
            }
        }
        if(idxSig_u16<Dcm_DIDConfig[idxDid_u16].nrSig_u16)
        {

            DcmDsp_IocbiStatus_array[cntrIocbiDid_u16].idxindex_u16 = idxDid_u16;
            DcmDsp_IocbiStatus_array[cntrIocbiDid_u16].IocbiStatus_en = DCM_IOCBI_IDLESTATE;
            cntrIocbiDid_u16++;
#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)
            if((TRUE == Dcm_DIDConfig[idxDid_u16].AtomicorNewSRCommunication_b) && \
               ((USE_ATOMIC_SENDER_RECEIVER_INTERFACE == Dcm_DIDConfig[idxDid_u16].didUsePort_u8) || (USE_ATOMIC_SENDER_RECEIVER_INTERFACE_AS_SERVICE == Dcm_DIDConfig[idxDid_u16].didUsePort_u8)))
            {

                (void)(*(IOControlrequest_pfct)(Dcm_DIDConfig[idxDid_u16].ioControlRequest_cpv))(DCM_IOCBI_INIT,NULL_PTR,DCM_VALUE_NULL,DCM_VALUE_NULL,DCM_INITIAL,NULL_PTR);
            }
#endif
        }
    }
}
#endif

static void Dcm_Lok_UDSinit(void)
{
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))
    uint16_least idxLoop_qu16;
#endif

    Dcm_DsldGlobal_st.idxActiveSession_u8 = 0x0u;
    Dcm_CC_ActiveSession_u8 =  DCM_DEFAULT_SESSION;

    Dcm_DsldGlobal_st.idxActiveSecurity_u8 = DCM_SEC_LEV_LOCKED;

    Dcm_DsldTimer_st.dataTimeoutP2max_u32    =  DCM_CFG_DEFAULT_P2MAX_TIME;
    Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 =  DCM_CFG_DEFAULT_P2STARMAX_TIME;

    Dcm_ActiveDiagnosticState_en = DCM_COMM_ACTIVE;

    DcmAppl_DcmUpdateRxTable();

    Dcm_isInitialised_b = FALSE;

    Dcm_CurProtocol_u8 = DCM_NO_ACTIVE_PROTOCOL;
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
    Dcm_CurOBDProtocol_u8 = DCM_NO_ACTIVE_PROTOCOL;
#endif

    Dcm_isStopProtocolInvoked_b = FALSE;

    Dcm_Lok_ResetDefaultSessionRequestFlag();

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))
#if (DCM_CFG_RC_NUMRIDS > 0u)

    for(idxLoop_qu16 = 0;idxLoop_qu16<DCM_CFG_RC_NUMRIDS;idxLoop_qu16++)
    {
        Dcm_RoutineStatus_aen[idxLoop_qu16] = DCM_ROUTINE_IDLE;
    }
#endif
#if (DCM_CFG_RC_RANGE_NUMRIDS > 0u)

    for(idxLoop_qu16 = 0;idxLoop_qu16<DCM_CFG_RC_RANGE_NUMRIDS;idxLoop_qu16++)
    {
        Dcm_RoutineRangeStatus_aen[idxLoop_qu16] = DCM_ROUTINE_IDLE;
    }
#endif
#endif

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
    Dcm_Lok_ROEInit();
#endif

#if (DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
    Dcm_Lok_RdpiInit();
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) && (DCM_CFG_NUM_IOCBI_DIDS != 0x00u))
    Dcm_Lok_IOCBIIinit();
#endif
}

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
static void Dcm_Lok_BufqueueInit(void)
{

    Dcm_DsldGlobal_st.adrBufferPtr_pu8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].rx_mainBuffer_pa;

    Dcm_QueueStructure_st.idxBufferIndex_u8 = 1;

    Dcm_QueueStructure_st.Dcm_QueHandling_en = DCM_QUEUE_IDLE;
}
#endif

#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )
static void Dcm_Lok_ActiveConfigSet(void)
{
    if ( Dcm_ActiveConfigSet_Ptr != NULL_PTR )
    {
        if((Dcm_ActiveConfigSet_Ptr->ConfigSetId) > DCM_PRV_MAXNUM_OF_CONFIG)
        {

            Dcm_ActiveConfiguration_u8 = 1 ;
        }
        else
        {

            Dcm_ActiveConfiguration_u8 = (1 << (Dcm_ActiveConfigSet_Ptr->ConfigSetId)) ;
        }
    }
    else
    {

        Dcm_ActiveConfiguration_u8 = 1 ;
    }
}
#endif

void Dcm_Init(const Dcm_ConfigType * ConfigPtr )
{
    PduIdType idxPduIndex_u8;
    uint8 idxIndex_u8;

#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )
    Dcm_ActiveConfigSet_Ptr = ConfigPtr;
#else
    (void)ConfigPtr;
#endif

    Dcm_DsldProtocol_pcst      = Dcm_Dsld_Conf_cs.protocol_table_pcs;
    Dcm_DsldRxTable_pcu8       = Dcm_Dsld_Conf_cs.ptr_rxtable_pca;
    Dcm_DsldConnTable_pcst     = Dcm_Dsld_Conf_cs.ptr_conntable_pcs;
    Dcm_DsldSessionTable_pcu8 = Dcm_Dsld_Conf_cs.session_lookup_table_pcau8;

    Dcm_Lok_UDSinit();

#if (DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)

    Dcm_Lok_RestoreDddId();
#endif

    for(idxIndex_u8 = 0;idxIndex_u8<DCM_NUM_COMM_CHANNEL;idxIndex_u8++)
    {
        Dcm_active_commode_e[idxIndex_u8].ComMState =   DCM_DSLD_NO_COM_MODE;
        Dcm_active_commode_e[idxIndex_u8].ComMChannelId= Dcm_Dsld_ComMChannelId_acu8[idxIndex_u8];
    }

    Dcm_DsldSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[0].ptr_service_table_pcs;

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)

    Dcm_DsldGlobal_st.dataNewRxPduId_u8      =  0xff;
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
    Dcm_DsldGlobal_st.dataPassRxPduId_u8     =  0xff;
#endif

    Dcm_Lok_SetDslPreemptionState((DSL_STATE_IDLE));
#endif

    for(idxPduIndex_u8=0x0; idxPduIndex_u8 < DCM_CFG_NUM_RX_PDUID;idxPduIndex_u8++)
    {

        Dcm_DslRxPduArray_ast[idxPduIndex_u8].Dcm_DslServiceId_u8   = DCM_SERVICEID_DEFAULT_VALUE;

        Dcm_DslRxPduArray_ast[idxPduIndex_u8].Dcm_DslFuncTesterPresent_b      = FALSE;
    }

    Dcm_Lok_SetDsdState((DSD_IDLE));

    Dcm_Lok_SetDslState((DSL_STATE_IDLE));
    Dcm_Lok_SetDslSubState((DSL_SUBSTATE_S3_OR_P3_TIMEMONITORING));

    Dcm_DsldGlobal_st.flgCommActive_b       =  FALSE;
    Dcm_DsldGlobal_st.idxCurrentProtocol_u8 =  0x00u;
    Dcm_DsldGlobal_st.nrActiveConn_u8      =  0x00u;

    Dcm_DslTransmit_st.isForceResponsePendRequested_b   =  FALSE;
    Dcm_SrvOpstatus_u8 = DCM_INITIAL;
    Dcm_ExtSrvOpStatus_u8 = DCM_INITIAL;
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
    Dcm_Lok_SetOBDState((DCM_OBD_IDLE));
    Dcm_OBDGlobal_st.flgCommActive_b = FALSE;
    Dcm_OBDGlobal_st.idxCurrentProtocol_u8 = 0x00;
    Dcm_OBDGlobal_st.nrActiveConn_u8 = 0x00u;
    Dcm_OBDSrvOpstatus_u8 = DCM_INITIAL;
    Dcm_OBDExtSrvOpStatus_u8 = DCM_INITIAL;
    Dcm_ObdSendTxConfirmation_b = FALSE;

#endif

#if( DCM_BUFQUEUE_ENABLED!= DCM_CFG_OFF)
    Dcm_Lok_BufqueueInit();
#endif

#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )
    Dcm_Lok_ActiveConfigSet();
#endif

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)

    Dcm_DsldGlobal_st.flgPagedBufferTxOn_b = FALSE;
#endif

#if (DCM_CFG_OSTIMER_USE != FALSE)
    Dcm_P2OrS3StartTick_u32 = 0x00u;
#if (DCM_PARALLELPROCESSING_ENABLED != DCM_CFG_OFF)
    Dcm_OBDP2OrS3StartTick_u32 = 0x00;
#endif
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
    Dcm_TimerStartTick_u32 = 0x00u;
#endif
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    Dcm_PagedBufferStartTick_u32 = 0x00u;
#endif
    Dcm_CurrTick_u32 = 0x00u;
#endif

#if ((DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF))
#if (DCM_CFG_OSTIMER_USE != FALSE)

    Dcm_SysPrevTick_u32 = 0x0;
#endif
#endif

#if (DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
    Dcm_Lok_WarmStart();
#endif

#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
    Dcm_Lok_SecaInit();
#endif

#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))
    Dcm_isFirstReponseSent_b = FALSE;
#endif

#if((DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))
    Dcm_VinReceived_b = FALSE;
    Dcm_GetvinConditionCheckRead = FALSE;
#endif

    Dcm_acceptRequests_b= TRUE;
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
