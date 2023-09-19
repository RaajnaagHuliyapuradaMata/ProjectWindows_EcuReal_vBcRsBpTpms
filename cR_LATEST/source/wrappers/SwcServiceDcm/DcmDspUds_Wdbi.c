#include "Std_Types.hpp"

#include "DcmDspUds_Wdbi_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)

#include "DcmDspUds_Wdbi_Priv.hpp"
#include "DcmDspUds_Wdbi_Inf.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Dcm_OpStatusType,  DCM_VAR) Dcm_stDspWdbiOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
#if(DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
static VAR (boolean,DCM_VAR) Dcm_flgNvmWritePending_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#endif
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static VAR (Dcm_DIDIndexType_tst,DCM_VAR) s_Dcm_idxwdbiDidIndexType;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
static VAR(uint16,DCM_VAR)  s_dataDID_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
static VAR(boolean,DCM_VAR) s_loopbreak_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Dcm_Cfg_MemMap.hpp"
#endif

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Dcm_SupportRet_t,AUTOMATIC) dataRetWriteSupport_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static VAR(Std_ReturnType,AUTOMATIC)   dataRetWriteFunc_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

static FUNC(void,DCM_CODE) Dcm_Lok_WDBIINIT_Pending(void)
        {
   VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNegResCode;
   P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrWriteFnc;
#if((DCM_CFG_DSP_WRITE_ASYNCH_FNC_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITE_ASYNCH_CS_ENABLED != DCM_CFG_OFF)||   \
        (DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF))
   P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig;
   P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig;
   P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA) ptrControlSigConfig;
#endif
    ptrWriteFnc=NULL_PTR;
    dataNegResCode = 0x0;

#if((DCM_CFG_DSP_WRITE_ASYNCH_FNC_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITE_ASYNCH_CS_ENABLED != DCM_CFG_OFF)||   \
        (DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF))

    ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16];
        ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
        ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];

#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)

        if(ptrSigConfig->idxDcmDspControlInfo_u16 > 0)
        {
            ptrWriteFnc   = ptrControlSigConfig->adrWriteFnc_cpv;

            if((ptrWriteFnc != NULL_PTR) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
            ||(ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
#endif
            ))
            {
#if(DCM_CFG_DSP_WRITE_ASYNCH_FNC_ENABLED != DCM_CFG_OFF)

                if(ptrDidConfig->dataFixedLength_b != FALSE)
                {
#if(DCM_CFG_DSP_WRITE_FIXED_LENGTH != DCM_CFG_OFF)

                    (void)(*(WdbiFnc4_pfct)(ptrWriteFnc))(NULL_PTR,DCM_CANCEL,&dataNegResCode);
#endif
                }
                else{
#if(DCM_CFG_DSP_WRITE_VARIABLE_LENGTH != DCM_CFG_OFF)

                    (void)(*(WdbiFnc3_pfct)(ptrWriteFnc))(NULL_PTR,0x0,DCM_CANCEL,&dataNegResCode);
#endif
                }
#endif
            }
#if(DCM_CFG_DSP_WRITE_ASYNCH_CS_ENABLED != DCM_CFG_OFF)

            else if((ptrWriteFnc != NULL_PTR)&& (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER))
            {

                if(ptrDidConfig->dataFixedLength_b != FALSE)
                {
#if(DCM_CFG_DSP_WRITE_FIXED_LENGTH != DCM_CFG_OFF)

                     (void)(*(WdbiFnc21_pfct)(ptrWriteFnc))(NULL_PTR,DCM_CANCEL,&dataNegResCode);
#endif
                }
                else{
#if(DCM_CFG_DSP_WRITE_VARIABLE_LENGTH != DCM_CFG_OFF)

                     (void)(*(WdbiFnc20_pfct)(ptrWriteFnc))(NULL_PTR,0x0,DCM_CANCEL,&dataNegResCode);
#endif
                }

            }
#endif
            else{
                (void)dataNegResCode;

            }
        }
        else{
            (void)dataNegResCode;
        }

#endif

#if((DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))
        if(ptrSigConfig->usePort_u8 == USE_BLOCK_ID)
        {

            NvM_SetBlockLockStatus(ptrSigConfig->dataNvmBlockId_u16,TRUE);
        }
#endif
#endif

        }

