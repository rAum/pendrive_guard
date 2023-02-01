#pragma once
#include "pch.h"
#include "resource.h"
#include <shellapi.h>

// Stara klasa ;p
class CTray
{
public:
	CTray(HWND parent, UINT id, UINT callbackMsg, HICON icon, const TCHAR *tip=TEXT("Pendrive Guard"))
	{
		nid.cbSize = sizeof(nid);
		nid.hWnd = hWnd = parent;
		nid.uID = id;
		nid.uCallbackMessage = callbackMsg;
		nid.hIcon = icon;
		lstrcpy(szTip,tip);		
	}
	void SetTip(const TCHAR *tip) { StrNCpy(szTip,tip,sizeof(szTip)/sizeof(char)); }
	void SetIcon(HICON icon) { nid.hIcon = icon; }
	BOOL ShowTrayIcon()
	{
		nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
		//strncpy(nid.szTip,szTip,sizeof(szTip)/sizeof(char));
        StrNCpy(nid.szTip,szTip,sizeof(szTip)/sizeof(TCHAR));

		return Shell_NotifyIcon(NIM_ADD, &nid);
	}
	BOOL HideTrayIcon()
	{
		nid.uID = ID_TRAY;
		nid.uFlags = 0;

		return Shell_NotifyIcon(NIM_DELETE, &nid);
	}
private:
	NOTIFYICONDATA nid;
	HWND hWnd;
	TCHAR szTip[128];
};
