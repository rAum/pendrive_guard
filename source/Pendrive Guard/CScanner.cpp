#include "CScanner.h"
#include "CHeuristicScanner.h"
#include "CStandardScanner.h"
#include "CFileManager.h"
#include "CLogger.h"
#include "Dialogs.h"

template<> CScanner *CScanner::msSingleton = 0;

void CScanner::Scan(TCHAR disk, PROGRESSFUNC f)
{
    OnProgress = f;
    completion = 0.f;

    if (disk != '\0')
    {
        gLogger << LOG_MSG << TEXT("---Skanowanie noœnika ") << disk << TEXT(":\\ ---");
        switch (ms_sType)
        {
        case CScanner::BOTH:
            gHeuristicScanner.ScanDisc(disk);
        case CScanner::STANDARD:
            gStandardScanner.ScanDisc(disk);
            break;
        case CScanner::HEURISTIC:
            gHeuristicScanner.ScanDisc(disk);
            break;
        };
        gLogger << LOG_MSG << TEXT("---Koniec skanowania dysku---");
    }
    else
    {
        gLogger << LOG_MSG << TEXT("---Skanowanie wszystkich dysków---");
        gStandardScanner.ScanAll();
        gLogger << LOG_MSG << TEXT("---Koniec skanowania dysków---");
    }

    if (OnProgress)
        OnProgress(100); 
    OnProgress = 0;
}
//------------------
void CScanner::TakeAction(const TCHAR *file)
{
    switch (ms_sAction)
    {
    case CScanner::ASK:
        switch (VirusActionDialog(file))
        {
        case IDC_NOACTION:
            return;
        case IDC_ADDEXCEPTION:
            gHeuristicScanner.AddException(file);
            return;
        }
    case CScanner::AUTODELETE:
        if (!gFileManager.Delete(file))
            gLogger << LOG_ERROR << TEXT("Nie uda³o siê usun¹æ pliku ") << file;
        else
            gLogger << LOG_MSG << TEXT("Usuniêto wirusa: ") << file;
        break;
    case CScanner::LISTANDASK:
        return ;
        AddVirus(file);
    }
}
//-------------------
void CScanner::ShowVirusListResult()
{
    virusList.pop();
}
