/*****************************************************************
*
*  PROJECT:  V8 for MTA:SA and SA:MP
*  LICENSE:  See LICENSE in the top level directory
*  FILE:     SAMP/SAMP.cpp
*
*****************************************************************/
#include "SAMP.h"
AMX* SAMP::ms_pAmxVM = nullptr;

AmxArgument SAMP::CallAmxFunction(const std::string& functionName, const AmxArguments& arguments)
{
    if (!ms_pAmxVM)
        return false;

    // Push arguments onto the stack
    for (const auto& argument : arguments.GetList())
    {
        switch (argument.GetType())
        {
        case eAmxArgumentType::Boolean:
            amx_Push(ms_pAmxVM, static_cast<cell>(argument.GetBool()));
            break;
        case eAmxArgumentType::Number:
            amx_Push(ms_pAmxVM, static_cast<cell>(argument.GetNumber()));
            break;
        case eAmxArgumentType::String:
            cell amx_addr, *amx_physaddr;
            amx_PushString(ms_pAmxVM, &amx_addr, &amx_physaddr, argument.GetString(), 0, 0);
        }
    }
    
    // Call function
    cell amx_return;
    amx_Exec(ms_pAmxVM, &amx_return, AMX_EXEC_MAIN);

    return AmxArgument(amx_return);
}
