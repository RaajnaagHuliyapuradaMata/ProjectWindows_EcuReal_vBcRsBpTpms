
#include "Dcm_Cfg_Prot.h"
#include "DcmCore_DslDsd_Inf.h"
#include "Rte_Dcm.h"

#if ((DCM_CFG_ROUTINEARRAY_INSIG != DCM_CFG_OFF)||(DCM_CFG_ROUTINEARRAY_OUTSIG != DCM_CFG_OFF)||(DCM_CFG_RCRANGE_ROUTINEARRAY_INSIG != DCM_CFG_OFF)||(DCM_CFG_RCRANGE_ROUTINEARRAY_OUTSIG != DCM_CFG_OFF))
#define DCM_START_SEC_CONST_8
#include "Dcm_MemMap.h"
static const uint8 CalArraySize_u8[6] = {8,16,32,8,16,32};
#if (LOW_BYTE_FIRST == CPU_BYTE_ORDER)
static  const uint8 EndianessConvLUT_u8[6] = {0,1,0,1,2,3};
#else
static const uint8 EndianessConvLUT_u8[6] = {1,0,3,2,1,0};
#endif
#define DCM_STOP_SEC_CONST_8
#include "Dcm_MemMap.h"
#endif

#define DCM_START_SEC_CODE
#include "Dcm_MemMap.h"

#if (((DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_WRITE_SR_ENABLED != DCM_CFG_OFF ))      ||            \
     ((DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_OBDMODE1_ENABLED != DCM_CFG_OFF)&& (DCM_CFG_DSP_OBDMODE1_SR_ENABLED!=DCM_CFG_OFF))               ||            \
     ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_READ_SR_ENABLED != DCM_CFG_OFF))         ||            \
     ((DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF)&&((DCM_CFG_ROUTINEVARLENGTH==DCM_CFG_OFF)||(DCM_CFG_RCRANGE_ROUTINEVARLENGTH==DCM_CFG_OFF)))                     ||            \
     (DCM_CFG_ROUTINEARRAY_INSIG != DCM_CFG_OFF) || \
     (DCM_CFG_ROUTINEARRAY_OUTSIG != DCM_CFG_OFF) || \
     (DCM_CFG_RCRANGE_ROUTINEARRAY_INSIG != DCM_CFG_OFF) || \
     (DCM_CFG_RCRANGE_ROUTINEARRAY_OUTSIG != DCM_CFG_OFF) || \
     (DCM_CFG_RBA_DEM_SR_ENABLED != DCM_CFG_OFF))

static boolean Dcm_IsEndiannessConversionNecessary(uint8 dataEndianness_u8)
{
    boolean flagConvStatus_b;

    flagConvStatus_b = FALSE;

    if((LOW_BYTE_FIRST==CPU_BYTE_ORDER) && (DCM_BIG_ENDIAN==dataEndianness_u8))
    {

        flagConvStatus_b = TRUE;
    }
    else if((HIGH_BYTE_FIRST==CPU_BYTE_ORDER) && (DCM_LITTLE_ENDIAN==dataEndianness_u8))
    {

        flagConvStatus_b = TRUE;
    }
    else
    {

        flagConvStatus_b = FALSE;
    }

    return flagConvStatus_b;
}
#endif

#if (((DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_WRITE_SR_ENABLED != DCM_CFG_OFF ))   ||     \
     (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF) && ((DCM_CFG_ROUTINEVARLENGTH==DCM_CFG_OFF)||(DCM_CFG_RCRANGE_ROUTINEVARLENGTH==DCM_CFG_OFF)))

