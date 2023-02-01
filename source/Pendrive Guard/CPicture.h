#pragma once
#include "IControl.h"

class CPicture : public IControl
{
    virtual void AddToWindow(HWND owner, HINSTANCE hInstance)
    {
        // niewidzialny przycisk :>
       //hControl = CreateWindow(TEXT("button"), text, WS_CHILD, posx,posy,w,h, owner, (HMENU) id, hInstance, NULL);
    }
public:
    CPicture() : hBmp(0), hdc(0) {}

    bool SetImage(int resource,HINSTANCE hInstance=0);
    bool SetImage(const TCHAR *file);
    virtual LRESULT Event(const SEvent &event)
    {
        switch(event.msg)
        {
        case WM_PAINT:
            MessageBox(0,0,0,0);
            return FALSE;
        };
        return TRUE;
    }
private:
    HBITMAP hBmp;
    HDC hdc;
};
