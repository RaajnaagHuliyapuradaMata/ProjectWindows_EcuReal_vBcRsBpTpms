
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Cdtcs_Inf.hpp"
#include "Rte_Dcm.hpp"

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

Std_ReturnType DcmAppl_DcmCheckCDTCRecord (
                                    const uint8 * ControlOptionRecord
   ,                                   uint8 Length
   ,                                   Dcm_NegativeResponseCodeType * ErrorCode
                                                                )
{
    Std_ReturnType retVal = E_OK;
   (void)ControlOptionRecord;
    (void)Length;
    *ErrorCode = 0x00;

    return(retVal);
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif

