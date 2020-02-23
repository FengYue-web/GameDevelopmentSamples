// Expression.cpp : Defines the entry point for the application.
//
/************************************************************************/
/*	����Ŀ�ģ�C�����еı��ʽ�����
	�����ܣ�����������������������㣬������������������
	�����߸Ľ�:ʵ�ָ��Ӹ��ӵ���ѧ����,����(9+22.5)*30/2.3=?
	��д�ߣ������ף�hanhonglei@sina.com��*/
/************************************************************************/

#include "stdafx.h"
#include "Expression.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

float x = 0, y = 0;			// �����������������
int num = 0;				// ��ǰ�û�����ĸ���
char oper;					// �����
char input[64];				// ��ʱ�����û���������Ϣ
float result;				// ���������
int bResult = 0;			// �Ƿ���ý��
WCHAR str[64];				// ���������ʾ���ַ���

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_EXPRESSION, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EXPRESSION));
	
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EXPRESSION));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_EXPRESSION);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CHAR:												// �������
		InvalidateRect(hWnd, NULL, TRUE);						// �ػ���Ļ��Ϣ
		if (wParam == VK_RETURN)								// ������»س���,��ʼ��һ�ּ���
		{
			num = 0;
			bResult = 0;
			memset(input, '\0', 64*sizeof(char));
		}
		else if (bResult)										// ����Ѿ��õ��˼��������򲻽�����ҵ��������룬ֱ�����������Ϣ
			break;
		if(wParam == '.' || (wParam >= '0' && wParam <= '9'))	// ����������Ĳ�������,�򲻼�¼.�߼����ʽ
		{
			input[num++] = wParam;								// ��ֵ���
		}
		else if (wParam == '+' || wParam == '-' || wParam == '*' || wParam == '/')	// ��¼�����
		{
			input[num++] = ' ';
			input[num++] = wParam;
			input[num++] = ' ';
		}
		else if (wParam == '=')									// �������Ⱥ�,��������
		{
			input[num++] = ' ';
			// �޸�Ϊ��ȫģʽ��scanf
			sscanf_s(input, "%f %c %f", &x, &oper, 1, &y);		// ��ȡ������������ּ������
			if (oper == '+')									// ������������ͽ��в�ͬ����
				result = x + y;									// �������ʽ
			else if( oper == '-')
				result = x - y;
			else if(oper == '*')
				result = x * y;
			else if(oper == '/')
				result = x / y;

			input[num++] = '=';		
			bResult = 1;										// ����������־��Ϊtrue
		}
		break; 
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		TextOut(hdc, 0, 0, L"���������ʽ", 6);	
		MultiByteToWideChar(CP_THREAD_ACP,MB_USEGLYPHCHARS,input,64,str,64);   // ���û�������ת��Ϊ���ַ���,�Ա����
		TextOut(hdc, 0, 20, str, wcslen(str));					// ��ʾ�û�������
		if (bResult)											// ����м�����,������һ��������
		{
			WCHAR str2[16];
			swprintf(str2, 16, L"%f", result);
			TextOut(hdc, 0, 40, str2, wcslen(str2));
		}	
		EndPaint(hWnd, &ps);
		break;	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