uint32 Dcm_GetSignal_u32(uint8 xDataType_u8,
                                    uint16 posnStart_u16,
                                    const uint8 * adrReqBuffer_u8,
                                    uint8 dataEndianness_u8)
{

    uint16 dataByteNum_u16;
    uint16 dataSignal_u16;
    uint32 dataSignal_u32;
    boolean flagConvStatus_b;

    dataByteNum_u16 = (uint16)((uint32)posnStart_u16/8u);
    dataSignal_u32  = 0;
    dataSignal_u16 = 0;

    flagConvStatus_b = FALSE;

    switch(xDataType_u8)
    {
        case DCM_BOOLEAN:
        {
            dataSignal_u32 = (uint32)(adrReqBuffer_u8[dataByteNum_u16]);
            dataSignal_u32 &= ((uint32)0x1u << (posnStart_u16 % 8u));
            break;
        }
        case DCM_UINT8:
        case DCM_SINT8:
        {
            dataSignal_u32 = adrReqBuffer_u8[dataByteNum_u16];
            break;
        }
        case DCM_UINT16:
        case DCM_SINT16:
        {

#if(LOW_BYTE_FIRST==CPU_BYTE_ORDER)

                dataSignal_u16 = (uint16)(adrReqBuffer_u8[dataByteNum_u16 + 1u]);
                dataSignal_u16 = (dataSignal_u16 << 8u);
                dataSignal_u16 |= (uint16)(adrReqBuffer_u8[dataByteNum_u16]);
#else

                dataSignal_u16 = (uint16)(adrReqBuffer_u8[dataByteNum_u16]);
                dataSignal_u16 = (dataSignal_u16 << 8u);
                dataSignal_u16 |= (adrReqBuffer_u8[dataByteNum_u16 + 1u]);
#endif

            flagConvStatus_b=Dcm_IsEndiannessConversionNecessary(dataEndianness_u8);

            if(TRUE==flagConvStatus_b)
            {
                DCM_ENDIANNESSCONVERSION16(dataSignal_u16);
            }

            dataSignal_u32 = (uint32)dataSignal_u16;
            break;
        }
        case DCM_UINT32:
        case DCM_SINT32:
        {

#if(LOW_BYTE_FIRST==CPU_BYTE_ORDER)

                dataSignal_u32  = (uint32)adrReqBuffer_u8[dataByteNum_u16];
                dataSignal_u32 |= (((uint32)adrReqBuffer_u8[dataByteNum_u16 + 1u]) << 8u) ;
                dataSignal_u32 |= (((uint32)adrReqBuffer_u8[dataByteNum_u16 + 2u]) << 16u);
                dataSignal_u32 |= (((uint32)adrReqBuffer_u8[dataByteNum_u16 + 3u]) << 24u);
#else

                dataSignal_u32  =   (uint32)adrReqBuffer_u8[dataByteNum_u16 + 3u];
                dataSignal_u32 |= (((uint32)adrReqBuffer_u8[dataByteNum_u16 + 2u]) << 8u) ;
                dataSignal_u32 |= (((uint32)adrReqBuffer_u8[dataByteNum_u16 + 1u]) << 16u);
                dataSignal_u32 |= (((uint32)adrReqBuffer_u8[dataByteNum_u16]) << 24u);
#endif

            flagConvStatus_b=Dcm_IsEndiannessConversionNecessary(dataEndianness_u8);

            if(TRUE==flagConvStatus_b)
            {
                DCM_ENDIANNESSCONVERSION32(dataSignal_u32);
            }
            break;
        }
        default:
        {

            break;
        }
    }

    return(dataSignal_u32);
}
#endif

#if (\
 \
((DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_OBDMODE1_ENABLED != DCM_CFG_OFF)&& (DCM_CFG_DSP_OBDMODE1_SR_ENABLED!=DCM_CFG_OFF)) ||            \
 \
     ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_READ_SR_ENABLED != DCM_CFG_OFF)) ||     \
     ((DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF)&&((DCM_CFG_ROUTINEVARLENGTH==DCM_CFG_OFF)||(DCM_CFG_RCRANGE_ROUTINEVARLENGTH==DCM_CFG_OFF)))||\
     (DCM_CFG_RBA_DEM_SR_ENABLED != DCM_CFG_OFF))

