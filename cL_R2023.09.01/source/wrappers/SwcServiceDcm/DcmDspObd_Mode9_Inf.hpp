

#ifndef DCMDSPOBD_MODE9_INF_H
#define DCMDSPOBD_MODE9_INF_H

#include "Dcm.hpp"
#include "DcmDsp_Lib_Prv.hpp"
#if(DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.hpp"
#endif

#if(DCM_CFG_DSP_OBDMODE9_DEM_SUPP != DCM_CFG_OFF)
#include "Dem.hpp"
#endif

#include "DcmCore_DslDsd_Prot.hpp"

#endif

#endif