FUNC(void,DCM_CODE) Dcm_Dcm_WDBIInit (void){

#if(DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)
   P2CONST(Dcm_DIDRangeConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidRangeConfig;
   VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNegResCode=0u;
   P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrWriteFnc;
#endif

    dataRetWriteFunc_u8=0x00;

   if((Dcm_stDspWdbiOpStatus_u8 == DCM_PENDING) && (s_Dcm_idxwdbiDidIndexType.dataRange_b== FALSE))
   {

       Dcm_Lok_WDBIINIT_Pending();

   }
   else{
#if(DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)
        ptrDidRangeConfig=&Dcm_DIDRangeConfig_cast[s_Dcm_idxwdbiDidIndexType.idxIndex_u16];
        ptrWriteFnc      = ptrDidRangeConfig->adrWriteFnc_pfct;

        if((ptrWriteFnc != NULL_PTR) && (s_Dcm_idxwdbiDidIndexType.dataRange_b!=FALSE))
        {

                (void)(*(WriteFncRange1_pfct)(ptrWriteFnc))(0x0,NULL_PTR,DCM_CANCEL,0x0,&dataNegResCode);

        }
        else{

            (void)dataNegResCode;

        }
#endif
   }

    Dcm_SrvOpstatus_u8 =  DCM_INITIAL;

    Dcm_DidSignalIdx_u16 = 0x0;
#if(DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)

    Dcm_flgNvmWritePending_b = FALSE;
#endif

    Dcm_stDspWdbiOpStatus_u8 = DCM_INITIAL;
    Dcm_ResetDIDIndexstruct(&s_Dcm_idxwdbiDidIndexType);
}
//#if((DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
#if(DCM_CFG_DSP_WRITE_SR_ENABLED != DCM_CFG_OFF)

static FUNC(void,DCM_CODE) Dcm_Lok_SenderReceiverVariableSignalGetBuffer
                            (P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext
   ,     P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig
   ,     P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig
   ,     VAR(uint16, AUTOMATIC) nrElements_u16
                             )
 {

   VAR (uint16, AUTOMATIC) idxLoop_u16 = 0u;
   VAR (uint32, AUTOMATIC) dataSignal_u32 = 0u;

    do
   {
        switch(ptrSigConfig->dataType_u8)
        {
#if(DCM_CFG_DSP_WRITE_UINT8_SR_ENABLED != DCM_CFG_OFF)
           case DCM_UINT8:
                dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,\
                                (ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16 +(uint16)(idxLoop_u16*8)),\
                                 &pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);

                Dcm_DspArraySignal_au8[idxLoop_u16]=(uint8)dataSignal_u32;
                break;
#endif

#if(DCM_CFG_DSP_WRITE_UINT16_SR_ENABLED != DCM_CFG_OFF)
           case DCM_UINT16:
                dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,\
                              (ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16 +(uint16)(idxLoop_u16*16)),\
                              &pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);

                Dcm_DspArraySignal_au16[idxLoop_u16]=(uint16)dataSignal_u32;
                break;
#endif

#if(DCM_CFG_DSP_WRITE_UINT32_SR_ENABLED != DCM_CFG_OFF)
           case DCM_UINT32:
                dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,\
                              (ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16+(uint16)(idxLoop_u16*32)),\
                              &pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);

                Dcm_DspArraySignal_au32[idxLoop_u16]=dataSignal_u32;
                break;
#endif

#if(DCM_CFG_DSP_WRITE_SINT8_SR_ENABLED != DCM_CFG_OFF)
           case DCM_SINT8:
                dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,\
                               (ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16+(uint16)(idxLoop_u16*8)),\
                               &pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);

                Dcm_DspArraySignal_as8[idxLoop_u16]=(sint8)dataSignal_u32;
                break;
#endif

#if(DCM_CFG_DSP_WRITE_SINT16_SR_ENABLED != DCM_CFG_OFF)
           case DCM_SINT16:
                dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,\
                                 (ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16+(uint16)(idxLoop_u16*16)),\
                                 &pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);

                Dcm_DspArraySignal_as16[idxLoop_u16]=(sint16)dataSignal_u32;
                break;
#endif

#if(DCM_CFG_DSP_WRITE_SINT32_SR_ENABLED != DCM_CFG_OFF)
           case DCM_SINT32:
                dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,\
                                (ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16+(uint16)(idxLoop_u16*32)),\
                                &pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);

                Dcm_DspArraySignal_as32[idxLoop_u16]=(sint32)dataSignal_u32;
                break;
#endif

           default:
                  {

                  break;
                  }
             }
       idxLoop_u16++;

   }while((idxLoop_u16 < nrElements_u16));
}

static FUNC(void,DCM_CODE) Dcm_Lok_WriteSenderReceiverVariableLengthSignal
                            (P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext
   ,     P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig
   ,     P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig,

                             P2VAR(void,AUTOMATIC, DCM_INTERN_CONST)  ptrWriteFnc
   ,     VAR (uint16, AUTOMATIC) nrElements_u16)
 {

   Dcm_Lok_SenderReceiverVariableSignalGetBuffer (pMsgContext,ptrDidConfig,ptrSigConfig,nrElements_u16);

  switch(ptrSigConfig->dataType_u8)
         {
#if(DCM_CFG_DSP_WRITE_UINT8_SR_ENABLED != DCM_CFG_OFF)

         case DCM_UINT8:

            dataRetWriteFunc_u8 = (*(WdbiFnc12_pfct)(ptrWriteFnc))(Dcm_DspArraySignal_au8);
            break;
#endif

#if(DCM_CFG_DSP_WRITE_UINT16_SR_ENABLED != DCM_CFG_OFF)

         case DCM_UINT16:

            dataRetWriteFunc_u8 = (*(WdbiFnc13_pfct)(ptrWriteFnc))(Dcm_DspArraySignal_au16);
            break;
#endif

#if(DCM_CFG_DSP_WRITE_UINT32_SR_ENABLED != DCM_CFG_OFF)

         case DCM_UINT32:

            dataRetWriteFunc_u8 = (*(WdbiFnc14_pfct)(ptrWriteFnc))(Dcm_DspArraySignal_au32);
            break;
#endif

#if(DCM_CFG_DSP_WRITE_SINT8_SR_ENABLED != DCM_CFG_OFF)

        case DCM_SINT8:

            dataRetWriteFunc_u8 = (*(WdbiFnc15_pfct)(ptrWriteFnc))(Dcm_DspArraySignal_as8);
            break;
#endif

#if(DCM_CFG_DSP_WRITE_SINT16_SR_ENABLED != DCM_CFG_OFF)

        case DCM_SINT16:

            dataRetWriteFunc_u8 = (*(WdbiFnc16_pfct)(ptrWriteFnc))(Dcm_DspArraySignal_as16);
            break;
#endif

#if(DCM_CFG_DSP_WRITE_SINT32_SR_ENABLED != DCM_CFG_OFF)

        case DCM_SINT32:

            dataRetWriteFunc_u8 = (*(WdbiFnc17_pfct)(ptrWriteFnc))(Dcm_DspArraySignal_as32);
            break;
#endif

        default:
            {

            break;
            }

         }
  }

