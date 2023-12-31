

#ifndef DEM_ENVMAIN_H
#define DEM_ENVMAIN_H

#include "Dem_Mapping.hpp"
#include "Dem_Cfg_EnvMain.hpp"
#include "Dem_Cfg_DistMem.hpp"
#include "Dem_EnvExtendedData.hpp"
#include "Dem_EnvFreezeFrame.hpp"
#include "Dem_EnvFFRecNumeration.hpp"
#include "Dem_EnvRecordIterator.hpp"

typedef struct{
   uint8 extDataId;
   uint8 freezeFrameId;
}Dem_EnvDataMap;

#define DEM_START_SEC_CONST
#include "Dem_MemMap.hpp"
extern const Dem_EnvDataMap Dem_Cfg_EnvEventId2EnvData[DEM_EVENTID_ARRAYLENGTH];
#define DEM_STOP_SEC_CONST
#include "Dem_MemMap.hpp"

DEM_INLINE Dem_boolean_least Dem_EnvHasExtendedData(Dem_EventIdType EventId)
{
   return (Dem_Cfg_EnvEventId2EnvData[EventId].extDataId != 0);
}
DEM_INLINE Dem_boolean_least Dem_EnvHasFreezeFrame(Dem_EventIdType EventId)
{
   return (Dem_Cfg_EnvEventId2EnvData[EventId].freezeFrameId != 0);
}

#define DEM_START_SEC_CODE
#include "Dem_MemMap.hpp"

void Dem_EnvCaptureED (Dem_EventIdType EventId, uint8* dest, uint16 destSize DEM_DEBUGDATA_PARAM(Dem_DebugDataType debug0, Dem_DebugDataType debug1));

#if(DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)
void Dem_EnvCaptureForDisturbanceMemory(Dem_EventIdType EventId, uint8* dest, uint16 destSize  DEM_DEBUGDATA_PARAM(Dem_DebugDataType debug0, Dem_DebugDataType debug1));
#endif
void Dem_EnvCaptureFF (Dem_EventIdType EventId, uint8* dest, uint16 destSize DEM_DEBUGDATA_PARAM(Dem_DebugDataType debug0, Dem_DebugDataType debug1));
void Dem_EnvCopyRawFF (Dem_EventIdType EventId, uint8* dest, uint16 destSize, uint8 ffIndex, const uint8* src);
void Dem_EnvCopyRawED (Dem_EventIdType EventId, uint8* dest, uint16 destSize, const uint8* src, Dem_EnvTriggerParamType* triggerParam);
Dem_boolean_least Dem_EnvIsEDRNumberStored(Dem_EventIdType EventId, uint8 RecordNumber, const Dem_EvMemEventMemoryType *EventMemory);

Dem_boolean_least Dem_EnvIsEDRNumberValid(Dem_EventIdType EventId, uint8 RecordNumber, Dem_TriggerType* trigger);
Std_ReturnType Dem_EnvRetrieveEDR(Dem_EventIdType EventId, uint8 RecordNumber, uint8* dest, uint16* destSize, const uint8* src, Dem_EvMemEventMemoryType *evMemLocation);
Std_ReturnType Dem_EnvRetrieveFF(Dem_EventIdType EventId, uint8* dest, uint16* destSize, uint8 ffIndex, const uint8* src, Dem_EvMemEventMemoryType *evMemLocation);
uint8 Dem_EnvGetTotalNumberOfStoredFFForEvent(Dem_EventIdType EventId, const Dem_EvMemEventMemoryType* EvMem);

Std_ReturnType Dem_EnvGetSizeOfEDR(Dem_EventIdType EventId, uint8 RecordNumber, uint16* size);
Std_ReturnType Dem_EnvGetSizeOfFF(Dem_EventIdType EventId, uint16* size);
Std_ReturnType Dem_EnvGetSizeOfEDR_AllOrObdStored(Dem_EventIdType EventId, uint16* size, const Dem_EvMemEventMemoryType *EventMemory, boolean OnlyOBD);

Std_ReturnType Dem_EnvRetrieveRawED(Dem_EventIdType EventId, uint8* dest, uint16* destSize, const uint8* src, Dem_EvMemEventMemoryType *evMemLocation);
Dem_boolean_least Dem_EnvRetrieveRawEDR(Dem_EventIdType EventId, uint8 RecordNumber, uint8* dest, uint16* destSize, const uint8* src, Dem_EvMemEventMemoryType *evMemLocation);
Std_ReturnType Dem_EnvRetrieveRawFF(Dem_EventIdType EventId, uint8* dest, uint16* destSize, uint8 ffIndex, const uint8* src, Dem_EvMemEventMemoryType *evMemLocation);
Dem_boolean_least Dem_EnvRetrieveRawDid(Dem_EventIdType EventId, uint8* dest, uint16* destSize, uint8 ffIndex, uint16 did, const uint8* src, Dem_EvMemEventMemoryType *evMemLocation);

DEM_INLINE uint16 Dem_EnvGetTotalNumOfConfEDR_OBDOrAll(Dem_EventIdType EventId, boolean OnlyOBD)
{
   uint8 edId = Dem_Cfg_EnvEventId2EnvData[EventId].extDataId;
   uint16 EDRecId;
   uint16 TotalConfEDR = 0;

   for(EDRecId = Dem_Cfg_EnvExtData[edId - 1].extDataRecIndex; EDRecId <Dem_Cfg_EnvExtData[edId].extDataRecIndex; EDRecId++)
   {
        uint8 RecNum = Dem_EnvEDRGetRecordNumber(Dem_Cfg_EnvExtData2ExtDataRec[EDRecId]);
        if((!OnlyOBD) || (RecNum >= DEM_START_OF_OBD_ED_REC_NUM))
        {
            TotalConfEDR ++;
        }
   }
    return TotalConfEDR;
}

