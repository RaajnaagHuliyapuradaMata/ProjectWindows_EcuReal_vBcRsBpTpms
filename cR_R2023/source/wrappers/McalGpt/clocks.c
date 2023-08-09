#include "Types.h"

#include "device.h"
#include "clocks.h"

void CLOCKS_SetMainOscClock(void)
{
  protected_write(PROTCMD1,PROTS1,CKSC_CPUCLKS_CTL,0x02);
  while(CKSC_CPUCLKS_ACT!=0x02);
}

void CLOCKS_SetPllClock(void)
{
  protected_write(PROTCMD1,PROTS1,CKSC_CPUCLKS_CTL,0x03);
  while(CKSC_CPUCLKS_ACT!=0x03);
}

void CLOCKS_DisableClockDomainsForDeepSleep(void)
{
  CKSC_ICANS_CTL = 0x00;
}

void WaitHard(uint32 ulMicroSeconds)
{
    uint32 ulTicks = ulMicroSeconds * 12;
    while(ulTicks--);
}
