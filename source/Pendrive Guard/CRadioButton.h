#pragma once
#include "IControl.h"

class CRadioButton : public IControl
{
    virtual void AddToWindow(HWND owner, HINSTANCE hInstance)
    {
        hControl = CreateWindowEx(0,TEXT("button"), text, style, posx,posy,w,h, owner, (HMENU) id, hInstance, NULL);
    }
    DWORD style;
public:
    CRadioButton() : style(WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_TABSTOP ) {}
    virtual LRESULT Event(const SEvent &event)
    {
        switch(event.msg)
        {
        case WM_COMMAND:
            MessageBox(0,TEXT("WM_COMMAND"), text,MB_OK);
            return FALSE;
        };
        return TRUE;
    }
    void StartingGroup(bool starts=true)
    {
        if (hControl)
        {
            style = GetWindowLong(hControl,GWL_STYLE);
            style |= starts? WS_GROUP : ~WS_GROUP;
            SetWindowLong(hControl,GWL_STYLE,style);
        }
        else
            style |= starts? WS_GROUP : ~WS_GROUP;
    }
	void SetState(bool state)
	{
		if (hControl)
			SendMessage(hControl,BM_SETCHECK,state? BST_CHECKED : BST_UNCHECKED,0);
	}
};
//-------------------------
class CCheckBox : public IControl
{
    virtual void AddToWindow(HWND owner, HINSTANCE hInstance)
    {
        hControl = CreateWindowEx(0,TEXT("button"), text, style, posx,posy,w,h, owner, (HMENU) id, hInstance, NULL);
    }
    DWORD style;
public:
	CCheckBox() : style(WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_TABSTOP ) {}
    virtual LRESULT Event(const SEvent &event)
    {
        switch(event.msg)
        {
        case WM_COMMAND:
            MessageBox(0,TEXT("WM_COMMAND"), text,MB_OK);
            return FALSE;
        };
        return TRUE;
    }
    void StartingGroup(bool starts=true)
    {
        if (hControl)
        {
            style = GetWindowLong(hControl,GWL_STYLE);
            style |= starts? WS_GROUP : ~WS_GROUP;
            SetWindowLong(hControl,GWL_STYLE,style);
        }
        else
            style |= starts? WS_GROUP : ~WS_GROUP;
    }
	void SetState(bool state)
	{
		if (hControl)
			SendMessage(hControl,BM_SETCHECK,state? BST_CHECKED : BST_UNCHECKED,0);
	}
};
