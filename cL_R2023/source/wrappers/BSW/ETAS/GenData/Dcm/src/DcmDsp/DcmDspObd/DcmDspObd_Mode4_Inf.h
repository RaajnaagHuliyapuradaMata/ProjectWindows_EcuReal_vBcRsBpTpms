

#ifndef DCMDSPOBD_MODE4_INF_H
#define DCMDSPOBD_MODE4_INF_H

#include "Dcm.h"
#include "DcmDsp_Lib_Prv.h"

#if (DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)

#if (DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.h"
#endif

#if(DCM_CFG_DSP_OBDMODE4_ENABLED != DCM_CFG_OFF)
#include "Dem.h"
#endif

#include "DcmCore_DslDsd_Prot.h"
#include "DcmAppl.h"

#endif

#endif
