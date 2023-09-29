#ifndef CAN_GENERAL_TYPES_H
#define CAN_GENERAL_TYPES_H

#include "ComStack_Types.hpp"
#include "Types_McalCan.hpp"

typedef struct{
   Type_McalCan_tId       CanId;
   Type_McalCan_tHandleHw Hoh;
   uint8            ControllerId;
}Can_HwType;

typedef enum{
      CANTRCV_TRCVMODE_NORMAL
   ,  CANTRCV_TRCVMODE_SLEEP
   ,  CANTRCV_TRCVMODE_STANDBY
}CanTrcv_TrcvModeType;

typedef enum{
      CANTRCV_WUMODE_ENABLE
   ,  CANTRCV_WUMODE_DISABLE
   ,  CANTRCV_WUMODE_CLEAR
}CanTrcv_TrcvWakeupModeType;

typedef enum{
      CANTRCV_WU_ERROR
   ,  CANTRCV_WU_NOT_SUPPORTED
   ,  CANTRCV_WU_BY_BUS
   ,  CANTRCV_WU_INTERNALLY
   ,  CANTRCV_WU_RESET
   ,  CANTRCV_WU_POWER_ON
   ,  CANTRCV_WU_BY_PIN
}CanTrcv_TrcvWakeupReasonType;
#endif

