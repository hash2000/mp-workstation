#ifndef __BASEVIEWPANEL_H__
#define __BASEVIEWPANEL_H__

#include <wx/control.h>

#include "BaseViewNotebook.h"


class BaseViewPanel : public wxControl
{
	DECLARE_EVENT_TABLE()
public:


public:
	BaseViewPanel(wxWindow * parent, wxWindowID id = wxID_ANY,
		const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize,
		long style = 0);
	virtual ~BaseViewPanel();

	// void InsertBrowser(pgObject * obj);
	// void InsertActivateControl(pgObject * obj);

public:

private:
	BaseViewNotebook* _Notebook;
};




#endif