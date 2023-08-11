

#ifndef FLS_VERSION_H
#define FLS_VERSION_H

#include "Fls.h"
#if (FLS_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
#endif

#include "Dem.h"
#if (FLS_CRITICAL_SECTION_PROTECTION == STD_ON)

#if (FLS_AR_VERSION  == FLS_AR_HIGHER_VERSION)

#include "Rte.h"
#elif (FLS_AR_VERSION  == FLS_AR_LOWER_VERSION)
#include "SchM.h"
#endif
#endif

#include "MemIf.h"

#include "Os.h"

#if (FLS_AR_VERSION  == FLS_AR_HIGHER_VERSION)

#define FLS_VERSION_AR_RELEASE_MAJOR_VERSION      FLS_AR_RELEASE_MAJOR_VERSION
#define FLS_VERSION_AR_RELEASE_MINOR_VERSION      FLS_AR_RELEASE_MINOR_VERSION
#define FLS_VERSION_AR_RELEASE_REVISION_VERSION   \
                                               FLS_AR_RELEASE_REVISION_VERSION
#elif (FLS_AR_VERSION  == FLS_AR_LOWER_VERSION)

#define FLS_VERSION_AR_MAJOR_VERSION   FLS_AR_MAJOR_VERSION_VALUE
#define FLS_VERSION_AR_MINOR_VERSION   FLS_AR_MINOR_VERSION_VALUE
#define FLS_VERSION_AR_PATCH_VERSION   FLS_AR_PATCH_VERSION_VALUE

#if (FLS_DEV_ERROR_DETECT == STD_ON)
#define FLS_DET_AR_MAJOR_VERSION   2
#define FLS_DET_AR_MINOR_VERSION   2
#endif

#define FLS_DEM_AR_MAJOR_VERSION  3
#define FLS_DEM_AR_MINOR_VERSION  3

#define FLS_SCHM_AR_MAJOR_VERSION  1
#define FLS_SCHM_AR_MINOR_VERSION  2

#define FLS_MEMIF_AR_MAJOR_VERSION  1
#define FLS_MEMIF_AR_MINOR_VERSION  3

#define FLS_OS_AR_MAJOR_VERSION  3
#define FLS_OS_AR_MINOR_VERSION  2
#endif

#define FLS_VERSION_SW_MAJOR_VERSION   FLS_SW_MAJOR_VERSION
#define FLS_VERSION_SW_MINOR_VERSION   FLS_SW_MINOR_VERSION

#endif

