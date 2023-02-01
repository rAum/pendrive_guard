#pragma once
#include "pch.h"
#include "Utils/CSingleton.h"
#include "IControl.h"
#include "CTray.h"
#include "CPopupMenu.h"

extern LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class CWindow : public CSingleton<CWindow>
{
public:
    CWindow() : hwnd(0), w(300), h(150) {}
    ~CWindow() { if (tray) delete tray; if (menu) delete menu;}

    bool Create(HINSTANCE hInstance);
    bool Show() const;
    void SetCaption(TCHAR *);
    void AddCallback(UID, WNDPROC);
    void SetSize(int w, int h);    
    int DoLoop();
    inline IControl *GetControl(UID c) { return controls[c.n]; } 
    inline IControl *operator[] (UID c) { return GetControl(c); }
    void AddControl(UID c, IControl *control);
    HWND GetHandle() { return hwnd; }
private:
    std::map<unsigned long long, IControl *> controls;
    std::map<unsigned long long, IControl *>::iterator it;
    WNDCLASSEX wcWnd;
    int w,h;
    HWND hwnd;
    HINSTANCE hInst;
    HBITMAP hbLogo;
    CTray *tray;
    CPopupMenu *menu;
    //-----
    LRESULT OwnProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    friend LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
