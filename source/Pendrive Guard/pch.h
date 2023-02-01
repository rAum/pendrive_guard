#pragma once

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <Shlwapi.h>

#include <WinIoCtl.h>
#include <Dbt.h>

#include "richedit.h"

#include <string>
#include <vector>
#include <stack>
#include <map>

#include <cstdio>
#include <sstream>

#include <cassert>

#include "StringUtils.h"
#include "md5/md5wrapper.h"
#include "Utils/CSingleton.h"

#include "resource.h"

#include <commctrl.h>
#pragma comment(lib,"comctl32.lib")

typedef unsigned int uint;

#ifdef UNICODE
    typedef std::wstring String;
#else
    typedef std::string String;
#endif

//----------------
union UID
{
    char txt[sizeof(unsigned long long)];
    unsigned long long n;
};
const size_t UID_LENGTH = sizeof(unsigned long long);
UID CreateUID(const char txt[sizeof(unsigned long long)]);
#define SID(x) reinterpret_cast<const char*>(x)
#define GenID(x) CreateUID(SID(x))

struct SEvent
{
    SEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) : hWnd(hWnd), msg(msg), wParam(wParam), lParam(lParam) {}
    
    HWND hWnd;
    UINT msg;
    WPARAM wParam;
    LPARAM lParam;
};
