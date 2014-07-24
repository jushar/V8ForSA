/*****************************************************************
*
*  PROJECT:  V8 for MTA:SA and SA:MP
*  LICENSE:  See LICENSE in the top level directory
*  FILE:     SAMP/SAMP.h
*
*****************************************************************/
#pragma once
#include "AmxArguments.h"

#define HAVE_STDINT_H
#include "../include/pawn/amx.h"

class SAMP
{
public:
    static AmxArgument CallAmxFunction(const std::string& functionName, const AmxArguments& arguments);

private:
    static AMX* ms_pAmxVM;
};
