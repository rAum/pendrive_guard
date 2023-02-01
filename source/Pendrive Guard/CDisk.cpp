#include "CDisk.h"
#include "CScanner.h"

template<> CDisk *CSingleton<CDisk>::msSingleton = 0;

TCHAR CDisk::FirstDriveFromMask(DWORD unitmask)
{
    TCHAR letter = '\0';
	for (int i=0;i<26; ++i)
	{
		if (unitmask & 0x1)
        {
			letter = TEXT('A') + i;
            break;
        }
		unitmask >>= 1;
	}
    return letter;
}
//-=--==--=-=-=-=-
void CDisk::operator()(TCHAR disk)
{
    gScanner.Scan(disk);
}
//-=-=-=-=-=-=-=-=
// TODO: check  msdn -> SetupDiGetDeviceRegistryProperty()
UINT CDisk::DriveType(TCHAR disk)
{
    TCHAR diskpath[4]; //3
	wsprintf(diskpath,TEXT("%c:/"),disk);

	return GetDriveType(diskpath);
}
