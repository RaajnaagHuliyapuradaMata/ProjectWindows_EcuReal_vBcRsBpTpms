

#ifndef FEE_30_SMALLSECTOR_INSTANCE_HANDLER_H
# define FEE_30_SMALLSECTOR_INSTANCE_HANDLER_H

#include "Fee_30_SmallSector.h"

typedef enum
{
  INSTANCE_STATUS_ERASED = 0,
  INSTANCE_STATUS_OK,
  INSTANCE_STATUS_INVALID,
  INSTANCE_STATUS_INCONSISTENT
}Fee_30_SmallSector_Ih_InstanceStatusType;

typedef P2VAR(uint8, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Ih_BufferPointerType;

typedef struct{
  Fee_30_SmallSector_AddressType Fee_30_SmallSector_Ih_CompareAddress;
  uint16 Fee_30_SmallSector_Ih_CompareLength;
  Fee_30_SmallSector_Ih_BufferPointerType Fee_30_SmallSector_Ih_CompareBufferPtr;
}Fee_30_SmallSector_Ih_CompareParameterType;

typedef struct{
  Fee_30_SmallSector_AddressType StartAddress;
  Fee_30_SmallSector_AddressType WP2Address;
  Fee_30_SmallSector_AddressType MgmtAddress;
  uint16 DataLength;
  Fee_30_SmallSector_StaticPatternState WP1State;
  Fee_30_SmallSector_StaticPatternState WP2State;
  Fee_30_SmallSector_StaticPatternState LastPageState;
  uint8 MgmtValue;
  Fee_30_SmallSector_Ih_InstanceStatusType InstanceStatus;
}Fee_30_SmallSector_Ih_InstanceType;

typedef P2VAR(Fee_30_SmallSector_Ih_CompareParameterType, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Ih_CompareParameterPointerType;
typedef P2VAR(Fee_30_SmallSector_Ih_InstanceType, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Ih_InstanceVarPointerType;
typedef P2CONST(Fee_30_SmallSector_Ih_InstanceType, AUTOMATIC, FEE_30_SMALLSECTOR_APPL_DATA) Fee_30_SmallSector_Ih_InstanceConstPointerType;

# define FEE_30_SMALLSECTOR_START_SEC_CODE
# include "MemMap.h"

FUNC(boolean, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_IsLastPageNecessary(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_CreateInstance(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance,
        Fee_30_SmallSector_AddressType InstanceStartAddress, uint16 DataLength);

FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_InitInstance(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance);

FUNC (Fee_30_SmallSector_AddressType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetInstanceStartAddress(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC (Fee_30_SmallSector_AddressType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetEndPatternAddress(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC (Fee_30_SmallSector_AddressType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetManagementAddress(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC (Fee_30_SmallSector_AddressType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetEndAddress(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC (uint16, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetInstanceDataLength(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC (Fee_30_SmallSector_Ih_InstanceStatusType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetInstanceStatus(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC(uint8, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetMgmtValue(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC (Fee_30_SmallSector_StaticPatternState, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetWP1State(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC (Fee_30_SmallSector_StaticPatternState, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetWP2State(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC (Fee_30_SmallSector_StaticPatternState, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetLastPageState(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC(void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_StoreMgmtValueFromBuffer(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance);

FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_SetInstanceStatus(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance, Fee_30_SmallSector_Ih_InstanceStatusType status);

FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_SetWP1State(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance, Fee_30_SmallSector_StaticPatternState state);

FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_SetWP2State(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance, Fee_30_SmallSector_StaticPatternState state);

FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_SetLastPageState(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance, Fee_30_SmallSector_StaticPatternState state);

FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_PrepareNextInstanceProperties(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance,
        Fee_30_SmallSector_AddressType StartAddress);

FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_SetManagementValuesAccordingToStatus(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance);

FUNC (MemIf_JobResultType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_SetNegativeJobResultAccordingToStatus(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_DetermineInstanceStatus(Fee_30_SmallSector_Ih_InstanceVarPointerType Instance);

FUNC (void, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_CorrectSingleBitFlips(Fee_30_SmallSector_Ih_BufferPointerType ManagementByte);

FUNC (Fee_30_SmallSector_StaticPatternState, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetStartPatternFromBuffer(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC (Fee_30_SmallSector_StaticPatternState, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetEndPatternFromBuffer(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC (Fee_30_SmallSector_StaticPatternState, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_GetPageStatusFromBuffer(void);

FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_BlankCheckStartPattern(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_BlankCheckEndPattern(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_BlankCheckLastPage(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_ReadLastPage(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_ReadAllMgmt(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance);

FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_ReadData(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
                                                    Fee_30_SmallSector_Ih_BufferPointerType DataBufferPtr,
                                                    uint16 BlockOffset,
                                                    uint16 ReadLength);

FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_WriteStartPattern(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
    Fee_30_SmallSector_Ih_CompareParameterPointerType CompareParameter);

FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_WriteManagementPage(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
        Fee_30_SmallSector_UserJobParameterType UserJobParameter, Fee_30_SmallSector_Ih_CompareParameterPointerType CompareParameter);

FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_WritePayload(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
        Fee_30_SmallSector_UserJobParameterType UserJobParameter, Fee_30_SmallSector_Ih_CompareParameterPointerType CompareParameter);

FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_WriteLastPage(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
    Fee_30_SmallSector_UserJobParameterType UserJobParameter, Fee_30_SmallSector_Ih_CompareParameterPointerType CompareParameter);

FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_WriteEndPattern(Fee_30_SmallSector_Ih_InstanceConstPointerType Instance,
    Fee_30_SmallSector_Ih_CompareParameterPointerType CompareParameter);

FUNC (Std_ReturnType, FEE_30_SMALLSECTOR_PUBLIC_CODE) Fee_30_SmallSector_Ih_VerifyData(Fee_30_SmallSector_Ih_CompareParameterType CompareParameter);

# define FEE_30_SMALLSECTOR_STOP_SEC_CODE
# include "MemMap.h"

#endif

