#pragma once
/******************************************************************************/
/* File   : Dem_Cfg_Deb.hpp                                                   */
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
#include "Std_Types.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define DEM_CFG_DEBMONINTERNAL_OFF  STD_OFF
#define DEM_CFG_DEBMONINTERNAL_ON   STD_ON
#define DEM_CFG_DEBMONINTERNAL  DEM_CFG_DEBMONINTERNAL_ON

#define DEM_CFG_PRJSPECIFIC_DEB_OPTIMIZATION_ON STD_ON
#define DEM_CFG_PRJSPECIFIC_DEB_OPTIMIZATION_OFF STD_OFF
#define DEM_CFG_PRJSPECIFIC_DEB_OPTIMIZATION DEM_CFG_PRJSPECIFIC_DEB_OPTIMIZATION_OFF

#define DEM_CFG_DEBMONINTERNAL_LENGTH 33
#define DEM_CFG_DEBMONINTERNAL_PARAMSET \
{ \
 \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
 { NULL_PTR },  \
}

#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X500042_EVENT  0u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X5000A2_EVENT  1u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X5000A3_EVENT  2u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X560116_EVENT  3u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X560131_EVENT  4u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X560149_EVENT  5u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X56014B_EVENT  6u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X560216_EVENT  7u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X560231_EVENT  8u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X560249_EVENT  9u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X56024B_EVENT  10u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X560316_EVENT  11u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X560331_EVENT  12u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X560349_EVENT  13u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X56034B_EVENT  14u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X560416_EVENT  15u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X560431_EVENT  16u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X560449_EVENT  17u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X56044B_EVENT  18u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X560504_EVENT  19u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X560531_EVENT  20u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X56064A_EVENT  21u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X560793_EVENT  22u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X560929_EVENT  23u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0X9CC055_EVENT  24u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0XD60129_EVENT  25u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0XD60329_EVENT  26u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0XD60429_EVENT  27u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0XD60529_EVENT  28u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0XD60629_EVENT  29u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0XD60729_EVENT  30u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0XD60829_EVENT  31u
#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0XD60929_EVENT  32u

#define DEM_CFG_DEBARTIMEBASE_OFF  STD_OFF
#define DEM_CFG_DEBARTIMEBASE_ON   STD_ON
#define DEM_CFG_DEBARTIMEBASE  DEM_CFG_DEBARTIMEBASE_OFF

#define DEM_CFG_DEBCOUNTERBASECLASS_OFF  STD_OFF
#define DEM_CFG_DEBCOUNTERBASECLASS_ON   STD_ON
#define DEM_CFG_DEBCOUNTERBASECLASS  DEM_CFG_DEBCOUNTERBASECLASS_ON

#define DEM_CFG_LIMIT_RELEVANTFOR_JUMPING_OFF  STD_OFF
#define DEM_CFG_LIMIT_RELEVANTFOR_JUMPING_ON   STD_ON
#define DEM_CFG_LIMIT_RELEVANTFOR_JUMPING DEM_CFG_LIMIT_RELEVANTFOR_JUMPING_OFF

#define DEM_CFG_DEFAULT_DEBCOUNTERCLASS_MAXLIMIT 32767
#define DEM_CFG_DEFAULT_DEBCOUNTERCLASS_MINLIMIT -32768
#define DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPUP_ENABLED TRUE
#define DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPUP_VALUE 0
#define DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPDOWN_ENABLED TRUE
#define DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPDOWN_VALUE 0

#define DEM_CFG_DEBCOUNTERBASECLASS_MINTHRESHOLD_OFF  STD_OFF
#define DEM_CFG_DEBCOUNTERBASECLASS_MINTHRESHOLD_ON   STD_ON
#define DEM_CFG_DEBCOUNTERBASECLASS_MINTHRESHOLD  DEM_CFG_DEBCOUNTERBASECLASS_MINTHRESHOLD_OFF

#define DEM_CFG_DEBCOUNTERBASECLASS_MAXTHRESHOLD_OFF  STD_OFF
#define DEM_CFG_DEBCOUNTERBASECLASS_MAXTHRESHOLD_ON   STD_ON
#define DEM_CFG_DEBCOUNTERBASECLASS_MAXTHRESHOLD  DEM_CFG_DEBCOUNTERBASECLASS_MAXTHRESHOLD_OFF

#define DEM_CFG_DEBCOUNTERBASECLASS_JUMPUPVALUE_OFF  STD_OFF
#define DEM_CFG_DEBCOUNTERBASECLASS_JUMPUPVALUE_ON   STD_ON
#define DEM_CFG_DEBCOUNTERBASECLASS_JUMPUPVALUE  DEM_CFG_DEBCOUNTERBASECLASS_JUMPUPVALUE_ON

