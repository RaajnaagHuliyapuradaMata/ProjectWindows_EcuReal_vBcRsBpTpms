

#ifndef DEM_PRV_CALLEVTSTCHNGDCBK_H
#define DEM_PRV_CALLEVTSTCHNGDCBK_H

#if(DEM_CFG_TRIGGERFIMREPORTS == DEM_CFG_TRIGGERFIMREPORTS_ON)
#include "FiM.hpp"
#endif
#if(DEM_CFG_TRIGGERDLTREPORTS == DEM_CFG_TRIGGERDLTREPORTS_ON)
#include "Dlt.hpp"
#endif
#if(DEM_CFG_J1939DCM == DEM_CFG_J1939DCM_ON)
#include "Dem_Lok_J1939Dcm.hpp"
#endif
#include "Dem_DTCs.hpp"
#include "Dem_Cfg_EventsCallback.hpp"
#include "Dem_EventStatus.hpp"
#include "Dem_Lok_CallDtcStChngdCbk.hpp"

DEM_INLINE void Dem_CallBackTriggerOnEventStatus (
   	Dem_EventIdType EventId
   ,  	Dem_UdsStatusByteType EventStatusOld
   ,  	Dem_UdsStatusByteType EventStatusNew
   ,  	Dem_UdsStatusByteType dtcStByteOld
)
{
#if( DEM_CFG_DTC_STATUSCHANGEDCALLBACK == DEM_CFG_DTC_STATUSCHANGEDCALLBACK_ON )||(DEM_CFG_J1939DCM == DEM_CFG_J1939DCM_ON)
    Dem_DtcIdType dtcId;
    Dem_UdsStatusByteType dtcStByteNew;
    Dem_DtcCodeType dtcCode;
#endif

    DEM_ASSERT_ISNOTLOCKED();
    DEM_UNUSED_PARAM(dtcStByteOld);
    DEM_UNUSED_PARAM(EventId);
    DEM_UNUSED_PARAM(EventStatusOld);
    DEM_UNUSED_PARAM(EventStatusNew);

#if(DEM_CFG_EVT_STATUS_CHANGE_NUM_CALLBACKS > 0)
    Dem_CallEventStatusChangedCallBack(EventId, EventStatusOld, EventStatusNew);
#endif

#if(DEM_CFG_GLOBAL_EVT_ST_CH_CALLBACK == DEM_CFG_GLOBAL_EVT_ST_CH_CALLBACK_ON)
    Dem_CallGlobalEventStatusChangedCallBack(EventId, EventStatusOld, EventStatusNew);
#endif

#if( DEM_CFG_TRIGGERDLTREPORTS == DEM_CFG_TRIGGERDLTREPORTS_ON )
    Dlt_DemTriggerOnEventStatus(EventId, EventStatusOld, EventStatusNew);
#endif
#if( DEM_CFG_DTC_STATUSCHANGEDCALLBACK == DEM_CFG_DTC_STATUSCHANGEDCALLBACK_ON )||(DEM_CFG_J1939DCM == DEM_CFG_J1939DCM_ON)
   if( Dem_EventIdIsDtcAssigned(EventId) )
   {
        dtcId = Dem_DtcIdFromEventId(EventId);
        if( Dem_DtcIsSupported(dtcId) && (Dem_DtcUsesOrigin(dtcId, DEM_DTC_ORIGIN_PRIMARY_MEMORY)))
        {
            dtcStByteNew = (uint8)(Dem_DtcStatusByteRetrieve (dtcId) & DEM_CFG_DTCSTATUS_AVAILABILITYMASK);
            if(dtcStByteNew != dtcStByteOld)
            {
                dtcCode = Dem_GetDtcCode(dtcId);
#if( DEM_CFG_DTC_STATUSCHANGEDCALLBACK == DEM_CFG_DTC_STATUSCHANGEDCALLBACK_ON )
                Dem_CallbackDTCStatusChangedIndication( dtcCode, dtcStByteOld, dtcStByteNew);
#endif
#if(DEM_CFG_J1939DCM == DEM_CFG_J1939DCM_ON)
                Dem_J1939DTCStatusChangedIndicationCallback(dtcId, dtcStByteOld, dtcStByteNew);
#endif
            }
        }
   }
#endif
}

