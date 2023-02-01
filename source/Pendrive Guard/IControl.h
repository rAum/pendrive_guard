#pragma once
#include "pch.h"

class CWindow;
/// Interfejs kontroli (button, edit etc)
class IControl
{
    friend CWindow;
public:
    IControl() : posx(0),posy(0),w(50),h(20), event(0), text(TEXT("Tekst")) { id = CreateId(); }
    virtual ~IControl() {}

    void SetEventFunc(WNDPROC eventFunc) { event = eventFunc; }

    LRESULT ProcessMessage(const SEvent &e)
    {
        if (LOWORD(e.wParam) == id)
            return (event? event(e.hWnd,e.msg,e.wParam,e.lParam) : Event(e));
        return TRUE;
    }
    virtual void SetPos(int x,int y) { posx = x; posy = y; if (hControl) SetWindowPos(hControl,0,x,y,0,0,SWP_NOSIZE | SWP_NOZORDER);}
    virtual void SetSize(int width, int height) { w = width; h = height;  if (hControl) SetWindowPos(hControl,0,0,0,w,h,SWP_NOREPOSITION | SWP_NOZORDER);}
    virtual void SetName(TCHAR *c) { text = c; if(hControl) SetWindowText(hControl,c); }
    virtual void Enable(bool en) { if (hControl) EnableWindow(hControl, en? TRUE : FALSE); }
    virtual void Visible(bool vis) { if (hControl) ShowWindow(hControl, vis? SW_SHOW : SW_HIDE); }
private:    
    virtual void AddToWindow(HWND owner, HINSTANCE hInstance) = 0;
    static int next_id;
    virtual LRESULT Event(const SEvent &event) { return TRUE; }
protected:
    int CreateId() { return next_id++; }
    int id;
    HWND hControl;
    int posx, posy, w, h;
    TCHAR *text;
    WNDPROC event;
};