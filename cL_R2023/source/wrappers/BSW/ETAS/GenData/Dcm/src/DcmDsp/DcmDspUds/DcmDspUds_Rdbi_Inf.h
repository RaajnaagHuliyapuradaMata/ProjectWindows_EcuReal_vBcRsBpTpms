

#ifndef DCMDSPUDS_RDBI_INF_H
#define DCMDSPUDS_RDBI_INF_H

#include "Dcm.h"
#include "rba_BswSrv.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#include "DcmCore_DslDsd_Prot.h"

#include "DcmDspUds_Rdbi_Prot.h"

#include "DcmDspUds_Uds_Prot.h"

#if(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Dddi_Prot.h"
#endif

#if (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
#include "Dcm_Lcfg_DspUds.h"
#endif

#include "DcmAppl.h"

#endif

#endif