static FUNC(void,DCM_CODE) Dcm_Lok_WriteSenderReceiverFixedLengthSignal
                            (P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext
   ,     P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig
   ,     P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig,

                             P2VAR(void,AUTOMATIC, DCM_INTERN_CONST)  ptrWriteFnc)
 {

VAR (uint32, AUTOMATIC) dataSignal_u32;
#if(DCM_CFG_DSP_WRITE_SINT32_SR_ENABLED != DCM_CFG_OFF)

   VAR (sint32, AUTOMATIC) dataSignal_s32;
#endif
#if(DCM_CFG_DSP_WRITE_UINT16_SR_ENABLED != DCM_CFG_OFF)

   VAR (uint16, AUTOMATIC) dataSignal_u16;
#endif
#if(DCM_CFG_DSP_WRITE_SINT16_SR_ENABLED != DCM_CFG_OFF)

   VAR (sint16, AUTOMATIC) dataSignal_s16;
#endif
#if(DCM_CFG_DSP_WRITE_UINT8_SR_ENABLED != DCM_CFG_OFF)

   VAR (uint8,  AUTOMATIC) dataSignal_u8;
#endif
#if(DCM_CFG_DSP_WRITE_SINT8_SR_ENABLED != DCM_CFG_OFF)

   VAR (sint8,  AUTOMATIC) dataSignal_s8;
#endif
#if(DCM_CFG_DSP_WRITE_BOOLEAN_SR_ENABLED != DCM_CFG_OFF)

   VAR (boolean,AUTOMATIC) dataSignal_b;
#endif

dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,\
                                   ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16,\
                                   &pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);
   switch(ptrSigConfig->dataType_u8)
   {
#if(DCM_CFG_DSP_WRITE_BOOLEAN_SR_ENABLED != DCM_CFG_OFF)
        case DCM_BOOLEAN:

              dataSignal_b = (dataSignal_u32 != 0u) ? (TRUE):(FALSE);

                dataRetWriteFunc_u8 = (*(WdbiFnc5_pfct)(ptrWriteFnc))(dataSignal_b);
                break;

#endif
#if(DCM_CFG_DSP_WRITE_UINT8_SR_ENABLED != DCM_CFG_OFF)
        case DCM_UINT8:

                dataSignal_u8 = (uint8)dataSignal_u32;

                 dataRetWriteFunc_u8 = (*(WdbiFnc6_pfct)(ptrWriteFnc))(dataSignal_u8);
                 break;
#endif
#if(DCM_CFG_DSP_WRITE_UINT16_SR_ENABLED != DCM_CFG_OFF)
        case DCM_UINT16:

                dataSignal_u16 = (uint16)dataSignal_u32;

                dataRetWriteFunc_u8 = (*(WdbiFnc7_pfct)(ptrWriteFnc))(dataSignal_u16);
                break;
#endif
#if(DCM_CFG_DSP_WRITE_UINT32_SR_ENABLED != DCM_CFG_OFF)

        case DCM_UINT32:

               dataRetWriteFunc_u8 = (*(WdbiFnc8_pfct)(ptrWriteFnc))(dataSignal_u32);
               break;
#endif

#if(DCM_CFG_DSP_WRITE_SINT8_SR_ENABLED != DCM_CFG_OFF)
        case DCM_SINT8:

                dataSignal_s8 = (sint8)dataSignal_u32;

                dataRetWriteFunc_u8 = (*(WdbiFnc9_pfct)(ptrWriteFnc))(dataSignal_s8);
                break;
#endif

#if(DCM_CFG_DSP_WRITE_SINT16_SR_ENABLED != DCM_CFG_OFF)
        case DCM_SINT16:

              dataSignal_s16 = (sint16)dataSignal_u32;

              dataRetWriteFunc_u8 = (*(WdbiFnc10_pfct)(ptrWriteFnc))(dataSignal_s16);
              break;
#endif

#if(DCM_CFG_DSP_WRITE_SINT32_SR_ENABLED != DCM_CFG_OFF)
        case DCM_SINT32:

              dataSignal_s32 = (sint32)dataSignal_u32;

              dataRetWriteFunc_u8 = (*(WdbiFnc11_pfct)(ptrWriteFnc))(dataSignal_s32);
              break;
#endif
          default:

            break;

   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_WriteSenderReceiverSignal
                            (P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext
   ,     P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig
   ,     P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig,

                             P2VAR(void,AUTOMATIC, DCM_INTERN_CONST)  ptrWriteFnc)
{
   VAR(uint16, AUTOMATIC) nrElements_u16 = 0;

   if(Dcm_Lok_SenderReceiverFixedLength(ptrSigConfig->dataSize_u16,ptrSigConfig->dataType_u8))
     {

           Dcm_Lok_WriteSenderReceiverFixedLengthSignal (pMsgContext,ptrDidConfig,ptrSigConfig,ptrWriteFnc);
     }

      else{
   	   if(Dcm_Lok_SenderReceiverVariableLength(ptrSigConfig->dataSize_u16,ptrSigConfig->dataType_u8) )
   	   {

               switch(ptrSigConfig->dataType_u8)
               {

#if((DCM_CFG_DSP_WRITE_UINT8_SR_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_WRITE_SINT8_SR_ENABLED != DCM_CFG_OFF))

               case DCM_UINT8:
               case DCM_SINT8:
                   nrElements_u16 = (ptrSigConfig->dataSize_u16)/8u;
                   break;
#endif
#if((DCM_CFG_DSP_WRITE_UINT16_SR_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_WRITE_SINT16_SR_ENABLED != DCM_CFG_OFF))

               case DCM_UINT16:
               case DCM_SINT16:
                   nrElements_u16 = (ptrSigConfig->dataSize_u16)/16u;
                    break;
#endif
#if((DCM_CFG_DSP_WRITE_UINT32_SR_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_WRITE_SINT32_SR_ENABLED != DCM_CFG_OFF))

               case DCM_UINT32:
               case DCM_SINT32:
                   nrElements_u16 = (ptrSigConfig->dataSize_u16)/32u;
                    break;
#endif
               default:
                 {

                   break;
                 }
              }
   	   }

           Dcm_Lok_WriteSenderReceiverVariableLengthSignal( pMsgContext,ptrDidConfig,ptrSigConfig,ptrWriteFnc,nrElements_u16);
       }
}
#endif

#if((DCM_CFG_DSP_WRITE_SYNCH_FNC_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_WRITE_SYNCH_CS_ENABLED != DCM_CFG_OFF))

 static FUNC(void,DCM_CODE) Dcm_Lok_WriteSYNCDID
                             (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,

                              P2VAR(void,AUTOMATIC, DCM_INTERN_CONST)  ptrWriteFnc
   ,     P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig
   ,     VAR (uint16,  AUTOMATIC) posnDidSignal_u16)
 {

     if(ptrDidConfig->dataFixedLength_b != FALSE)
     {

#if(DCM_CFG_DSP_WRITE_FIXED_LENGTH != DCM_CFG_OFF)

         dataRetWriteFunc_u8 = (*(WdbiFnc2_pfct)(ptrWriteFnc))
                                 (&pMsgContext->reqData[posnDidSignal_u16], dataNegRespCode_u8);
#endif

     }
#if(DCM_CFG_DSP_WRITE_VARIABLE_LENGTH != DCM_CFG_OFF)
     else{

         dataRetWriteFunc_u8 = (*(WdbiFnc1_pfct)(ptrWriteFnc))
                                (&pMsgContext->reqData[posnDidSignal_u16],\
                                 (uint16)(pMsgContext->reqDataLen-0x02u),dataNegRespCode_u8);

     }
#endif
 }

#endif

#if((DCM_CFG_DSP_WRITE_ASYNCH_FNC_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_WRITE_ASYNCH_CS_ENABLED != DCM_CFG_OFF)\
    || ((DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF )&& (DCM_CFG_DSP_WRITE_ASYNCH_FNC_ENABLED != DCM_CFG_OFF)))

