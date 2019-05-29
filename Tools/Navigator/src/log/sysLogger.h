#ifndef __SYSLOGGER_H__
#define __SYSLOGGER_H__



// App headers
#include "sysLoggerLevel.h"

// Class declarations
class sysLogger : public wxLog
{
public:
#if wxCHECK_VERSION(2, 9, 0)// wxWindows headers

	void DoLogTextAtLevel(wxLogLevel level, const wxString &msg);
#else
	virtual void DoLog(wxLogLevel level, const wxChar *msg, time_t timestamp);
#endif

	static wxLogLevel logLevel;
	static wxString logFile;

private:
	void WriteLog(const wxString &msg);
	bool SilenceMessage(const wxString &msg);
};

#define wxLOG_Notice (wxLOG_User+1)
#define wxLOG_Sql (wxLOG_User+2)
#define wxLOG_QuietError (wxLOG_User+3)
#define wxLOG_Script (wxLOG_User+4)
#define wxLOG_ScriptVerbose (wxLOG_User+5)

#if wxCHECK_VERSION(2, 9, 0)
	#define wxLogNotice wxDO_LOG(Notice)
	#define wxLogSql wxDO_LOG(Sql)
	#define wxLogQuietError wxDO_LOG(QuietError)
	#define wxLogScript wxDO_LOG(Script)
	#define wxLogScriptVerbose wxDO_LOG(ScriptVerbose)
#else
	#define DECLARE_INT_LOG_FUNCTION(level)                                  \
	extern void wxVLog##level(const wxChar *szFormat, va_list argptr);       \
	extern void wxLog##level(const wxChar *szFormat, ...)

	DECLARE_INT_LOG_FUNCTION(Notice);
	DECLARE_INT_LOG_FUNCTION(Sql);
	DECLARE_INT_LOG_FUNCTION(QuietError);
	DECLARE_INT_LOG_FUNCTION(Script);
	DECLARE_INT_LOG_FUNCTION(ScriptVerbose);
#endif



#endif // __SYSLOGGER_H__