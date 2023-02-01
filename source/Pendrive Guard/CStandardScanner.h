#pragma once
#include "pch.h"
#include "CScanner.h"

#define gStandardScanner CStandardScanner::GetSingleton()

class CStandardScanner : public CSingleton<CStandardScanner>
{
public:
    void ScanDisc(TCHAR letter);
    void ScanAll();
};
