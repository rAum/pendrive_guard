#ifndef __CREGEDIT_H_
#define __CREGEDIT_H_

enum ProtectionStat { NOPROT, ASKPROT, AUTOPROT };

#include "Utils/CSingleton.h"

#define gRegedit CRegedit::GetSingleton() 

class CRegedit : public CSingleton<CRegedit>
{
public:
    /// sprawdza czy program jest autouruchamiany
    bool CheckAutoRun();
    // decyduje czy dodaæ program do autostartu
    bool AddAutoRun(bool install = true);
    /// Funkcje oznaczaj¹ce auto-usuwanie potencjalnych wirusów
    bool GetAutodel();
    bool SaveAutodel(bool autodel);
    // typ protekcji
    bool SaveProtType(bool type);
    bool GetProtType();
    bool SaveProtectionStat(ProtectionStat stat);
    ProtectionStat GetProtectionStat();
    /// Wy³¹cznie/w³¹czanie WSH (Windows Script)
    bool SetWSH(bool on);
	/// Sprawdzenie stanu WSH
	bool CheckWSH();
    /// Usuwa z³e wpisy z mountpoints
    bool DeleteEvilMountPoints();
};

#endif // __CREGEDIT_H_ //
