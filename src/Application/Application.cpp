#include "framework.h"
#include "Application.h"

#include "Util/BresenhamLine.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BRESENHAMLINE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, NULL, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BRESENHAMLINE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int s_StartX = 0;
    static int s_StartY = 0;

    static int s_EndX = 0;
    static int s_EndY = 0;

    static bool s_IsDown = false;

    switch (message)
    {
        case WM_LBUTTONDOWN:
        {
            s_StartX = LOWORD(lParam);
            s_StartY = HIWORD(lParam);

            s_IsDown = true;

            InvalidateRect(hWnd, nullptr, TRUE);

            break;
        }

        case WM_LBUTTONUP:
        {
            s_IsDown = false;

            InvalidateRect(hWnd, nullptr, TRUE);

            break;
        }

        case WM_MOUSEMOVE:
        {
            s_EndX = LOWORD(lParam);
            s_EndY = HIWORD(lParam);

            InvalidateRect(hWnd, nullptr, TRUE);

            break;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc;
            
            hdc = BeginPaint(hWnd, &ps);
            {
                if (s_IsDown)
                {
                    std::vector<BresenhamPoint> linePoints;

                    int cellStartX = s_StartX / 24;
                    int cellStartY = s_StartY / 24;

                    int cellEndX = s_EndX / 24;
                    int cellEndY = s_EndY / 24;

                    BresenhamLineCaseA(cellStartX, cellStartY, cellEndX, cellEndY, &linePoints);

                    HBRUSH hGrayBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
                    HBRUSH hOldBrush  = (HBRUSH)SelectObject(hdc, hGrayBrush);

                    for (auto& point : linePoints)
                    {
                        int drawStartX = point.x * 24;
                        int drawStartY = point.y * 24;

                        int drawEndX = drawStartX + 24;
                        int drawEndY = drawStartY + 24;

                        Rectangle(hdc, drawStartX, drawStartY, drawEndX, drawEndY);
                    }

                    SelectObject(hdc, hOldBrush);

                    HPEN hLinePen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
                    HPEN hOldPen  = (HPEN)SelectObject(hdc, hLinePen);

                    MoveToEx(hdc, s_StartX, s_StartY, nullptr);
                    LineTo(hdc, s_EndX, s_EndY);

                    SelectObject(hdc, hOldPen);
                    DeleteObject(hLinePen);
                }
            }
            EndPaint(hWnd, &ps);
            
            break;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);

            break;
        }

        default:
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
}
