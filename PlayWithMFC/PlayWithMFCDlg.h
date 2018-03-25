
// PlayWithMFCDlg.h : header file
//

#pragma once

#define OPTION_MAX_COUNT    3
#define OPTION_STR_SIZE     50
#define QUESTION_MAX_COUNT  10

// CPlayWithMFCDlg dialog
class CPlayWithMFCDlg : public CDialogEx
{
private:
    struct QnA
    {
        wchar_t strQuestion[200];
        int     nAnswer;
        wchar_t strArrOption[OPTION_MAX_COUNT][OPTION_STR_SIZE];
    };

    QnA m_lstQnA[10];
    int m_cntQuestion;

    int m_currentQuest;
    bool m_bGameProceeding;

	int ReadQnAFile();
    void ShowNextQuestion();
    void FinishGame();
    void ResetGame();
    
    void OnOptionClicked(int nOpt);

// Construction
public:
	CPlayWithMFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLAYWITHMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartBtn();

private:
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedAns1Btn();
    afx_msg void OnBnClickedAns2Btn();
    afx_msg void OnBnClickedAns3Btn();
    afx_msg void OnBnClickedOk();
};
