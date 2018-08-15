// MakeFileListDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MakeFileList.h"
#include "MakeFileListDlg.h"
#include <shlwapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
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


// CMakeFileListDlg ダイアログ




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


// CMakeFileListDlg メッセージ ハンドラ

BOOL CMakeFileListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
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

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// ファイルのドロップが出来るようにする
	DragAcceptFiles(TRUE);

	// 初期値
	m_strOutputCsvEdit = _T("FindFileList.csv");
	m_strMessage = _T("");
	UpdateData(FALSE);

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
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

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMakeFileListDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMakeFileListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// CSV出力ボタン押下時処理
void CMakeFileListDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	if( PathFileExists( m_strFindPathEdit ) && PathIsDirectory( m_strFindPathEdit ) )
	{
		SearchFileAndOutputCsv(m_strFindPathEdit, m_strOutputCsvEdit);
		m_strMessage = _T("出力完了");
	}
	else
	{
		m_strMessage = _T("検索フォルダが見つかりません");
	}

	UpdateData(FALSE);
}

// ファイルドロップ時処理
void CMakeFileListDlg::OnDropFiles(HDROP hDropInfo)
{
	// ドロップされたファイル数を取得
	UINT iCount = ::DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	char filepath[MAX_PATH + 1];
	for (UINT i=0; i<iCount; i++)
	{
		// ファイルの絶対パスを取得	
		::DragQueryFile(hDropInfo, i, filepath, MAX_PATH + 1);
		// 絶対パス名を表示	
		UpdateData(TRUE);
		m_strFindPathEdit = filepath;
		UpdateData(FALSE);
		break;
	}
	// ファイル名を取得するために
	// システムが確保したメモリを解放
	::DragFinish(hDropInfo);

	//CDialog::OnDropFiles(hDropInfo);
}

// 参照ボタン押下時処理
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

	// メッセージ
	m_strMessage = _T("出力中．．．") + strFolder;
	UpdateData(FALSE);
    
    // すべてのファイルを検索
    CString strSearchFile = strFolder + _T("\\*.*");
    
    if (!FileFind.FindFile(strSearchFile))
	{
        return; 
	}

    BOOL bContinue = TRUE;
    while (bContinue)
	{     
        bContinue = FileFind.FindNextFile();
        
		// ドット("." , "..")の場合 無視
		if (FileFind.IsDots())
		{
			continue; 
		}

        // ディレクトリの場合、そのディレクトリ内を検索するため再起呼び出し
        if (FileFind.IsDirectory())
		{
			SearchFileAndOutputCsv(FileFind.GetFilePath(), strOutputCsv);
		}
        else
		{
			// ファイルの場合
			BOOL bRet = OutputCsvFile(&FileFind, strOutputCsv);

			if (FALSE == bRet)
			{
				::AfxMessageBox("CSVファイル出力失敗");
				return;
			}
		}
    }
}

BOOL CMakeFileListDlg::OutputCsvFile(CFileFind* pFileFind, CString strFilename)
{
	CFile file;

	// ファイルオープン
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

	// 出力内容
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

	// 書き込み
	try
	{
		file.SeekToEnd();
		file.Write(strOutput, strOutput.GetLength());
	}
	catch (...)
	{
		return FALSE;
	}

	// クローズ
	file.Close();

	return TRUE;
}

CString CMakeFileListDlg::ShowFolderSelDlg()
{
	CString strSelectFolder(_T(""));
    BROWSEINFO bInfo;
    LPITEMIDLIST pIDList;
    TCHAR szDisplayName[MAX_PATH];
    
    // BROWSEINFO構造体に値を設定
    bInfo.hwndOwner             = AfxGetMainWnd()->m_hWnd;          // ダイアログの親ウインドウのハンドル
    bInfo.pidlRoot              = NULL;                             // ルートフォルダを示すITEMIDLISTのポインタ (NULLの場合デスクトップフォルダが使われます）
    bInfo.pszDisplayName        = szDisplayName;                    // 選択されたフォルダ名を受け取るバッファのポインタ
    bInfo.lpszTitle             = _T("フォルダの選択");             // ツリービューの上部に表示される文字列 
    bInfo.ulFlags               = BIF_RETURNONLYFSDIRS;             // 表示されるフォルダの種類を示すフラグ
    bInfo.lpfn                  = NULL;                             // BrowseCallbackProc関数のポインタ
    bInfo.lParam                = (LPARAM)0;                        // コールバック関数に渡す値
    
    // フォルダ選択ダイアログを表示
    pIDList = ::SHBrowseForFolder(&bInfo);
    if(pIDList == NULL)
	{
        // 戻り値がNULLの場合、フォルダが選択されずにダイアログが閉じられたことを意味します。
    }
	else
	{
        // ItemIDListをパス名に変換します
        if(::SHGetPathFromIDList(pIDList, szDisplayName))
		{
            // szDisplayNameに選択されたフォルダのパスが入っています
			strSelectFolder = szDisplayName;
        }

        // 最後にpIDListのポイントしているメモリを開放します
        ::CoTaskMemFree( pIDList );
    }

	return strSelectFolder;
}

