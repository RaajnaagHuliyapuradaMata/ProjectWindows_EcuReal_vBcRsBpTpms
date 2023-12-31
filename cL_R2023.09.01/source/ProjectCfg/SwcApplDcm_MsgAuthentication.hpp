#pragma once
/******************************************************************************/
/* File   : SwcApplDcm_MsgAuthentication.hpp                                  */
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
#include "Types.hpp"
#include "DcmMsgAuthenticationX.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cSidDiagSessionCtrl   0x10
#define cSidEcuReset          0x11    // yes
#define cSidSecAccess         0x27
#define cSidCommControl       0x28
#define cSidTesterPresent     0x3E
#define cSidCtrlDtcSetting    0x85
#define cSidRoutineControl    0x31    // yes depending on RID
#define cSidReadDataByIdent   0x22    // yes depending on DID
#define cSidWriteDataByIdent  0x2E    // yes

#define cSubFuncHardReset     0x01
#define cSubFuncSoftReset     0x03
#define cSubFuncHRwoResp      0x40
#define cSubFuncSRwoResp      0x41
#define cSubFuncResUDSTimer   0x4C

#define cDidBootSwId          0xF180u // no
#define cDidApplSwId          0xF181u // no
#define cDidCalSwId           0xF182u // NA
#define cDidBootSwFingerprint 0xF183u // yes r+w
#define cDidApplSwFingerprint 0xF184u // yes r+w
#define cDidAppCalFingerprint 0xF185u // NA
#define cDidActiveSession     0xF186u // no
#define cDidSerialNumber      0xF18Cu // no
#define cDidVin               0xF190u // no
#define cDidRivianHwPN        0xF191u // no
#define cDidProgImgBM         0xF010u // NA
#define cDidProgImgBL         0xF011u // yes r
#define cDidProgImgBLUP       0xF012u // NA
#define cDidProgImgRAMUP      0xF013u // NA
#define cDidProgImgAPP1       0xF014u // yes r
#define cDidProgImgAPP2       0xF015u // NA
#define cDidProgImgCAL        0xF016u // NA
#define cDidProgImgRAMAPP     0xF019u // NA
#define cDidKeyGenCounters    0xF017u // yes r+w
#define cDidManufSuppMode     0xF018u // yes r+w
#define cDidCompAndSwType     0x0101u // no
#define cDidGenealVerNumber   0xF110u // no
#define cDidBoardPartNumber   0xF112u // no
#define cDidBoardSerNumber    0xF192u // no
#define cDidGenealCrc         0xF116u // no
#define cDidGenealFull        0xF117u // no
#define cDidCalVersionNumber  0xF118u // NA
#define cDidCalCrc            0xF119u // NA
#define cDidCalBlock          0xF11Au // NA
#define cDidEepBlockStatus    0xF11Bu // yes r
#define cDidAuxId             0xF11Cu // no
#define cDidModeId            0xF11Du // no

#define cRidSelfTest          0xF200u // no   Did ge�ndert! anpassen in cdd
#define cRidKeyExchange       0x0207u // yes r+w -> rid is supported in bootloader only!


#define NO_OF_SID     4
#define NO_OF_DID_RID 8

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
static boolean DcmHashExist(uint8 ucSid, uint16 ushDidRid, uint32 ulServiceLength);
static boolean DcmAuthenticationNeeded(uint8 ucSid, uint16 ushDidRid);
static boolean DcmKeyExist(uint8* aucKey, uint8 ucLength);
static boolean DcmGetSubFunctionFromMessageBuffer(uint8 ucSID, const uint8* aucMessage, uint16* ushSubFunc);

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

