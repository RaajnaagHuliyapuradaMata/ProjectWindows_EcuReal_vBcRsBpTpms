

#ifndef DEM_NVM_H
#define DEM_NVM_H

#include "NvM.hpp"
#include "Dem_Main.hpp"
#include "Dem_Nvm_Types.hpp"
#include "Dem_Array.hpp"
#include "Dem_Types.hpp"
#include "Dem_Cfg_Main.hpp"
#include "rba_DiagLib_Bits8.hpp"
#include "Dem_NvmHashIdNvData.hpp"

#define DEM_START_SEC_VAR_CLEARED
#include "Dem_MemMap.hpp"

DEM_ARRAY_DECLARE(Dem_NvMBlockStatusDoubleBufferType, Dem_NvMBlockStatusDoubleBuffer, DEM_NVM_CFG_NUM_BLOCKS_TOTAL);
DEM_ARRAY_DECLARE(Dem_NvMStorageBufferType, Dem_NvMStorageBuffer, DEM_NVM_CFG_NUM_STORAGEBUFFER);

extern Dem_EraseAllStatusType Dem_EraseAllNvMDataStatus;
extern boolean Dem_NvMAnyClearFailed;
#if(DEM_CFG_TRIGGER_TO_STORE_NVM_SUPPORTED)
extern boolean Dem_NvMImmediateStorageRequested;
#endif

#define DEM_STOP_SEC_VAR_CLEARED
#include "Dem_MemMap.hpp"

#define DEM_START_SEC_CONST
#include "Dem_MemMap.hpp"

DEM_ARRAY_DECLARE_CONST(NvM_BlockIdType, Dem_NvMBlockMap2NvmId, DEM_NVM_CFG_NUM_BLOCKS_TOTAL);
DEM_ARRAY_DECLARE_CONST(Dem_NvmBlockIdExtendedType, Dem_NvmBlockIdExtended, DEM_NVM_CFG_NUM_BLOCKS_EXTENDED);
DEM_ARRAY_DECLARE_CONST(Dem_NvmCopyFunction, DemCopyFctPtrTable, DEM_NVM_CFG_COPYFCT_NUM);
#if(DEM_CFG_ERASE_ALL_DATA_SUPPORTED == DEM_CFG_ERASE_ALL_WITH_HASHID_CHECK)
DEM_ARRAY_DECLARE_CONST(Dem_NvmHashIdType, Dem_HashIdInRom, DEM_NVM_HASH_ID_SIZE);
#endif

#define DEM_STOP_SEC_CONST
#include "Dem_MemMap.hpp"

DEM_INLINE NvM_BlockIdType Dem_NvMGetNvMBlocKId(Dem_NvmBlockIdType id)
{
    return Dem_NvMBlockMap2NvmId[id];
}

DEM_INLINE Dem_NvmResultType Dem_NvmGetStatus (Dem_NvmBlockIdType id)
{
    NvM_RequestResultType result;
    Dem_NvmResultType returnValue;
   if(NvM_GetErrorStatus (Dem_NvMGetNvMBlocKId(id), &result) == E_NOT_OK)
   {
        returnValue = DEM_NVM_FAILED;
   }
   else{
        switch(result)
        {
            case NVM_REQ_CANCELED:
                returnValue = DEM_NVM_CANCELED;
                break;

            case NVM_REQ_OK:
            case NVM_REQ_REDUNDANCY_FAILED:
            case NVM_REQ_RESTORED_FROM_ROM:
                returnValue = DEM_NVM_SUCCESS;
                break;

            case NVM_REQ_PENDING:
                returnValue = DEM_NVM_PENDING;
                break;

            case NVM_REQ_NV_INVALIDATED:
                returnValue = DEM_NVM_INVALID;
                break;

            case NVM_REQ_INTEGRITY_FAILED:
                returnValue = DEM_NVM_INTEGRITY_FAILED;
                break;

            case NVM_REQ_BLOCK_SKIPPED:
                returnValue = DEM_NVM_BLOCK_SKIPPED;
                break;

            default:

                returnValue = DEM_NVM_FAILED;
                break;
        }
   }
    return returnValue;
}