static FUNC(void,DCM_CODE) Dcm_Lok_WriteASYNCDID
                           (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,

                            P2VAR(void,AUTOMATIC, DCM_INTERN_CONST)  ptrWriteFnc
   ,     P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig
   ,     VAR (uint16,  AUTOMATIC) posnDidSignal_u16)
{

     if(ptrDidConfig->dataFixedLength_b != FALSE)
     {
#if(DCM_CFG_DSP_WRITE_FIXED_LENGTH != DCM_CFG_OFF)

         dataRetWriteFunc_u8 = (*(WdbiFnc4_pfct)(ptrWriteFnc))
                               (&pMsgContext->reqData[posnDidSignal_u16],Dcm_stDspWdbiOpStatus_u8,dataNegRespCode_u8);
#endif
     }
     else{
#if(DCM_CFG_DSP_WRITE_VARIABLE_LENGTH != DCM_CFG_OFF)

         dataRetWriteFunc_u8 = (*(WdbiFnc3_pfct)(ptrWriteFnc))
                               (&pMsgContext->reqData[posnDidSignal_u16],(uint16)(pMsgContext->reqDataLen-0x02u),\
                               Dcm_stDspWdbiOpStatus_u8,dataNegRespCode_u8);
#endif
     }
 }
#endif

static FUNC(void,DCM_CODE) Dcm_Lok_WriteDidUsePort
                           (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext
   ,     P2VAR(void,AUTOMATIC, DCM_INTERN_CONST)  ptrWriteFnc
   ,     P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig
   ,     VAR (uint16,  AUTOMATIC) posnDidSignal_u16)
{

   P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig;
    ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];

