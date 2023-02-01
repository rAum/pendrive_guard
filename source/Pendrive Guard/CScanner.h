#pragma once
#include "pch.h"

#define gScanner CScanner::GetSingleton()

class CStandardScanner;
class CHeuristicScanner;

typedef void (*PROGRESSFUNC)(unsigned procent);

class CScanner : public CSingleton<CScanner>
{
    friend class CStandardScanner;
    friend class CHeuristicScanner;
public:
    CScanner() : ms_sAction(ASK), ms_sType(BOTH) {}

    enum ScannerType { NONE, STANDARD, HEURISTIC, BOTH };
    enum VirusAction { AUTODELETE, ASK, LISTANDASK };
    
    ScannerType GetCurrentScanner() { return ms_sType; }
    void SetCurrentScanner(ScannerType type) { ms_sType = type; }

    VirusAction GetVirusAction() { return ms_sAction; }
    void SetVirusAction(VirusAction action) { ms_sAction = action; }


    void Scan(TCHAR disk='\0', PROGRESSFUNC f = 0);

    void ShowVirusListResult();
private:
    void TakeAction(const TCHAR *file);
    void AddVirus(const TCHAR *v) { virusList.push(v); }
    void AddPercent(float inc)
    {
        if (OnProgress)
        {
            completion += ms_sType != BOTH? inc*2.f : inc;
            OnProgress(static_cast<unsigned>(completion));
        }
    }

    ScannerType ms_sType;
    VirusAction ms_sAction;
    PROGRESSFUNC OnProgress;
    float completion;
    std::stack<String> virusList;
};
