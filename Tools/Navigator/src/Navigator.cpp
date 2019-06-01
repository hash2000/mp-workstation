#include "wxconfig.h"

//#include "stdafx.h"
#include <wx/cmdline.h>
#include <wx/dir.h>

#include "../images/ex_merge.pngc"
#include "../images/box-open.pngc"

#include "Navigator.h"
#include "NavigatorRes.h"
#include "taskbar/TaskbarManager.h"
#include "log/sysLogger.h"
#include "view/MainFrm.h"



IMPLEMENT_APP(mpNavigator)


void mpNavigator::OnInitCmdLine(wxCmdLineParser& parser)
{
	static const wxCmdLineEntryDesc g_cmdLineDesc[] =
	{
		{ wxCMD_LINE_OPTION, "cp", "ContentPath", "select content path (default ./AddData)",
		    wxCMD_LINE_VAL_STRING, wxCMD_LINE_SWITCH_NEGATABLE },
		{ wxCMD_LINE_NONE }
	};
	parser.SetDesc(g_cmdLineDesc);
	parser.SetSwitchChars(wxT("-"));
}


bool mpNavigator::OnCmdLineParsed(wxCmdLineParser& parser)
{
	for (int i = 0, __end = parser.GetParamCount(); i < __end; i++) {
		auto param = parser.GetParam(i);
        if(param == wxT("ContentPath")) {
            _ContentPath = param;
            _ContentPath.Normalize();
        }
	}

	// auto arguments = parser.GetArguments();
	// for (auto i = arguments.begin(), __end = arguments.end(); i != __end; i++) {
	// 	auto param = i;
	// 	if (param->GetLongName() == wxT("ContentPath")) {
	// 		_ContentPath = param->GetStrVal();
	// 		_ContentPath.Normalize();
	// 	}
	// }

	return true;
}


/*
https://www.cse.iitb.ac.in/infolab/cep/downloads/pgadmin3/wxGTK-2.6.3/samples/console/console.cpp

static void TestDllListLoaded()
{
    wxPuts(_T("*** testing wxDynamicLibrary::ListLoaded() ***\n"));

    puts("\nLoaded modules:");
    wxDynamicLibraryDetailsArray dlls = wxDynamicLibrary::ListLoaded();
    const size_t count = dlls.GetCount();
    for ( size_t n = 0; n < count; ++n )
    {
        const wxDynamicLibraryDetails& details = dlls[n];
        printf("%-45s", details.GetPath().mb_str());

        void *addr;
        size_t len;
        if ( details.GetAddress(&addr, &len) )
        {
            printf(" %08lx:%08lx",
                   (unsigned long)addr, (unsigned long)((char *)addr + len));
        }

        printf(" %s\n", details.GetVersion().mb_str());
    }
}
*/


bool mpNavigator::OnInit()
{
	::wxInitAllImageHandlers();

	wxLog *seLog = new wxLogStderr();
	wxLog::SetActiveTarget(seLog);

	if (!wxApp::OnInit())
		return false;

	if (wxTaskBarIcon::IsAvailable())
	{
		// wxMessageBox
		// (
		// 	wxT("There appears to be no system tray support in your current environment. ")
		// 	wxT("This sample may not behave as expected."),
		// 	"Warning",
		// 	wxOK | wxICON_EXCLAMATION
		// );

		_TaskbarManager = new TaskbarManager;
		_TaskbarManager->SetIcon(*box_open_png_ico);

	}

	_MainFrame = new MainFrm(nullptr, wxT("Navigator"));
	if (!_MainFrame) {
		wxLogFatalError(wxT("Couldn't create the main window!"));
		return false;
	}

	_MainFrame->Show();
	SetTopWindow(_MainFrame);


// 	//sysLogger::logFile = settings->GetLogFile();
// 	//sysLogger::logLevel = settings->GetLogLevel();

	wxLog::SetVerbose(true);
	wxLog::SetActiveTarget(new sysLogger);
	wxLog::Resume();


	wxString msgAppVersion,
		msgAppContentPath;

	msgAppVersion << wxT("# ") << APP_NAME << wxT(" Version ") << APP_VERSION_STRING << wxT(" Startup");
	msgAppContentPath << wxT("# Content path: ") << _ContentPath.GetLongPath();

	wxLogInfo(wxT("####"));
	wxLogInfo(wxT("%s"), msgAppVersion.c_str());
	wxLogInfo(wxT("%s"), msgAppContentPath.c_str());
	wxLogInfo(wxT("####"));

#ifdef _DEBUG
	wxLogInfo(wxT("Running a DEBUG build."));
#else
	wxLogInfo(wxT("Running a RELEASE build."));
#endif



	return true;
}

void mpNavigator::CleanUp()
{
	wxApp::CleanUp();


}

int mpNavigator::OnExit()
{
	if (_TaskbarManager) {        
		_TaskbarManager->RemoveIcon();
	}

	return wxApp::OnExit();
}

void mpNavigator::DoExitApplication()
{
	if (wxMessageBox(wxT("Close application ?"), wxT("Close"), wxOK | wxCANCEL | wxCENTRE) == wxOK) {
		wxExit();
	}

}
