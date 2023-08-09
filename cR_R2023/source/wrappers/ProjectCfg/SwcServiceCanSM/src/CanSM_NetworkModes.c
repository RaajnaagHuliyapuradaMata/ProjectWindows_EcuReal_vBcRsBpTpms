

#include "CanSM_Prv.h"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_NetworkModeTrans( VAR(NetworkHandleType, AUTOMATIC) network,VAR(ComM_ModeType, AUTOMATIC) ComM_Mode )
{

    VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CanSM_BswM_Mode_en;

    VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CanSM_CurrNwMode_en;

    CanSM_CurrNwMode_en = CanSM_CurrNw_Mode_en[network];

    if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_FULLCOM) && (ComM_Mode == COMM_FULL_COMMUNICATION ))
        {
        if(CanSM_PreFullCom_Substates_en[network]== CANSM_PRE_FULLCOM_DEFAULT)
        {
            CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_TRCV_NORMAL;
        }
            CanSM_NO2FULL_COM(network);
        }
    else if((CanSM_CurrNwMode_en == CANSM_BSM_S_FULLCOM) && ((ComM_Mode == COMM_SILENT_COMMUNICATION )))
        {

            CanSM_FULL2SILENT_COM(network);

        }

    else if((CanSM_CurrNwMode_en == CANSM_BSM_S_SILENTCOM) && ((ComM_Mode == COMM_FULL_COMMUNICATION )) )
        {
            if(CanSM_PreFullCom_Substates_en[network]== CANSM_PRE_FULLCOM_DEFAULT)
            {
                CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_TRCV_NORMAL;
            }

            CanSM_SILENT2FULL_COM(network);

        }
    else if((CanSM_CurrNwMode_en == CANSM_BSM_S_FULLCOM) && ((ComM_Mode == COMM_NO_COMMUNICATION )))
        {
            CanSM_CurrNw_Mode_en[network]=CANSM_BSM_S_PRE_NOCOM;

            CanSM_BswM_Mode_en=CANSM_BSWM_NO_COMMUNICATION;

            BswM_CanSM_CurrentState(CanSM_Network_pcst[network].ComM_channelId_uo,CanSM_BswM_Mode_en);

            if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].Trcv_hndle_u8 != 255)
             {
               #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
               if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].TrcvPnConfig_b == TRUE)
                 {
                   if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
                   {
                       CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
                   }
                   CanSM_DeInitPnSupported(network);
                 }
               else
                 {
                   if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
                       {
                           CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                       }
                   CanSM_DeInitPnNotSupported(network);
                 }
               #else
               if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
                   {
                       CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                   }
               CanSM_DeInitPnNotSupported(network);
               #endif
             }
           else
             {
               if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
                   {
                       CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                   }
               CanSM_DeInitPnNotSupported(network);
             }

        }

    else if((CanSM_CurrNwMode_en == CANSM_BSM_S_SILENTCOM) && ((ComM_Mode == COMM_NO_COMMUNICATION )) )
        {
            CanSM_CurrNw_Mode_en[network]=CANSM_BSM_S_PRE_NOCOM;

            CanSM_BswM_Mode_en=CANSM_BSWM_NO_COMMUNICATION;

            BswM_CanSM_CurrentState(CanSM_Network_pcst[network].ComM_channelId_uo,CanSM_BswM_Mode_en);

            if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].Trcv_hndle_u8 != 255)
             {
               #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
               if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].TrcvPnConfig_b == TRUE)
                 {
                   if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
                   {
                       CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
                   }
                   CanSM_DeInitPnSupported(network);
                 }
               else
                 {
                   if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
                       {
                           CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                       }
                   CanSM_DeInitPnNotSupported(network);
                 }
               #else
                   if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
                       {
                           CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                       }
                   CanSM_DeInitPnNotSupported(network);
               #endif
             }
           else
             {
               if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
               {
                   CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
               }
               CanSM_DeInitPnNotSupported(network);
             }

        }

    else if ((CanSM_CurrNw_Mode_en[network] == CANSM_BSM_S_PRE_NOCOM)&&(ComM_Mode == COMM_NO_COMMUNICATION))
    {

     if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].Trcv_hndle_u8 != 255)
      {
        #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
        if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].TrcvPnConfig_b == TRUE)
          {
            if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
            {
                CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
            }
            CanSM_DeInitPnSupported(network);
          }
        else
          {
            if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
            {
                CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
            }
            CanSM_DeInitPnNotSupported(network);
          }
        #else
        if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
        {
            CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
        }
        CanSM_DeInitPnNotSupported(network);
        #endif
      }
    else
      {
        if(CanSM_PreNoCom_Substates_en[network] == CANSM_DEFAULT)
        {
            CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
        }
        CanSM_DeInitPnNotSupported(network);
      }
    }
    else
    {

    }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_GetNetworkMode_Substate(VAR(NetworkHandleType, AUTOMATIC) network,
        P2VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC, CANSM_APPL_DATA) NetworkMode_SubstatePtr
        )
{

    VAR(Std_ReturnType, AUTOMATIC) CanSM_FuncVal_uo;

    CanSM_FuncVal_uo = E_NOT_OK;

    network = CanSM_GetHandle(network);

    CANSM_REPORT_ERROR_NOK((CanSM_Init_ab == (boolean)CANSM_UNINITED),
                           ((uint8)CANSM_GETNETWORKMODESUBSTATE_SID),
                           ((uint8)CANSM_E_UNINIT))

    CANSM_REPORT_ERROR_NOK(((uint8)network >= (uint8)CANSM_NUM_CAN_NETWORKS),
                           ((uint8)CANSM_GETNETWORKMODESUBSTATE_SID),
                           ((uint8)CANSM_E_INVALID_NETWORK_HANDLE))

    CANSM_REPORT_ERROR_NOK((NetworkMode_SubstatePtr == NULL_PTR),
                           ((uint8)CANSM_GETNETWORKMODESUBSTATE_SID),
                           ((uint8)CANSM_E_PARAM_POINTER))

    *NetworkMode_SubstatePtr = CanSM_CurrNw_Mode_en[network];

    CanSM_FuncVal_uo = E_OK;

    return (CanSM_FuncVal_uo);
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
