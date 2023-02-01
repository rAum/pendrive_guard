#include "CWindow.h"
#include "CDisk.h"
#include "resource.h"
#include "Dialogs.h"

int IControl::next_id = 100;

template<> CWindow *CSingleton<CWindow>::msSingleton = 0;

HBITMAP CreateBitmapMask(HBITMAP hbmColour, COLORREF crTransparent);

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return CWindow::GetSingleton().OwnProc(hWnd,msg,wParam,lParam);
}
//------
bool CWindow::Create(HINSTANCE hInstance)
{
    hInst = hInstance;

    memset(&wcWnd,0,sizeof(wcWnd));
    wcWnd.lpfnWndProc    = WndProc;
    wcWnd.cbSize         = sizeof(wcWnd);
    wcWnd.style          = CS_HREDRAW | CS_VREDRAW;
    wcWnd.hInstance      = hInst;
    wcWnd.lpszClassName  = TEXT("pgWndClass@rAum");
    wcWnd.hIcon          = LoadIcon(hInst, MAKEINTRESOURCE(IDI_PROGRAM));
    wcWnd.hIconSm        = LoadIcon(hInst, MAKEINTRESOURCE(IDI_PROGRAM16));
    wcWnd.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcWnd.hbrBackground  = (HBRUSH) GetStockObject(BLACK_BRUSH);//(COLOR_WINDOW+1);

    if (!RegisterClassEx(&wcWnd))
    {
        MessageBox(0,TEXT("Failed to register window class"),0,MB_OK | MB_ICONERROR);
        return false;
    }

    hwnd = CreateWindowEx ( 0,
                            TEXT("pgWndClass@rAum"),
                            TEXT("Pendrive Guard"),
                            WS_DLGFRAME | WS_SYSMENU, //WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT, CW_USEDEFAULT,
                            w,h,
                            0,0,
                            hInst,
                            0 );
    if (!hwnd)
    {
        MessageBox(0,TEXT("Failed to create window"),0,MB_OK | MB_ICONERROR);
        return false;
    }

    hbLogo = LoadBitmap(GetModuleHandle(NULL),MAKEINTRESOURCE(IDB_LOGO));
    tray = new CTray(hwnd,ID_TRAY, CMSG_TRAY, LoadIcon(hInst,MAKEINTRESOURCE(IDI_PROGRAM16)));
    menu = new CPopupMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

    return true;
}
//------
int CWindow::DoLoop()
{
    assert(hwnd != 0);

    MSG msg;
    while (GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
///--------
//-----
LRESULT CWindow::OwnProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT l;
    switch(msg)
    {
    case WM_DESTROY:        
        if (IsIconic(hWnd))
        {
			tray->HideTrayIcon();
            // aby ikonka znika³a:
            ShowWindow(hWnd,SW_SHOW);
        }
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd,&ps);
		HDC hdcN = CreateCompatibleDC(hdc);

		//RECT wndRect;
		//GetWindowRect(hWnd,&wndRect);

		//HBRUSH gray = CreateSolidBrush(0xAAAAAA);
		//HBRUSH black = CreateSolidBrush(0x000000);
		//SelectObject(hdc,gray);
		//Rectangle(hdc,0,0,wndRect.right,45);
		//SelectObject(hdc,black);
		//Rectangle(hdc,0,45,wndRect.right,wndRect.bottom);
		//DeleteObject(gray);
		//DeleteObject(black);

		SelectObject(hdcN, CreateBitmapMask(hbLogo,0xFF00FF));
		BitBlt(hdc,5,20,96,96,hdcN,0,0,SRCAND);

		SelectObject(hdcN,hbLogo);
		BitBlt(hdc,5,20,96,96,hdcN,0,0,SRCPAINT);

		SelectObject(hdcN,hdc);
		DeleteDC(hdcN);
		EndPaint(hWnd,&ps);

    }
        return 0;
    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
    	case IDM_PRZYWR__1:
			SendMessage(hWnd,CMSG_TRAY,ID_TRAY,WM_LBUTTONDOWN);
			break;
		case IDM_SKANUJ_DYSKI_WYMIENNE1:
            ScanDialog();			
			break;
		case IDM_ZAMKNIJ1:
			SendMessage(hWnd,WM_DESTROY,0,0);
			break;
        }
        break;
    case WM_CLOSE:
    	tray->ShowTrayIcon();
		ShowWindow(hWnd,SW_HIDE);
        return 0;
    case CMSG_TRAY:
		if (wParam == ID_TRAY)
			if (lParam == WM_LBUTTONDOWN)
			{
                ShowWindow(hWnd, SW_SHOW);
				tray->HideTrayIcon();
			}
			else if (lParam == WM_RBUTTONDOWN)
			{
				POINT point;
				GetCursorPos(&point);				
				menu->ShowMenu(hWnd,point.x,point.y);
			}
		return 0;
    case WM_DEVICECHANGE:
	{
		PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR) lParam;
		switch(wParam)
		{
		case DBT_DEVICEARRIVAL:
			if (lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
			{
				PDEV_BROADCAST_VOLUME lpdv = (PDEV_BROADCAST_VOLUME) lpdb;
                Beep(400,100);
				TCHAR z = gDisk.FirstDriveFromMask(lpdv->dbcv_unitmask);
                if (gDisk.DriveType(z) == DRIVE_REMOVABLE)
				    gDisk(z);
			}
		}
	}
    };

    SEvent event(hWnd,msg,wParam,lParam);
    it = controls.begin();    
    while(it != controls.end())
    {
        l = (it++)->second->ProcessMessage(event);
        if (l == 0)
            return l;
    }

    return DefWindowProc(hWnd,msg,wParam,lParam);
}
//------
void CWindow::SetSize(int width, int height)
{
    w = width;
    h = height;
    if (hwnd)
        SetWindowPos(hwnd,0,0,0,w,h,SWP_NOREPOSITION | SWP_NOZORDER);
}
//------
bool CWindow::Show() const
{
    assert(hwnd != 0);
    ShowWindow(hwnd,SW_SHOW);

    return true;
}
//------
void CWindow::SetCaption(TCHAR *text)
{
    SetWindowText(this->hwnd,text);
}
//------
void CWindow::AddControl(UID c, IControl *control)
{
    assert(control != 0);
    controls[c.n] = control; control->AddToWindow(hwnd,hInst);
}
//------------------------
#include <windowsx.h>
// code snippet zapo¿yczony z jakiejœ strony :P
HBITMAP CreateBitmapMask(HBITMAP hbmColour, COLORREF crTransparent)
{
    HDC hdcMem, hdcMem2;
    HBITMAP hbmMask;
    BITMAP bm;

    // Create monochrome (1 bit) mask bitmap.  

    GetObject(hbmColour, sizeof(BITMAP), &bm);
    hbmMask = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

    // Get some HDCs that are compatible with the display driver

    hdcMem = CreateCompatibleDC(0);
    hdcMem2 = CreateCompatibleDC(0);

    SelectBitmap(hdcMem, hbmColour);
    SelectBitmap(hdcMem2, hbmMask);

    // Set the background colour of the colour image to the colour
    // you want to be transparent.
    SetBkColor(hdcMem, crTransparent);

    // Copy the bits from the colour image to the B+W mask... everything
    // with the background colour ends up white while everythig else ends up
    // black...Just what we wanted.

    BitBlt(hdcMem2, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

    // Take our new mask and use it to turn the transparent colour in our
    // original colour image to black so the transparency effect will
    // work right.
    BitBlt(hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem2, 0, 0, SRCINVERT);

    // Clean up.

    DeleteDC(hdcMem);
    DeleteDC(hdcMem2);

    return hbmMask;
}
