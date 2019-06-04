#include <stdafx.h>

#include "ListLogView.h"



ListLogView::ListLogView(const wxString & name, const wxString & title)
	: _Name(name)
	, _Title(title)
	, _List(nullptr)
{
}


ListLogView::~ListLogView()
{
}

wxString ListLogView::GetName() const {
	return _Name;
}

wxString ListLogView::GetTitle() const {
	return _Title;
}

bool ListLogView::Create(wxWindow * parent)
{

	if (!_List)
	{
		_List = new wxListCtrl(parent, wxID_ANY,
			wxDefaultPosition,
			wxDefaultSize,
			wxLC_REPORT
		);
		_List->InsertColumn(0, _("Message"), 0, 400);
		_List->InsertColumn(1, _("Type"));
	}

	return true;
}

void ListLogView::SendMessage(
	const wxString & type,
	const wxString & message)
{
	if (!_List)
		return;
	_List->Freeze();
	wxListItem item;
	item.SetId(_List->GetItemCount());
	item.SetText(message);
	item.SetColumn(0);
	_List->InsertItem(item);
	item.SetText(type);
	item.SetColumn(1);
	_List->SetItem(item);
	_List->Thaw();
}

wxWindow * ListLogView::GetTargetView()
{
	return _List;
}
