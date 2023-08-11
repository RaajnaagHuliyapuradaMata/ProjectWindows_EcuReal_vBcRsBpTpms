

#ifndef DCMDSPUDS_WMBA_PUB_H
#define DCMDSPUDS_WMBA_PUB_H

#if(DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)

typedef enum
{
    DCM_WMBA_SUPPORT_OK,
    DCM_WMBA_SUPPORT_SESSION_VIOLATED,
    DCM_WMBA_SUPPORT_SECURITY_VIOLATED,
    DCM_WMBA_SUPPORT_CONDITION_VIOLATED
} Dcm_WmbaSupportRet_t;

#endif

#endif
