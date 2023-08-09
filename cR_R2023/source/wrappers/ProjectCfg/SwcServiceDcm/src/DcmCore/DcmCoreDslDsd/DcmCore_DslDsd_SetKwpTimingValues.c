

#include "DcmCore_DslDsd_Inf.h"

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

FUNC(void,DCM_CODE) Dcm_SetKwpTimingValues (void)
{

    if(DCM_IS_KWPPROT_ACTIVE() != FALSE)
    {

    SchM_Enter_Dcm_DsldTimer_NoNest();

    Dcm_DsldTimer_st.dataTimeoutP2max_u32 = Dcm_DsldKwpReqTiming_st.P2_max_u32;
    Dcm_DsldTimer_st.dataTimeoutP3max_u32 = Dcm_DsldKwpReqTiming_st.P3_max_u32;

    Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 = Dcm_DsldTimer_st.dataTimeoutP3max_u32;

    DCM_TimerSetNew(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,Dcm_DsldTimer_st.dataTimeoutP3max_u32)
    SchM_Exit_Dcm_DsldTimer_NoNest();
    }
}

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif

