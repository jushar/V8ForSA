/*****************************************************************
*
*  PROJECT:  V8 for MTA:SA and SA:MP
*  LICENSE:  See LICENSE in the top level directory
*  FILE:     MTASA/ml_v8_mtasa.cpp
*
*****************************************************************/
#include "ml_v8_mtasa.h"
#include "../V8Wrapper.h"

ILuaModuleManager10* pModuleManager = NULL;

// Initialisation function (module entrypoint)
MTAEXPORT bool InitModule(ILuaModuleManager10* pManager, char* szModuleName, char* szAuthor, float* fVersion)
{
    pModuleManager = pManager;

    // Set the module info
    strncpy ( szModuleName, MODULE_NAME, MAX_INFO_LENGTH );
    strncpy ( szAuthor, MODULE_AUTHOR, MAX_INFO_LENGTH );
    (*fVersion) = (float)MODULE_VERSION;

    // Initialise V8
    g_pV8Wrapper = new V8Wrapper(true);

    return true;
}

MTAEXPORT bool ShutdownModule(void)
{
    delete g_pV8Wrapper;
    g_pV8Wrapper = nullptr;

    return true;
}

MTAEXPORT void RegisterFunctions(lua_State* luaVM)
{
    if (pModuleManager && luaVM)
    {
        pModuleManager->RegisterFunction(luaVM, "initialiseV8", MTASA::Lua_InitialiseV8);
        pModuleManager->RegisterFunction(luaVM, "executeJavascript", MTASA::Lua_ExecuteJavascript);
    }
}

MTAEXPORT bool DoPulse(void)
{
    return true;
}

MTAEXPORT bool ResourceStopping(lua_State* luaVM)
{
    return true;
}

MTAEXPORT bool ResourceStopped(lua_State* luaVM)
{
    MTASA::CleanVMUp(luaVM);
    return true;
}
