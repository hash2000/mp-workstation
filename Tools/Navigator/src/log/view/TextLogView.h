#ifndef __TEXTLOGVIEW_H__
#define __TEXTLOGVIEW_H__

#include <wx/textctrl.h>

#include "BaseLogView.h"


class TextLogView : public BaseLogView
{
public:
	TextLogView(const wxString & name, const wxString & title);
	virtual ~TextLogView();

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
	wxTextCtrl * _Text;
};

#endif