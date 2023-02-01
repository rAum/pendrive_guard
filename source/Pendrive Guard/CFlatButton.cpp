#include "CFlatButton.h"

bool CFlatButton::registerd = false;

LRESULT CALLBACK FlatBtnProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    BITMAP bmInfo = {0};
	RECT rect;
	switch(msg)
	{
    case WM_COMMAND:
        MessageBox(0,TEXT("FLat Btn"),TEXT("Test"),MB_OK);
        break;
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

		TCHAR text[401];
		GetWindowText(hwnd,text,400);
		
		if (GetWindowLong(hwnd,0) == 1)
			SetTextColor(hdc,0x00FF00);
		else if (GetWindowLong(hwnd,0) == 2)
			SetTextColor(hdc,0xFFFFFF);
		else
			SetTextColor(hdc,0xFFFFFF);

		SetBkMode(hdc,TRANSPARENT);
		TextOut(hdc,10,12,text,GetWindowTextLength(hwnd));
		RECT r;
		GetWindowRect(hwnd,&r);
		DrawText(hdc,text,GetWindowTextLength(hwnd),&r,DT_CENTER | DT_VCENTER);

		SelectObject(hdcMem, bmp);
		BitBlt(hdc,0,0,bmInfo.bmWidth,bmInfo.bmHeight,hdcMem,0,0,SRCPAINT);

		EndPaint(hwnd,&ps);
        break;
	}
	return DefWindowProc (hwnd, msg, wParam, lParam);
}

void CFlatButton::RegisterControl(HINSTANCE hInstance)
{
    HBITMAP bmp = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BUTTONBKG));
	HDC hdcMem = CreateCompatibleDC(NULL);
	HBRUSH brush = CreatePatternBrush(bmp);

	WNDCLASS wc;
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("FlatBtn");
	wc.lpfnWndProc = FlatBtnProc;
	wc.hCursor = NULL; //LoadCursor(0,IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH); //GetSysColorBrush(COLOR_BTNFACE);
	wc.style = 0;
	wc.hIcon = NULL;
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 16; // na uchwyt bitmapy 
	wc.cbWndExtra = 8;  // na informacjê czy przycisk jest wciœniêty
	
	if(!RegisterClass(&wc))
        return;

	// tymczasowe okno nowej klasy
	HWND tmp = CreateWindowEx(0,TEXT("FlatBtn"),NULL,WS_POPUP,0,0,0,0,NULL,NULL,hInstance,NULL);

	// zapamiêtanie kontekstu i bitmap w dodatkowej pamiêci okna
	SetClassLong(tmp, 0, (LONG)hdcMem);
	SetClassLong(tmp, 4, (LONG)bmp);
	SetClassLong(tmp, 8, (LONG)brush);

    registerd = true;
}
