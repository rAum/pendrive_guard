#include "CFileManager.h"
#include "md5/md5.h"
#include "md5/md5wrapper.h"

template<> CFileManager *CFileManager::msSingleton = 0;

BOOL CFileManager::Exist(const TCHAR *path)
{
    //return GetFileAttributes(path) == INVALID_FILE_ATTRIBUTES ? FALSE : TRUE;
    return PathFileExists(path);
}
//-=-=--=-=-=-=-=-=-
void CFileManager::TurnOffAttributes(const TCHAR *file)
{
    DWORD attrib;
	// pobranie atrybutów
	if ((attrib = GetFileAttributes(file)) == INVALID_FILE_ATTRIBUTES)
		return;

	// usuwamy atrybut systemowy jesli jest ustawiony
	if (attrib & FILE_ATTRIBUTE_SYSTEM)
		SetFileAttributes(file,attrib & ~FILE_ATTRIBUTE_SYSTEM);
	// usuwamy atrybut ukryty jeśli jest ustawiony
	if (attrib & FILE_ATTRIBUTE_HIDDEN)
		SetFileAttributes(file,attrib & ~FILE_ATTRIBUTE_HIDDEN);
	// usuwamy atrybut READONLY jeśli jest ustawiony
	if (attrib & FILE_ATTRIBUTE_READONLY)
		SetFileAttributes(file,attrib & ~FILE_ATTRIBUTE_READONLY);
}
//-=-=--=-=-=-=-=-=-
DWORD CFileManager::GetAttributes(const TCHAR *path)
{
    return GetFileAttributes(path);
}
//-=-=--=-=-=-=-=-=-
bool CFileManager::SetAttributes(const TCHAR *path, DWORD attributes)
{
    if (SetFileAttributes(path,attributes))
        return true;
    return false;
}
//-=-=--=-=-=-=-=-=-
void CFileManager::TurnOnAttributes(const TCHAR *file)
{
    DWORD attrib = GetFileAttributes(file);
	attrib |= FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY;
	SetFileAttributes(file,attrib);
}
//-=-=--=-=-=-=-=-=-
int CFileManager::DoesItLookEvil(const TCHAR *path)
{
    int evilLvl = 0;
    DWORD attrib = GetFileAttributes(path);

    if (attrib != INVALID_FILE_ATTRIBUTES && !(attrib & FILE_ATTRIBUTE_DIRECTORY))
    {
        if (attrib & FILE_ATTRIBUTE_HIDDEN)
            ++evilLvl;
        if (attrib & FILE_ATTRIBUTE_SYSTEM)
            ++evilLvl;
    }

    return evilLvl;
}
//-=-=--=-=-=-=-=-=-
bool CFileManager::Delete(const TCHAR *file)
{
    if(!Exist(file))
        return false;

	TurnOffAttributes(file);

	if(!DeleteFile(file))
		return false;

	return true;
}
//-=-=--=-=-=-=-=-=-
TCHAR *evilExt[] = {
    TEXT(".exe"),
    TEXT(".vbs"),
    TEXT(".bat"),
    TEXT(".pif"),
    TEXT(".com"),
    TEXT(".cmd"),
    TEXT(".scf"),
    TEXT(".scr")
};
const int nEvilExt = sizeof(evilExt)/sizeof(evilExt[0]);
bool CFileManager::IsExecutable(const String &path)
{
    bool is_exe = false;

    for (int i=0; i<nEvilExt; ++i)
    {
        if (path.rfind(evilExt[i]) != String::npos)
        {
            is_exe = true;
            break;
        }
    }

    return is_exe;
}
//---------------------------
String CFileManager::CountMD5(const String &path)
{
    md5wrapper md5;

#ifdef UNICODE
    std::string tmp(WStringToString(path));
    std::string res = md5.getHashFromFile(tmp);
    return StringToWString(res);
#else
    std::string tmp(path);
    return md5.getHashFromFile(tmp);
#endif

}
#include "CDisk.h"
bool CFileManager::AddEasyProtForAll()
{
	DWORD disks = GetLogicalDrives();
	DWORD disk = 3; // pomijamy napęd dyskietek A oraz B (3 w disk/2 w for)
	TCHAR letter;
	bool errors = false;
	for (int i = 1; i < 26; ++i, disk <<= 1) 
    {		
        if (disks & disk) // disk founded! :P
        {
			letter = TEXT('A')+i;
            switch (gDisk.DriveType(letter))
            {
            case DRIVE_FIXED:
            case DRIVE_REMOVABLE:
				errors = AddEasyProt(letter);
			}
		}
	}

	return errors;
}

wchar_t foo[] = L"\\░▒▓豫►◙◘PendriveGuard◘◙◄豫▓▒░";

bool CFileManager::AddEasyProt(TCHAR d)
{
    String disk;
    disk += d;
    disk += TEXT(":\\autorun.inf");

    //if (IsDirectory(disk))
    //    return true;

    // usunięcie starego pliku
    Delete(disk.c_str());

    if (!CreateDirectory(disk.c_str(),NULL))
        return false;

#ifndef UNICODE
    std::wstring file = StringToWString(disk);
#else
    std::wstring file = disk;
#endif

    // nazwa pliku w Unicode (powinno to znacznie utrudnić usunięcie folderu przez wirusy)
    file += foo;

    HANDLE hFile = CreateFileW(file.c_str(),GENERIC_WRITE, 0, NULL,CREATE_ALWAYS, FILE_FLAG_RANDOM_ACCESS, 0);

    if (hFile == INVALID_HANDLE_VALUE)
        return false;

    DWORD bar;
    WriteFile(hFile,foo+1,(sizeof(foo)-1),&bar,NULL);

    CloseHandle(hFile);

    TurnOnAttributes(disk.c_str());

#ifndef UNICODE
    TurnOnAttributes(WStringToString(file).c_str());
#else
    TurnOnAttributes(file.c_str());
#endif

    return true;
}
//#include <Commdlg.h>
//void Save()
//{
//	OPENFILENAME ofn;
//	ofn.lStructSize = sizeof (OPENFILENAME);
//	ofn.hwndOwner = 0;
//	ofn.hInstance = NULL;
//	ofn.lpstrFilter = TEXT("JPEG\0*.jpg\0PNG\0*.png\0BMP\0*.bmp\0");
//	ofn.lpstrCustomFilter = NULL;
//	ofn.nMaxCustFilter = 0;
//	ofn.nFilterIndex = 0;
//	ofn.lpstrFile = new TCHAR[MAX_PATH+1];
//	memcpy(ofn.lpstrFile,TEXT("atraktor"),9);
//	ofn.nMaxFile = MAX_PATH ;
//	ofn.lpstrFileTitle = NULL ;
//	ofn.nMaxFileTitle = MAX_PATH ;
//	ofn.lpstrInitialDir = NULL ;
//	ofn.lpstrTitle = TEXT("Zapisz obraz");
//	ofn.Flags = OFN_OVERWRITEPROMPT;
//	ofn.nFileOffset = 0;
//	ofn.nFileExtension = 0;
//	ofn.lpstrDefExt = TEXT("jpg");
//	ofn.lCustData = 0;
//	ofn.lpfnHook = NULL;
//	ofn.lpTemplateName = NULL;
//
//	if(GetSaveFileName(&ofn))
//	{
//        ;
//    }
//    delete[] ofn.lpstrFile;
//}
