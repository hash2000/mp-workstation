#include <stdafx.h>

#include "BaseViewPanel.h"

#include <wx/sizer.h>


BEGIN_EVENT_TABLE(BaseViewPanel, wxControl)
/*{ Begin }*/

/*{ End }*/
END_EVENT_TABLE()



BaseViewPanel::BaseViewPanel(wxWindow * parent, wxWindowID id,
	const wxPoint &pos, const wxSize &size, long style)
	: wxControl(parent, id, pos, size, style)
{
	_Notebook = new BaseViewNotebook(this);
	auto sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(_Notebook, 1, wxEXPAND);
	SetSizerAndFit(sizer);
}

BaseViewPanel::~BaseViewPanel()
{
}

// void CenterControl::InsertBrowser(pgObject * obj)
// {

// 	wxColour clrBkGround = wxSystemSettings::GetColour(
// 		wxSYS_COLOUR_BTNFACE);

// 	auto browser = new BrowserTree(_Notebook, wxID_ANY);
// 	browser->SetBackgroundColour(clrBkGround);
// 	obj->PopulateBrowserNode(browser, nullptr);

// 	_Notebook->AddPage(browser, obj->GetName());
// }

// void CenterControl::InsertActivateControl(pgObject * obj)
// {
// 	if (!obj)
// 		return;

// 	auto actionResult = obj->Activate(_Notebook);
// 	if (!actionResult)
// 		return;

// 	_Notebook->AddPage(actionResult, obj->GetName());	
// }