#if(DCM_CFG_DSP_WRITE_SYNCH_FNC_ENABLED != DCM_CFG_OFF)
   if((ptrWriteFnc != NULL_PTR) && (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC))
   {
        Dcm_Lok_WriteSYNCDID(dataNegRespCode_u8,pMsgContext,ptrWriteFnc,ptrDidConfig,posnDidSignal_u16);
   }
#endif
#if(DCM_CFG_DSP_WRITE_SYNCH_CS_ENABLED != DCM_CFG_OFF)
   if((ptrWriteFnc != NULL_PTR) && (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
   {
        Dcm_Lok_WriteSYNCDID(dataNegRespCode_u8,pMsgContext,ptrWriteFnc,ptrDidConfig,posnDidSignal_u16);
   }
#endif

#if((DCM_CFG_DSP_WRITE_ASYNCH_FNC_ENABLED != DCM_CFG_OFF))
   if((ptrWriteFnc != NULL_PTR) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)
#if((DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF))
            || (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
#endif
    ))
   {
        Dcm_Lok_WriteASYNCDID(dataNegRespCode_u8,pMsgContext,ptrWriteFnc,ptrDidConfig,posnDidSignal_u16);
   }
#endif
#if(DCM_CFG_DSP_WRITE_ASYNCH_CS_ENABLED != DCM_CFG_OFF)
   if((ptrWriteFnc != NULL_PTR) && (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER))
   {
        Dcm_Lok_WriteASYNCDID(dataNegRespCode_u8,pMsgContext,ptrWriteFnc,ptrDidConfig,posnDidSignal_u16);
   }
#endif

#if(DCM_CFG_DSP_WRITE_SR_ENABLED != DCM_CFG_OFF)
   if(((ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER)||(ptrSigConfig->usePort_u8 ==USE_DATA_SENDER_RECEIVER_AS_SERVICE))
           && (ptrWriteFnc != NULL_PTR))
   {
       Dcm_Lok_WriteSenderReceiverSignal (pMsgContext,ptrDidConfig,ptrSigConfig,ptrWriteFnc);
   }
#endif
}

#if(DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)

 static FUNC(void,DCM_CODE) Dcm_Lok_WriteDIDNvRam
                            (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext
   ,     P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig
   ,     VAR (uint16,  AUTOMATIC) posnDidSignal_u16)
 {

VAR(Std_ReturnType, AUTOMATIC) dataNvmWriteBlockRetVal_u8;
VAR(Std_ReturnType, AUTOMATIC) dataNvmGetErrorRetVal_u8;
VAR(NvM_RequestResultType, AUTOMATIC) dataRequestResult_u8;

   if(Dcm_flgNvmWritePending_b ==FALSE)
   {
        NvM_SetBlockLockStatus(ptrSigConfig->dataNvmBlockId_u16,FALSE);

        dataNvmWriteBlockRetVal_u8=NvM_WriteBlock(ptrSigConfig->dataNvmBlockId_u16,&pMsgContext->reqData[posnDidSignal_u16]);
        if(dataNvmWriteBlockRetVal_u8 != E_OK)
        {

            *dataNegRespCode_u8 = DCM_E_GENERALPROGRAMMINGFAILURE;

            Dcm_flgNvmWritePending_b=FALSE;

            NvM_SetBlockLockStatus(ptrSigConfig->dataNvmBlockId_u16,TRUE);
        }
        else{

            Dcm_flgNvmWritePending_b=TRUE;
            dataRetWriteFunc_u8 =DCM_E_PENDING;
        }
        s_loopbreak_b = TRUE;

   }
   else{
        dataNvmGetErrorRetVal_u8= NvM_GetErrorStatus(ptrSigConfig->dataNvmBlockId_u16,&dataRequestResult_u8);

        Dcm_flgNvmWritePending_b = FALSE;
        if(dataNvmGetErrorRetVal_u8 != E_OK)
        {

            *dataNegRespCode_u8 =DCM_E_GENERALPROGRAMMINGFAILURE;

            NvM_SetBlockLockStatus(ptrSigConfig->dataNvmBlockId_u16,TRUE);
            s_loopbreak_b = TRUE;
        }
        else{
             switch(dataRequestResult_u8)
             {
                 case NVM_REQ_PENDING:

                         Dcm_flgNvmWritePending_b = TRUE;
                         dataRetWriteFunc_u8 = DCM_E_PENDING;
                         break;
                 case NVM_REQ_OK:
                         dataRetWriteFunc_u8 =E_OK;
                         break;
                 default:
                         *dataNegRespCode_u8 = DCM_E_GENERALPROGRAMMINGFAILURE;
                         break;
             }
        }
        if((dataRequestResult_u8 != NVM_REQ_PENDING) && (dataNvmGetErrorRetVal_u8==E_OK))
        {

            NvM_SetBlockLockStatus(ptrSigConfig->dataNvmBlockId_u16,TRUE);
        }
        if(dataRequestResult_u8!=NVM_REQ_OK)
        {
            s_loopbreak_b = TRUE;
        }
      }
}

#endif

