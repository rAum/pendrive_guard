/// Pendrive Guard - prosty program przeciwko wirusom/robakom itp
/// przenosz¹cymi siê przy pomocy noœników wymiennych
/// Autor: Piotr "rAum" Gródek 2009
///-----------------------------------------------------
// http://www.md5hashing.com/c++/
#include "pch.h"

#include "CWindow.h"
#include "CButton.h"
#include "CRegedit.h"
#include "CScanner.h"
#include "CLogger.h"
#include "CFlatButton.h"
#include "CRadioButton.h"
#include "CFileManager.h"
#include "Dialogs.h"
#include "CPicture.h"

LRESULT CALLBACK Quit(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_COMMAND)
        SendMessage(hWnd,WM_DESTROY,0,0);
    return TRUE;
}
LRESULT CALLBACK ScanAll(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_COMMAND)
        ScanDialog();
    return TRUE;
}

LRESULT CALLBACK AddProtection(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_COMMAND){
		if (MessageBox(0,TEXT("Czy chcesz dodaæ prost¹ ochronê przeciwko wirusom na wszystkie dyski?"),TEXT("Pytanie"),MB_YESNO | MB_ICONQUESTION)
			== IDYES)
			gFileManager.AddEasyProtForAll();
	}
	return TRUE;
}

LRESULT CALLBACK ToggleAutorun(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_COMMAND)
		gRegedit.AddAutoRun(!gRegedit.CheckAutoRun());

	return TRUE;
}

LRESULT CALLBACK ToggleWSH(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_COMMAND)
	{
		switch (gRegedit.CheckWSH())
		{
		case true:
			if (MessageBox(0,TEXT("Czy chcesz wy³¹czyæ obs³ugê skryptów Windows Script Host(zalecane)?\nZnacz¹co zwiêkszy to bezpieczeñstwo, a nie s¹ one czêsto wykorzystywane"),
				TEXT("Pytanie"),MB_YESNO | MB_ICONQUESTION) == IDNO)
				return TRUE;

			if (!gRegedit.SetWSH(false))
				MessageBox(0,TEXT("Nie uda³o siê wy³¹czyæ Windows Script Host.\n"),0,MB_OK | MB_ICONERROR);
			
			break;
		case false:
			if (MessageBox(0,TEXT("Czy na pewno chcesz w³¹czyæ obs³ugê skryptów? Jest to niezalecane."),TEXT("Pytanie"), MB_YESNO | MB_ICONQUESTION)
				== IDNO)
				return TRUE;
			
			if(!gRegedit.SetWSH(true))
				MessageBox(0,TEXT("Nie uda³o siê w³¹czyæ Windows Script Host.\nAplikacja mo¿e nie byæ zainstalowana w systemie."),0,MB_OK | MB_ICONERROR);
		}
	}

	SendMessage(hWnd,BM_SETCHECK,!gRegedit.CheckWSH(),0);
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE,LPSTR cmd,int)
{
    // dla œwiêtego spokoju :P :
    InitCommonControls();

    CWindow wnd;
    wnd.Create(hInstance);

    CButton bQuit, bScanAll, bAddProt;
  
    bScanAll.SetName(TEXT("Skanuj dyski"));
    bScanAll.SetEventFunc(ScanAll);
    bScanAll.SetSize(190,20);
    bScanAll.SetPos(100,10);

	bAddProt.SetName(TEXT("Dodaj ochronê"));
	bAddProt.SetEventFunc(AddProtection);
	bAddProt.SetSize(190,20);
	bAddProt.SetPos(100,30);
	
	CCheckBox cbAutorun;
	cbAutorun.SetName(TEXT("Autouruchamianie"));
	cbAutorun.SetEventFunc(ToggleAutorun);
	cbAutorun.SetPos(100,50);
	cbAutorun.SetSize(190,20);

	CCheckBox cbWSH;
	cbWSH.SetName(TEXT("Ochrona przed skryptami"));
	cbWSH.SetPos(100,70);
	cbWSH.SetSize(190,20);
	cbWSH.SetEventFunc(ToggleWSH);

    bQuit.SetName(TEXT("Zamknij"));
    bQuit.SetPos(100,95);
    bQuit.SetSize(190,20);
    bQuit.SetEventFunc(Quit);

    wnd.AddControl(GenID("bScanAll"),&bScanAll);
	wnd.AddControl(GenID("bAddProt"),&bAddProt);
    wnd.AddControl(GenID("bQuit"),&bQuit);
	wnd.AddControl(GenID("cbAuto"),&cbAutorun);
	wnd.AddControl(GenID("cbWSH"), &cbWSH);
    

	cbAutorun.SetState(gRegedit.CheckAutoRun());
	cbWSH.SetState(!gRegedit.CheckWSH());

	if (strcmp("/tray",cmd) == 0)
		SendMessage(wnd.GetHandle(),WM_CLOSE,0,0);
	else
		wnd.Show();

    wnd.DoLoop();    

    return 0;
    // UID f;
    //f = CreateUID(SID("test"));
    //fprintf(stderr,"%s odpowiada %ull\n", f.txt, f.n);
    //MessageBoxA(0,ToString(f.n).c_str() ,(char *)f.txt,MB_OK);

    //f = CreateUID(SID(""));
    //MessageBoxA(0,ToString(f.n).c_str() ,(char *)f.txt,MB_OK);

    //f = CreateUID(SID("12345678"));
    //MessageBoxA(0,ToString(f.n).c_str() ,(char *)f.txt,MB_OK);
}
