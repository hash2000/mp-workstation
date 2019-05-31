#ifndef __SYSLOGPANEL_H__
#define __SYSLOGPANEL_H__


#include "view/BaseLogView.h"

#include <wx/notebook.h>
#include <list>
#include <memory>


class sysLogPanel : public wxControl
{
	DECLARE_DYNAMIC_CLASS(sysLogPanel)
	DECLARE_EVENT_TABLE()
public:
	sysLogPanel(wxWindow * parent, wxWindowID id = -1,
		const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize,
		long style = 0);
	sysLogPanel();
	virtual ~sysLogPanel();

	void DoLogMessage(const wxString & msg, int icon);

private:
	BaseLogView * AddLogView(BaseLogView * view);

private:
	wxNotebook * _Notebook;
	std::list<std::auto_ptr<BaseLogView>> _Views;
	BaseLogView * _ViewInfo = nullptr;
};


#endif