void Dcm_StoreSignal(uint8 xDataType_u8,
                                    uint16 posnStart_u16,
                                    uint8 * adrRespBuffer_u8,
                                    uint32 dataSignalValue_u32,
                                    uint8 dataEndianness_u8)
{
    uint16 dataByteNum_u16;
    uint16 dataSignalValue_u16;
    boolean flagConvStatus_b;

    dataByteNum_u16 = (uint16)((uint32)posnStart_u16/8u);

    flagConvStatus_b = FALSE;

    flagConvStatus_b=Dcm_IsEndiannessConversionNecessary(dataEndianness_u8);

    switch(xDataType_u8)
    {
        case DCM_BOOLEAN:
        {

            if(dataSignalValue_u32 != 0u)
            {
                adrRespBuffer_u8[dataByteNum_u16] |= (uint8)(0x1u<<(posnStart_u16%8u));
            }
            break;

        }
        case DCM_UINT8:
        case DCM_SINT8:
        {
            adrRespBuffer_u8[dataByteNum_u16] = (uint8)(dataSignalValue_u32);
            break;
        }
        case DCM_UINT16:
        case DCM_SINT16:
        {
            dataSignalValue_u16=(uint16)dataSignalValue_u32;

            if(FALSE!=flagConvStatus_b)
            {
                DCM_ENDIANNESSCONVERSION16(dataSignalValue_u16);
            }

#if(LOW_BYTE_FIRST==CPU_BYTE_ORDER)

                adrRespBuffer_u8[dataByteNum_u16] =  (uint8)(dataSignalValue_u16);
                adrRespBuffer_u8[dataByteNum_u16 + 1u] =  (uint8)(dataSignalValue_u16 >> 8u);

#else

                adrRespBuffer_u8[dataByteNum_u16] =  (uint8)(dataSignalValue_u16 >> 8u);
                adrRespBuffer_u8[dataByteNum_u16 + 1u] =  (uint8)(dataSignalValue_u16);
#endif

            break;
        }
        case DCM_UINT32:
        case DCM_SINT32:
        {

            if(FALSE!=flagConvStatus_b)
            {
                DCM_ENDIANNESSCONVERSION32(dataSignalValue_u32);
            }

#if(LOW_BYTE_FIRST==CPU_BYTE_ORDER)

                adrRespBuffer_u8[dataByteNum_u16] =  (uint8)(dataSignalValue_u32);
                adrRespBuffer_u8[dataByteNum_u16 + 1u] =  (uint8)(dataSignalValue_u32 >> 8u);
                adrRespBuffer_u8[dataByteNum_u16 + 2u] =  (uint8)(dataSignalValue_u32 >> 16u);
                adrRespBuffer_u8[dataByteNum_u16 + 3u] =  (uint8)(dataSignalValue_u32 >> 24u);

#else

                adrRespBuffer_u8[dataByteNum_u16] =  (uint8)(dataSignalValue_u32 >> 24u);
                adrRespBuffer_u8[dataByteNum_u16 + 1u] =  (uint8)(dataSignalValue_u32 >> 16u);
                adrRespBuffer_u8[dataByteNum_u16 + 2u] =  (uint8)(dataSignalValue_u32 >> 8u);
                adrRespBuffer_u8[dataByteNum_u16 + 3u] =  (uint8)(dataSignalValue_u32);

#endif
            break;
        }
        default:
        {

            break;
        }
    }
}
#endif

#if (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF)
#if ( (DCM_CFG_ROUTINEARRAY_INSIG != DCM_CFG_OFF)  || (DCM_CFG_ROUTINEARRAY_OUTSIG != DCM_CFG_OFF) || \
(DCM_CFG_RCRANGE_ROUTINEARRAY_INSIG != DCM_CFG_OFF)||(DCM_CFG_RCRANGE_ROUTINEARRAY_OUTSIG != DCM_CFG_OFF) )

#if ((DCM_CFG_ROUTINEARRAY_INSIG != DCM_CFG_OFF) || (DCM_CFG_RCRANGE_ROUTINEARRAY_INSIG != DCM_CFG_OFF))

