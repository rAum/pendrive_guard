#pragma once
#include "pch.h"

template<typename type>
std::string ToString(const type &var)
{
    std::ostringstream s;
    s << var;
    return s.str();
}

template<typename type>
std::wstring ToWString(const type &var)
{
    return StringToWString(ToString(var));
    //std::wostringstream s;
    //s << var;
    //return s.str();
}

std::string WStringToString(const std::wstring &w);
std::wstring StringToWString(const std::string &w);

#ifdef UNICODE
    typedef std::wstring String;
#else
    typedef std::string String;
#endif

void StringTokenize(const String&str, std::vector<String>&tokens, const String&delimiters);
