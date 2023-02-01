#pragma once
#include "IControl.h"

class CButton : public IControl
{
    virtual void AddToWindow(HWND owner, HINSTANCE hInstance)
    {
        hControl = CreateWindow(TEXT("button"), text, WS_CHILD | WS_VISIBLE | WS_TABSTOP, posx,posy,w,h, owner, (HMENU) id, hInstance, NULL);
    }
public:
    virtual LRESULT Event(const SEvent &event)
    {
        switch(event.msg)
        {
        case WM_COMMAND:
            MessageBox(0,TEXT("It's working!"), text,MB_OK);
            return FALSE;
        };
        return TRUE;
    }
};
