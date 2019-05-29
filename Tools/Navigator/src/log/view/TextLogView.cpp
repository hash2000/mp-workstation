#include "wxconfig.h"

#include "TextLogView.h"





TextLogView::TextLogView(const wxString & name, const wxString & title)
	: _Name(name)
	, _Title(title)
	, _Text(nullptr)
{
}


TextLogView::~TextLogView()
{
}

wxString TextLogView::GetName() const {
	return _Name;
}

wxString TextLogView::GetTitle() const {
	return _Title;
}

bool TextLogView::Create(wxWindow * parent)
{
	if (!_Text)
	{
		_Text = new wxTextCtrl(parent, wxID_ANY, wxEmptyString,
			wxDefaultPosition,
			wxDefaultSize,
			wxTE_READONLY | wxTE_MULTILINE
		);
	}

	return true;
}

void TextLogView::SendMessage(
	const wxString & type,
	const wxString & message)
{
	_Text->AppendText(message + wxT("\r\n"));
}

wxWindow * TextLogView::GetTargetView()
{
	return _Text;
}
