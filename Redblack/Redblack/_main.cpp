#include "stdafx.h"
#include "Redblack.h"

mylib::CTree* g_pTree;
mylib::CBinarySearchTree* g_pBSTree;
mylib::CRedBlackTree* g_pRBTree;
HINSTANCE g_hInst;
HWND g_hWnd;
HWND g_hDlg;

bool	g_bMouseDown;
int		g_iNodeKey;

// Draw
RECT	g_MemDCRect;
POINT	g_ptRootCur;
POINT	g_ptMousePre;
POINT	g_ptMouseCur;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	DlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
        return FALSE;

	g_hDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), g_hWnd, (DLGPROC)DlgProc);
	ShowWindow(g_hDlg, SW_SHOW);

    MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_REDBLACK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)GetStockObject(GRAY_BRUSH);// (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_REDBLACK);
    wcex.lpszClassName  = L"RedBlackTree";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(L"RedBlackTree" , L"RedBlackTree", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GetClientRect(hWnd, &g_MemDCRect);
	GetCursorPos(&g_ptMouseCur);
	
    switch (message)
    {
    case WM_CREATE:
		g_ptRootCur = { g_MemDCRect.right / 2,  80 };
		g_pBSTree = new mylib::CBinarySearchTree();
		g_pRBTree = new mylib::CRedBlackTree();
		g_pTree = g_pRBTree;
        break;
	case WM_LBUTTONDOWN:
		g_bMouseDown = true;

		/*----------------------------------------------------------------*/
		// 마우스 영역 제한
		POINT ptTemp1, ptTemp2;
		RECT rcClipRange;

		// GetClientRect()는 좌표가 아니라 `크기`를 가져오므로 클라이언트 기준 좌표로 변경해야함
		ptTemp1.x = g_MemDCRect.left;	ptTemp1.y = g_MemDCRect.top;
		ptTemp2.x = g_MemDCRect.right;	ptTemp2.y = g_MemDCRect.bottom;
		ClientToScreen(hWnd, &ptTemp1);	ClientToScreen(hWnd, &ptTemp2);
		rcClipRange.left = ptTemp1.x;	rcClipRange.top = ptTemp1.y;
		rcClipRange.right = ptTemp2.x;	rcClipRange.bottom = ptTemp2.y;

		ClipCursor(&rcClipRange); // 윈도우 기준 좌표 필요
		/*----------------------------------------------------------------*/
		break;
	case WM_LBUTTONUP:
	case WM_MOUSELEAVE:
		g_bMouseDown = false;

		// 마우스 영역 제한 해제
		ClipCursor(nullptr);
		break;
	case WM_MOUSEMOVE:
		if (g_bMouseDown)
		{
			ScreenToClient(hWnd, &g_ptMousePre);
			ScreenToClient(hWnd, &g_ptMouseCur);
			g_ptRootCur.x -= g_ptMousePre.x - g_ptMouseCur.x;
			g_ptRootCur.y -= g_ptMousePre.y - g_ptMouseCur.y;
			InvalidateRect(g_hWnd, NULL, TRUE);
		}
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			
			WCHAR szBuff[64];
			wsprintf(szBuff, L"(%d, %d)", g_ptRootCur.x, g_ptRootCur.y);
			TextOut(hdc, g_MemDCRect.right - 80, 0, szBuff, wcslen(szBuff));

           /*----------------------------------------------------------------*/
			SetTextColor(hdc, RGB(255, 255, 255));
			SetBkMode(hdc, TRANSPARENT);

			
			if (g_pTree->GetNodeCount() != 0)
			{
				int iDepth = 0;
				g_pTree->DrawNode(hdc, g_ptRootCur, iDepth, NULL, g_pTree->GetNodeCount());
			}
			/*----------------------------------------------------------------*/

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

	g_ptMousePre = g_ptMouseCur;
    return 0;
}

LRESULT CALLBACK DlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	int iRandKey;
	switch (iMsg)
	{
	case WM_INITDIALOG:
	{
		CheckRadioButton(hWnd, IDC_RADIO_RB, IDC_RADIO_BS, IDC_RADIO_RB);
		break;
	}
	case WM_COMMAND:
		switch (wParam)
		{
		case IDC_RADIO_RB:
			g_pTree = g_pRBTree;
			break;
		case IDC_RADIO_BS:
			g_pTree = g_pBSTree;
			break;
		case IDC_CREATE_BUTTON:
			g_iNodeKey = GetDlgItemInt(g_hDlg, IDC_KEY_EDIT, NULL, FALSE);
			g_pRBTree->InsertNode(g_iNodeKey);
			g_pBSTree->InsertNode(g_iNodeKey);
			break;
		case IDC_DELETE_BUTTON:
			g_iNodeKey = GetDlgItemInt(g_hDlg, IDC_KEY_EDIT, NULL, FALSE);
			g_pRBTree->DeleteNode(g_iNodeKey);
			g_pBSTree->DeleteNode(g_iNodeKey);
			break;
		case IDC_RANDOM_BUTTON:
			iRandKey = rand() % 1000;
			g_pRBTree->InsertNode(iRandKey);
			g_pBSTree->InsertNode(iRandKey);
			break;
		case IDC_POSRESET_BUTTON:
			g_ptRootCur = { g_MemDCRect.right / 2,  80 };
			break;
		case IDC_EXIT_BUTTON:
			DestroyWindow(g_hDlg);
			g_hDlg = nullptr;
			PostQuitMessage(0);
			break;
		}
		InvalidateRect(g_hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		DestroyWindow(g_hDlg);
		g_hDlg = nullptr;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, iMsg, wParam, lParam);
	}
	return 0;
}
