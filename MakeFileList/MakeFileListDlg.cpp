// MakeFileListDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MakeFileList.h"
#include "MakeFileListDlg.h"
#include <shlwapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMakeFileListDlg �_�C�A���O




CMakeFileListDlg::CMakeFileListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMakeFileListDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMakeFileListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strFindPathEdit);
	DDX_Text(pDX, IDC_EDIT2, m_strOutputCsvEdit);
	DDX_Text(pDX, IDC_LABEL1, m_strMessage);
}

BEGIN_MESSAGE_MAP(CMakeFileListDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CMakeFileListDlg::OnBnClickedOk)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CMakeFileListDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMakeFileListDlg ���b�Z�[�W �n���h��

BOOL CMakeFileListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// �t�@�C���̃h���b�v���o����悤�ɂ���
	DragAcceptFiles(TRUE);

	// �����l
	m_strOutputCsvEdit = _T("FindFileList.csv");
	m_strMessage = _T("");
	UpdateData(FALSE);

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

void CMakeFileListDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CMakeFileListDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CMakeFileListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// CSV�o�̓{�^������������
void CMakeFileListDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	if( PathFileExists( m_strFindPathEdit ) && PathIsDirectory( m_strFindPathEdit ) )
	{
		SearchFileAndOutputCsv(m_strFindPathEdit, m_strOutputCsvEdit);
		m_strMessage = _T("�o�͊���");
	}
	else
	{
		m_strMessage = _T("�����t�H���_��������܂���");
	}

	UpdateData(FALSE);
}

// �t�@�C���h���b�v������
void CMakeFileListDlg::OnDropFiles(HDROP hDropInfo)
{
	// �h���b�v���ꂽ�t�@�C�������擾
	UINT iCount = ::DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	char filepath[MAX_PATH + 1];
	for (UINT i=0; i<iCount; i++)
	{
		// �t�@�C���̐�΃p�X���擾	
		::DragQueryFile(hDropInfo, i, filepath, MAX_PATH + 1);
		// ��΃p�X����\��	
		UpdateData(TRUE);
		m_strFindPathEdit = filepath;
		UpdateData(FALSE);
		break;
	}
	// �t�@�C�������擾���邽�߂�
	// �V�X�e�����m�ۂ��������������
	::DragFinish(hDropInfo);

	//CDialog::OnDropFiles(hDropInfo);
}

// �Q�ƃ{�^������������
void CMakeFileListDlg::OnBnClickedButton1()
{
	CString strFolder = ShowFolderSelDlg();

	if (strFolder.GetLength() > 0)
	{
		m_strFindPathEdit = strFolder;
		UpdateData(FALSE);
	}
}


void CMakeFileListDlg::SearchFileAndOutputCsv(CString strFolder, CString strOutputCsv)
{ 
    CFileFind FileFind;

	// ���b�Z�[�W
	m_strMessage = _T("�o�͒��D�D�D") + strFolder;
	UpdateData(FALSE);
    
    // ���ׂẴt�@�C��������
    CString strSearchFile = strFolder + _T("\\*.*");
    
    if (!FileFind.FindFile(strSearchFile))
	{
        return; 
	}

    BOOL bContinue = TRUE;
    while (bContinue)
	{     
        bContinue = FileFind.FindNextFile();
        
		// �h�b�g("." , "..")�̏ꍇ ����
		if (FileFind.IsDots())
		{
			continue; 
		}

        // �f�B���N�g���̏ꍇ�A���̃f�B���N�g�������������邽�ߍċN�Ăяo��
        if (FileFind.IsDirectory())
		{
			SearchFileAndOutputCsv(FileFind.GetFilePath(), strOutputCsv);
		}
        else
		{
			// �t�@�C���̏ꍇ
			BOOL bRet = OutputCsvFile(&FileFind, strOutputCsv);

			if (FALSE == bRet)
			{
				::AfxMessageBox("CSV�t�@�C���o�͎��s");
				return;
			}
		}
    }
}

BOOL CMakeFileListDlg::OutputCsvFile(CFileFind* pFileFind, CString strFilename)
{
	CFile file;

	// �t�@�C���I�[�v��
	BOOL bRet = file.Open(
		strFilename, 
		CFile::modeWrite |
		CFile::shareDenyWrite |
		CFile::modeCreate |
		CFile::modeNoTruncate);

	if (FALSE == bRet)
	{
		return FALSE;
	}

	// �o�͓��e
	TCHAR szDrive[_MAX_DRIVE];
	TCHAR szDir[_MAX_DIR];
	TCHAR szFile[_MAX_FNAME];
	TCHAR szExt[_MAX_EXT];
	_tsplitpath_s(pFileFind->GetFilePath(), szDrive, szDir, szFile, szExt);

	CString strOutput(_T(""));
	strOutput += pFileFind->GetFilePath();
	strOutput += _T(",");
	strOutput += szDrive;
	strOutput += szDir;
	strOutput += _T(",");
	strOutput += szFile;
	strOutput += szExt;
	strOutput += _T(",");
	strOutput += szFile;
	strOutput += _T(",");
	strOutput += szExt;
	strOutput += _T("\r\n");

	// ��������
	try
	{
		file.SeekToEnd();
		file.Write(strOutput, strOutput.GetLength());
	}
	catch (...)
	{
		return FALSE;
	}

	// �N���[�Y
	file.Close();

	return TRUE;
}

CString CMakeFileListDlg::ShowFolderSelDlg()
{
	CString strSelectFolder(_T(""));
    BROWSEINFO bInfo;
    LPITEMIDLIST pIDList;
    TCHAR szDisplayName[MAX_PATH];
    
    // BROWSEINFO�\���̂ɒl��ݒ�
    bInfo.hwndOwner             = AfxGetMainWnd()->m_hWnd;          // �_�C�A���O�̐e�E�C���h�E�̃n���h��
    bInfo.pidlRoot              = NULL;                             // ���[�g�t�H���_������ITEMIDLIST�̃|�C���^ (NULL�̏ꍇ�f�X�N�g�b�v�t�H���_���g���܂��j
    bInfo.pszDisplayName        = szDisplayName;                    // �I�����ꂽ�t�H���_�����󂯎��o�b�t�@�̃|�C���^
    bInfo.lpszTitle             = _T("�t�H���_�̑I��");             // �c���[�r���[�̏㕔�ɕ\������镶���� 
    bInfo.ulFlags               = BIF_RETURNONLYFSDIRS;             // �\�������t�H���_�̎�ނ������t���O
    bInfo.lpfn                  = NULL;                             // BrowseCallbackProc�֐��̃|�C���^
    bInfo.lParam                = (LPARAM)0;                        // �R�[���o�b�N�֐��ɓn���l
    
    // �t�H���_�I���_�C�A���O��\��
    pIDList = ::SHBrowseForFolder(&bInfo);
    if(pIDList == NULL)
	{
        // �߂�l��NULL�̏ꍇ�A�t�H���_���I�����ꂸ�Ƀ_�C�A���O������ꂽ���Ƃ��Ӗ����܂��B
    }
	else
	{
        // ItemIDList���p�X���ɕϊ����܂�
        if(::SHGetPathFromIDList(pIDList, szDisplayName))
		{
            // szDisplayName�ɑI�����ꂽ�t�H���_�̃p�X�������Ă��܂�
			strSelectFolder = szDisplayName;
        }

        // �Ō��pIDList�̃|�C���g���Ă��郁�������J�����܂�
        ::CoTaskMemFree( pIDList );
    }

	return strSelectFolder;
}

