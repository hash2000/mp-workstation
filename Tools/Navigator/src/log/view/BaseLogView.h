#ifndef __BASELOGVIEW_H__
#define __BASELOGVIEW_H__


#include <string>
#include <wx/window.h>


class BaseLogView
{
public:
	virtual ~BaseLogView() {
	}
	virtual void SendMessage(
		const wxString & type,
		const wxString & message) = 0;
	virtual wxWindow * GetTargetView() = 0;
	virtual bool Create(wxWindow * parent) = 0;
	virtual wxString GetName() const = 0;
	virtual wxString GetTitle() const = 0;
};


#endif