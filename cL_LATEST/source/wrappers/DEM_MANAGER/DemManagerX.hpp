#ifndef DEM_MANAGER_X_H
#define DEM_MANAGER_X_H

#include "Std_Types.hpp"

#define cECU_UBAT_FLS_MIN 55
#define cECU_UBAT_MIN     95
#define cECU_UBAT_MAX     170

typedef enum{
  DEMMGR_E_BCM_PERIPHERAL_MASTER_CLOCK_INDEX = 0U
   ,  DEMMGR_E_ESP_WHEEL_PULSE_STAMPED_INDEX
   ,  DEMMGR_E_ESP_WSPEED_FRONT_BODY_LCAN_INDEX1
   ,  DEMMGR_E_ESP_WSPEED_REAR_BODY_LCAN_INDEX1
   ,  DEMMGR_E_ESP_WSPEED_FRONT_BODY_LCAN_INDEX2
   ,  DEMMGR_E_ESP_WSPEED_REAR_BODY_LCAN_INDEX2
   ,  DEMMGR_E_TMM_STATUS_BODY_LCAN_INDEX
   ,  DEMMGR_E_VEH_STS_BODY_LCAN_INDEX
   ,  DEMMGR_E_NUMBER_OF_RX_MESSAGES_MONITED
}DemMGR_Enum_RxMessages;

extern void DemMGR_Init(void);

extern void DemMGR_StartMonitoring(void);

extern void DemMGR_StopMonitoring(void);

extern void DemMGR_MainFunction(void);

extern void DemMGR_RxReceived(DemMGR_Enum_RxMessages EN_RxMessage);

extern void DemMGR_ClearMonitor(DemMGR_Enum_RxMessages EN_RxMessage);

extern void DemMGR_EcuVoltageMonitorMainFunction(void);

extern void DemMGR_CheckModuleProvisioning(void);
#endif
