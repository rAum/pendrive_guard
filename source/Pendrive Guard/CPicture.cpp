#include "CPicture.h"

bool CPicture::SetImage(int resource, HINSTANCE hInstance)
{
    if (hBmp)
        DeleteObject(hBmp);
    hBmp = (HBITMAP) LoadImage(hInstance,MAKEINTRESOURCE(resource),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    return hBmp != 0;
}
bool CPicture::SetImage(const TCHAR *file)
{
   if (hBmp)
        DeleteObject(hBmp);
    hBmp = (HBITMAP) LoadImage(0,file,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

    return hBmp != 0;
}