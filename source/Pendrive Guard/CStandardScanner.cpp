#include "CStandardScanner.h"
#include "CFileManager.h"
#include "CDisk.h"
#include "CLogger.h"
#include "CHeuristicScanner.h"

template<> CStandardScanner *CStandardScanner::msSingleton = 0;
template<> CLogger *CLogger::msSingleton = 0;
//-------Pocz¹tek bazy------------------
// Wariant MS32DLL.dll.vbs (VBS.Solow, VBS.Pica.E@mm)
// Wariant PegeFile.pif:
// Wariant RavMonE.exe / AdobeR.exe (RJump Worm):
// Wariant activexdebugger32.exe (Amca Worm):
// Wariant svchost.exe (Perlovga Worm / TrojanDropper.Small.Apl)
// Wariant ctfmon.exe (FakeRecycled)
//-----------------------------------------
// Moje detecty:
// 2u.com
// pagefile.sys.vbs
// yew.bat
// vva0hc0p.cmd
// ise.exe
// x3.exe && program.exe
//--------------------------------------------
TCHAR *paths[] = {			
		TEXT("%c:\\copy.exe"),
        TEXT("%c:\\xcopy.exe"),
		TEXT("%c:\\host.exe"),
		TEXT("%c:\\Recycled\\desktop.ini"),
		TEXT("%c:\\Recycled\\INFO2"),
		TEXT("%c:\\Recycled\\ctfmon.exe"),
		TEXT("%c:\\msvcr71.dll"),		
		TEXT("%c:\\PegeFile.pif"),
		TEXT("%c:\\MS32DLL.dll.vbs"),
		TEXT("%c:\\jxqevly.exe"),
        TEXT("%c:\\2u.com"),
        TEXT("%c:\\pagefile.sys.vbs"),
        TEXT("%c:\\yew.bat"),
        TEXT("%c:\\pnt.com"),
        TEXT("%c:\\vva0hc0p.cmd"),
        TEXT("%c:\\RECYCLER\\S-1-5-21-1482476501-1644491937-682003330-1013\\ise.exe"),
        TEXT("%c:\\x3.exe"),
        TEXT("c:\\program.exe"),
        TEXT("%c:\\autorun.inf")
	};

TCHAR *pathsExpand[] = {
	TEXT("%USERPROFILE%\\Menu Start\\Programy\\Autostart\\ctfmon.exe"),	
	TEXT("%ProgramFiles%\\Internet Explorer\\PLUGINS\\NewTemp.bak"),
	TEXT("%ProgramFiles%\\Internet Explorer\\PLUGINS\\NewTemp.dll"),
	TEXT("%ProgramFiles%\\Internet Explorer\\PLUGINS\\System64.Jmp"),
	TEXT("%ProgramFiles%\\Internet Explorer\\PLUGINS\\System64.Sys"),
	TEXT("%ProgramFiles%\\Internet Explorer\\IEXPLORE32.jmp"),
	TEXT("%ProgramFiles%\\Internet Explorer\\IEXPLORE32.Sys"),
	TEXT("%ProgramFiles%\\Internet Explorer\\IEXPLORE32.Dat"),
	TEXT("%ProgramFiles%\\Internet Explorer\\IEXPLORE32.win"),
	TEXT("%temp%\\nesneler.exe"),
	TEXT("%windir%\\xcopy.exe"),
	TEXT("%windir\\system\\ACD2.CMD"),
	TEXT("%windir\\system\\ACD.CMD"),
	TEXT("%windir\\system32\\scrrntr.dll"),
	TEXT("%windir\\system32\\PAC.EXE"),
	TEXT("%windir\\system32\\KTKBDHK3.DLL"),
	TEXT("%windir\\system32\\Ijl11.dll"),
	TEXT("%windir\\system32\\activexdebugger32.exe"),
	TEXT("%windir\\system32\\kmon.ocx"),
	TEXT("%windir\\system32\\mswinsck.ocx"),
    TEXT("%windir\\system32\\avsjmjcx.exe"),
	TEXT("%windir\\RavMonE.exe"),
	TEXT("%windir\\system32\\visin.exe"),
	TEXT("%windir\\MS32DLL.dll.vbs"),
	TEXT("%windir\\autorun.inf"),
	TEXT("%windir\\svchost.exe"),
	TEXT("%windir\\system32\\temp1.exe"),
	TEXT("%windir\\system32\\temp2.exe"),
	TEXT("%windir\\boot.ini"),
	TEXT("%USERPROFILE%\\ravmonlog"),
    TEXT("%ALLUSERSPROFILE%\\Dane aplikacji\\nudsxizg"),
    TEXT("%ALLUSERSPROFILE%\\Application Data\\nudsxizg"),
    TEXT("%ProgramFiles%\\onjjvyc")
	};
    // TODO: SHGetSpecialFolderLocation Function

const uint nPaths = sizeof(paths)/sizeof(paths[0]);
const uint nPathsExpand = sizeof(pathsExpand)/sizeof(pathsExpand[0]);
//=========-Koniec bazy-=============

void CStandardScanner::ScanDisc(TCHAR d)
{
    TCHAR file[MAX_PATH+1];

    for (uint i=0; i<nPaths; ++i)
    {
        // dodaje literê do œcie¿ek
        wsprintf((TCHAR *)file,paths[i],d);

        if (gFileManager.Exist(file))
        {
            gScanner.TakeAction(file);
        }
    }
}
//----------------
void CStandardScanner::ScanAll()
{
    TCHAR file[MAX_PATH*2+1];

    DWORD disks = GetLogicalDrives();
	DWORD disk = 3; // pomijamy napêd dyskietek A oraz B (3 w disk/2 w for)
	TCHAR letter;
    uint k;
    float step = 200.f/25.f;
	for (int i = 1; i < 26; ++i, disk <<= 1) 
    {
		gScanner.AddPercent(step);
        if (disks & disk) // disk founded! :P
        {
			letter = TEXT('A')+i;
            switch (gDisk.DriveType(letter))
            {
            case DRIVE_FIXED:
            case DRIVE_REMOVABLE:
			    for(k = 0; k < nPaths; ++k)
			    {
				    wsprintf(file,paths[k],letter);
                    if (gFileManager.Exist(file))
                        gScanner.TakeAction(file);
			    }
            };
		}
	}

    step =  200.f/nPathsExpand;
	// II faza pliki systemowe ;p
	for(k = 0; k < (sizeof(pathsExpand)/sizeof(pathsExpand[0])); ++k)
	{
		ExpandEnvironmentStrings(pathsExpand[k],file,MAX_PATH<<1);
		if (gFileManager.Exist(file))
        {
            gScanner.TakeAction(file);
        }
        gScanner.AddPercent(step);
	}
}
