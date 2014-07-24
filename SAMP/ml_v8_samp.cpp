/*****************************************************************
*
*  PROJECT:  V8 for MTA:SA and SA:MP
*  LICENSE:  See LICENSE in the top level directory
*  FILE:     SAMP/ml_v8_samp.cpp
*
*****************************************************************/
#include "ml_v8_samp.h"
extern V8Wrapper* g_pV8Wrapper;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** ppData)
{
    pAmxFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    
    g_pV8Wrapper = new V8Wrapper(false);
    
    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
    delete g_pV8Wrapper;
    g_pV8Wrapper = nullptr;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* pAMX)
{
    return 0;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* pAMX)
{
    return AMX_ERR_NONE;
}
