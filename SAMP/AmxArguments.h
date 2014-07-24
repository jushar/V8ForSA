/*****************************************************************
*
*  PROJECT:  V8 for MTA:SA and SA:MP
*  LICENSE:  See LICENSE in the top level directory
*  FILE:     SAMP/AmxArguments.h
*
*****************************************************************/
#pragma once
#include <vector>

enum class eAmxArgumentType : char { Boolean, Number, String, Array };

class AmxArgument
{
    eAmxArgumentType m_Type;
    union
    {
        bool m_Boolean;
        int m_Number;
        char* m_String;
    };

public:
    AmxArgument(bool b)
    {
        m_Boolean = b;
        m_Type = eAmxArgumentType::Boolean;
    }
    AmxArgument(int n)
    {
        m_Number = n;
        m_Type = eAmxArgumentType::Number;
    }
    AmxArgument(char* s)
    {
        m_String = s;
        m_Type = eAmxArgumentType::String;
    }

    eAmxArgumentType GetType() const { return m_Type; };

    bool GetBool() const { return m_Boolean; };
    int GetNumber() const { return m_Number; };
    char* GetString() const { return m_String; };
};

class AmxArguments
{
public:
    inline void PushBoolean(bool b) { m_Arguments.push_back(AmxArgument(b)); };
    inline void PushNumber(int n) { m_Arguments.push_back(AmxArgument(n)); };
    inline void PushString(char* s) { m_Arguments.push_back(AmxArgument(s)); };

    const std::vector<AmxArgument>& GetList() const { return m_Arguments; };

private:
    std::vector<AmxArgument> m_Arguments;
};
