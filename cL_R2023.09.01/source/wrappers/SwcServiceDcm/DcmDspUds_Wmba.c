

#include "DcmDspUds_Wmba_Inf.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)

#include "DcmDspUds_Wmba_Priv.hpp"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
static uint32 Dcm_adrMemoryAddress_u32;
static uint32 Dcm_nrWriteMemoryLength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

static uint16 Dcm_idxDspWmba_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
static Dcm_OpStatusType Dcm_stWmbaOpstatus_u8;
static uint8 Dcm_nrMemDataSize_u8;
static uint8 Dcm_nrMemAddrSize_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

void Dcm_WMBAIni (void){
   if(DCM_PENDING == Dcm_stWmbaOpstatus_u8)
   {
        (void)(DcmAppl_Dcm_WriteMemory(DCM_CANCEL,Dcm_WMBAConfig_cast[Dcm_idxDspWmba_u16].dataMemoryValue_u8
   ,                                  Dcm_adrMemoryAddress_u32,Dcm_nrWriteMemoryLength_u32
   ,                                  NULL_PTR,NULL_PTR));
   }

    Dcm_SrvOpstatus_u8 = DCM_INITIAL;

    Dcm_stWmbaOpstatus_u8 = DCM_INITIAL;
}

static Std_ReturnType Dcm_Lok_GetAddressRangeIndex_u8(uint32 dataMemAddr_u32
   ,       uint32 dataMemLength_u32
   ,       uint16 * idxLoop_u8)
{

   uint16 dataSize_u16;
   uint16 idxWmba_u16;
    Std_ReturnType dataRetVal_en;

    dataRetVal_en=E_NOT_OK;

   if((uint32)0u != dataMemLength_u32)
   {
        dataSize_u16 = Dcm_WmbacalculateTableSize_u16();
        for(idxWmba_u16 = 0;idxWmba_u16<dataSize_u16;idxWmba_u16++)
        {
            if((dataMemAddr_u32 >= Dcm_WMBAConfig_cast[idxWmba_u16].dataWriteMemoryRangeLow_u32) && \
               ((dataMemAddr_u32 + (dataMemLength_u32-1uL))<= \
               (Dcm_WMBAConfig_cast[idxWmba_u16].dataWriteMemoryRangeHigh_u32)))
            {
                *idxLoop_u8 = idxWmba_u16;
                dataRetVal_en = E_OK;
                break;
            }
        }
   }

    return (dataRetVal_en);
}

LOCAL_INLINE void Dcm_Lok_WMBATotalCheckLength (
                                       const Dcm_MsgContextType * pMsgContext
   ,                                      Dcm_NegativeResponseCodeType * dataNegRespCode_u8)
{
    Std_ReturnType dataRetGetIdxWmba_u8;
    *dataNegRespCode_u8 = 0x00;

   if((DCM_MINSIZE!=Dcm_nrMemAddrSize_u8)&&
      (DCM_MINSIZE!=Dcm_nrMemDataSize_u8)&&
      (Dcm_nrMemDataSize_u8 <=DCM_MAXSIZE)&&
      (Dcm_nrMemAddrSize_u8<=DCM_MAXSIZE))
   {

     Dcm_GetMemoryInfo(Dcm_nrMemAddrSize_u8,&(pMsgContext->reqData[1]),&Dcm_adrMemoryAddress_u32);

     Dcm_GetMemoryInfo(Dcm_nrMemDataSize_u8,&(pMsgContext->reqData[Dcm_nrMemAddrSize_u8+1])
   ,                      &Dcm_nrWriteMemoryLength_u32);

      if(pMsgContext->reqDataLen == (Dcm_nrMemAddrSize_u8 + Dcm_nrMemDataSize_u8 + Dcm_nrWriteMemoryLength_u32 + 1u))
      {

        dataRetGetIdxWmba_u8 = Dcm_Lok_GetAddressRangeIndex_u8(Dcm_adrMemoryAddress_u32
   ,                                                              Dcm_nrWriteMemoryLength_u32
   ,                                                              &Dcm_idxDspWmba_u16);

            if(E_OK == dataRetGetIdxWmba_u8)
            {
              Dcm_SrvOpstatus_u8 = DCM_CHECKDATA;
            }

            else{
              *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            }
       }
       else{

          *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
       }
   }
   else{

     *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
   }
}

