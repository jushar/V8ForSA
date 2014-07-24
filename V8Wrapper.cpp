/*****************************************************************
*
*  PROJECT:  V8 for MTA:SA and SA:MP
*  LICENSE:  See LICENSE in the top level directory
*  FILE:     V8Wrapper.cpp
*
*****************************************************************/
#include "V8Wrapper.h"
#include "MTASA/MTASA.h"
#include "extra/CLuaArguments.h"
using namespace v8;

V8Wrapper* g_pV8Wrapper;

V8Wrapper::V8Wrapper(bool isMTA) : m_IsMTA(isMTA), m_pIsolate(Isolate::New()), m_IsolateScope(m_pIsolate)
{
    HandleScope handleScope(m_pIsolate);
    
    Handle<ObjectTemplate> global = ObjectTemplate::New();
    global->Set(String::NewFromUtf8(m_pIsolate, "print"), FunctionTemplate::New(m_pIsolate, Script_Print));
    global->Set(String::NewFromUtf8(m_pIsolate, "callNativeFunction"), FunctionTemplate::New(m_pIsolate, Script_CallNativeFunction));

    Handle<Context> context = Context::New(m_pIsolate, nullptr, global);
    Context::Scope contextScope(context);
    m_Context.Reset(m_pIsolate, context);

    
    std::string s = "print('Hello world!')";
    Handle<String> source = String::NewFromUtf8(m_pIsolate, s.c_str());
    Handle<Script> script = Script::Compile(source);
    Handle<Value> result = script->Run();
}

V8Wrapper::~V8Wrapper()
{
}

bool V8Wrapper::ExecuteCode(const std::string& code)
{
    HandleScope handleScope(m_pIsolate);
    
    Local<Context> context = Local<Context>::New(m_pIsolate, m_Context);
    Context::Scope contextScope(context);

    Local<String> source = String::NewFromUtf8(m_pIsolate, code.c_str());
    Local<Script> script = Script::Compile(source);
    Local<Value> result = script->Run();

    String::Utf8Value utf8(result);
    printf("%s\n", *utf8);
    return true;
}

void V8Wrapper::Script_Print(const FunctionCallbackInfo<Value>& args)
{
    Handle<Value> arg = args[0];
    String::Utf8Value value(arg);
    printf("%s\n", *value);
}

void V8Wrapper::Script_CallNativeFunction(const FunctionCallbackInfo<Value>& args)
{
    if (args.Length() < 1)
    {
        args.GetReturnValue().Set(false);
        return;
    }

    std::string functionName(*String::Utf8Value(args[0]->ToString()));
    
    if (g_pV8Wrapper->IsMTA())
    {
        // Call lua function
        CLuaArguments arguments;
        
        // Iterate args (start at index 1 since the first argument is the function name)
        for (int i = 1; i < args.Length(); ++i)
        {
            Handle<Value> arg = args[i];
            
            if (arg->IsNull())
                arguments.PushNil();
            else if (arg->IsBoolean())
                arguments.PushBoolean(arg->BooleanValue());
            else if (arg->IsNumber())
                arguments.PushNumber(arg->NumberValue());
            else if (arg->IsString())
                arguments.PushString(*String::Utf8Value(arg->ToString()));
        }

        MTASA::CallLuaFunction(functionName, arguments);
    }
    else
    {
        // Todo
        return;
    }
}

/*bool V8Wrapper::BindFunction(const std::string& functionName, std::function<void(const FunctionCallbackInfo<Value>&)> func)
{
    HandleScope handleScope(m_pIsolate);

    Handle<ObjectTemplate> global = ObjectTemplate::New();
    FunctionCallback* function = func.target<FunctionCallback>();
    global->Set(String::NewFromUtf8(m_pIsolate, functionName.c_str()), FunctionTemplate::New(m_pIsolate, *function));
    Handle<Context> funcContext = Context::New(m_pIsolate, nullptr, global);
    Context::Scope contextFuncScope(funcContext);
}*/
