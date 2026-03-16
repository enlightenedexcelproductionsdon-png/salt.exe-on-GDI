#include <windows.h>
#include <cmath>

const int WIDTH = 800;
const int HEIGHT = 600;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static int t = 0;
    switch (uMsg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            for (int i = 0; i < 10; ++i) {
                int x = (t + i * 100) % WIDTH;
                int y = (t + i * 50) % HEIGHT;
                int size = (t + 1234) & ((t + 1234) >> 8);
                Rectangle(hdc, x, y, x + size, y + size);
            }
            EndPaint(hwnd, &ps);
            break;
        }
        case WM_TIMER:
            t++;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nShowCmd) {
    const char CLASS_NAME[] = "BouncingSquaresClass";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, "Bouncing Squares", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nShowCmd);
    SetTimer(hwnd, 1, 29, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
