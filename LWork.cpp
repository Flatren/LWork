// LWork.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "LWork.h"
#include "LWork_2.h"
#include "LWork_3.h"
#include "LWork_4.h"
#include "LWork_5.h"
#include "LWork_7.h"
#include <ctime>
#include <process.h>
#include <vector>
#define MAX_LOADSTRING 100
//#define SPECIAL_CTRL_CHANGE_T L"Create_new_message_click"
//static UINT IDM_CONNECT = RegisterWindowMessage(SPECIAL_CTRL_CHANGE_T);
//#define IDM_CONNECT (IDM_CONNECT_)
char* dataPtr;

char ID_Gamer=0;
std::vector<Image*>* images;
// ���������� ����������:
HINSTANCE hInst;                                // ������� ���������
WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����
ConfigINI Config;

// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPWSTR lpCmdLine,_In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
	
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LWORK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	Read_Write_Choise((char*)lpCmdLine,Config,0);
	HANDLE hMapFile;
	CreateConnect(hMapFile,dataPtr,Config.n*Config.n+1);
	ID_Gamer = *dataPtr; 
	char text[9]{'P','l','a','y','e','r','_','0'};
	text[7] += ID_Gamer;
	wchar_t wc[9];
	mbstowcs(wc, text, 9);
	srand(time(0));
	images = Get_Images(&Config);
	if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	SetWindowText(FindWindowW(L"LWork", NULL), wc);
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LWORK));
    MSG msg;
	
	
    while (GetMessage(&msg, nullptr, 0, 0))
    {
		//paint += 1;
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
	
	Delete_Images(images);
	Read_Write_Choise((char*)lpCmdLine, Config, 1);
	CloseConnect(hMapFile, dataPtr);
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LWORK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(Config.ColorRGB_Backgraund);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LWORK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, Config.size.wight,Config.size.height , nullptr, nullptr, hInstance, nullptr);
  
   if (!hWnd)
   {
      return FALSE;
   }
 
   ShowWindow(hWnd, nCmdShow);
   _beginthread(Paint, 0, (void*)hWnd);
   UpdateWindow(hWnd);
   return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	if (message ==RegisterWindowMessage(SPECIAL_CTRL_CHANGE_T))
	{
		InvalidateRect(hWnd, NULL, FALSE);
	}

    switch (message)
    {
		case WM_LBUTTONUP:
		{
			//SetWindowText(hWnd, L"player_1");
			if (Check_Player_Try(dataPtr, ID_Gamer))
			{
				dataPtr[1] = ID_Gamer;
				ClickPaintCircle_(hWnd, dataPtr,ID_Gamer, &Config, images, LOWORD(lParam), HIWORD(lParam));
			}
			else
				MessageBox(NULL, L"Err", L"Check_Player_Try", 0);
		}
		break;
	case WM_KEYDOWN:
	{
		switch (LOWORD(wParam))
		{
		case 27:
		{
			PostQuitMessage(0);
		}
		break;
		case 13:
		{
			CreateFonColor(hWnd, &Config);
		}
		break;
		}
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // ��������� ����� � ����:
            switch (wmId)
            {
			case IDM_OpenNotepad:
			{
				OpenProgramm();
			}
			break;
            case IDM_EXIT:
				PostQuitMessage(0);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	//case IDM_CONNECT:
	//	InvalidateRect(hWnd, NULL, FALSE);
	//	break;
    case WM_PAINT:
        {
			//Paint(hWnd);
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			//_beginthread(Paint, 0, (void*)Hwnd);
			CreateFonLine(hWnd, hdc, &Config);
			PaintCircle_(hdc, dataPtr, &Config, images);
			EndPaint(hWnd, &ps);
			
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
		
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
	//InvalidateRect(hWnd, NULL, FALSE);
    return 0;
}
//����� ����