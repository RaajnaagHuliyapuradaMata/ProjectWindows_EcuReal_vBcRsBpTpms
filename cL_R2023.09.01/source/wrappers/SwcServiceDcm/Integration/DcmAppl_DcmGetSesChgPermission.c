
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Dsc_Inf.hpp"
#include "Rte_Dcm.hpp"

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ( DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF ) )

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

Std_ReturnType DcmAppl_DcmGetSesChgPermission(
   									Dcm_SesCtrlType SesCtrlTypeActive
   ,  									Dcm_SesCtrlType SesCtrlTypeNew
   ,  									Dcm_NegativeResponseCodeType * ErrorCode
   									)
{
    Std_ReturnType retVal = E_OK;
   *ErrorCode = 0x00;

    return (retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

