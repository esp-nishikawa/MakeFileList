// MakeFileList.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CMakeFileListApp:
// このクラスの実装については、MakeFileList.cpp を参照してください。
//

class CMakeFileListApp : public CWinApp
{
public:
	CMakeFileListApp();

// オーバーライド
	public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CMakeFileListApp theApp;