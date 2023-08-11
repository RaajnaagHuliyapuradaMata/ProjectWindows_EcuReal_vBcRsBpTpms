
#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

void Dcm_GetKwpTimingValues(
                                           Dcm_TimerModeType TimerMode,
                                           Dcm_Dsld_KwpTimerServerType * TimerServerCurrent
                                          )
{
    uint8 idxLimitTmg_u8;

    if(TimerServerCurrent != NULL_PTR)
    {

        idxLimitTmg_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].timings_limit_idx_u8;

        if(TimerMode == DCM_CURRENT)
        {

            SchM_Enter_Dcm_DsldTimer_NoNest();
            TimerServerCurrent-> P2_max_u32 = Dcm_DsldTimer_st.dataTimeoutP2max_u32;
            TimerServerCurrent-> P3_max_u32 = Dcm_DsldTimer_st.dataTimeoutP3max_u32;
            SchM_Exit_Dcm_DsldTimer_NoNest();
        }
        else
        {

            TimerServerCurrent-> P2_max_u32 = Dcm_Dsld_Limit_timings_acs[idxLimitTmg_u8].P2_max_u32;
            TimerServerCurrent-> P3_max_u32 = Dcm_Dsld_Limit_timings_acs[idxLimitTmg_u8].P3_max_u32;
        }
    }
	else
	{
		
		DCM_DET_ERROR(DCM_KWPTIMING_ID , DCM_E_PARAM_POINTER )
	}
}

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#endif
