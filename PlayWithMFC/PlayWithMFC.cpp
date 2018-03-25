
// PlayWithMFC.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PlayWithMFC.h"
#include "PlayWithMFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlayWithMFCApp

BEGIN_MESSAGE_MAP(CPlayWithMFCApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPlayWithMFCApp construction

CPlayWithMFCApp::CPlayWithMFCApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CPlayWithMFCApp object

CPlayWithMFCApp theApp;


// CPlayWithMFCApp initialization

BOOL CPlayWithMFCApp::InitInstance()
{
#ifdef _DEBUG
    if (!AllocConsole())
    {
        // AfxMessageBox(L"Console doesn't work.", MB_ICONERROR);
    }
#endif

	CWinApp::InitInstance();

	CPlayWithMFCDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CPlayWithMFCApp::ExitInstance()
{
#ifdef _DEBUG
    if (!FreeConsole())
    {
        // AfxMessageBox(L"Fail FreeConsole", MB_ICONERROR);
    }
#endif
    return CWinApp::ExitInstance();
}

