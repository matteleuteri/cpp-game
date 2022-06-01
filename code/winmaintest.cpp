#include "winmaintest.h"

static inline int64_t GetTicks()
{
    LARGE_INTEGER ticks;
    if (!QueryPerformanceCounter(&ticks))
    {
        // log error
    }
    return ticks.QuadPart;
}

/*  THESE KEY FUNCTIONS BELOW ARE NOT FINAL  */
static void handleKeyDown(WPARAM wParam)
{
    OutputDebugStringA("key down\n");
    
    if(wParam == VK_RETURN) // hitting ENTER starts the game
    {
        scene->player->isActive = true;

        scene->player->x = 400;
        scene->player->y = 400;

        scene->player->width = 20;
        scene->player->height = 20;
        
        scene->player->leftSpeed = 0;
        scene->player->rightSpeed = 0;
        scene->player->upSpeed = 0;
        scene->player->downSpeed = 0;
    }
    else if(wParam == VK_UP)
    {
        scene->player->goingUp = true;
    }
    else if(wParam == VK_RIGHT)
    {
        scene->player->goingRight = true;
    }
    else if(wParam == VK_DOWN)
    {
        scene->player->goingDown = true;
    }
    else if(wParam == VK_LEFT)
    {
        scene->player->goingLeft = true;
    }
}

static void handleKeyUp(WPARAM wParam)
{
    OutputDebugStringA("key up\n");
    if(wParam == VK_UP)
    {
        scene->player->goingUp = false;
    }
    else if(wParam == VK_RIGHT)
    {
        scene->player->goingRight = false;
    }
    else if(wParam == VK_DOWN)
    {
        scene->player->goingDown = false;
    }
    else if(wParam == VK_LEFT)
    {
        scene->player->goingLeft = false;
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    // POINT pt;

    switch (uMsg)
    {

        case WM_CLOSE: 
        {
            isRunning = false;
            // if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK) 
            DestroyWindow(hwnd);
            break;
        } 

        case WM_DESTROY:
        {
            isRunning = false;
            PostQuitMessage(0);
            break;
        } 

        // case WM_PAINT:
        // {
        // } 
        case WM_LBUTTONDOWN:
        {
            if(!scene->player->isActive) break;
            Projectile* p = new Projectile(lParam, scene->player->x,  scene->player->y); // dont forget to free
            scene->projectiles.push_back(p);
        }
        
        case WM_KEYDOWN:
        {
            handleKeyDown(wParam);
            return 0;
        } 
        case WM_KEYUP:
        {
            handleKeyUp(wParam);
            return 0;
        } 

        default: 
        {
            result = DefWindowProc(hwnd, uMsg, wParam, lParam);
        } 

    }
    return result;
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[]  = L"Matt's Windows c++ Project";
    
    WNDCLASS wc = { };
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
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
                    WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 
                    CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);

        if(hwnd) 
        {
            isRunning = true;

            RECT rc;
            GetClientRect(hwnd, &rc);
            
            scene = new Scene(hwnd, &rc);

            int64_t startTime = GetTicks();
            
            while(isRunning)
            {
                MSG msg;
                while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
                {
                    if(msg.message == WM_QUIT)
                    {
                        isRunning = false;
                        break;
                    }
                    TranslateMessage(&msg);
                    DispatchMessageA(&msg);
                }

                int64_t endTime = GetTicks();
                scene->updateState(endTime - startTime);
                startTime = endTime;
                scene->renderState(&rc);
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