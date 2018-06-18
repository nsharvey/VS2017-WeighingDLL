// AdxGadgetContainer.cpp
// ----------------------
// project : Adonix X3 Centrale de Pesee
// author : EP		28/05/01
//--------------------------------------------------------------
//
// Declaration des classes decrivant les Gadget Container chez Adonix
//
#include "stdafx.h"
#include "AdxGadgetContainer.h"
#include "AdxInterface.h"
#include "AdxMessage.h"

void AdxGadgetContainer::init()
{
	this->_displayed = IlvFalse;
}
void AdxGadgetContainer::init(AdxInterface* m_interface)
{
	_interface = m_interface;
}

void AdxGadgetContainer::show()
{
	HWND hwndWindow;
	BOOL bRetour = false;
	

	hwndWindow = (HWND)getSystemView();
	// on show en maximized

//	IlvGadgetContainer::show();
	bRetour = ShowWindow(hwndWindow,SW_MAXIMIZE);
	this->_displayed = IlvTrue;
	this->reDraw();
}

void AdxGadgetContainer::hide()
{
	this->_displayed = IlvFalse;
	// Appel de la fonction de base
	IlvGadgetContainer::hide();
}
void AdxGadgetContainer::disableTitleBarButtons()
{
	HWND hwndWindow;
	
	hwndWindow = (HWND)getSystemView();
	// 19/04/2013 GBE On désactive la croix rouge dans la title bar
    HMENU hmenu= GetSystemMenu(hwndWindow,FALSE);
    DeleteMenu(hmenu,SC_CLOSE,MF_BYCOMMAND );
    LONG style = GetWindowLong(hwndWindow,GWL_STYLE);
    style ^= WS_SYSMENU;
    SetWindowLong(hwndWindow,GWL_STYLE,style);
}
IlvBoolean AdxGadgetContainer::IsDisplayed()
{
	return (this->_displayed);
}