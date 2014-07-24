/*****************************************************************
*
*  PROJECT:  V8 for MTA:SA and SA:MP
*  LICENSE:  See LICENSE in the top level directory
*  FILE:     MTASA/MTASA.h
*
*****************************************************************/
#pragma once

#include "../include/ILuaModuleManager.h"
#include "../extra/CLuaArguments.h"
extern ILuaModuleManager10* pModuleManager;


class MTASA
{
public:
    static void CleanVMUp               (lua_State* pLuaVM);
    static bool CallLuaFunction         (const std::string& functionName, const CLuaArguments& arguments);

    static int Lua_InitialiseV8         (lua_State* pLuaVM);
    static int Lua_ExecuteJavascript    (lua_State* pLuaVM);

private:
    static lua_State* ms_LuaVM;
};