static FUNC(void,DCM_CODE) Dcm_Lok_WriteNormalDID
                        (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext)
{

  P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16];
  P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrSigConfig;
  P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA) ptrControlSigConfig;

  P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrWriteFnc;

  VAR (uint16,  AUTOMATIC) posnDidSignal_u16;
  VAR (uint16,  AUTOMATIC) loopIndex_u16 = Dcm_DidSignalIdx_u16;
  VAR(boolean,  AUTOMATIC) Rtn_InfrastureError;

   for(;((loopIndex_u16 < ptrDidConfig->nrSig_u16) && (dataRetWriteFunc_u8 == E_OK)); loopIndex_u16++)
   {
        Dcm_DidSignalIdx_u16 = loopIndex_u16;
        ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
        ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];

        posnDidSignal_u16 = (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16/8u) +2u);

        if(ptrSigConfig->idxDcmDspControlInfo_u16 > 0u)
        {
            ptrWriteFnc = ptrControlSigConfig->adrWriteFnc_cpv;

            Dcm_Lok_WriteDidUsePort(dataNegRespCode_u8,pMsgContext,ptrWriteFnc,ptrDidConfig,posnDidSignal_u16);
            if(dataRetWriteFunc_u8 != E_OK)
             {

                Rtn_InfrastureError=Dcm_IsInfrastructureErrorPresent_b(dataRetWriteFunc_u8);

                 if((((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) ||
                     (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER) ||
                      ((ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER)||(ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER_AS_SERVICE))))&&(Rtn_InfrastureError == TRUE))

                  {

#if((DCM_CFG_DSP_WRITE_ASYNCH_CS_ENABLED != DCM_CFG_OFF) || \
                          (DCM_CFG_DSP_WRITE_SYNCH_CS_ENABLED != DCM_CFG_OFF) || \
                           (DCM_CFG_DSP_WRITE_SR_ENABLED != DCM_CFG_OFF))

                          *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                          dataRetWriteFunc_u8 = DCM_INFRASTRUCTURE_ERROR;
#endif
                  }

                 s_loopbreak_b =TRUE;
             }
             else{

                  *dataNegRespCode_u8=0x00;
                  Dcm_stDspWdbiOpStatus_u8 = DCM_INITIAL;
             }
        }
        else{
#if(DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
            if((ptrSigConfig->usePort_u8 == USE_BLOCK_ID))
            {

                Dcm_Lok_WriteDIDNvRam(dataNegRespCode_u8,pMsgContext,ptrSigConfig,posnDidSignal_u16);
            }
#endif
        }
        if(s_loopbreak_b == TRUE)
        {

            s_loopbreak_b = FALSE;
            break;
        }
   }
}

static FUNC(void,DCM_CODE) Dcm_Lok_WriteDidMaxLenCheck
                            (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext)
{

VAR(uint16,AUTOMATIC)  nrLenDataRec_u16;

#if(DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)

      if(s_Dcm_idxwdbiDidIndexType.dataRange_b == FALSE)
#endif
        {

           nrLenDataRec_u16 = (Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].dataMaxDidLen_u16+2u);

           if(Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].dataFixedLength_b != FALSE)
           {

                if(pMsgContext->reqDataLen != nrLenDataRec_u16)
                {
                    *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                }
           }
           else{

               if(pMsgContext->reqDataLen > nrLenDataRec_u16)
               {
                   *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
               }
               else  if(DcmAppl_DcmCheckWDBIReqLen(s_dataDID_u16,(pMsgContext->reqDataLen-2u))!= E_OK)
               {

                   *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
               }
               else{

               }
           }
        }
#if(DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)
        else{
           nrLenDataRec_u16 = (uint16)(Dcm_DIDRangeConfig_cast[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].dataMaxDidLen_u16+2u);

           if(pMsgContext->reqDataLen > nrLenDataRec_u16)
           {
               *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
           }
           else{
   		   if(DcmAppl_DcmCheckWDBIReqLen(s_dataDID_u16,(pMsgContext->reqDataLen-2u))!= E_OK)
   		   {

              *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
   		   }
           }
        }

#endif
}

static FUNC(void,DCM_CODE) Dcm_Priv_DidWriteSupport
                            (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext
                             )

