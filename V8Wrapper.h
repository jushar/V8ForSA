/*****************************************************************
*
*  PROJECT:  V8 for MTA:SA and SA:MP
*  LICENSE:  See LICENSE in the top level directory
*  FILE:     V8Wrapper.h
*
*****************************************************************/
#pragma once
#include "lib/v8/include/v8.h"
#include <string>

class V8Wrapper
{
public:
    V8Wrapper(bool isMTA);
    ~V8Wrapper();

    inline bool IsMTA() { return m_IsMTA; };
    bool ExecuteCode(const std::string& code);

    static void Script_Print(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void Script_CallNativeFunction(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void Script_IsMTA(const v8::FunctionCallbackInfo<v8::Value>& info);

private:
    bool m_IsMTA;
    v8::Isolate* m_pIsolate;
    v8::Isolate::Scope m_IsolateScope;

    v8::Persistent<v8::Context> m_Context;
};

extern V8Wrapper* g_pV8Wrapper;
