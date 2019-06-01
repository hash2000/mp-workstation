#ifndef __NAVIGATOR_H__
#define __NAVIGATOR_H__




class MainFrm;
class TaskbarManager;

class mpNavigator : public wxApp
{
public:
	virtual bool OnInit() override;
	virtual int OnExit() override;
	virtual void CleanUp() override;
	virtual void OnInitCmdLine(wxCmdLineParser& parser) override;
	virtual bool OnCmdLineParsed(wxCmdLineParser& parser) override;

	void DoExitApplication();
	
public:
	MainFrm * _MainFrame = nullptr;
	TaskbarManager * _TaskbarManager = nullptr;
	wxFileName _ContentPath;
};

DECLARE_APP(mpNavigator)



#endif