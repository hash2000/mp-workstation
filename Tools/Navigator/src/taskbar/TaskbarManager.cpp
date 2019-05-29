#include "wxconfig.h"

#include "TaskbarManager.h"
#include "../Navigator.h"


wxBEGIN_EVENT_TABLE(TaskbarManager, wxTaskBarIcon)
	EVT_MENU(PU_RESTORE, TaskbarManager::OnMenuRestore)
	EVT_MENU(PU_EXIT, TaskbarManager::OnMenuExit)
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
	// auto mfrm = wxGetApp()._MainFrame;
	// if (mfrm->IsVisible()) {
	// 	mfrm->Hide();
	// }
	// else {
	// 	mfrm->Show();
	// }
}

void TaskbarManager::OnMenuExit(wxCommandEvent&)
{
	if (wxMessageBox(wxT("Close application ?"), wxT("Close"), wxOK | wxCANCEL | wxCENTRE) == wxOK) {
		wxExit();
	}
}

// Overridables
wxMenu *TaskbarManager::CreatePopupMenu()
{
	wxMenu *menu = new wxMenu;
	menu->Append(PU_RESTORE, "&Restore");
	menu->AppendSeparator();
	menu->Append(PU_EXIT, "E&xit");
	return menu;
}


