#ifndef __BASEVIEWNOTEBOOK_H__
#define __BASEVIEWNOTEBOOK_H__

#include <wx/notebook.h>

class BaseViewNotebook : public wxNotebook
{
	DECLARE_EVENT_TABLE()
public:
	BaseViewNotebook(wxWindow * parent, wxWindowID id = wxID_ANY,
		const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize,
		long style = 0);
	virtual ~BaseViewNotebook();

public:
	void OnMouseEvents(wxMouseEvent & event);

};



#endif