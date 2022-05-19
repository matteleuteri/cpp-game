#include "winmaintest.h"

struct StateInfo 
{
    // ... (struct members not shown)
};


inline StateInfo* GetAppState(HWND hwnd)
{
    LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    StateInfo *pState = reinterpret_cast<StateInfo*>(ptr);
    return pState;
}

void OnSize(HWND hwnd, UINT flag, int width, int height)
{
    // Handle resizing
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    StateInfo *pState = new StateInfo;

    FRAMES_PER_SECOND = 60;

    if (pState == NULL) return 0;

    const wchar_t CLASS_NAME[]  = L"Matt's Windows c++ Project";

    WNDCLASS wc = { };
    
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance     = hInstance;
    wc.hIcon = 0;
    wc.hCursor = 0;
    wc.hbrBackground = 0;
    wc.lpszMenuName = 0;
    wc.lpszClassName = CLASS_NAME;

    if(RegisterClass(&wc))
    {
        HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Learn to Program Windows", 
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, pState);

        if(hwnd) 
        {
            ShowWindow(hwnd, nCmdShow);
            isRunning = true;
            while(isRunning)
            {
                

                    MSG msg = { };
                    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
                    {
                        if(msg.message == WM_QUIT)
                        {
                            isRunning = false;
                            break;
                        }
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }

                    //InvalidateRect(hwnd, NULL, TRUE);
                    // processFrame();

            }
            // no longer running
        }
        else 
        {
            // TODO log window creation failure
        }
    }
    else 
    {
        // TODO log window registration failure
    }
    
    
    return 0;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

//     POINT pt;
// pt.x = LOWORD(lParam); 
//                 pt.y = HIWORD(lParam);
//                 renderScene2(hwnd, pt);

    StateInfo *pState;
    if (uMsg == WM_CREATE)
    {
        // loads state info
        // CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        // pState = reinterpret_cast<StateInfo*>(pCreate->lpCreateParams);
        // SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pState);
    }
    else
    {
        // pState = GetAppState(hwnd);
    }

    switch (uMsg)
    {
        // case MK_LBUTTON:
        //     InvalidateRect(hwnd, NULL, TRUE);

        case WM_SIZE:
        {
            // InvalidateRect(hwnd, NULL, TRUE);
            // OnSize(hwnd, (UINT)wParam, width, height);
        } break;

        case WM_CLOSE: 
        {
            isRunning = false;
            // if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK) 
            DestroyWindow(hwnd);
        } break;

        case WM_DESTROY:
        {
            isRunning = false;
            PostQuitMessage(0);
        } break;

        case WM_PAINT:
        {
            renderScene(hwnd);
        } break;
        


        case WM_LBUTTONDOWN:
            {
                
            }
        
        break;


        default: 
        {
            result = DefWindowProc(hwnd, uMsg, wParam, lParam);
        } 

    }
    return result;
}
