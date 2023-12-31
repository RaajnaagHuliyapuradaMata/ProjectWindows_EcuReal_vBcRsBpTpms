

#include "EcuM.hpp"

#if(ECUM_CFG_MODE_HANDLING == STD_ON)

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
#include "Det.hpp"
//#if(!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
// #error "AUTOSAR major version undefined or mismatched"
//#endif
//#if(!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
// #error "AUTOSAR minor version undefined or mismatched"
//#endif
#endif

#include "EcuM_Prv.hpp"

#define ECUM_START_SEC_CODE
#include "EcuM_MemMap.hpp"

Std_ReturnType EcuM_ReleaseRUN( EcuM_UserType user)

{
    Std_ReturnType Return_Value = E_NOT_OK;
    EcuM_UserType User_u16 = user;

   if(FALSE != EcuM_Lok_IsUserHandlingPossible_b(&User_u16, ECUM_RELEASERUN_APIID))
   {
        if(FALSE != EcuM_Lok_userRUNReqStatus_ab[User_u16])
        {

            EcuM_Lok_userRUNReqStatus_ab[User_u16] = FALSE;

            Return_Value = E_OK;
        }
        else{

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID,ECUM_RELEASERUN_APIID, ECUM_E_MISMATCHED_RUN_RELEASE);
#endif//ECUM_DEV_ERROR_DETECT
        }
   }

    return Return_Value;
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_MemMap.hpp"

#else

#endif

