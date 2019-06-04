#include <stdafx.h>

#include "TaskbarManager.h"
#include "../Navigator.h"
#include "../view/MainFrm.h"


wxBEGIN_EVENT_TABLE(TaskbarManager, wxTaskBarIcon)
	EVT_MENU(MENU_APPLICATION_RESTORE, TaskbarManager::OnMenuRestore)
	EVT_MENU(MENU_APPLICATION_EXIT, TaskbarManager::OnMenuExit)
	EVT_TASKBAR_LEFT_DCLICK(TaskbarManager::OnLeftButtonDClick)
wxEND_EVENT_TABLE()

void TaskbarManager::OnMenuRestore(wxCommandEvent&)
{
	CheckOrRestoreMainForm();
}

void TaskbarManager::OnLeftButtonDClick(wxTaskBarIconEvent&)
{
	CheckOrRestoreMainForm();
}

void TaskbarManager::CheckOrRestoreMainForm()
{
	auto mfrm = wxGetApp()._MainFrame;
	if (mfrm->IsVisible()) {
		mfrm->Hide();
	}
	else {
		mfrm->Show();
	}
}

void TaskbarManager::OnMenuExit(wxCommandEvent&)
{
	wxGetApp().DoExitApplication();
}

// Overridables
wxMenu *TaskbarManager::CreatePopupMenu()
{
	wxMenu *menu = new wxMenu;
	menu->Append(MENU_APPLICATION_RESTORE, "&Restore");
	menu->AppendSeparator();
	menu->Append(MENU_APPLICATION_EXIT, "E&xit");
	return menu;
}


