
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "DcmDspUds_Dddi_Inf.hpp"
#include "Rte_Dcm.hpp"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

Std_ReturnType DcmAppl_DDDI_Read_Memory_Condition (
   const Dcm_DDDI_DEF_MEM_t * record
   ,   Dcm_NegativeResponseCodeType * NegRespCode
                                                                  )
{
    Std_ReturnType retVal = E_OK;
   *NegRespCode = 0;

    (void)(record);

    return retVal;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif
