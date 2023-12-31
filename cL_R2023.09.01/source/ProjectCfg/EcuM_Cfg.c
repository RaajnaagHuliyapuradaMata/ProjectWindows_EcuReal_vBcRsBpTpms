/******************************************************************************/
/* File   : EcuM_Cfg.c                                                        */
/*                                                                            */
/* Author : Raajnaag HULIYAPURADA MATA                                        */
/*                                                                            */
/* License / Warranty / Terms and Conditions                                  */
/*                                                                            */
/* Everyone is permitted to copy and distribute verbatim copies of this lice- */
/* nse document, but changing it is not allowed. This is a free, copyright l- */
/* icense for software and other kinds of works. By contrast, this license is */
/* intended to guarantee your freedom to share and change all versions of a   */
/* program, to make sure it remains free software for all its users. You have */
/* certain responsibilities, if you distribute copies of the software, or if  */
/* you modify it: responsibilities to respect the freedom of others.          */
/*                                                                            */
/* All rights reserved. Copyright � 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "EcuM.hpp"

#include "types.hpp" //TBD: Remove
#include "CfgMcalMcu.hpp"

#if(ECUM_INCLUDE_COMM == STD_ON)
#include "ComM.hpp"
#endif

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.hpp"
const Type_SwcServiceEcuM_stListRefsPncWakeup EcuM_Cfg_dataWkupPNCRef_cast[CfgSwcServiceEcuM_dNumSourceWakeup] = {
      { 0,   NULL_PTR }
   ,  { 0,   NULL_PTR }
   ,  { 0,   NULL_PTR }
   ,  { 0,   NULL_PTR }
   ,  { 0,   NULL_PTR }
};
#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.hpp"

#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.hpp"
const EcuM_Cfg_dataWkupSrcStruct_tst EcuM_Cfg_idxWakeupSourcesPC_au32[CfgSwcServiceEcuM_dNumSourceWakeup] = {
      {FALSE, 255 ,  McalMcu_eReasonReset_Undefined, 0 , FALSE, CfgSwcServiceEcuM_dPOWER,          0}
   ,  {FALSE, 255 ,  McalMcu_eReasonReset_Undefined, 0 , FALSE, CfgSwcServiceEcuM_dRESET,          0}
   ,  {FALSE, 255 ,  McalMcu_eReasonReset_Undefined, 0 , FALSE, CfgSwcServiceEcuM_dINTERNAL_RESET, 0}
   ,  {FALSE, 255 ,  McalMcu_eReasonReset_Undefined, 0 , FALSE, CfgSwcServiceEcuM_dINTERNAL_WDG,   0}
   ,  {FALSE, 255 ,  McalMcu_eReasonReset_Undefined, 0 , FALSE, CfgSwcServiceEcuM_dEXTERNAL_WDG,   0}
};

#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
const EcuM_Cfg_dataSleepModeStruct_tst EcuM_Cfg_idxSleepModes_au32[ECUM_CFG_NUM_SLEEP_MODES]= {
};
#endif

#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.hpp"
#if(ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
#define ECUM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_MemMap.hpp"
volatile EcuM_Cfg_CheckWakeupSrc_tst EcuM_Cfg_CheckWakeupTimer_ast[CfgSwcServiceEcuM_dNumSourceWakeup] = {
      {CfgSwcServiceEcuM_dPOWER,          0, ECUM_FLAG_RESET_E}
   ,  {CfgSwcServiceEcuM_dRESET,          0, ECUM_FLAG_RESET_E}
   ,  {CfgSwcServiceEcuM_dINTERNAL_RESET, 0, ECUM_FLAG_RESET_E}
   ,  {CfgSwcServiceEcuM_dINTERNAL_WDG,   0, ECUM_FLAG_RESET_E}
   ,  {CfgSwcServiceEcuM_dEXTERNAL_WDG,   0, ECUM_FLAG_RESET_E}
};
#define ECUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_MemMap.hpp"
#endif

#define ECUM_START_SEC_CONST_16
#include "EcuM_MemMap.hpp"
const uint16 EcuM_Cfg_idxGoDownValidCallerArr_au16[ECUM_CFG_GODOWN_CALLER_ARR_LEN] = {
   1
};
#define ECUM_STOP_SEC_CONST_16
#include "EcuM_MemMap.hpp"

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