LOCAL_INLINE Std_ReturnType Dcm_Lok_WMBAUpdateStatus (
                                       Dcm_MsgContextType * pMsgContext
   ,                                      Dcm_NegativeResponseCodeType * dataNegRespCode_u8)

   {

      uint8 idxLoop_u8;
      Std_ReturnType dataRetVal_u8;

      Dcm_WriteMemoryRet_t dataWriteReturnVal_en;

      dataWriteReturnVal_en = DCM_WRITE_FAILED;

      dataWriteReturnVal_en= DcmAppl_Dcm_WriteMemory(
                                                Dcm_stWmbaOpstatus_u8
   ,                                               Dcm_WMBAConfig_cast[Dcm_idxDspWmba_u16].dataMemoryValue_u8
   ,                                               Dcm_adrMemoryAddress_u32,Dcm_nrWriteMemoryLength_u32
   ,                                              &(pMsgContext->reqData[Dcm_nrMemDataSize_u8 + Dcm_nrMemAddrSize_u8 + 1])
   ,                                               dataNegRespCode_u8);

      if(DCM_WRITE_OK==dataWriteReturnVal_en)
      {

         pMsgContext->resDataLen =  Dcm_nrMemDataSize_u8 + Dcm_nrMemAddrSize_u8 + 1;

        for(idxLoop_u8=Dcm_nrMemDataSize_u8 + Dcm_nrMemAddrSize_u8+1;idxLoop_u8!=0;idxLoop_u8--)
        {

          pMsgContext->resData[idxLoop_u8-1] = pMsgContext->reqData[idxLoop_u8-1];
        }

        dataRetVal_u8=E_OK;

        Dcm_SrvOpstatus_u8 = DCM_INITIAL;
        Dcm_stWmbaOpstatus_u8 = DCM_INITIAL;
        *dataNegRespCode_u8=0x00;
      }
      else if(DCM_WRITE_PENDING==dataWriteReturnVal_en)
      {
        Dcm_stWmbaOpstatus_u8=DCM_PENDING;
        dataRetVal_u8=DCM_E_PENDING;
        *dataNegRespCode_u8=0x00;
      }
      else if(DCM_WRITE_FORCE_RCRRP == dataWriteReturnVal_en)
      {
           Dcm_stWmbaOpstatus_u8 = DCM_FORCE_RCRRP_OK;
           *dataNegRespCode_u8=0x00;
           dataRetVal_u8=DCM_E_FORCE_RCRRP;
      }
      else{
            if(*dataNegRespCode_u8 ==0x00)
            {
               *dataNegRespCode_u8 =   DCM_E_GENERALPROGRAMMINGFAILURE;
            }

            Dcm_stWmbaOpstatus_u8=DCM_INITIAL;
            dataRetVal_u8=E_NOT_OK;
      }

      return dataRetVal_u8;
   }

LOCAL_INLINE Dcm_WmbaSupportRet_t Dcm_Lok_WMBASecurityCheck (
                                     uint32 dataSecurityMask_u32
   ,                                    const Dcm_WMBAConfig_tst * adrWmbaConfig_pcst
   ,                                    Dcm_NegativeResponseCodeType * adrNegRespCode_pu8)
   {

        Dcm_WmbaSupportRet_t dataRetVal_en;
        Std_ReturnType dataModeChkRetval_u8;

        dataRetVal_en = DCM_WMBA_SUPPORT_OK;

        if((Dcm_DsldGetActiveSecurityMask_u32() & dataSecurityMask_u32) != 0x0uL)
        {

            if(adrWmbaConfig_pcst->adrUserMemWriteModeRule_pfct!=NULL_PTR)
            {

                dataModeChkRetval_u8 =(*adrWmbaConfig_pcst->adrUserMemWriteModeRule_pfct)(adrNegRespCode_pu8
   ,                                                                                         Dcm_adrMemoryAddress_u32
   ,                                                                                         Dcm_nrWriteMemoryLength_u32
   ,                                                                                         DCM_SUPPORT_WRITE);
            }
            else{

                dataModeChkRetval_u8 =DcmAppl_UserMemoryRangeModeRuleService(adrNegRespCode_pu8
   ,                                                                            Dcm_adrMemoryAddress_u32
   ,                                                                            Dcm_nrWriteMemoryLength_u32
   ,                                                                            DCM_SUPPORT_WRITE);
            }

            if(dataModeChkRetval_u8!=E_OK)
            {
                if(*adrNegRespCode_pu8 ==0x00)
                {
                    *adrNegRespCode_pu8 = DCM_E_CONDITIONSNOTCORRECT;
                }
                dataRetVal_en = DCM_WMBA_SUPPORT_CONDITION_VIOLATED;
            }
            else{
                *adrNegRespCode_pu8=0;
            }
#if(DCM_CFG_DSP_MODERULEFORWRITEMEMORY != DCM_CFG_OFF)
            if((*adrNegRespCode_pu8==0x00)&&(NULL_PTR != adrWmbaConfig_pcst->addrWmbaModeRuleChkFnc_pfct))
            {
                (void)(*(adrWmbaConfig_pcst->addrWmbaModeRuleChkFnc_pfct))(adrNegRespCode_pu8);
            }

            if(*adrNegRespCode_pu8 !=0x00)
            {
                dataRetVal_en = DCM_WMBA_SUPPORT_CONDITION_VIOLATED;
            }
#endif

        }

        else{
            *adrNegRespCode_pu8 = DCM_E_SECURITYACCESSDENIED;
            dataRetVal_en       = DCM_WMBA_SUPPORT_SECURITY_VIOLATED;
        }

        return dataRetVal_en;
   }

