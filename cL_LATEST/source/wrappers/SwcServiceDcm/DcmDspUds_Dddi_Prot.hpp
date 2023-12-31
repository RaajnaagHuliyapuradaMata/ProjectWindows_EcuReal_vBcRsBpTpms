

#ifndef DCMDSPUDS_DDDI_PROT_H
#define DCMDSPUDS_DDDI_PROT_H

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))

#define DCM_DEFINITION_BY_ID                (0x01u)
#define DCM_DEFINITION_BY_MEMORYADDRESS     (0x02u)
#define DCM_DDDI_CLEAR_DYNAMIC_IDENTIFIER   (0x03u)

#define DCM_DDDI_MEMADDR_MINLEN             (0x06u)

#define DCM_STACK_BUFFER  0u
#define DCM_RAM_BUFFER    1u

typedef struct{
      uint32 sigPosnBit_u32;
      uint32 sigDataSize_u32;
}Dcm_DynamicSignalConfig_tst;

#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern const Dcm_DddiMainConfig_tst Dcm_DDDIBaseConfig_cast[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern Dcm_DynamicSignalConfig_tst Dcm_DynamicSignalConfig_cast[];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
extern uint16 Dcm_DddiCalculateTableSize_u16(void);
void Dcm_DddiResetCompleteContext(Dcm_DddiIdContext_tst * adrContext_pst);
void Dcm_DddiResetProcessingInfoInContext(Dcm_DddiIdContext_tst * adrPtrToContext_pst);

Std_ReturnType Dcm_DddiReadById_u8(const Dcm_DddiDefId_tst * adrRecord_pst
   ,                                                 uint16 * adrLength_pu16
   ,                                                 uint8 * adrData_pu8);

Std_ReturnType Dcm_DddiRead_u8(const Dcm_DddiMainConfig_tst * adrConfig_pcst
   ,                                           uint8 * adrData_pu8
   ,                                           Dcm_NegativeResponseCodeType * dataNegRespCode_u8);

Std_ReturnType Dcm_DddiGetLen_u8(const Dcm_DddiMainConfig_tst * adrConfig_pcst
   ,                                             uint32 * adrLen_pu32);

Std_ReturnType Dcm_DddiGetCondition_u8(const Dcm_DddiMainConfig_tst * adrConfig_pcst
   ,                                                   Dcm_NegativeResponseCodeType * dataNegRespCode_u8);

Std_ReturnType Dcm_DspGetIndexOfDDDI_u8(uint16 dataDid_u16, uint16 * idxIndex_u16);

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_DDDI_MIN_LENGTH (1u)

typedef enum{
    DCM_DDDI_IDLE
   ,   DCM_DDDI_NEGRESP
   ,   DCM_DDDI_GETLENGTH
   ,   DCM_DDDI_GETSUPPORT
   ,   DCM_DDDI_SENDRESP
  }
Dcm_DddiServiceStatus_ten;
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern Dcm_DddiServiceStatus_ten Dcm_DspStDddi_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
extern Dcm_OpStatusType Dcm_DspDddidOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.hpp"
typedef enum{
    DCM_DDDI_DEFINE_BY_ID_INIT
   ,   DCM_DDDI_DEFINE_BY_ID_GETINDEX
   ,   DCM_DDDI_DEFINE_BY_ID_GETSUPPORT
   ,   DCM_DDDI_DEFINE_BY_ID_GETLENGTH
  }Dcm_DddiDefineById_ten;

#define DCM_DDDI_DEFINE_BY_ID_BLOCKLENGTH (4u)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern Dcm_DddiDefineById_ten Dcm_stAddIdRecords_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
extern uint16 Dcm_AddIdCurrentBlockIndex_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
extern uint32 Dcm_AddIdCurrentLength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
Std_ReturnType Dcm_DcmDddiAddIdRecords_u8( uint16 nrBlocks_u16
   ,                                                       uint16 nrCurrentlyDefinedRecords_u16
   ,                                                       const uint8 * adrSourceBuffer_pcu8
   ,                                                       Dcm_DddiRecord_tst * adrRecord_pst
   ,                                                       Dcm_NegativeResponseCodeType * dataNegRespCode_u8
   ,                                                       uint16 idxIndex_u16
   ,                                                       Dcm_MsgLenType nrResponseBufferLen_u32
                                                       );
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"

typedef enum{
    DCM_DDDI_DEFINE_BY_MEM_INIT
   ,   DCM_DDDI_DEFINE_BY_MEM_GETSUPPORT
  }Dcm_DddiDefineByMem_ten;
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
extern Dcm_DddiDefineByMem_ten Dcm_stAddMemRecords_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
extern uint16 Dcm_AddMemCurrentBlockIndex_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.hpp"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
Std_ReturnType Dcm_DcmDddiAddMemRecords_u8(uint16 nrBlocks_u16
   ,                                                       uint16 nrCurrentlyDefinedRecords_u16
   ,                                                       const uint8 * adrSourceBuffer_pcu8
   ,                                                       Dcm_DddiRecord_tst * adrRecord_pst
   ,                                                       Dcm_NegativeResponseCodeType * dataNegRespCode_u8
   ,                                                       uint8 nrBytesForAddress_u8
   ,                                                       uint8 nrBytesForLength_u8
   ,                                                       uint16 idxIndex_u16
   ,                                                       Dcm_MsgLenType nrResponseBufferLen_u32);
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.hpp"
#endif
#endif

