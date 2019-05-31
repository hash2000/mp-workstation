#include "wxconfig.h"
#include "BaseViewNotebook.h"


BEGIN_EVENT_TABLE(BaseViewNotebook, wxNotebook)
/*{ Begin }*/
    EVT_MOUSE_EVENTS(BaseViewNotebook::OnMouseEvents)
/*{ End }*/
END_EVENT_TABLE()



BaseViewNotebook::BaseViewNotebook(wxWindow * parent, wxWindowID id,
	const wxPoint &pos, const wxSize &size, long style)
	: wxNotebook(parent, id, pos, size, style)
{
}

BaseViewNotebook::~BaseViewNotebook()
{
}

void BaseViewNotebook::OnMouseEvents(wxMouseEvent & event)
{
	const auto & pos = event.GetPosition();
	event.Skip();

	if (event.MiddleUp())
	{
		int pageId = HitTest(pos);
		RemovePage(pageId);
	}
}