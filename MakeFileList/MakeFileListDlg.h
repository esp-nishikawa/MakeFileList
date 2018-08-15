// MakeFileListDlg.h : ヘッダー ファイル
//

#pragma once


// CMakeFileListDlg ダイアログ
class CMakeFileListDlg : public CDialog
{
private:
	HICON m_hIcon;
	CString m_strFindPathEdit;
	CString m_strOutputCsvEdit;
	CString m_strMessage;

// コンストラクション
public:
	CMakeFileListDlg(CWnd* pParent = NULL);	// 標準コンストラクタ

// ダイアログ データ
	enum { IDD = IDD_MAKEFILELIST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

// 実装
protected:
	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();

private:
	void SearchFileAndOutputCsv(CString strFolder, CString strOutputCsv);
	BOOL OutputCsvFile(CFileFind* pFileFind, CString strFilename);
	CString ShowFolderSelDlg();
};
