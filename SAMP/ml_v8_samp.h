/*****************************************************************
*
*  PROJECT:  V8 for MTA:SA and SA:MP
*  LICENSE:  See LICENSE in the top level directory
*  FILE:     SAMP/ml_v8_samp.h
*
*****************************************************************/
#include "../V8Wrapper.h"

#define HAVE_STDINT_H
#include "../include/pawn/amx.h"
#include "plugincommon.h"

#ifdef WIN32
#define PLUGIN_EXPORT PLUGIN_EXTERN_C _declspec(dllexport)
#endif

void *pAmxFunctions;