DEM_INLINE boolean Dem_EnvEDRIteratorIsValid(const Dem_EnvRecordIteratorType* it)
{
    return (it->current_recIndex < it->end_recIndex);
}

DEM_INLINE uint8 Dem_EnvEDRIteratorCurrentRecNum(const Dem_EnvRecordIteratorType* it)
{
    return Dem_Cfg_EnvExtDataRec[Dem_Cfg_EnvExtData2ExtDataRec[it->current_recIndex]].recordNumber;
}

DEM_INLINE void Dem_EnvEDRIteratorNext(Dem_EnvRecordIteratorType* it)
{
   it->current_recIndex++;
   if(it->requestedRecNum == 0xFE)
   {
        while((Dem_EnvEDRIteratorIsValid(it)) && (Dem_EnvEDRIteratorCurrentRecNum(it) < DEM_START_OF_OBD_ED_REC_NUM) )
        {
            it->current_recIndex++;
        }
   }
}

DEM_INLINE void Dem_EnvEDRIteratorNew(Dem_EnvRecordIteratorType* it, uint8 RecordNumber, Dem_EventIdType EventId)
{
   uint8 edId = Dem_Cfg_EnvEventId2EnvData[EventId].extDataId;
    Dem_TriggerType Trigger;

   it->isRequestedRecValid = TRUE;
   it->requestedRecNum = RecordNumber;
   it->current_recIndex = Dem_Cfg_EnvExtData[edId - 1].extDataRecIndex;
   it->end_recIndex = Dem_Cfg_EnvExtData[edId].extDataRecIndex;

   if(RecordNumber == 0xFF)
   {

   }
   else if(RecordNumber == 0xFE)
   {
        if( Dem_EnvEDRIteratorCurrentRecNum(it) < DEM_START_OF_OBD_ED_REC_NUM)
        {
            Dem_EnvEDRIteratorNext(it);
        }
   }
   else if(Dem_EnvEDIsRecordNumberValid(edId, RecordNumber, &Trigger, &(it->current_recIndex))) // Current Record Iterator gets initialized in this call
   {
        it->end_recIndex = (it->current_recIndex + 1);
   }
   else{
        it->isRequestedRecValid = FALSE;
        it->current_recIndex = it->end_recIndex;
   }
}

DEM_INLINE uint16 Dem_EnvEDRIteratorCurrent(const Dem_EnvRecordIteratorType* it)
{
    return it->current_recIndex;
}

DEM_INLINE uint8 Dem_EnvEDRIteratorRequestedRecNum(const Dem_EnvRecordIteratorType* it)
{
    return it->requestedRecNum;
}

DEM_INLINE boolean Dem_EnvEDRIteratorIsRequestedRecValid(const Dem_EnvRecordIteratorType* it)
{
    return it->isRequestedRecValid;
}

DEM_INLINE boolean Dem_EnvFFRecIteratorIsValid(const Dem_EnvRecordIteratorType* it)
{
    return (it->current_recIndex < it->end_recIndex);
}

DEM_INLINE void Dem_EnvFFRecIteratorNext(Dem_EnvRecordIteratorType* it)
{
   it->current_recIndex++;
}

DEM_INLINE void Dem_EnvFFRecIteratorNew(Dem_EnvRecordIteratorType* it, uint8 RecordNumber, Dem_EventIdType EventId)
{
   it->isRequestedRecValid = TRUE;
   it->requestedRecNum = RecordNumber;
   it->current_recIndex = 0;
   it->end_recIndex = Dem_EvtParam_GetMaxNumberFreezeFrameRecords(EventId);
   it->EventId = EventId;

   if(RecordNumber == 0xFF)
   {

   }
   else if(Dem_EnvIsFFRecNumValid(EventId, RecordNumber))
   {
        it->current_recIndex = Dem_EnvGetIndexFromFFRecNum(EventId, RecordNumber);
        it->end_recIndex = (it->current_recIndex + 1);
   }
   else{
        it->isRequestedRecValid = FALSE;
        it->current_recIndex = it->end_recIndex;
   }
}

DEM_INLINE uint16 Dem_EnvFFRecIteratorCurrent(const Dem_EnvRecordIteratorType* it)
{
    return it->current_recIndex;
}

DEM_INLINE uint8 Dem_EnvFFRecIteratorCurrentRecNum(const Dem_EnvRecordIteratorType* it)
{
    return Dem_EnvGetFFRecNumFromIndex(it->EventId, (uint8)it->current_recIndex);
}

DEM_INLINE uint8 Dem_EnvFFRecIteratorRequestedRecNum(const Dem_EnvRecordIteratorType* it)
{
    return it->requestedRecNum;
}

DEM_INLINE boolean Dem_EnvFFRecIteratorIsRequestedRecValid(const Dem_EnvRecordIteratorType* it)
{
    return it->isRequestedRecValid;
}

#define DEM_STOP_SEC_CODE
#include "Dem_MemMap.hpp"

#endif

