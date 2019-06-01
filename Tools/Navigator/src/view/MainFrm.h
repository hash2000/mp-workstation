#ifndef __MAINFRM_H__
#define __MAINFRM_H__



#include <wx/aui/auibook.h>
#include <wx/aui/aui.h>
#include <wx/stc/stc.h>
#include <list>




class sysLogPanel;
class BaseViewPanel;
class AttributeControl;
class ConnectionsTree;

class MainFrm : public wxFrame
{
	DECLARE_EVENT_TABLE()
public:
	MainFrm(wxFrame *parent, const wxString &title,
		const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize,
		long flags = wxDEFAULT_FRAME_STYLE);
	virtual ~MainFrm();

public:

	void OnClose(wxCloseEvent& evt);
	void OnViewAttributes(wxCommandEvent& evt);
	void OnViewLogger(wxCommandEvent& evt);
	void OnViewConnections(wxCommandEvent& evt);
	void OnViewTopmost(wxCommandEvent& evt);
	void OnApplicationExit(wxCommandEvent& evt);
	void OnAuiPaneClose(wxAuiManagerEvent& evt);

public:
	void ToggleMenuPane(int menuId);
	void ToggleMenuCheck(const wxString & name);

	bool IsWindowTopmost() const;

private: 
	void LoadMenuBar();
	void LoadMenuView();
	void CheckMenuViews();

protected:
	wxAuiManager _Manager;
public:
	sysLogPanel * _LogPanel = nullptr;
	BaseViewPanel * _BaseViewPanel = nullptr;
	AttributeControl * _AttributePanel = nullptr;
	ConnectionsTree * _ConnectionsTree = nullptr;

private:
	wxMenu * _MenuFile = nullptr;
	wxMenu * _MenuView = nullptr;

	struct PaneHandler {
		PaneHandler() {
		}
		PaneHandler(const wxString & n, const wxString & t)
			: name(n)
			, title(t) {
		}
		wxString name;
		wxString title;
	};

	std::list<std::pair<int, PaneHandler>> _MenuView2Pane;
};

#endif