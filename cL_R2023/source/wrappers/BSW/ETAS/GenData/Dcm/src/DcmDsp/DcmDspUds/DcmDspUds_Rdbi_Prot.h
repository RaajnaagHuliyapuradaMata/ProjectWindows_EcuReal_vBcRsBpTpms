

#ifndef DCMDSPUDS_RDBI_PROT_H
#define DCMDSPUDS_RDBI_PROT_H

#if (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)

#define DCM_RDBI_SIZE_DID            (0x02u)

typedef enum
{
    DCM_RDBI_IDLE,
    DCM_RDBI_NEG_RESP,
    DCM_RDBI_PROCESS_NEW_DID,
    DCM_RDBI_CHECK_READACCESS,
    DCM_RDBI_CHECK_CONDITIONS,
    DCM_RDBI_GET_LENGTH,
    DCM_RDBI_GET_DATA
}Dcm_StRdbi_ten;
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
extern uint16 Dcm_RdbiReqDidNb_u16;
extern uint16 Dcm_NumOfIndices_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_StRdbi_ten Dcm_stRdbi_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
extern uint32 Dcm_TotalLength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"

typedef enum {
  DCM_LENCALC_RETVAL_OK,
  DCM_LENCALC_RETVAL_ERROR,
  DCM_LENCALC_RETVAL_PENDING
}
Dcm_LenCalcRet_ten;

typedef enum {
  DCM_LENCALC_STATUS_INIT,
  DCM_LENCALC_STATUS_GETINDEX,
  DCM_LENCALC_STATUS_GETLENGTH,
  DCM_LENCALC_STATUS_GETSUPPORT
}
Dcm_LenCalc_ten;
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_LenCalc_ten Dcm_StLenCalc_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern uint8 * Dcm_IdxList_pu8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
extern uint32 Dcm_NumberOfBytesInResponse_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
extern uint16 Dcm_NumberOfProcessedDIDs_u16;
extern uint16 Dcm_NumberOfAcceptedDIDs_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
extern Dcm_OpStatusType Dcm_DspReadDidOpStatus_u8;	
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_MemMap.h"
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
Dcm_LenCalcRet_ten Dcm_DspGetTotalLengthOfDIDs_en(uint8 * adrSourceIds_pu8,
                                                             uint16 nrDids_u16,
                                                             uint16 * adrNumOfIndices_pu16,
                                                             uint32 * adrTotalLength_pu32,
                                                             Dcm_NegativeResponseCodeType * dataNegRespCode_u8);
extern void Dcm_Lok_DspRdbiConfirmation(
	Dcm_IdContextType dataIdContext_u8,
	PduIdType dataRxPduId_u8,
	uint16 dataSourceAddress_u16,
	Dcm_ConfirmationStatusType status_u8
													);
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"
typedef enum
  {
    DCM_GETDATA_RETVAL_OK,
    DCM_GETDATA_RETVAL_INTERNALERROR,
    DCM_GETDATA_RETVAL_PENDING,
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
    DCM_GETDATA_PAGED_BUFFER_TX,
#endif
    DCM_GETDATA_RETVAL_INVALIDCONDITIONS
  } Dcm_GetDataRet_ten;

#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)

  #ifndef DCM_E_DATA_PAGE_FILLED
  #define DCM_E_DATA_PAGE_FILLED  45u
  #endif
#endif

typedef enum
  {
    DCM_GETDATA_STATUS_INIT,
    DCM_GETDATA_STATUS_GETLENGTH,
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
    DCM_GETDATA_STATUS_TRANSMITPAGE,
#endif
    DCM_GETDATA_STATUS_GETDATA
  } Dcm_GetData_ten;
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
extern Dcm_GetData_ten Dcm_GetDataState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
extern uint16 Dcm_GetDataNumOfIndex_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
extern uint32 Dcm_GetDataTotalLength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_MemMap.h"
#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
Dcm_GetDataRet_ten Dcm_GetData_en(const uint8 * adrIdBuffer_pcu8,
                                            uint8 * adrTargetBuffer_pu8,
                                            uint16 nrIndex_u16,
                                            Dcm_NegativeResponseCodeType * dataNegRespCode_u8
                                            );
#else
Dcm_GetDataRet_ten Dcm_GetData_en(const uint8 * adrIdBuffer_pcu8,
                                            uint8 * adrTargetBuffer_pu8,
                                            uint16 nrIndex_u16,
                                            Dcm_NegativeResponseCodeType * dataNegRespCode_u8,
                                            uint32 adrTotalLength_pu32);

#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

#endif

#endif