static void StoreRcBuffer(uint8 xDataType_u8,uint16 IndexSig_u16, uint16 dataSignal_u16)
{
    if(xDataType_u8 == DCM_UINT16_N)
    {
        Dcm_RCSigInN_au16[IndexSig_u16] = dataSignal_u16;
    }
    else
    {
        Dcm_RCSigInN_as16[IndexSig_u16] = (sint16)dataSignal_u16;
    }
}

void Dcm_RcSetSignalArray(const Dcm_DspRoutineSignalInfo_tst * adrSignal_pcst,const uint8 * adrReqBuffer_u8)
{
     uint8 xDataType_u8;
     uint16 DataLen_u16;
     uint16 IndexSig_u16;
     uint16 IndexReqData_u16;

     boolean flagConvStatus_b;
     uint16 idx;
     uint16 dataSignal_u16;
     uint32 dataSignal_u32;

     dataSignal_u32 = 0;
     dataSignal_u16 = 0;
     xDataType_u8 = adrSignal_pcst->dataType_u8;
     DataLen_u16 = adrSignal_pcst->dataLength_u16 / CalArraySize_u8[xDataType_u8 - DCM_RCARRAYINDEX];
     flagConvStatus_b=Dcm_IsEndiannessConversionNecessary(adrSignal_pcst->dataEndianness_u8);
     IndexSig_u16 = adrSignal_pcst->idxSignal_u16;
     IndexReqData_u16 = (uint16)((adrSignal_pcst->posnStart_u16)/8);

    switch(xDataType_u8)
    {
        case DCM_UINT8_N:
        {

             DCM_MEMCOPY(&(Dcm_RCSigInN_au8[IndexSig_u16]),&(adrReqBuffer_u8[IndexReqData_u16]),DataLen_u16);
        }
        break;
        case DCM_SINT8_N:
        {

            DCM_MEMCOPY(&(Dcm_RCSigInN_as8[IndexSig_u16]),&(adrReqBuffer_u8[IndexReqData_u16]),DataLen_u16);
        }
        break;
        case DCM_UINT16_N:
        case DCM_SINT16_N:
        {

            for(idx=0;idx<DataLen_u16;idx++)
            {

                dataSignal_u16 = (uint16)(((uint16)adrReqBuffer_u8[IndexReqData_u16 + EndianessConvLUT_u8[0]]) + ((uint16)(adrReqBuffer_u8[IndexReqData_u16 + EndianessConvLUT_u8[1]]) * 0x100u));

                IndexReqData_u16 = IndexReqData_u16 + 2;

                if(TRUE==flagConvStatus_b)
                {
                    DCM_ENDIANNESSCONVERSION16(dataSignal_u16);
                }
                StoreRcBuffer(xDataType_u8,IndexSig_u16,dataSignal_u16);

              IndexSig_u16++;
            }
        }
        break;

        case DCM_UINT32_N:
        case DCM_SINT32_N:
        {
            for(idx=0;idx<DataLen_u16;idx++)
            {

                 dataSignal_u32 = (uint32)((adrReqBuffer_u8[IndexReqData_u16 + EndianessConvLUT_u8[2]]) + ((adrReqBuffer_u8[IndexReqData_u16 + EndianessConvLUT_u8[3]]) * 0x100u) + ((adrReqBuffer_u8[IndexReqData_u16 + EndianessConvLUT_u8[4]]) *  0x10000u) + ((adrReqBuffer_u8[IndexReqData_u16 + EndianessConvLUT_u8[5]]) * 0x1000000u) );

                IndexReqData_u16 = IndexReqData_u16+4;

                if(TRUE==flagConvStatus_b)
                {
                    DCM_ENDIANNESSCONVERSION32(dataSignal_u32);
                }

                if(xDataType_u8 == DCM_UINT32_N)
                {
                    Dcm_RCSigInN_au32[IndexSig_u16] = dataSignal_u32;
                }
                else
                {
                    Dcm_RCSigInN_as32[IndexSig_u16] = (sint32)dataSignal_u32;
                }

                IndexSig_u16++;
            }
        }
        break;

        default:

            break;
    }
}
#endif

