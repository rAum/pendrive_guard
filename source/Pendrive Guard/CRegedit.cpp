#include "CRegedit.h"
#include "pch.h"

template<> CRegedit *CRegedit::msSingleton = 0;

bool CRegedit::CheckAutoRun()
{
	HKEY keyAutorun;
	if (RegOpenKeyEx(HKEY_CURRENT_USER,TEXT("software\\microsoft\\windows\\CurrentVersion\\run"),0,KEY_ALL_ACCESS,&keyAutorun)
		            != ERROR_SUCCESS)
		return false;

	if (RegQueryValueEx(keyAutorun,TEXT("PendriveGuard"),NULL,NULL,NULL,NULL) != ERROR_SUCCESS)
		return false;

	RegCloseKey(keyAutorun);
	return true;
}
//--------------
ProtectionStat CRegedit::GetProtectionStat()
{
	DWORD cbData = sizeof(ProtectionStat);
	ProtectionStat value = AUTOPROT;
	HKEY prot;
	if (RegOpenKeyEx(HKEY_CURRENT_USER,TEXT("software\\rAum Soft\\Pendrive Guard"),0,KEY_ALL_ACCESS,&prot) 
					!= ERROR_SUCCESS)
		return value;

	if (RegQueryValueEx(prot,TEXT("ProtectionMode"),NULL,NULL,(PBYTE) &value,&cbData) != ERROR_SUCCESS)
		return AUTOPROT;

	return value;
}
//--------------
bool CRegedit::SaveProtectionStat(ProtectionStat stat)
{
	HKEY prot;
	if (RegCreateKeyEx(HKEY_CURRENT_USER,TEXT("software\\rAum Soft\\Pendrive Guard"),NULL,NULL,REG_OPTION_VOLATILE,KEY_ALL_ACCESS,NULL,&prot,NULL)
					!= ERROR_SUCCESS)
		return false;

	if (RegSetValueEx(prot,TEXT("ProtectionMode"),NULL,REG_DWORD,(PBYTE) &stat, sizeof(stat)) != ERROR_SUCCESS)
		return false;

	return true;
}
//--------------
bool CRegedit::GetProtType()
{
	bool value = true;
	DWORD cbData = sizeof(value);
	HKEY prot;
	if (RegOpenKeyEx(HKEY_CURRENT_USER,TEXT("software\\rAum Soft\\Pendrive Guard"),0,KEY_ALL_ACCESS,&prot) 
					!= ERROR_SUCCESS)
		return value;

	if (RegQueryValueEx(prot,TEXT("ProtectionType"),NULL,NULL,(PBYTE) &value,&cbData) != ERROR_SUCCESS)
		return true;

	return value;
}
//--------------
bool CRegedit::SaveProtType(bool type)
{
	HKEY prot;
	if (RegCreateKeyEx(HKEY_CURRENT_USER,TEXT("software\\rAum Soft\\Pendrive Guard"),NULL,NULL,REG_OPTION_VOLATILE,KEY_ALL_ACCESS,NULL,&prot,NULL)
					!= ERROR_SUCCESS)
		return false;

	if (RegSetValueEx(prot,TEXT("ProtectionType"),NULL,REG_NONE,(PBYTE) &type, sizeof(type)) != ERROR_SUCCESS)
		return false;

	return true;
}
//--------------
bool CRegedit::GetAutodel()
{
	bool value;
	DWORD cbData;
	HKEY prot;
	if (RegOpenKeyEx(HKEY_CURRENT_USER,TEXT("software\\rAum Soft\\Pendrive Guard"),0,KEY_ALL_ACCESS,&prot) 
					!= ERROR_SUCCESS)
		return false;

	if (RegQueryValueEx(prot,TEXT("Autodel"),NULL,NULL,(PBYTE) &value,&cbData) != ERROR_SUCCESS)
		return false;

	return value;
}
//--------------
bool CRegedit::SaveAutodel(bool autodel)
{
	HKEY prot;
	if (RegCreateKeyEx(HKEY_CURRENT_USER,TEXT("software\\rAum Soft\\Pendrive Guard"),NULL,NULL,REG_OPTION_VOLATILE,KEY_ALL_ACCESS,NULL,&prot,NULL)
					!= ERROR_SUCCESS)
		return false;

	if (RegSetValueEx(prot,TEXT("Autodel"),NULL,REG_NONE,(PBYTE) &autodel, sizeof(autodel)) != ERROR_SUCCESS)
		return false;

	return true;
}
//--------------
bool CRegedit::AddAutoRun(bool install)
{
    //TODO poprawiæ
	TCHAR exe[MAX_PATH*2];
	GetModuleFileName(GetModuleHandle(NULL),exe,MAX_PATH);
    String path(TEXT("\""));
	path.append(exe);
	path.append(TEXT("\" /tray"));

	HKEY keyAutorun;
	if (RegOpenKeyEx(HKEY_CURRENT_USER,TEXT("software\\microsoft\\windows\\CurrentVersion\\run"),0,KEY_ALL_ACCESS,&keyAutorun)
		            != ERROR_SUCCESS)
					return false;
	if (install)
	{
		if (RegSetValueEx(keyAutorun,TEXT("PendriveGuard"),0,REG_SZ,(LPBYTE) path.c_str(),path.size()*sizeof(TCHAR))
					!= ERROR_SUCCESS)
			return false;
	}
	else
	{
		if (RegDeleteValue(keyAutorun,TEXT("PendriveGuard")) != ERROR_SUCCESS)
			return false;
	}

	RegCloseKey(keyAutorun);
	return true;
}
//--------------
bool CRegedit::SetWSH(bool on)
{
    HKEY wsh;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT("Software\\Microsoft\\Windows Script Host\\Settings"),0,KEY_ALL_ACCESS,&wsh)
				    != ERROR_SUCCESS)
	    if (RegOpenKeyEx(HKEY_CURRENT_USER,TEXT("Software\\Microsoft\\Windows Script Host\\Settings"),0,KEY_ALL_ACCESS,&wsh)
					    != ERROR_SUCCESS)
		    return false;
    DWORD enabled = on? 1 : 0;
    if (RegSetValueEx(wsh, TEXT("Enabled"),0,REG_DWORD,(LPBYTE) &enabled,sizeof(enabled))
					    != ERROR_SUCCESS)
		    return false;

    return true;
}
bool CRegedit::CheckWSH()
{
	HKEY wsh;
    if ((RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT("Software\\Microsoft\\Windows Script Host\\Settings"),0,KEY_ALL_ACCESS,&wsh)
				    != ERROR_SUCCESS)
	    && (RegOpenKeyEx(HKEY_CURRENT_USER,TEXT("Software\\Microsoft\\Windows Script Host\\Settings"),0,KEY_ALL_ACCESS,&wsh)
					    != ERROR_SUCCESS))
		    return true;

	DWORD enabled;
	DWORD size = sizeof(enabled);
	if (RegQueryValueEx(wsh, TEXT("Enabled"),NULL,NULL,(PBYTE) &enabled,&size)
					    != ERROR_SUCCESS)
		    return true;

	RegCloseKey(wsh);
	return enabled == 1;
}
//--------------
#include "shlwapi.h"
#pragma comment(lib,"shlwapi.lib")
//--------------
bool CRegedit::DeleteEvilMountPoints()
{
    HKEY mp;
	if (RegOpenKeyEx(HKEY_CURRENT_USER,TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MountPoints2"),0,KEY_ALL_ACCESS,&mp)
					!= ERROR_SUCCESS)
			return false;

	DWORD i=0, size = MAX_PATH;
	TCHAR buff[MAX_PATH];

	while (RegEnumKeyEx(mp,i++,buff,&size,NULL,NULL,NULL,NULL) == ERROR_SUCCESS)
	{
		size = MAX_PATH;			
		if (buff[0] == TEXT('{'))
		{
			// ta funkcja usuwa puste klucze
			if(RegDeleteKey(mp,buff) == ERROR_SUCCESS)
				i = 0;
			// ta usuwa zaœ klucze z ich wartoœcami (ale mniej zgodna, dlatego jest wywo³ywana jako druga)
			else if (SHDeleteKey(mp,buff) == ERROR_SUCCESS)
				i = 0;
		}
	}

	return false;
}
