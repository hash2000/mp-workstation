#include <stdafx.h>

#include <wx/menu.h>


#include "MainFrm.h"
#include "MainFrmRes.h"
#include "../Navigator.h"

#include "panel/BaseViewPanel.h"

#include "../taskbar/TaskbarManagerRes.h"
#include "../log/sysLogPanel.h"



BEGIN_EVENT_TABLE(MainFrm, wxFrame)
/*{ Begin }*/
    EVT_CLOSE(MainFrm::OnClose)
    EVT_MENU(MENU_VIEW_ATTRIBUTES, MainFrm::OnViewAttributes)
    EVT_MENU(MENU_VIEW_LOGGER, MainFrm::OnViewLogger)
    EVT_MENU(MENU_VIEW_CONNECTIONS, MainFrm::OnViewConnections)
    EVT_MENU(MENU_VIEW_TOPMOST, MainFrm::OnViewTopmost)
    EVT_MENU(MENU_APPLICATION_EXIT, MainFrm::OnApplicationExit)
    EVT_AUI_PANE_CLOSE(MainFrm::OnAuiPaneClose)
/*{ End }*/
END_EVENT_TABLE()




MainFrm::MainFrm(wxFrame *parent, const wxString &title,
	const wxPoint &pos, const wxSize &size, long flags)
	: wxFrame(parent, -1, title, pos, size, flags)
{
	SetSize(wxSize(800, 600));

	_Manager.SetManagedWindow(this);
	_Manager.SetFlags(wxAUI_MGR_DEFAULT | wxAUI_MGR_TRANSPARENT_DRAG |
		wxAUI_MGR_ALLOW_ACTIVE_PANE);


	_LogPanel = new sysLogPanel(this, CTL_LOGPANE,
	 	wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);

	// // панель атрибутов должна быть загружена раньше чем панель навигации, 
	// //	потому что она используется при выборе объекта в дереве объектов
	// _AttributePanel = new AttributeControl(this);

	// _Manager.AddPane(_AttributePanel, wxAuiPaneInfo()
	// 	.Name(wxT("attributePane"))
	// 	.Caption(_("Attributes"))
	// 	.Bottom()
	// 	.MaximizeButton()
	// 	.MinimizeButton()
	// 	.MinSize(wxSize(100, 100))
	// 	.BestSize(wxSize(400, 200))
	// );

	_BaseViewPanel = new BaseViewPanel(this);

	_Manager.AddPane(_BaseViewPanel, wxAuiPaneInfo()
		.Name(wxT("objectBrowser"))
		.Caption(_("Object browser"))
		.Center()
		.CaptionVisible(false)
		.CloseButton(false)
		.MinSize(wxSize(100, 100))
		.BestSize(wxSize(800, 600))
	);

	// _ConnectionsTree = new ConnectionsTree(this, CTL_CONNECTIONS);

	// _Manager.AddPane(_ConnectionsTree, wxAuiPaneInfo()
	// 	.Name(wxT("connectionsPane"))
	// 	.Caption(_("Connections"))
	// 	.Bottom()
	// 	.MaximizeButton()
	// 	.MinimizeButton()
	// 	.MinSize(wxSize(100, 100))
	// 	.BestSize(wxSize(400, 200))
	// );


	_Manager.AddPane(_LogPanel, wxAuiPaneInfo()
		.Name(wxT("logPane"))
		.Caption(_("Log pane"))
		.Bottom()
		.MaximizeButton()
		.MinimizeButton()
		.MinSize(wxSize(100, 100))
		.BestSize(wxSize(400, 200))
	);

	_Manager.Update();

	LoadMenuBar();
}

MainFrm::~MainFrm()
{
	_Manager.UnInit();

}

