#pragma once
#include "pch.h"
#include "Utils/CSingleton.h"

#define gFileManager CFileManager::GetSingleton()

//GetFileType()
class CFileManager : public CSingleton<CFileManager>
{
public:
    /// Zwraca czy plik istnieje
    BOOL Exist(const TCHAR *path);
    /// Wy³¹cza atrybuty: ukryty, systemowy oraz tylko do odczytu
    void TurnOffAttributes(const TCHAR *path);
    /// Pobiera atrybuty danego pliku
    DWORD GetAttributes(const TCHAR *path);
    /// Ustawia atrybuty danego pliku
    bool SetAttributes(const TCHAR *path, DWORD attributes);
    /// W³¹cza atrybuty ukryty, systemowy oraz tylko do odczytu
    void TurnOnAttributes(const TCHAR *path);
    /// Sprawdza czy plik ma ustawione podejrzane flagi (im wy¿sza wartoœæ tym wiêksze "ZUO")
    int DoesItLookEvil(const TCHAR *path);
    /// Usuwa plik
    bool Delete(const TCHAR *path);
    /// Sprawdza czy dany plik jest plikiem wykonywalnym (exe,bat, com etc)
    bool IsExecutable(const String &path);
    /// Sprawdza czy dany plik jest folderem
    bool IsDirectory(const String &path) { return GetAttributes(path.c_str()) & FILE_ATTRIBUTE_DIRECTORY ? true : false; }
    /// Oblicza md5
    String CountMD5(const String &path);
    /// Dodaje _proste_ zabezpieczenie przeciwko autorun - trzeba podaæ œcie¿kê do dysku
    bool AddEasyProt(TCHAR d);
	/// Dodaje _proste_ zabezpieczenie dla wsztstkich dyskow
	bool AddEasyProtForAll();
};
