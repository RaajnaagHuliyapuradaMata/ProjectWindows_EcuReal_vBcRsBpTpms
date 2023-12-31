

#include "Dem_EvBuff.hpp"
#include "Dem_EvBuffDistributor.hpp"
#include "Dem_Bfm.hpp"
#include "Dem_EvMem.hpp"
#include "Dem_EnvMain.hpp"
#include "Dem_Clear.hpp"

#if(DEM_CFG_SUPPORT_PROJECTSPECIFIC_FAILUREMEMORY == TRUE)
#include "Dem_PrjSpecificFailureMemory.hpp"
#endif

#define DEM_START_SEC_VAR_INIT
#include "Dem_MemMap.hpp"
static boolean Dem_isDistributionRunning = FALSE;
#define DEM_STOP_SEC_VAR_INIT
#include "Dem_MemMap.hpp"

DEM_INLINE void Dem_EvBuffDistributorCallReceivers (Dem_EvBuffEvent* fe)
{

   const Dem_EvBuffEvent_MemData* memData_ptr;

#if(DEM_CFG_EVBUFF_STORES_ENVDATA == DEM_CFG_EVBUFF_STORES_ENVDATA_ON)

    memData_ptr = &(fe->memData);

#else

    Dem_EvBuffEvent_MemData memData;
    Dem_EvBuffCaptureAllEnvData(fe, &memData);
    memData_ptr = &memData;

#endif

   if(   (fe->eventType == C_EVENTTYPE_SET)
            || (fe->eventType == C_EVENTTYPE_SET_RESET)
#if(DEM_CFG_STOREWAITINGFORMONITORINGEVENT == TRUE)
            || (fe->eventType == C_EVENTTYPE_SET_WAITINGFORMONITORING)
#endif
    )
   {
        Dem_EvMemSetEventFailedAllMem(fe->eventId, memData_ptr->envData.Buffer);
   }

   if(   (fe->eventType == C_EVENTTYPE_RESET)
            || (fe->eventType == C_EVENTTYPE_SET_RESET)
    )
   {
        Dem_EvMemSetEventPassedAllMem(fe->eventId, memData_ptr->envData.Buffer);
   }

   if(fe->eventType == C_EVENTTYPE_UNROBUST)
   {

        Dem_EvMemSetEventUnRobustAllMem(fe->eventId, memData_ptr->envData.Buffer);
   }

#if(DEM_BFM_ENABLED == DEM_BFM_ON)
    rba_DemBfm_EnvReport((const Dem_EvBuffEvent*)fe, &(memData_ptr->DemRbBfmFailureMemoryData));
#endif

#if(DEM_CFG_SUPPORT_PROJECTSPECIFIC_FAILUREMEMORY == TRUE)
    Dem_ProjectSpecificFailureMemoryReport((const Dem_EvBuffEvent*)fe, &(memData_ptr->DemRbProjectSpecificFailureMemoryData));
#endif
}

#define DEM_START_SEC_VAR_CLEARED
#include "Dem_MemMap.hpp"
static Dem_EvBuffEvent tmpEvBuffLocation;
#define DEM_STOP_SEC_VAR_CLEARED
#include "Dem_MemMap.hpp"
#define DEM_START_SEC_CODE
#include "Dem_MemMap.hpp"

void Dem_EvBuffDistributorMainFunction(void){
   Dem_boolean_least performDistribution = FALSE;
   uint32 idx;
   const Dem_EvBuffEvent* fEvent;

   #if( DEM_BFM_ENABLED == DEM_BFM_ON )
   if( rba_DemBfm_DeleteAllIsInProgress() )
   {
   	return;
   }
   #endif

   DEM_ENTERLOCK_MON();
   if(!Dem_isDistributionRunning)
   {
   	performDistribution = TRUE;
   	Dem_isDistributionRunning = TRUE;
   }
   DEM_EXITLOCK_MON();

   while(performDistribution)
   {
   	DEM_ENTERLOCK_MON();

   	fEvent = Dem_EvBuffGetEvent(&idx);

   	if(fEvent == NULL_PTR)
   	{
   		performDistribution = FALSE;
   		Dem_isDistributionRunning = FALSE;
   	}
   	else
   	{
   		DEM_MEMCPY(&tmpEvBuffLocation, fEvent, DEM_SIZEOF_VAR(tmpEvBuffLocation));

            Dem_EvtSetNextReportRelevantForMemories(fEvent->eventId, FALSE);

   		Dem_EvBuffRemoveEvent(idx);
   	}
   	DEM_EXITLOCK_MON();

   	if(performDistribution)
   	{
   		Dem_EvBuffDistributorCallReceivers(&tmpEvBuffLocation);
   	}
   }
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.hpp"
