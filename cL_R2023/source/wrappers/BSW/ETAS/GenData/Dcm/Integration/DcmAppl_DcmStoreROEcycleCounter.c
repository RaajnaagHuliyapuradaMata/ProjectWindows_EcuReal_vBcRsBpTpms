
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
//::warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif

#include "Dcm_Cfg_Prot.h"
#include "DcmDspUds_Roe_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#if((DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF) && ((DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)))

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
void DcmAppl_DcmStoreROEcycleCounter(uint8 RoeeventID,
                                                                  uint8 CycleValue
                                                                  )
{

    (void)(RoeeventID);
    (void)(CycleValue);

	
    return ;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#endif
#endif
