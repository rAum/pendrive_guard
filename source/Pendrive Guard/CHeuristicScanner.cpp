#include "CHeuristicScanner.h"
#include "StringUtils.h"
#include "CFileManager.h"
#include "CLogger.h"

template<> CHeuristicScanner *CHeuristicScanner::msSingleton = 0;

TCHAR *evilNames[] = {
    TEXT("open"),
    TEXT("shellexecute"),
    TEXT("shell\\open(&0)\\command"),
    TEXT("shell\\open\\command"),
    TEXT("shell\\auto\\command"),
    TEXT("shell\\explore\\command")
};
//~~~~~~~~~~~~~~~~~~~~
const uint nEvilNames = sizeof(evilNames)/sizeof(evilNames[0]);

void CHeuristicScanner::ScanDisc(TCHAR d)
{
    float step = 100.f/nEvilNames;

    TCHAR autorunPath[16];
    wsprintf((TCHAR *)autorunPath,TEXT("%c:\\autorun.inf"),d);
    TCHAR buff[MAX_PATH+1];

    detected = 0;
    for (uint i=0; i<nEvilNames; ++i)
    {        
        if (GetPrivateProfileString(TEXT("AutoRun"), evilNames[i], TEXT(""), (TCHAR *)buff, MAX_PATH, autorunPath))
        {
            LocateAndKillEvil(buff, d);
        }
        gScanner.AddPercent(step);
    }
    // usuniêcie autorun.inf
    if (detected)
        gScanner.TakeAction(autorunPath);
}
//----------------------
void CHeuristicScanner::LocateAndKillEvil(const TCHAR *evil, const TCHAR d)
{
    std::vector<String> tokens;
    StringTokenize(evil,tokens,TEXT(" "));
    String path;
    path = d;
    path += TEXT(":\\");

    std::vector<String>::iterator it = tokens.begin();
    while(it != tokens.end())
    {
        it->insert(0,path);

        if (gFileManager.Exist(it->c_str()) && gFileManager.IsExecutable(*it) && !IsSafe(*it))
        {
            if (gFileManager.DoesItLookEvil(it->c_str()) > protLvl)
            {
                gScanner.TakeAction(it->c_str());
                ++detected;
            }
        }

        ++it;
    }
}
//--------------------------
bool CHeuristicScanner::IsSafe(const String &path)
{
    if (exceptions.find(path) == exceptions.end())
        return false;

    String md5 = gFileManager.CountMD5(path);
    if (exceptions[path] == md5)
        return true;

    return false;
}
//--------------------------
bool CHeuristicScanner::AddException(const String &file)
{
    if (!gFileManager.Exist(file.c_str()))
        return false;
    
    exceptions[file] = gFileManager.CountMD5(file);

    return true;
}
