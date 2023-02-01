#pragma once
#include "pch.h"
#include "CScanner.h"
#include <map>

#define gHeuristicScanner CHeuristicScanner::GetSingleton()

class CHeuristicScanner : public CSingleton<CHeuristicScanner>
{
    void LocateAndKillEvil(const TCHAR *evil, const TCHAR d);
    bool IsSafe(const String &path);
    int protLvl;
    unsigned detected;
public:
    CHeuristicScanner() : protLvl(-1) {}
    void ScanDisc(TCHAR letter);

    // dodaje wyj¹tek do bazy
    bool AddException(const String & file);
private:
    std::map<String, String> exceptions;
};