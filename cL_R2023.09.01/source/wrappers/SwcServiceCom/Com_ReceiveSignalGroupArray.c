

#include "Com_Prv.hpp"
#include "Com_Lok_Inl.hpp"

#ifdef COM_RX_SIGNALGROUP_ARRAY

#define COM_START_SEC_CODE
#include "Com_MemMap.hpp"

uint8 Com_ReceiveSignalGroupArray( Com_SignalGroupIdType SignalGroupId, uint8 * SignalGroupArrayPtr )
{

   Com_RxSigGrpConstPtrType        RxSigGrpConstPtr;
   uint8                           returnValue_u8;
   Com_MainFuncType                rxMainFuncId;
   Com_IpduIdType                  IpduId_ui;

    returnValue_u8 = COM_SERVICE_NOT_AVAILABLE;

#if(COM_CONFIGURATION_USE_DET == STD_ON)
   if(Com_Lok_DETCheck_Param_Ptr((SignalGroupId >= COM_GET_NUM_RX_SIGNALGRP),(SignalGroupArrayPtr == NULL_PTR)
   ,                                       COMServiceId_ReceiveSignalGroupArray))
#endif
   {

        SignalGroupId    = COM_GET_RXSIGNALGRP_ID( SignalGroupId );

        RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA( SignalGroupId );

        IpduId_ui        = RxSigGrpConstPtr->IpduRef;

        rxMainFuncId     = (COM_GET_RX_IPDU_CONSTDATA(IpduId_ui))->MainFunctionRef;

        if( Com_GetValue(RXSIGGRP,_ARRAYACCESS,RxSigGrpConstPtr->rxSignalGrpFields) )
        {
            Com_RxSigGrpArrayConstPtrType        RxSigGrpArrayConstPtr;
            uint8 * RxSigGrpArrayBufRamPtr;

            RxSigGrpArrayConstPtr  = COM_GET_RXSIGGRP_ARRAY_CONSTDATA( RxSigGrpConstPtr->SigGrpArray_Index );

            RxSigGrpArrayBufRamPtr =
                                &COM_GET_RXSIGGRP_ARRAY_BUFF( rxMainFuncId,RxSigGrpArrayConstPtr->RxSigGrpBuf_Index );

            if( Com_CheckRxIPduStatus((PduIdType)IpduId_ui ) )
            {
                returnValue_u8 = E_OK;
            }

            SchM_Enter_Com_RxSigGrpArrayBuff();

            Com_ByteCopy(   ( uint8 * )( SignalGroupArrayPtr    )
   ,                           ( const uint8 * )( RxSigGrpArrayBufRamPtr )
   ,                           ( uint32 )( RxSigGrpConstPtr->lastByte_u8 - RxSigGrpArrayConstPtr->FirstByteNo ) );

            SchM_Exit_Com_RxSigGrpArrayBuff();
        }
   }
    return returnValue_u8;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.hpp"

#endif

