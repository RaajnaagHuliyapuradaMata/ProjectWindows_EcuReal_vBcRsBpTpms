#pragma once
/******************************************************************************/
/* File   : CfgSwcServiceCanSM.h                                              */
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
/* All rights reserved. Copyright © 1982 Raajnaag HULIYAPURADA MATA           */
/*                                                                            */
/* Always refer latest software version from:                                 */
/* https://github.com/RaajnaagHuliyapuradaMata?tab=repositories               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "ComStack_Types.hpp"
#include "CanSM_Cfg.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef struct{
   const uint8*                 Cntrl_startidx_pu8;
         uint16                 BorTimeL1_u16;
         uint16                 BorTimeL2_u16;
         uint16                 BorTimeTxEnsured_u16;
         Dem_EventIdType        BusOffEventId_uo;
         uint8                  Trcv_hndle_u8;
         uint8                  SizeofController_u8;
         uint8                  BorCntL1L2_u8;
         NetworkHandleType      ComM_channelId_uo;
         boolean                BusOffDelayConfig_b;
         boolean                TrcvPnConfig_b;
}CanSM_NetworkConf_tst;

typedef struct{
   const CanSM_NetworkConf_tst* CanSM_NetworkConf_pcst;
   P2CONST(uint8,                 AUTOMATIC, SWCSERVICECANSM_CONST) CanSM_NetworktoCtrlConf_pcu8;
     CONST(uint16,                           SWCSERVICECANSM_CONST) CanSMModeRequestRepetitionTime_u16;
     CONST(uint8,                            SWCSERVICECANSM_CONST) CanSMModeRequestRepetitionMax_u8;
       VAR(uint8,                            SWCSERVICECANSM_VAR)   CanSM_SizeOfCanSMNetworks_u8;
       VAR(uint8,                            SWCSERVICECANSM_VAR)   CanSM_ActiveConfigset_u8;
}Type_CfgSwcServiceCanSM_st;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
extern CONST(Type_CfgSwcServiceCanSM_st, CANSM_CONST) CfgSwcServiceCanSM_castConfigSet[];

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
extern P2CONST(Type_CfgSwcServiceCanSM_st, CANSM_VAR, CANSM_APPL_CONST) CfgSwcServiceCanSM_castConfigSet_pcst;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
