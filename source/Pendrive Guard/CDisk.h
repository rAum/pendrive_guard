#pragma once
#include "pch.h"

#define gDisk CDisk::GetSingleton()

class CDisk : public CSingleton<CDisk>
{
public:
    void operator()(TCHAR disk);

    TCHAR FirstDriveFromMask(DWORD unitmask);
    UINT DriveType(TCHAR disk);
private:
};
