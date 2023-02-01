#include "pch.h"

UID CreateUID(const char txt[sizeof(unsigned long long)])
{
    UID uid;
    memset(uid.txt,0,UID_LENGTH);
    strncpy((char *)uid.txt, txt, UID_LENGTH);
    return uid;
}