

#ifndef RBA_DIAGLIB_MEMUTILS_H
#define RBA_DIAGLIB_MEMUTILS_H

#include "Std_Types.hpp"
#include "rba_BswSrv.hpp"

#define RBA_DIAGLIB_MEMCPY(xDest_p, xSrc_pc, numBytes_u32)                  rba_DiagLib_MemUtils_MemCpy((uint8*)(xDest_p),(const uint8*)(xSrc_pc),(uint32)(numBytes_u32))
#define RBA_DIAGLIB_MEMSET(xDest_p, xPattern_u32, numBytes_u32)             rba_DiagLib_MemUtils_MemSet((uint8*)(xDest_p),(sint32)(xPattern_u32),(uint32)(numBytes_u32))
#define RBA_DIAGLIB_MEMCMP(xSrc1_pc, xSrc2_pc, numBytes_u32)                rba_DiagLib_MemUtils_MemCmp((const uint8*)(xSrc1_pc),(const uint8*)(xSrc2_pc),(uint32)(numBytes_u32))

#define RBA_DIAGLIB_START_SEC_CODE
#include "rba_DiagLib_MemMap.hpp"

LOCAL_INLINE void rba_DiagLib_MemUtils_MemCpy(uint8* xDest_p, const uint8* xSrc_pc, uint32 numBytes_s32)
{

    (void) rba_BswSrv_MemCopy(xDest_p, xSrc_pc, numBytes_s32);
}

LOCAL_INLINE void rba_DiagLib_MemUtils_MemSet(uint8* xDest_pv, sint32 xPattern_u32, uint32 numBytes_s32)
{

    (void) rba_BswSrv_MemSet(xDest_pv, xPattern_u32, numBytes_s32);
}

LOCAL_INLINE sint32 rba_DiagLib_MemUtils_MemCmp(const uint8* xSrc1_pc, const uint8* xSrc2_pc, uint32 numBytes_s32)
{

    return rba_BswSrv_MemCompare(xSrc1_pc, xSrc2_pc, numBytes_s32);
}

#define RBA_DIAGLIB_STOP_SEC_CODE
#include "rba_DiagLib_MemMap.hpp"

#endif
