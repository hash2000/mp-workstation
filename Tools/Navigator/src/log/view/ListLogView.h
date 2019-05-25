#ifndef __LISTLOGVIEW_H__
#define __LISTLOGVIEW_H__


#include <wx/listctrl.h>

#include "BaseLogView.h"

class ListLogView : public BaseLogView
{
public:
	ListLogView(const wxString & name, const wxString & title);
	virtual ~ListLogView();

	void SendMessage(
		const wxString & type,
		const wxString & message) override;
	wxWindow * GetTargetView() override;
	bool Create(wxWindow * parent) override;
	wxString GetName() const override;
	wxString GetTitle() const override;

private:
	wxString _Name;
	wxString _Title;
	wxListCtrl * _List;
};

#endif