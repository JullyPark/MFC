
// PlayWithMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PlayWithMFC.h"
#include "PlayWithMFCDlg.h"
#include "afxdialogex.h"
#include <conio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMER_EVT_GAME_PROG		1
#define END_OF_PROG             59

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPlayWithMFCDlg dialog



CPlayWithMFCDlg::CPlayWithMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PLAYWITHMFC_DIALOG, pParent), m_bGameProceeding(false), m_currentQuest(-1), m_cntQuestion(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    memset(m_lstQnA, sizeof(m_lstQnA), 0);
}

void CPlayWithMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPlayWithMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BTN, &CPlayWithMFCDlg::OnBnClickedStartBtn)
	ON_WM_TIMER()
    ON_BN_CLICKED(IDC_ANS2_BTN, &CPlayWithMFCDlg::OnBnClickedAns2Btn)
    ON_BN_CLICKED(IDC_ANS3_BTN, &CPlayWithMFCDlg::OnBnClickedAns3Btn)
	ON_BN_CLICKED(IDC_ANS1_BTN, &CPlayWithMFCDlg::OnBnClickedAns1Btn)
    ON_BN_CLICKED(IDOK, &CPlayWithMFCDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPlayWithMFCDlg message handlers

BOOL CPlayWithMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

    SetWindowText(L"위기의 커플");

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

    InitializeUI();
    ReadQnAFile();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPlayWithMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPlayWithMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPlayWithMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPlayWithMFCDlg::OnBnClickedStartBtn()
{
	if (false == m_bGameProceeding)
	{
        SetTimer(1, 500, NULL);
        m_bGameProceeding = true;
        ShowNextQuestion();
	}
	else
	{
	}
}


void CPlayWithMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case TIMER_EVT_GAME_PROG:
	{
		CProgressCtrl *pProgCtrl = (CProgressCtrl *)GetDlgItem(IDC_TIME_PROG);
		if (pProgCtrl && m_bGameProceeding)
		{
            pProgCtrl->SetPos(pProgCtrl->GetPos() + 1);
            if (END_OF_PROG <= pProgCtrl->GetPos())
            {
                KillTimer(TIMER_EVT_GAME_PROG);
                FinishGame();
            }
		}
		break;
	}
	default:
		break;
	}

    CDialogEx::OnTimer(nIDEvent);
}


int CPlayWithMFCDlg::ReadQnAFile()
{
    CStdioFile file;
    wchar_t *pFilePath = L"..\\Question.txt";
    if(file.Open(pFilePath, CFile::modeRead | CFile::typeUnicode))
    {
#ifdef _DEBUG
        _cprintf("File Open");
        _cwprintf(pFilePath);
#endif 
        int     i = 0;
        wchar_t strQuestionLine[200];
        while (i < QUESTION_MAX_COUNT && file.ReadString(strQuestionLine, 200))
        {
            wcscpy_s(m_lstQnA[i].strQuestion, strQuestionLine);

            // Read answer                                        
            int j = 0;
            file.ReadString(m_lstQnA[i].strArrOption[j++], OPTION_STR_SIZE);
            file.ReadString(m_lstQnA[i].strArrOption[j++], OPTION_STR_SIZE);
            file.ReadString(m_lstQnA[i].strArrOption[j++], OPTION_STR_SIZE);

            wchar_t strAnswer[10];
            file.ReadString(strAnswer, 10);
            m_lstQnA[i].nAnswer = _wtoi(strAnswer);
#ifdef _DEBUG
            /*_cwprintf(m_lstQnA[i].strQuestion);
            _cwprintf(m_lstQnA[i].strArrOption[0]);
            _cwprintf(m_lstQnA[i].strArrOption[1]);
            _cwprintf(m_lstQnA[i].strArrOption[2]);
            _cprintf("%d", m_lstQnA[i].nAnswer);*/
#endif 
            
            i++;
        }

        m_cntQuestion = i;

#ifdef _DEBUG
#endif

        file.Close();
    }
    else
    {
#ifdef _DEBUG
        _cprintf("File Open fail");
#endif
    }
    return 1;
}

void CPlayWithMFCDlg::ShowNextQuestion()
{
    if (++m_currentQuest < m_cntQuestion)
    {
        SetDlgItemTextW(IDC_QUESTION_EDIT, m_lstQnA[m_currentQuest].strQuestion);
        SetDlgItemTextW(IDC_ANS1_BTN, m_lstQnA[m_currentQuest].strArrOption[0]);
        SetDlgItemTextW(IDC_ANS2_BTN, m_lstQnA[m_currentQuest].strArrOption[1]);
        SetDlgItemTextW(IDC_ANS3_BTN, m_lstQnA[m_currentQuest].strArrOption[2]);
    }
    else
    {
        FinishGame();
    }
}

void CPlayWithMFCDlg::OnOptionClicked(int nOpt)
{
    if (!m_bGameProceeding)
        return;

    if (nOpt == m_lstQnA[m_currentQuest].nAnswer)
    {
        SetDlgItemTextW(IDC_TEST_EDIT, L"정답!!");
    }
    else
    {
        SetDlgItemTextW(IDC_TEST_EDIT, L"오답..");
    }

    ShowNextQuestion();
}

void CPlayWithMFCDlg::InitializeUI()
{
    CProgressCtrl *pProgCtrl = (CProgressCtrl *)GetDlgItem(IDC_TIME_PROG);
    if (pProgCtrl)
    {
        pProgCtrl->SetRange(0, END_OF_PROG);
        pProgCtrl->SetPos(0);
        pProgCtrl->SetBarColor(COLORREF(0x000EC9FF));
    }

    SetDlgItemTextW(IDC_TEST_EDIT, L"문제를 맞춰줘 >_<");
}

void CPlayWithMFCDlg::OnBnClickedAns1Btn()
{
    OnOptionClicked(1);
}

void CPlayWithMFCDlg::OnBnClickedAns2Btn()
{
    OnOptionClicked(2);
}


void CPlayWithMFCDlg::OnBnClickedAns3Btn()
{
    OnOptionClicked(3);
}

void CPlayWithMFCDlg::FinishGame()
{
    if (!m_bGameProceeding)
        return;

    KillTimer(TIMER_EVT_GAME_PROG);
    AfxMessageBox(L"Game Finish!!");

    InitializeGameData();
    InitializeUI();
}

void CPlayWithMFCDlg::InitializeGameData()
{
    m_bGameProceeding = false;
    m_currentQuest = -1;
}

void CPlayWithMFCDlg::OnBnClickedOk()
{
    // TBD 힌트 기능
    // CDialogEx::OnOK();
}