#define DEM_CFG_DEBCOUNTERBASECLASS_JUMPDOWNVALUE_OFF  STD_OFF
#define DEM_CFG_DEBCOUNTERBASECLASS_JUMPDOWNVALUE_ON   STD_ON
#define DEM_CFG_DEBCOUNTERBASECLASS_JUMPDOWNVALUE  DEM_CFG_DEBCOUNTERBASECLASS_JUMPDOWNVALUE_ON

#define DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPDOWN_OFF  STD_OFF
#define DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPDOWN_ON   STD_ON
#define DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPDOWN  DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPDOWN_OFF

#define DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPUP_OFF  STD_OFF
#define DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPUP_ON   STD_ON
#define DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPUP  DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPUP_OFF

#define DEMRB_DEBOUNCECOUNTERSETS_SIZE                                 2

#define DEMRB_DEBOUNCECOUNTERSETS_CUSTOMSETSOFFSET                     2

#define DemConf_DemRbDebounceCounterSet_Standard                       0
#define DemConf_DemRbDebounceCounterSet_Alternative                    1

#define DEM_CFG_DEBCOUNTERBASECLASS_PARAMSET_LENGTH 1

#define DEM_CFG_DEBCOUNTERCLASS_PARAMSETS \
{ \
  {  \
   DEM_DEBCOUNTERBASECLASS_INIT (DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPDOWN_ENABLED,DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPUP_ENABLED,DEM_CFG_DEFAULT_DEBCOUNTERCLASS_MINLIMIT,DEM_CFG_DEFAULT_DEBCOUNTERCLASS_MAXLIMIT,0,0,DEM_CFG_DEFAULT_DEBCOUNTERCLASS_MAXLIMIT,DEM_MAXSINT16,1,-1), \
}, \
  {   \
   DEM_DEBCOUNTERBASECLASS_INIT (DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPDOWN_ENABLED,DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPUP_ENABLED,DEM_CFG_DEFAULT_DEBCOUNTERCLASS_MINLIMIT,DEM_CFG_DEFAULT_DEBCOUNTERCLASS_MAXLIMIT,0,0,DEM_CFG_DEFAULT_DEBCOUNTERCLASS_MAXLIMIT,DEM_MAXSINT16,1,-1), \
  }, \
}

#define DEM_DEBPARAMCLASS_IDX_CANSM_E_DEMDEBOUNCECOUNTERBASEDCLASS_NETWORK_0  0u

#define DEM_DEBPARAM_IDX_EVENTPARAMETER_DTC_0XD60188_EVENT  DEM_DEBPARAMCLASS_IDX_CANSM_E_DEMDEBOUNCECOUNTERBASEDCLASS_NETWORK_0

#define DEM_CFG_DEB_DEFINE_ALL_PARAMSETS \
static const Dem_DebounceMonitorInternal Dem_Cfg_DebMonInternal_Paramset[DEM_CFG_DEBMONINTERNAL_LENGTH] = DEM_CFG_DEBMONINTERNAL_PARAMSET;\
static const Dem_DebCounterBaseClass_ParamSet  Dem_Cfg_DebCounterBaseClass_Paramsets[DEMRB_DEBOUNCECOUNTERSETS_SIZE][DEM_CFG_DEBCOUNTERBASECLASS_PARAMSET_LENGTH] = DEM_CFG_DEBCOUNTERCLASS_PARAMSETS; \

#define DEM_CFG_DEB_CLASSES \
{ \
   { \
      NULL_PTR, \
      NULL_PTR, \
      &Dem_Cfg_DebMonInternal_Paramset, \
      DEM_CFG_DEBMONINTERNAL_LENGTH, \
      NULL_PTR \
   }\
   ,{ \
      &Dem_DebCounterBaseClass_GetLimits, \
      NULL_PTR, \
      &Dem_Cfg_DebCounterBaseClass_Paramsets[DemConf_DemRbDebounceCounterSet_Standard], \
      DEM_CFG_DEBCOUNTERBASECLASS_PARAMSET_LENGTH, \
      &Dem_DebCounterBaseClass_Filter \
   }\
}

#define DEM_CFG_DEB_NUMBEROFCLASSES  2

#define DEM_DEBMETH_IDX_MONINTERNAL      (0u)
#define DEM_DEBMETH_IDX_ARCTRBASECLASS      (1u)

#define DEM_CFG_SUPPORT_DEB_RESET_AFTER_STOCO_OFF                                    0u
#define DEM_CFG_SUPPORT_DEB_RESET_AFTER_STOCO_ACCORDING_DEBOUNCEBEHAVIOR             1u

#define DEM_CFG_SUPPORT_DEB_RESET_AFTER_STOCO           DEM_CFG_SUPPORT_DEB_RESET_AFTER_STOCO_OFF

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

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