DEM_INLINE void Dem_CallBackTriggerOnMultipleEventStatus(
        Dem_EventIdType EventId
   ,       Dem_UdsStatusByteType EventStatusOld
   ,       Dem_UdsStatusByteType EventStatusNew
   ,       Dem_DTCStatusAndUpdateInfoType* Dem_DTCStatusAndUpdateInfo)
{
    DEM_UNUSED_PARAM(EventId);
    DEM_UNUSED_PARAM(EventStatusOld);
    DEM_UNUSED_PARAM(EventStatusNew);
    DEM_UNUSED_PARAM(Dem_DTCStatusAndUpdateInfo);

#if(DEM_CFG_EVT_STATUS_CHANGE_NUM_CALLBACKS > 0)
    Dem_CallEventStatusChangedCallBack(EventId, EventStatusOld, EventStatusNew);
#endif
#if(DEM_CFG_GLOBAL_EVT_ST_CH_CALLBACK == DEM_CFG_GLOBAL_EVT_ST_CH_CALLBACK_ON)
    Dem_CallGlobalEventStatusChangedCallBack(EventId, EventStatusOld, EventStatusNew);
#endif
#if( DEM_CFG_TRIGGERDLTREPORTS == DEM_CFG_TRIGGERDLTREPORTS_ON )
    Dlt_DemTriggerOnEventStatus(EventId, EventStatusOld, EventStatusNew);
#endif
#if( DEM_CFG_DTC_STATUSCHANGEDCALLBACK == DEM_CFG_DTC_STATUSCHANGEDCALLBACK_ON )
   if( Dem_EventIdIsDtcAssigned(EventId) )
   {
        Dem_DtcIdType dtcId = Dem_DtcIdFromEventId(EventId);
        if( Dem_DtcIsSupported(dtcId) && (Dem_DtcUsesOrigin(dtcId, DEM_DTC_ORIGIN_PRIMARY_MEMORY)))
        {
            Dem_DTCStatusAndUpdateInfo[dtcId].isStatusChangeToBeCalculated = TRUE;
        }
   }
#endif
}

DEM_INLINE void Dem_StatusChange_GetOldStatus (
   	Dem_EventIdType EventId
   ,  	Dem_UdsStatusByteType *isoByteOld
   ,  	Dem_UdsStatusByteType *dtcStByteOld
)
{
#if(( DEM_CFG_DTC_STATUSCHANGEDCALLBACK == DEM_CFG_DTC_STATUSCHANGEDCALLBACK_ON )||(DEM_CFG_J1939DCM == DEM_CFG_J1939DCM_ON))
   Dem_DtcIdType dtcId;
#endif
   *(isoByteOld) = Dem_EvtGetIsoByte(EventId);
    *dtcStByteOld = 0;
#if(( DEM_CFG_DTC_STATUSCHANGEDCALLBACK == DEM_CFG_DTC_STATUSCHANGEDCALLBACK_ON )||(DEM_CFG_J1939DCM == DEM_CFG_J1939DCM_ON))
   if( Dem_EventIdIsDtcAssigned(EventId) )
   {
   	dtcId = Dem_DtcIdFromEventId(EventId);
   	if( Dem_DtcIsSupported(dtcId) )
   	{
   		*(dtcStByteOld) = (uint8)(Dem_DtcStatusByteRetrieve (dtcId) & DEM_CFG_DTCSTATUS_AVAILABILITYMASK);
   	}
   }
#else
   (void) dtcStByteOld;
#endif
}

#if(DEM_CFG_TRIGGERFIMREPORTS == DEM_CFG_TRIGGERFIMREPORTS_ON)
DEM_INLINE void Dem_FimTriggerOnEventStatus(Dem_EventIdType EventId, Dem_UdsStatusByteType isoByteOld, Dem_UdsStatusByteType isoByteNew)
{

        if(Dem_Is_Fim_Initialized())
        {
            DEM_ENTERLOCK_MON();
            FiM_DemTriggerOnEventStatus (EventId, isoByteOld, isoByteNew);
            DEM_EXITLOCK_MON();
        }
}
#endif

DEM_INLINE void Dem_TriggerOn_EventStatusChange (
        Dem_EventIdType EventId
   ,       Dem_UdsStatusByteType isoByteOld
   ,       Dem_UdsStatusByteType isoByteNew
   ,       Dem_UdsStatusByteType dtcStByteOld
)
{
   if( isoByteNew != isoByteOld )
   {
#if(DEM_CFG_TRIGGERFIMREPORTS == DEM_CFG_TRIGGERFIMREPORTS_ON)
        Dem_FimTriggerOnEventStatus(EventId, isoByteOld, isoByteNew);
#endif
        Dem_CallBackTriggerOnEventStatus(EventId,isoByteOld,isoByteNew,dtcStByteOld);
   }
}

DEM_INLINE void Dem_TriggerOn_MultipleEventStatusChange(
        Dem_EventIdType EventId
   ,       Dem_UdsStatusByteType isoByteOld
   ,       Dem_UdsStatusByteType isoByteNew
   ,       Dem_DTCStatusAndUpdateInfoType* Dem_DTCStatusAndUpdateInfo)
{
   if( isoByteNew != isoByteOld )
   {
#if(DEM_CFG_TRIGGERFIMREPORTS == DEM_CFG_TRIGGERFIMREPORTS_ON)
        Dem_FimTriggerOnEventStatus(EventId, isoByteOld, isoByteNew);
#endif
        Dem_CallBackTriggerOnMultipleEventStatus(EventId,isoByteOld,isoByteNew, Dem_DTCStatusAndUpdateInfo);
   }
}
#endif