static Dcm_WmbaSupportRet_t Dcm_Lok_WmbaAccessCheck_u8 (uint16 idxLoop_u8
   ,       Dcm_NegativeResponseCodeType * adrNegRespCode_pu8)
{

   uint32 dataSessionMask_u32;
   uint32 dataSecurityMask_u32;
   const Dcm_WMBAConfig_tst * adrWmbaConfig_pcst;
    Dcm_WmbaSupportRet_t dataRetVal_en;
    Std_ReturnType stGetMemAccess_u8;

    dataRetVal_en = DCM_WMBA_SUPPORT_OK;
    *adrNegRespCode_pu8     = 0x00;
    adrWmbaConfig_pcst = &Dcm_WMBAConfig_cast[idxLoop_u8];

    dataSessionMask_u32 = adrWmbaConfig_pcst -> dataAllowedSessWrite_u32;
    dataSecurityMask_u32 = adrWmbaConfig_pcst -> dataAllowedSecWrite_u32;

   if((Dcm_DsldGetActiveSessionMask_u32() & dataSessionMask_u32) != 0x0uL)
   {

        stGetMemAccess_u8 = DcmAppl_DcmGetPermissionForMemoryAccess_u8(Dcm_adrMemoryAddress_u32
   ,                                                                      Dcm_nrWriteMemoryLength_u32,DCM_SUPPORT_WRITE);
        if(stGetMemAccess_u8 != E_OK)
        {
            *adrNegRespCode_pu8 = DCM_E_REQUESTOUTOFRANGE;
            dataRetVal_en = DCM_WMBA_SUPPORT_CONDITION_VIOLATED;
        }
        else{
            dataRetVal_en = Dcm_Lok_WMBASecurityCheck (dataSecurityMask_u32,adrWmbaConfig_pcst,adrNegRespCode_pu8);
        }
   }

   else{
        *adrNegRespCode_pu8 = DCM_E_REQUESTOUTOFRANGE;
        dataRetVal_en       = DCM_WMBA_SUPPORT_SESSION_VIOLATED;
   }
    return dataRetVal_en;
}

Std_ReturnType Dcm_DcmWriteMemoryByAddress (Dcm_SrvOpStatusType OpStatus
   ,                                   Dcm_MsgContextType * pMsgContext
   ,                                   Dcm_NegativeResponseCodeType * dataNegRespCode_u8)
{

    Dcm_WmbaSupportRet_t dataRetWriteSupport_en;
    Std_ReturnType dataRetVal_u8;

    dataRetVal_u8=E_NOT_OK;
    *dataNegRespCode_u8 = 0x0;

   if(OpStatus == DCM_CANCEL)
   {

        Dcm_WMBAIni();

        dataRetVal_u8 = E_OK;
   }
   else{
        if(Dcm_SrvOpstatus_u8 == DCM_INITIAL)
        {

            if(pMsgContext->reqDataLen >= DCM_DSP_WMBA_MINREQLEN)
            {

                Dcm_nrMemAddrSize_u8 = ((pMsgContext->reqData[0])& (0xFu));
                Dcm_nrMemDataSize_u8 = (uint8)(((pMsgContext->reqData[0])& (0xF0u))>>4u);

                Dcm_Lok_WMBATotalCheckLength (pMsgContext,dataNegRespCode_u8);
            }
            else{

                *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            }
        }

       if(Dcm_SrvOpstatus_u8 == DCM_CHECKDATA)
        {

            dataRetWriteSupport_en = Dcm_Lok_WmbaAccessCheck_u8(Dcm_idxDspWmba_u16,dataNegRespCode_u8);

            if(dataRetWriteSupport_en == DCM_WMBA_SUPPORT_OK)
            {

                Dcm_SrvOpstatus_u8 = DCM_PROCESSSERVICE;
            }
        }

        if(Dcm_SrvOpstatus_u8 == DCM_PROCESSSERVICE)
        {
            dataRetVal_u8 =  Dcm_Lok_WMBAUpdateStatus (pMsgContext,dataNegRespCode_u8);

        }

        if(*dataNegRespCode_u8 != 0)
        {

            Dcm_SrvOpstatus_u8 = DCM_INITIAL;
            dataRetVal_u8=E_NOT_OK;
        }
   }
    return dataRetVal_u8;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
