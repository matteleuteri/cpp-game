#include "winmaintest.h"






//turn()



void handleKeyDown(WPARAM wParam)
{
    if(wParam == VK_RETURN) // hitting ENTER starts the game
    {
        player->isActive = true;
        player->x = 300;
        player->y = 300;
        player->speed = 1.0f;
        player->width = 20;
        player->height = 20;
        player->direction = RIGHT;
    }
    // modify the direction by something. use acceleration
    else if(wParam == VK_UP)
    {
        // turn(UP);
    }
    else if(wParam == VK_RIGHT)
    {
        // turn(RIGHT);
    }
    else if(wParam == VK_DOWN)
    {
        // turn(DOWN);
    }
    else if(wParam == VK_LEFT)
    {
        // turn(LEFT);
    }
}



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;




    // StateInfo *pState;
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
            renderScene(hwnd, player);
        } break;
        
        case WM_KEYDOWN:
        {
            handleKeyDown(wParam);

        } break;

        default: 
        {
            result = DefWindowProc(hwnd, uMsg, wParam, lParam);
        } 

    }
    return result;
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // StateInfo *pState = new StateInfo;


    player = new Player();


    FRAMES_PER_SECOND = 60;

    // if (pState == NULL) return 0;

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
        NULL, NULL, hInstance, NULL);

        if(hwnd) 
        {
            ShowWindow(hwnd, nCmdShow);
            isRunning = true;
            while(isRunning)
            {
                // do something about iming and framerate here ????
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
                        renderScene(hwnd, player);
                    }




                        //clear
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