DEM_INLINE void Dem_NvMWriteBlockOnShutdown(Dem_NvmBlockIdType id)
{
    Dem_NvMBlockStatusDoubleBuffer[id][DEM_NVM_STATUSINDEX_SHUTDOWN] = DEM_NVM_STATUSBITMASK_SHUTDOWN;
}

DEM_INLINE void Dem_NvMWriteBlockImmediate(Dem_NvmBlockIdType id)
{
    Dem_NvMBlockStatusDoubleBuffer[id][DEM_NVM_STATUSINDEX_IMMEDIATE] = DEM_NVM_STATUSBITMASK_IMMEDIATE;
}

DEM_INLINE void Dem_NvMClearBlockByWrite(Dem_NvmBlockIdType id)
{
    Dem_NvMBlockStatusDoubleBuffer[id][DEM_NVM_STATUSINDEX_CLEAR] = DEM_NVM_STATUSBITMASK_CLEAR;
}

DEM_INLINE void Dem_NvMClearBlockByInvalidate(Dem_NvmBlockIdType id)
{
    Dem_NvMBlockStatusDoubleBuffer[id][DEM_NVM_STATUSINDEX_CLEAR] = DEM_NVM_STATUSBITMASK_INVALIDATE;
}

DEM_INLINE void Dem_NvMExcludeBlockFromStatemachine(Dem_NvmBlockIdType id, boolean exclude)
{
   if(exclude)
   {
        Dem_NvMBlockStatusDoubleBuffer[id][DEM_NVM_STATUSINDEX_EXCLUDE] = DEM_NVM_STATUSBITMASK_EXCLUDE;
   }
   else{
        Dem_NvMBlockStatusDoubleBuffer[id][DEM_NVM_STATUSINDEX_EXCLUDE] = DEM_NVM_STATUSBITMASK_NONE;
   }
}

void Dem_NvMInit(void);
void Dem_NvMMainFunction(void);
void Dem_NvMShutdown(void);
boolean Dem_NvMIsClearPending(void);
boolean Dem_NvMIsImmediatePending(void);
boolean Dem_NvMIsBlockClearPending( Dem_NvmBlockIdType demNvMId);
boolean Dem_NvMIsBlockAllowedToBeExcluded(Dem_NvmBlockIdType demNvMId);
boolean Dem_NvMIsBlockExcluded( Dem_NvmBlockIdType demNvMId);
void Dem_NvMNormalMemCopy(void* Dest_pv, const void* Src_pcv, uint32 numBytes_s32);

#if(DEM_CFG_ERASE_ALL_DATA_SUPPORTED != DEM_CFG_ERASE_ALL_OFF)
Dem_HashIdCheckResultType Dem_NvmIsHashIDChanged(void);
#endif

DEM_INLINE void Dem_NvMStartClear(void){
    Dem_NvMAnyClearFailed = FALSE;
}

DEM_INLINE boolean Dem_NvMIsClearFailed(void){
    return Dem_NvMAnyClearFailed;
}

#if(DEM_CFG_TRIGGER_TO_STORE_NVM_SUPPORTED)
DEM_INLINE void Dem_NvMSetImmediateStorageRequested(boolean state)
{
    Dem_NvMImmediateStorageRequested = state;
}

DEM_INLINE boolean Dem_NvMIsImmediateStorageRequested(void){
    return Dem_NvMImmediateStorageRequested;
}
#endif

DEM_INLINE uint8 Dem_NvMGetInvalidateAllNvMBlocksStatus(void){
    return Dem_EraseAllNvMDataStatus;
}

DEM_INLINE Dem_boolean_least Dem_NvMIsInvalidateAllNVMBlocksRequested (void){
#if(DEM_CFG_ERASE_ALL_DATA_SUPPORTED == DEM_CFG_ERASE_ALL_WITH_HASHID_CHECK)
   return ((Dem_EraseAllNvMDataStatus == DEM_ERASE_ALL_STATUS_PENDING)||(Dem_EraseAllNvMDataStatus == DEM_ERASE_ALL_STATUS_HASHID_WRITE_PENDING));
#elif(DEM_CFG_ERASE_ALL_DATA_SUPPORTED == DEM_CFG_ERASE_ALL_WITHOUT_HASHID_CHECK)
   return (Dem_EraseAllNvMDataStatus == DEM_ERASE_ALL_STATUS_PENDING);
#else
   return FALSE;
#endif
}
#endif