void MainFrm::LoadMenuBar()
{
	auto menuBar = new wxMenuBar;
	auto _MenuFile = new wxMenu;
	menuBar->Append(_MenuFile, wxT("File"));

	_MenuFile->Append(MENU_APPLICATION_EXIT, wxT("Exit"));

	LoadMenuView();
	menuBar->Append(_MenuView, wxT("View"));


	SetMenuBar(menuBar);
}
void MainFrm::OnApplicationExit(wxCommandEvent& evt)
{
	wxGetApp().DoExitApplication();
}

void MainFrm::LoadMenuView() 
{
	_MenuView = new wxMenu;
	_MenuView2Pane.push_back(std::make_pair(MENU_VIEW_ATTRIBUTES, PaneHandler(wxT("attributePane"), wxT("Attributes"))));
	_MenuView2Pane.push_back(std::make_pair(MENU_VIEW_LOGGER, PaneHandler(wxT("logPane"), wxT("Logger"))));
	_MenuView2Pane.push_back(std::make_pair(MENU_VIEW_CONNECTIONS, PaneHandler(wxT("connectionsPane"), wxT("Connections"))));
	
	for (auto i : _MenuView2Pane) {
		_MenuView->Append(i.first, i.second.title, wxEmptyString, true);
	}

	_MenuView->AppendSeparator();
	_MenuView->Append(MENU_VIEW_TOPMOST, wxT("Topmost"), wxEmptyString, true);

	CheckMenuViews();

}

void MainFrm::CheckMenuViews()
{
	for (auto i : _MenuView2Pane) {
		_MenuView->Check(i.first, _Manager.GetPane(i.second.name).IsShown());
	}
}

void MainFrm::OnClose(wxCloseEvent& evt)
{
	if(wxGetApp()._TaskbarManager != nullptr) {
		Hide();
	}
	else {
		wxGetApp().DoExitApplication();
	}
	evt.Veto();
}

void MainFrm::ToggleMenuPane(int menuId)
{
	std::list<std::pair<int, PaneHandler>>::iterator i = _MenuView2Pane.begin(),
		_end = _MenuView2Pane.end();
	for (; i != _end; i++) {
		if (i->first == menuId)
			break;
	}

	if (i == _end)
		return;

	if (_MenuView->IsChecked(i->first))
		_Manager.GetPane(i->second.name).Show(true);
	else
		_Manager.GetPane(i->second.name).Show(false);
	_Manager.Update();
}

void MainFrm::ToggleMenuCheck(const wxString & name)
{
	std::list<std::pair<int, PaneHandler>>::iterator i = _MenuView2Pane.begin(),
		_end = _MenuView2Pane.end();
	for (; i != _end; i++) {
		if (i->second.name == name)
			break;
	}

	if (i == _end)
		return;

	_MenuView->Check(i->first, !_Manager.GetPane(i->second.name).IsShown());
}

void MainFrm::OnViewAttributes(wxCommandEvent& evt)
{
	ToggleMenuPane(MENU_VIEW_ATTRIBUTES);
}

void MainFrm::OnViewLogger(wxCommandEvent& evt)
{
	ToggleMenuPane(MENU_VIEW_LOGGER);
}

void MainFrm::OnViewConnections(wxCommandEvent& evt)
{
	ToggleMenuPane(MENU_VIEW_CONNECTIONS);
}

void MainFrm::OnAuiPaneClose(wxAuiManagerEvent& evt)
{
	ToggleMenuCheck(evt.GetPane()->name);
}

bool MainFrm::IsWindowTopmost() const {
	return (GetWindowStyle() & wxSTAY_ON_TOP) == wxSTAY_ON_TOP;
}

void MainFrm::OnViewTopmost(wxCommandEvent& evt)
{
	auto style = GetWindowStyle();
	if((style & wxSTAY_ON_TOP) != wxSTAY_ON_TOP) {
		style |= wxSTAY_ON_TOP;
	}
	else {
		style &= ~wxSTAY_ON_TOP;
	}

	SetWindowStyle(style);

	_MenuView->Check(MENU_VIEW_TOPMOST, IsWindowTopmost());
}