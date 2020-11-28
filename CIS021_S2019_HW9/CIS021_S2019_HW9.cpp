// Project: CIS021_S2019_HW9
// Module:	CIS021_S2019_HW9.cpp 
// Author:	Evan Mayhew
// Date:	5/19/2019
// Purpose:	Understand modeling software.
//			Understand actions that occur in a simulator.
//			Demonstrate the effect of formulaic modification on programmatic output.
//


#include "stdafx.h"
#include "CIS021_S2019_HW9.h"

#define MAX_LOADSTRING 100
#define WM_TIMER_LIGHT 2000
#define WM_TIMER_TRAFFIC 2001

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
string strFlag;									// flag to prevent cars overlapping
int iFlagT = 0;
int iFlagR = 0;
int iFlagB = 0;
int iFlagL = 0;

LightsClass* Lights[4];							// traffic control stop lights
string strLight[4];
int iDirection = 0;
RECT rCheck;

vector<CarClass> vList;							// "list of" graphic object

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void DrawStreets(HDC);						// draw the background

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CIS021_S2019_HW9, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CIS021_S2019_HW9));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
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
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CIS021_S2019_HW9));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CIS021_S2019_HW9);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 900, 700, nullptr, nullptr, hInstance, nullptr);

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
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
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
	}
	break;


	case WM_TIMER:
		for (int i = 0; i < 4; i++)					// set state to array of strings to pass into move function
		{
			if (Lights[i]->GetState() == RED)
			{
				strLight[i] = "RED";
			}
			else if (Lights[i]->GetState() == YELLOW)
			{
				strLight[i] = "YELLOW";
			}
			else if (Lights[i]->GetState() == GREEN)
			{
				strLight[i] = "GREEN";
			}
		}

		if (wParam == WM_TIMER_TRAFFIC)					// move cars
		{

			for (vector<CarClass>::size_type i = 0; i < vList.size(); i++)
			{

				if (vList[i].Move(hWnd, iDirection, strLight, vList))							// move to graphic object
				{
					InvalidateRect(hWnd, NULL, TRUE);
				}
					
					else
					{
						InvalidateRect(hWnd, NULL, TRUE);
						vList.erase(vList.begin() + i);						// delete object
					}
				}
				InvalidateRect(hWnd, NULL, FALSE);
		}

		if (wParam == WM_TIMER_LIGHT)					// control traffic lights
		{
			for (int i = 0; i < 4; i++)
				Lights[i]->Set();						// tell lights 1 second has expired
		}
		

		break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			for (auto sim : vList)
				sim.Draw(hdc);

			DrawStreets(hdc);									// draw background
			for (int i = 0; i < 4; i++)							// draw traffic lights
				Lights[i]->Draw(hdc);



            EndPaint(hWnd, &ps);
        }
        break;



	case WM_KEYDOWN:										// capture key press
		switch (wParam)
		{
		
		case VK_UP:														// up arrow pressed
		{
			bool bFlag = true;
			for (vector<CarClass>::size_type i = 0; i < vList.size(); i++)
			{
				rCheck = vList.at(i).GetrDimT();
				if (rCheck.top < 150 && rCheck.top > 0)
				{
					bFlag = false;
				}
			}

			if (bFlag)
			{
				CarClass sim(hWnd, 1);									// create a graphic object
				vList.push_back(sim);									// add to the vector
			}
		}
		break;
			

		case VK_RIGHT:							// right arrow pressed
		{
			bool bFlag = true;
			for (vector<CarClass>::size_type i = 0; i < vList.size(); i++)
			{
				rCheck = vList.at(i).GetrDimR();
				if (rCheck.right <= 760 && rCheck.right >= 710)
				{
					bFlag = false;
				}
			}

			if (bFlag)
			{
				CarClass sim(hWnd, 2);									// create a graphic object
				vList.push_back(sim);									// add to the vector
			}

	}
		break;
		case VK_DOWN:							// down arrow pressed
		{
			bool bFlag = true;
			for (vector<CarClass>::size_type i = 0; i < vList.size(); i++)
			{
				rCheck = vList.at(i).GetrDimB();
				if (rCheck.bottom >= 510 && rCheck.bottom <= 560)
				{
					bFlag = false;
				}
			}

			if (bFlag)
			{
				CarClass sim(hWnd, 3);									// create a graphic object
				vList.push_back(sim);									// add to the vector
			}

		}
		break;
		case VK_LEFT:							// left arrow pressed
		{
			bool bFlag = true;
			for (vector<CarClass>::size_type i = 0; i < vList.size(); i++)
			{
				rCheck = vList.at(i).GetrDimL();
				if (rCheck.left >= 100 && rCheck.left <= 160)
				{
					bFlag = false;
				}
			}

			if (bFlag)
			{
				CarClass sim(hWnd, 4);									// create a graphic object
				vList.push_back(sim);									// add to the vector
			}
		}
		break;
		}

		break;

	case WM_CREATE:
		SetTimer(hWnd, WM_TIMER_TRAFFIC, 20, NULL);					// move cars
		SetTimer(hWnd, WM_TIMER_LIGHT, 1000, NULL);					// control traffic lights

		// create traffic lights
		for (int i = 0; i < 4; i++)								
			Lights[i] = new LightsClass(i);


		break;

    case WM_DESTROY:

		// stop timers
		KillTimer(hWnd, WM_TIMER_TRAFFIC);
		KillTimer(hWnd, WM_TIMER_LIGHT);

		for (int i = 0; i < 4; i++)								// destroy traffic lights
			if (Lights[i])
				delete Lights[i];


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

// draw the background
void DrawStreets(HDC hdc)
{
	HPEN penCurb, penDash, oldPen;
	TCHAR sz_DisplayA[32] = { 0 };

	penCurb = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));	 // black
	penDash = CreatePen(PS_DASH, 1, RGB(0, 0, 0));	 // dash
	oldPen = (HPEN)SelectObject(hdc, penCurb);

	// main street
	MoveToEx(hdc, 100, 300, NULL);
	LineTo(hdc, 400, 300);

	MoveToEx(hdc, 100, 360, NULL);
	LineTo(hdc, 400, 360);

	MoveToEx(hdc, 460, 300, NULL);
	LineTo(hdc, 760, 300);

	MoveToEx(hdc, 460, 360, NULL);
	LineTo(hdc, 760, 360);

	SelectObject(hdc, penDash);
	MoveToEx(hdc, 100, 330, NULL);
	LineTo(hdc, 400, 330);

	MoveToEx(hdc, 460, 330, NULL);
	LineTo(hdc, 760, 330);

	// 1st street
	SelectObject(hdc, penCurb);
	MoveToEx(hdc, 400, 100, NULL);
	LineTo(hdc, 400, 300);

	MoveToEx(hdc, 400, 360, NULL);
	LineTo(hdc, 400, 560);

	MoveToEx(hdc, 460, 100, NULL);
	LineTo(hdc, 460, 300);

	MoveToEx(hdc, 460, 360, NULL);
	LineTo(hdc, 460, 560);

	SelectObject(hdc, penDash);
	MoveToEx(hdc, 430, 100, NULL);
	LineTo(hdc, 430, 300);

	MoveToEx(hdc, 430, 360, NULL);
	LineTo(hdc, 430, 560);

	SelectObject(hdc, penCurb);

	// labels
	TextOut(hdc, 30, 322, _T("Main St."), 8);
	TextOut(hdc, 407, 72, _T("1st St."), 7);

	// release the line pen
	SelectObject(hdc, oldPen);
	DeleteObject(penDash);
	DeleteObject(penCurb);
}
