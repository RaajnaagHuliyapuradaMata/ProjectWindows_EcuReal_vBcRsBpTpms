

#ifndef RDC_RINGBUFFER_X_H
#define RDC_RINGBUFFER_X_H

#include "Std_Types.h"
#include "ata_dev_5785.h"
#include "iTpms_Interface.h"

extern void RdcRb_Init(void);

extern void RdcRb_StoreTelegram(struct rfstruct* PS_TelegramData, uint32* PU32_Timestamp);

extern tsWS_RxDataIn* RdcRb_ReadTelegram(void);

extern boolean RdcRb_IsBufferEmpty(void);

#endif
