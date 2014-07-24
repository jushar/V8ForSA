/*****************************************************************
*
*  PROJECT:  V8 for MTA:SA and SA:MP
*  LICENSE:  See LICENSE in the top level directory
*  FILE:     MTASA/MTASA.cpp
*
*****************************************************************/
#include "MTASA.h"
#include "../V8Wrapper.h"

lua_State* MTASA::ms_LuaVM = nullptr;

void MTASA::CleanVMUp(lua_State* pLuaVM)
{
    if (pLuaVM == ms_LuaVM)
        ms_LuaVM = nullptr;
}

bool MTASA::CallLuaFunction(const std::string& functionName, const CLuaArguments& arguments)
{
    if (!ms_LuaVM)
        return false;

    return arguments.Call(ms_LuaVM, functionName.c_str());
}

int MTASA::Lua_InitialiseV8(lua_State* pLuaVM)
{
    if (!pLuaVM)
        return 0;

    // Check if already loaded from somewhere
    if (ms_LuaVM)
    {
        pModuleManager->ErrorPrintf("V8 has already been loaded! You can't load it twice!");
        lua_pushboolean(pLuaVM, false);
        return 1;
    }

    ms_LuaVM = pLuaVM;
    lua_pushboolean(pLuaVM, true);
    return 1;
}

int MTASA::Lua_ExecuteJavascript(lua_State* pLuaVM)
{
    if (!pLuaVM)
        return 0;

    // Check parameters
    if (lua_type(pLuaVM, 1) != LUA_TSTRING)
    {
        lua_pushboolean(pLuaVM, false);
        return 1;
    }

    g_pV8Wrapper->ExecuteCode(lua_tostring(pLuaVM, 1));
    lua_pushboolean(pLuaVM, true);
    return 1;
}
