#include "winmaintest.h"

static win32_window_dimension Win32GetWindowDimension(HWND Window)
{
    win32_window_dimension Result;
    
    RECT ClientRect;
    GetClientRect(Window, &ClientRect);
    Result.Width = ClientRect.right - ClientRect.left;
    Result.Height = ClientRect.bottom - ClientRect.top;

    return(Result);
}


static void GameUpdateAndRender(game_offscreen_buffer *Buffer, int64_t elapsed)
{
    updateState(player, elapsed);
    renderState(Buffer, player);
}


static inline int64_t GetTicks()
{
    LARGE_INTEGER ticks;
    if (!QueryPerformanceCounter(&ticks))
    {
        // log error
    }
    return ticks.QuadPart;
}

static void handleKeyDown(WPARAM wParam, HWND hwnd)
{
    OutputDebugStringA("key down\n");
    
        if(wParam == VK_RETURN) // hitting ENTER starts the game
        {
        //     player->isActive = true;
        //     player->x = 300;
        //     player->y = 300;

        //     player->width = 20;
        //     player->height = 20;
        
        //     player->xSpeed = 0;
        //     player->ySpeed = 0;
        }
        // // modify the direction by something. use acceleration
        else if(wParam == VK_UP)
        {
            yoff-= 1;
        }
        else if(wParam == VK_RIGHT)
        {
            xoff+= 1;
        }
        else if(wParam == VK_DOWN)
        {
            yoff+= 1;
        }
        else if(wParam == VK_LEFT)
        {
            xoff -= 1;
        }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

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
        //     PAINTSTRUCT Paint;
        //     HDC DeviceContext = BeginPaint(hwnd, &Paint);
        //     win32_window_dimension Dimension = Win32GetWindowDimension(hwnd);
        //     Win32DisplayBufferInWindow(&GlobalBackbuffer, DeviceContext, Dimension.Width, Dimension.Height);
        //     EndPaint(hwnd, &Paint);            
        //     break;
        // } 
        
        case WM_KEYDOWN:
        {
            handleKeyDown(wParam, hwnd);
            break;
        } 
        // case WM_KEYUP:
        // {
        //     break;
        // } 

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
    player = new Player();
    WNDCLASS wc = { };
    // Win32ResizeDIBSection(&GlobalBackbuffer, 1280, 720);
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

    yoff = 0;
    xoff = 0;

    if(RegisterClass(&wc))
    {
        HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Learn to Program Windows", WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);

        if(hwnd) 
        {
            // HDC DeviceContext = GetDC(hwnd);

            isRunning = true;

            // direct2d code begins here
            ID2D1Factory* pD2DFactory = NULL;
            //  returns HRESULT
            D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
            
            // repeat this as needed
            RECT rc;
            GetClientRect(hwnd, &rc);
            
            ID2D1HwndRenderTarget* pRT = NULL;          
            
            //  returns HRESULT
            HRESULT hr = pD2DFactory->CreateHwndRenderTarget(
                        D2D1::RenderTargetProperties(),
                        D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)), &pRT
            );


            ID2D1SolidColorBrush* pBlackBrush = NULL;
            if (SUCCEEDED(hr))
            {
                pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &pBlackBrush); 
            }

            // int64_t startTime = GetTicks();
            
            while(isRunning)
            {


                MSG msg;
                while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
                {
                    if(msg.message == WM_QUIT)
                    {
                        isRunning = false;
                    }
                    TranslateMessage(&msg);
                    DispatchMessageA(&msg);
                }

                pRT->BeginDraw();
                pRT->Clear(D2D1::ColorF(D2D1::ColorF::Black));// "clears" the screen to a solid color

                pRT->DrawRectangle(D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom), pBlackBrush);


                pRT->DrawRectangle(D2D1::RectF(rc.left + 100.0f + xoff, rc.top + 100.0f+yoff, rc.right - 100.0f+xoff, rc.bottom - 100.0f+yoff), pBlackBrush);
                
                HRESULT hr = pRT->EndDraw();  
                // int64_t endTime = GetTicks();

                // startTime = endTime;

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