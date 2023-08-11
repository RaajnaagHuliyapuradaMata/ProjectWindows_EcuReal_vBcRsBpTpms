

#ifndef DCMDSPUDS_REQUESTDOWNLOAD_PRIV_H
#define DCMDSPUDS_REQUESTDOWNLOAD_PRIV_H

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED != DCM_CFG_OFF)

#define DCM_DSP_REQUESTDOWNLOAD_MINREQLEN 0x04u

typedef enum
{
    DCM_DSP_REQUESTDOWNLOAD_IDLE = 0,
    DCM_DSP_REQUESTDOWNLOAD_GETBLOCKNUM ,
    DCM_DSP_REQUESTDOWNLOAD_ERROR
}Dcm_DspRequestDownloadStates_ten;

#endif
#endif

