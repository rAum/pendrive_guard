#pragma once
#include "pch.h"

class CPopupMenu
{
public:
    CPopupMenu(HINSTANCE hInstance, LPCTSTR lpMenuName)
    {
        hMenu = LoadMenu(hInstance, lpMenuName); 
    }
	HMENU GetHandle() { return hMenu; }
	BOOL ShowMenu(HWND hWnd, int x, int y)
    {
        SetForegroundWindow(hWnd); 
        return TrackPopupMenu(GetSubMenu(hMenu,0),GetSystemMetrics(SM_MENUDROPALIGNMENT),x,y,0,hWnd,NULL);  
        PostMessage(hWnd, WM_NULL, 0, 0);
    }
private:
	HMENU hMenu;
};
