#pragma once
#include "pch.h"
#include <fstream>

// TODO: przepisac na uzywanie jedynie winapi

#define gLogger CLogger::GetSingleton()

enum LOGGER { LOG_MSG, LOG_WARNING, LOG_ERROR };

class CLogger : public CSingleton<CLogger>
{
    String log;
    unsigned errCount, warCount, msgCount;
public:
    CLogger() : log(TEXT("Pendrive Guard Log File: \n-=-=-=-=-=-=-=-=-=-=-=-")), errCount(0), warCount(0), msgCount(0) {}
    ~CLogger() {}

#ifdef UNICODE
    typedef std::wofstream plik;
#else
    typedef std::ofstream plik;
#endif

    void Dump()
    {
        plik f("log.txt");
        f << log.c_str();
        f.close();
    }

    CLogger &operator<<(const TCHAR *msg)
    {
        log.append(msg);
        return *this;
    }

    CLogger &operator<<(const TCHAR t)
    {
        log += t;
        return *this;
    }

    CLogger &operator<<(LOGGER l)
    {
        switch (l)
        {
        case LOG_WARNING:
            log.append(TEXT("\n[WAR] "));
            ++warCount;
            break;
        case LOG_ERROR:
            log.append(TEXT("\n[ERR] "));
            ++errCount;
            break;
        default:
            log.append(TEXT("\n"));
            ++msgCount;
        };

        return *this;
    }

    unsigned ErrorsCount() { return errCount; }
    unsigned WarningsCount() { return warCount; }
    unsigned MessageCount() { return msgCount; }
    unsigned InfoCount() { return errCount + warCount + msgCount; }
    const TCHAR *GetLog() { return log.c_str(); }
};