{

VAR (uint32,AUTOMATIC) dataSessionMask_u32 = 0;

P2CONST(Dcm_ExtendedDIDConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrExtendedConfig_pcst;

#if( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
     if(s_Dcm_idxwdbiDidIndexType.dataRange_b == FALSE)
     {
#endif
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
        adrExtendedConfig_pcst = Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].adrExtendedConfig_pcst;

#endif
#if( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
     }
     else{
        adrExtendedConfig_pcst = Dcm_DIDRangeConfig_cast[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].adrExtendedConfig_pcst;
     }
#endif

    dataSessionMask_u32  = adrExtendedConfig_pcst->dataAllowedSessWrite_u32;

   if(((Dcm_DsldGetActiveSessionMask_u32 () & dataSessionMask_u32) != 0x0uL))
   {
        Dcm_Lok_WriteDidMaxLenCheck(dataNegRespCode_u8,pMsgContext);

   }
   else{
        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
   }

   if(*dataNegRespCode_u8 == 0)
   {

      dataRetWriteSupport_en = Dcm_GetSupportOfIndex(&s_Dcm_idxwdbiDidIndexType, DCM_SUPPORT_WRITE,dataNegRespCode_u8);

      if(dataRetWriteSupport_en == DCM_SUPPORT_OK)
      {
          Dcm_stDspWdbiOpStatus_u8  = DCM_INITIAL;
          Dcm_SrvOpstatus_u8 = DCM_PROCESSSERVICE;
          dataRetWriteFunc_u8 = E_OK;
      }
   }
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Priv_DidWriteFuncAvailableCheck
                           (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

VAR(Std_ReturnType, AUTOMATIC) dataRetVal_u8 = E_NOT_OK;
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)

VAR(uint16,AUTOMATIC)  idxDidSignal_u16 = 0;

VAR(uint16,AUTOMATIC)  nrDidSignal_u16 = 0;

VAR(uint8,AUTOMATIC)   useDidPort_u8 = 0;

VAR(uint32,AUTOMATIC)  alloweWritedSession_u32 = 0;
#endif

P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrWriteFnc = NULL_PTR;

#if(DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)

   if(s_Dcm_idxwdbiDidIndexType.dataRange_b == FALSE)
#endif
   {
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
        nrDidSignal_u16 = Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].nrSig_u16;

        useDidPort_u8 = Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].\
                        adrDidSignalConfig_pcst[idxDidSignal_u16].idxDcmDspDatainfo_u16].usePort_u8;

        alloweWritedSession_u32 = Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].\
                                    adrExtendedConfig_pcst->dataAllowedSessWrite_u32;

        ptrWriteFnc = Dcm_DspDid_ControlInfo_st[Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].\
                      adrDidSignalConfig_pcst[idxDidSignal_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16].adrWriteFnc_cpv;

        for(idxDidSignal_u16=0x0; idxDidSignal_u16 < nrDidSignal_u16; idxDidSignal_u16++)
        {
            if((useDidPort_u8 != USE_BLOCK_ID)&&(alloweWritedSession_u32 >0x00u)&&(ptrWriteFnc == NULL_PTR ))
            {
                    break;
            }
        }
        if(idxDidSignal_u16 == nrDidSignal_u16)
        {
            dataRetVal_u8 =E_OK;
        }
        else{
            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;

            DCM_DET_ERROR(DCM_WDBI_ID , DCM_E_NO_WRITE_ACCESS )
        }
#endif
   }
#if(DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)
   else{
         ptrWriteFnc = Dcm_DIDRangeConfig_cast[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].adrWriteFnc_pfct;
          if(ptrWriteFnc != NULL_PTR)
          {
              dataRetVal_u8 = E_OK;
          }
          else{

              *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;

              DCM_DET_ERROR(DCM_WDBI_ID , DCM_E_NO_WRITE_ACCESS )
          }
   }
# endif

 return dataRetVal_u8;
}

static FUNC(void,DCM_CODE) Dcm_Lok_DidAvailableCheck
                                    (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   VAR(Std_ReturnType,AUTOMATIC)   dataRetGetDID_u8 = E_NOT_OK;

    dataRetGetDID_u8 = Dcm_GetIndexOfDID(s_dataDID_u16, &s_Dcm_idxwdbiDidIndexType);
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0u)

   if((dataRetGetDID_u8 == E_OK)&& (s_Dcm_idxwdbiDidIndexType.dataRange_b==FALSE))
   {

        if(*Dcm_DIDIsAvail[Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].idxDIDSupportedFnc_u16] != NULL_PTR)
        {
            if((*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].\
                                                   idxDIDSupportedFnc_u16]))(s_dataDID_u16)!=E_OK)
            {
                dataRetGetDID_u8 = E_NOT_OK;
            }
        }
   }
#endif

   if(dataRetGetDID_u8 == E_OK)
   {

        dataRetGetDID_u8 = Dcm_Priv_DidWriteFuncAvailableCheck(dataNegRespCode_u8);

   	    if(dataRetGetDID_u8 == E_OK)
            {

               Dcm_SrvOpstatus_u8 = DCM_CHECKDATA;

            }
   }
   else if(dataRetGetDID_u8 == DCM_E_PENDING)
   {
        dataRetWriteFunc_u8 = DCM_E_PENDING;
   }
   else{

        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;

   }
}

#if(DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)

static FUNC(void,DCM_CODE) Dcm_Lok_WriteRangeDID
                        (P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
                        )

{
 P2CONST(Dcm_DIDRangeConfig_tst,AUTOMATIC, DCM_INTERN_DATA)ptrDidRangeConfig;
 P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrWriteFnc;
 ptrDidRangeConfig = &Dcm_DIDRangeConfig_cast[s_Dcm_idxwdbiDidIndexType.idxIndex_u16];
 ptrWriteFnc = ptrDidRangeConfig->adrWriteFnc_pfct;
 if(ptrWriteFnc != NULL_PTR)
 {

   if(ptrDidRangeConfig->nrRangeUsePort_b != FALSE)
   {

        dataRetWriteFunc_u8 = (*(WriteFncRange1_pfct)(ptrWriteFnc))
                              (s_dataDID_u16,&pMsgContext->reqData[0x2],Dcm_stDspWdbiOpStatus_u8,\
                              (uint16)(pMsgContext->reqDataLen-0x02u),dataNegRespCode_u8);

        if((Dcm_IsInfrastructureErrorPresent_b(dataRetWriteFunc_u8) != FALSE))

        {
            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
            Dcm_stDspWdbiOpStatus_u8 = DCM_INITIAL;
        }
   }
   else{

        dataRetWriteFunc_u8 = (*(WriteFncRange1_pfct)(ptrWriteFnc))
                              (s_dataDID_u16,&pMsgContext->reqData[0x2],Dcm_stDspWdbiOpStatus_u8,\
                              (uint16)(pMsgContext->reqDataLen-0x02u),dataNegRespCode_u8);
   }
 }
}
#endif

