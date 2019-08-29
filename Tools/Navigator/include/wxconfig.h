#ifndef __WXCONFIG_H__
#define __WXCONFIG_H__


#define wxUSE_TASKBARICON 1
#define wxUSE_UNICODE 1
// #define WXUSINGDLL 
// #define WX_PRECOMP 
// #define __WXGTK__

#include <wx/wxprec.h>

#if !defined(WX_PRECOMP)
    #include <wx/wx.h>
    #include <wx/intl.h>
    #include <wx/laywin.h>
    #include <wx/image.h>
    #include <wx/filename.h>
    #include <wx/hashmap.h>
    // recent files history
    #include <wx/docview.h> 
#endif

#include <wx/hashmap.h>
#include <wx/colordlg.h>
#include <wx/listctrl.h>
#include <wx/xrc/xmlres.h>
#include <wx/taskbar.h>
#include <wx/splash.h>
#include <wx/snglinst.h>
#include <wx/image.h>
#include <wx/mdi.h>
#include <wx/stdpaths.h>
#include <wx/xrc/xmlres.h>

#endif // !__WXCONFIG_H__

