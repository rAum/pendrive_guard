#include "Dialogs.h"
#include "resource.h"
#include "CWindow.h"
#include "CScanner.h"

#include <commctrl.h>

const TCHAR *virus_name = 0;

BOOL CALLBACK VirusActionProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch(Msg)
    {
    case WM_INITDIALOG:
        SetDlgItemText(hwnd,IDC_VIRUSNAME,virus_name);
        break;
    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case IDC_DELETE:
            EndDialog(hwnd,IDC_DELETE); break;
        case IDC_ADDEXCEPTION:
            EndDialog(hwnd,IDC_ADDEXCEPTION); break;
        case IDC_NOACTION:
            EndDialog(hwnd,IDC_NOACTION); break;
        }
        break;
    case WM_CLOSE:
        EndDialog(hwnd,IDC_NOACTION);
        break;
    default:
            return FALSE;
    }
    return TRUE;
}

int VirusActionDialog(const TCHAR *virus)
{
    virus_name = virus;
    return DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_VIRUSFOUND), CWindow::GetSingleton().GetHandle(), VirusActionProc);
}

HWND hDialog;
void ShowProgress(unsigned i)
{
    SendMessage(GetDlgItem(hDialog,IDC_SCANPROGRESS),PBM_SETPOS,i,0);
}

DWORD WINAPI ScanThread(PVOID dialogHWND)
{
    HWND hwnd = *reinterpret_cast<HWND *>(dialogHWND);
    unsigned percent = 0;

    SetDlgItemText(hwnd,IDC_TEXT3,TEXT("Trwa skanowanie, proszê czekaæ..."));

    gScanner.Scan('\0',ShowProgress);

    SetDlgItemText(hwnd,IDC_TEXT3,TEXT("Skanowanie zakoñczone."));

    SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(666,0),0);

    return 0;
}
//-----------------------------------
BOOL CALLBACK ScanDialogProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    static bool scanning    = false;
    static bool suspend     = false;
    static HANDLE hThread   = 0;
    static DWORD idThread   = 0;
    static DWORD threadStatus;

    switch(Msg)
    {
    case WM_INITDIALOG:        
        SendDlgItemMessage(hwnd,IDC_SCANPROGRESS,PBM_SETPOS,(WPARAM)0,0);
        hDialog = hwnd;
        break;
    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case 333:
            SendMessage(GetDlgItem(hwnd,IDC_SCANPROGRESS),PBM_SETPOS,HIWORD(wParam),0);
            break;
        case 666:
            scanning = false;
            SetDlgItemText(hwnd,IDOK,TEXT("Skanuj"));
            break;
        case IDOK:
            if (scanning == false)
            {
                hThread = CreateThread(NULL,0,ScanThread,&hwnd,0,&idThread);                
                SetDlgItemText(hwnd,IDOK,TEXT("Pauza"));
                scanning = true;
            }
            else
            {
                GetExitCodeThread(hThread,&threadStatus);
                if (threadStatus == STILL_ACTIVE)
                {
                    suspend = !suspend;
                    if (suspend)
                    {
                        SuspendThread(hThread);
                        SetDlgItemText(hwnd,IDOK,TEXT("Wznów"));
                    }
                    else
                    {
                        ResumeThread(hThread);
                        SetDlgItemText(hwnd,IDOK,TEXT("Pauza"));
                    }
                }
            }
            break;
        case IDCANCEL:
            if (!scanning)
                EndDialog(hwnd,0);
            break;
        }
        break;
    case WM_CLOSE:
        if (!scanning)
            EndDialog(hwnd,0);
        break;
    default:
        return FALSE;
    }
    return TRUE;
}

int ScanDialog()
{
    return DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SCANDIALOG),CWindow::GetSingleton().GetHandle(), ScanDialogProc);
}