static FUNC(void,DCM_CODE) Dcm_Lok_WdbiStateProcessing
                                    ( P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext
                                     )

{

   if(Dcm_SrvOpstatus_u8 == DCM_INITIAL)
   {

       if(pMsgContext->reqDataLen >= DCM_DSP_WDBI_MINREQLEN)
       {

           s_dataDID_u16 = (uint16)(pMsgContext->reqData[0]);
           s_dataDID_u16 = s_dataDID_u16 <<8u;
           s_dataDID_u16 |= (uint16)(pMsgContext->reqData[1]);

            Dcm_Lok_DidAvailableCheck(dataNegRespCode_u8);
       }
       else{

           *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
       }
   }

   if(Dcm_SrvOpstatus_u8 == DCM_CHECKDATA)
   {
      Dcm_Priv_DidWriteSupport(dataNegRespCode_u8, pMsgContext);
   }

   if(Dcm_SrvOpstatus_u8 == DCM_PROCESSSERVICE)
   {

#if(DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)

       if(s_Dcm_idxwdbiDidIndexType.dataRange_b == FALSE)
#endif
       {
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
           Dcm_Lok_WriteNormalDID(dataNegRespCode_u8,pMsgContext);
#endif
       }
#if(DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)
       else{
           Dcm_Lok_WriteRangeDID(pMsgContext,dataNegRespCode_u8);
       }
#endif
   }
}

static FUNC(Std_ReturnType,DCM_CODE) Dcm_Lok_WriteDIDServevice_status
                                    (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
   ,     P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
                                     )

{

VAR(Std_ReturnType, AUTOMATIC) dataRetVal_u8 = E_NOT_OK;

   if( (dataRetWriteFunc_u8 == E_OK) && (*dataNegRespCode_u8 == 0x00) )
   {
        pMsgContext->resData[0] = pMsgContext->reqData[0];
        pMsgContext->resData[1] = pMsgContext->reqData[1];
        pMsgContext->resDataLen = 0x02;

        Dcm_SrvOpstatus_u8  = DCM_INITIAL;
        Dcm_DidSignalIdx_u16 = 0x0;
        Dcm_stDspWdbiOpStatus_u8 = DCM_INITIAL;
        dataRetVal_u8=E_OK;
   }

   else if((dataRetWriteFunc_u8 == DCM_E_PENDING) || (dataRetWriteSupport_en == DCM_SUPPORT_CONDITION_PENDING))
   {

        Dcm_stDspWdbiOpStatus_u8 = DCM_PENDING;
        *dataNegRespCode_u8=0x00;
        dataRetVal_u8=DCM_E_PENDING;
   }
   else{
        if(*dataNegRespCode_u8 == 0x00)
        {
            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
        }

        Dcm_stDspWdbiOpStatus_u8 = DCM_INITIAL;
        dataRetVal_u8=E_NOT_OK;
   }

   if(*dataNegRespCode_u8 != 0x0)
   {
      dataRetVal_u8=E_NOT_OK;

      Dcm_SrvOpstatus_u8  = DCM_INITIAL;
      Dcm_DidSignalIdx_u16 = 0x0;
      Dcm_stDspWdbiOpStatus_u8 = DCM_INITIAL;
   }

return dataRetVal_u8;
}

FUNC(Std_ReturnType,DCM_CODE) SwcServiceDcm_tWriteDataByIdentifier
                                (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus
   ,     P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
   ,     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

   VAR(Std_ReturnType, AUTOMATIC) dataRetVal_u8;

#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
   s_loopbreak_b = FALSE;
#endif

    *dataNegRespCode_u8 = 0x0;
    dataRetWriteFunc_u8 = E_OK;
    dataRetWriteSupport_en = DCM_SUPPORT_OK;
    dataRetVal_u8 = E_NOT_OK;

   if(OpStatus == DCM_CANCEL)
   {

        Dcm_Dcm_WDBIInit();

        dataRetVal_u8 = E_OK;
   }
   else{

        Dcm_Lok_WdbiStateProcessing(dataNegRespCode_u8,pMsgContext);

        dataRetVal_u8  =   Dcm_Lok_WriteDIDServevice_status(dataNegRespCode_u8,pMsgContext);
   }
        return dataRetVal_u8;
}

FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveWDBIDid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16)
{
   VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;

    dataRetVal_u8 = E_NOT_OK;

   if(s_Dcm_idxwdbiDidIndexType.dataRange_b==FALSE)
   {

        *dataDid_u16 = Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].dataDid_u16;

        dataRetVal_u8 = E_OK;
   }
   else{
#if(DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)

        *dataDid_u16 = s_Dcm_idxwdbiDidIndexType.dataRangeDid_16;

        dataRetVal_u8 = E_OK;
#endif
   }
    return (dataRetVal_u8);
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif