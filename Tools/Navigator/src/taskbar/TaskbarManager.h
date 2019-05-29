#ifndef __TASKBARMANAGER_H__
#define __TASKBARMANAGER_H__


#include "TaskbarManagerRes.h"


#include <wx/taskbar.h>
#include <wx/menu.h>



class TaskbarManager : public wxTaskBarIcon
{
	wxDECLARE_EVENT_TABLE();
public:
	TaskbarManager(wxTaskBarIconType iconType = wxTBI_DEFAULT_TYPE)
		: wxTaskBarIcon(iconType) {
	}

	void OnLeftButtonDClick(wxTaskBarIconEvent& evt);
	void OnMenuRestore(wxCommandEvent& evt);
	void OnMenuExit(wxCommandEvent& evt);

private:

	void CheckOrRestoreMainForm();

public:
	virtual wxMenu *CreatePopupMenu() override;
};


#endif