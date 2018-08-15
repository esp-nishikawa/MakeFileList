// MakeFileListDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once


// CMakeFileListDlg �_�C�A���O
class CMakeFileListDlg : public CDialog
{
private:
	HICON m_hIcon;
	CString m_strFindPathEdit;
	CString m_strOutputCsvEdit;
	CString m_strMessage;

// �R���X�g���N�V����
public:
	CMakeFileListDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_MAKEFILELIST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g

// ����
protected:
	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
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
