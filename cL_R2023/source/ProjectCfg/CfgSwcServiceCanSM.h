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
//   const CanSM_NetworkConf_tst* CanSM_NetworkConf_pcst;
   const uint8*                 CanSM_NetworktoCtrlConf_pcu8;
/*
#if(CANSM_GETBUSOFFDELAY_SUPPORT == STD_ON)
   void (*User_GetBusOffDelay) (NetworkHandleType, uint8* CANSM_APPL_CODE);
#endif
*/
   const uint16                 CanSMModeRequestRepetitionTime_u16;
   const uint8                  CanSMModeRequestRepetitionMax_u8;
         uint8                  CanSM_SizeOfCanSMNetworks_u8;
         uint8                  CanSM_ActiveConfigset_u8;
}Type_CfgSwcServiceCanSM_st;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

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
