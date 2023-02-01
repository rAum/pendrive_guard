#pragma once
#include "IControl.h"
class CFlatButton : public IControl
{
    static bool registerd;
    virtual void AddToWindow(HWND owner, HINSTANCE hInstance)
    {
        if (!registerd) 
            RegisterControl(hInstance);
        hControl = CreateWindow(TEXT("FlatBtn"), text, WS_CHILD | WS_VISIBLE, posx,posy,w,h, owner, (HMENU) id, hInstance, NULL);
    }
    void RegisterControl(HINSTANCE hInstance);
public:
    virtual LRESULT Event(const SEvent &event)
    {
        HWND hwnd = event.hWnd;
        WPARAM wParam = event.wParam;
        LPARAM lParam = event.lParam;
BITMAP bmInfo;
	RECT rect;
	switch(event.msg)
	{
	case WM_CREATE:
		//inicjalizacja stanu przycisku - na niewciœniêty
		 SetWindowLong(hwnd, 0, (LONG)FALSE);
		 //pobierz wymiary okna i ustaw odpowiedni region
		 GetWindowRect(hwnd,&rect);
		 HRGN hRgn;
		 hRgn = CreateRoundRectRgn(0,0,rect.right - rect.left,rect.bottom - rect.top,10,10);// CreateEllipticRgn(0,0,bmInfo.bmWidth/2-1,bmInfo.bmHeight-1);
		 SetWindowRgn(hwnd, hRgn, FALSE);
		break;
	case WM_LBUTTONDOWN:
		SetWindowLong(hwnd,0,(LONG)1);
		InvalidateRgn(hwnd,NULL,TRUE);
		SetCapture(hwnd);
		break;
	case WM_LBUTTONUP:
		SetWindowLong(hwnd,0,(LONG)0);
		InvalidateRgn(hwnd,NULL,TRUE);
		ReleaseCapture();
		
		SendMessage(GetParent(hwnd),WM_COMMAND,(WPARAM)MAKELONG((WORD)GetWindowLong(hwnd, GWL_ID), BN_CLICKED),(LPARAM)hwnd);
		break;
	case WM_MOUSEMOVE:
		POINT cur;
		HRGN rgn;
		rgn = CreateRectRgn(0,0,1,1);
		GetCursorPos(&cur);
		ScreenToClient(hwnd,&cur);
		GetWindowRgn(hwnd,rgn);

		if (PtInRegion(rgn,cur.x,cur.y) && (GetWindowLong(hwnd,0) != 0))
		{
			SetWindowLong(hwnd,0,(LONG)0);
			InvalidateRgn(hwnd,NULL,TRUE);
		}

		if (!PtInRegion(rgn,cur.x,cur.y) &&	(BOOL)GetWindowLong(hwnd,0))
			SendMessage(hwnd,WM_LBUTTONUP,wParam,lParam);
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd,&ps);

		// wczytanie danych
		HDC hdcMem;
		hdcMem = (HDC)GetClassLong(hwnd,0);
		HBITMAP bmp;
		bmp = (HBITMAP)GetClassLong(hwnd,4);

		HBRUSH brush = CreatePatternBrush(bmp);

		FillRect(hdc,&ps.rcPaint,brush);

		TCHAR text[400];
		GetWindowText(hwnd,text,400);
		
		if (GetWindowLong(hwnd,0) == 1)
			SetTextColor(hdc,0xFFFFFF);
		else if (GetWindowLong(hwnd,0) == 2)
			SetTextColor(hdc,0x0000FF);
		else
			SetTextColor(hdc,0x000000);

		SetBkMode(hdc,TRANSPARENT);
		TextOut(hdc,0,12,text,GetWindowTextLength(hwnd));
		RECT r;
		GetWindowRect(hControl,&r);
		DrawText(hdc,text,GetWindowTextLength(hwnd),&r,DT_CENTER | DT_VCENTER);

		SelectObject(hdcMem, bmp);
		BitBlt(hdc,0,0,bmInfo.bmWidth*2,bmInfo.bmHeight*6,hdcMem,0,0,SRCPAINT);

		EndPaint(hwnd,&ps);
	}
        return TRUE;
    }
};