#if((DCM_CFG_ROUTINEARRAY_OUTSIG != DCM_CFG_OFF) || (DCM_CFG_RCRANGE_ROUTINEARRAY_OUTSIG != DCM_CFG_OFF))

void Dcm_RcStoreSignalArray(const Dcm_DspRoutineSignalInfo_tst * adrSignal_pcst,uint8 * adrResBuffer_u8)
{

     uint8 xDataType_u8;
     uint16 DataLen_u16;
     uint16 IndexSig_u16;
     uint16 IndexResData_u16;

     boolean flagConvStatus_b;
     uint16 idx;
     uint16 dataSignal_u16;
     uint32 dataSignal_u32;

     dataSignal_u32 = 0;
     dataSignal_u16 = 0;
     xDataType_u8 = adrSignal_pcst->dataType_u8;
     DataLen_u16 = adrSignal_pcst->dataLength_u16 / CalArraySize_u8[xDataType_u8 - DCM_RCARRAYINDEX];
     flagConvStatus_b=Dcm_IsEndiannessConversionNecessary(adrSignal_pcst->dataEndianness_u8);
     IndexSig_u16 = adrSignal_pcst->idxSignal_u16;
     IndexResData_u16 = (uint16)(adrSignal_pcst->posnStart_u16/8);

    switch(xDataType_u8)
    {
        case DCM_UINT8_N:
        {

            DCM_MEMCOPY(&(adrResBuffer_u8[IndexResData_u16]),&(Dcm_RCSigOutN_au8[IndexSig_u16]),DataLen_u16);
        }
        break;

        case DCM_SINT8_N:
        {

            DCM_MEMCOPY(&(adrResBuffer_u8[IndexResData_u16]),&(Dcm_RCSigOutN_as8[IndexSig_u16]),DataLen_u16);
        }
        break;

        case DCM_UINT16_N:
        case DCM_SINT16_N:
        {
            for(idx=0;idx<DataLen_u16;idx++)
            {
                dataSignal_u16 = (xDataType_u8 == DCM_UINT16_N) ? Dcm_RCSigOutN_au16[IndexSig_u16]:(uint16)Dcm_RCSigOutN_as16[IndexSig_u16];
                IndexSig_u16++;

                if(TRUE==flagConvStatus_b)
                {
                    DCM_ENDIANNESSCONVERSION16(dataSignal_u16);
                }

                adrResBuffer_u8[IndexResData_u16 + EndianessConvLUT_u8[0]] =  (uint8)(dataSignal_u16);
                adrResBuffer_u8[IndexResData_u16 + EndianessConvLUT_u8[1]] =  (uint8)(dataSignal_u16 >> 8u);

                 IndexResData_u16 = IndexResData_u16 + 2;
            }
        }
        break;

        case DCM_UINT32_N:
        case DCM_SINT32_N:
        {
            for(idx=0;idx<DataLen_u16;idx++)
            {
                dataSignal_u32 = (xDataType_u8 == DCM_UINT32_N) ? Dcm_RCSigOutN_au32[IndexSig_u16]:(uint32)Dcm_RCSigOutN_as32[IndexSig_u16];
                IndexSig_u16++;

                if(TRUE==flagConvStatus_b)
                {
                    DCM_ENDIANNESSCONVERSION32(dataSignal_u32);
                }

              adrResBuffer_u8[IndexResData_u16 + EndianessConvLUT_u8[2]] =  (uint8)(dataSignal_u32);
              adrResBuffer_u8[IndexResData_u16 + EndianessConvLUT_u8[3]] =  (uint8)(dataSignal_u32 >> 8u);
              adrResBuffer_u8[IndexResData_u16 + EndianessConvLUT_u8[4]] =  (uint8)(dataSignal_u32 >> 16u);
              adrResBuffer_u8[IndexResData_u16 + EndianessConvLUT_u8[5]] =  (uint8)(dataSignal_u32 >> 24u);

              IndexResData_u16 = IndexResData_u16+4;
            }
        }
        break;

        default:

            break;
    }
}

#endif
#endif
#endif

#define DCM_STOP_SEC_CODE
#include "Dcm_MemMap.h"

