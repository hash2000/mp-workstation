#include "wxconfig.h"

#include "sysLogPanel.h"

#include "view/ListLogView.h"
#include "view/TextLogView.h"



#include <wx/log.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>

IMPLEMENT_DYNAMIC_CLASS(sysLogPanel, wxControl)

BEGIN_EVENT_TABLE(sysLogPanel, wxControl)
END_EVENT_TABLE()


sysLogPanel::sysLogPanel(wxWindow * parent, wxWindowID id,
	const wxPoint &pos,
	const wxSize &size,
	long style)
	: wxControl(parent, id, pos, size, style)
{
	_Notebook = new wxNotebook(this, wxID_ANY);

	_ViewInfo = AddLogView(new TextLogView(wxT("log/info"), _("Info")));

	auto sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(_Notebook, 1, wxEXPAND);
	SetSizerAndFit(sizer);

	//auto control = static_cast<MultiLogControl*>(wxLog::GetActiveTarget());
	//control->SetLogTarget(this);
}

sysLogPanel::sysLogPanel()
{

}

sysLogPanel::~sysLogPanel()
{
}

BaseLogView * sysLogPanel::AddLogView(BaseLogView * view)
{
	if (!view)
		return nullptr;
	auto page = new wxPanel(_Notebook);
	if (!view->Create(page))
		return nullptr;
	auto target = view->GetTargetView();
	if (target != nullptr)
	{
		auto sizer = new wxBoxSizer(wxVERTICAL);
		sizer->Add(target, 1, wxEXPAND);
		page->SetSizer(sizer);
	}
	_Notebook->AddPage(page, view->GetTitle());
	return view;
}

void sysLogPanel::DoLogMessage(const wxString & msg, int icon)
{
	_ViewInfo->SendMessage(_("Info"), msg);
}