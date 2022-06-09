#include "headers/Winmain.h"

static inline int64_t GetTicks()
{
    LARGE_INTEGER ticks;
    if (!QueryPerformanceCounter(&ticks))
    {
        // log error
    }
    return ticks.QuadPart;
}

static HRESULT LoadBitmapFromFile(IWICImagingFactory *pIWICFactory, LPCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap **ppBitmap)
{
    IWICBitmapDecoder *pDecoder = NULL;
    IWICBitmapFrameDecode *pSource = NULL;
    // IWICStream *pStream = NULL;
    IWICFormatConverter *pConverter = NULL;
    // IWICBitmapScaler *pScaler = NULL;

    HRESULT hr = pIWICFactory->CreateDecoderFromFilename(uri, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);

    if (SUCCEEDED(hr))
    {
        hr = pDecoder->GetFrame(0, &pSource);
    }

    if (SUCCEEDED(hr))
    {
        hr = pIWICFactory->CreateFormatConverter(&pConverter);
    }

    if (SUCCEEDED(hr))
    {
        hr = pConverter->Initialize(pSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
    }
    
    if (SUCCEEDED(hr))
    {
        hr = renderTarget->CreateBitmapFromWicBitmap(pConverter, ppBitmap);
    }
    return hr;
}

static void loadBitmapFile(IWICImagingFactory* pIWICFactory, std::filesystem::path bitmapFileName, ID2D1Bitmap **tBitmap)
{
    p /= bitmapFileName;
    LoadBitmapFromFile(pIWICFactory, p.c_str(), 20, 20, tBitmap);  
    p.remove_filename();
}

static void createResources(HWND hwnd, RECT* rc)
{
    ID2D1Factory* pD2DFactory = NULL;

    // both lines below return HRESULT, I should make sure they succeez
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
    D2D1_SIZE_U clientSize = D2D1::SizeU(rc->right - rc->left, rc->bottom - rc->top);
    pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, clientSize), &renderTarget);
  
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &brushes[0]); 
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &brushes[1]); 
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Pink), &brushes[2]); 

    // load images here
    IWICImagingFactory *pIWICFactory = NULL; 
    playerBitmap = NULL;
    enemyBitmap = NULL;
    projectile1Bitmap = NULL;
    
    CoInitializeEx(NULL, COINIT_MULTITHREADED); 
    HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pIWICFactory));    

    p /= "assets";
    loadBitmapFile(pIWICFactory, "player.png", &playerBitmap);
    loadBitmapFile(pIWICFactory, "enemy.png", &enemyBitmap);
    loadBitmapFile(pIWICFactory, "projectile1.png", &projectile1Bitmap);
    loadBitmapFile(pIWICFactory, "ENTERTOPLAY.png", &button1Bitmap);
    loadBitmapFile(pIWICFactory, "target.png", &targetBitmap);
    loadBitmapFile(pIWICFactory, "explosion1.png", &explosion1Bitmap);
    loadBitmapFile(pIWICFactory, "explosion2.png", &explosion2Bitmap);
    loadBitmapFile(pIWICFactory, "explosion3.png", &explosion3Bitmap);
}

/*  THESE KEY FUNCTIONS BELOW ARE NOT FINAL  */
static void handleKeyDown(WPARAM wParam)
{
    OutputDebugStringA("key down\n");
    
    if(wParam == VK_RETURN) // hitting ENTER starts the game
    {
        // put this in a constructor  or something, this is poor form
        screenState = SCENE;
        scene->player->isActive = true;

        scene->player->x = 400;
        scene->player->y = 400;

        scene->player->width = 20;
        scene->player->height = 20;

        scene->player->speedScale = 1.0f;
        
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
    else if(wParam == 77)// M key, or menu button
    {
        // screenState = MAINMENU;
        q_Button->execute(scene->player.get());// can be swapped out
    }
    else if(wParam == 69)//E
    {
        e_Button->execute(scene->player.get());
    }
    else if(wParam == 81)//Q
    {
        q_Button->execute(scene->player.get());
    }
    else if(wParam == 82)//R
    {
        r_Button->execute(scene->player.get());
    }
    else if(wParam == 87)//W
    {
        w_Button->execute(scene->player.get());
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
            Projectile* proj = new Projectile(lParam, scene->player->x,  scene->player->y, projectile1Bitmap); // dont forget to free
            scene->projectiles.push_back(*proj);
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
    wc.hInstance = hInstance;
    wc.hIcon = 0;
    wc.hCursor = 0;
    wc.hbrBackground = 0;
    wc.lpszMenuName = 0;
    wc.lpszClassName = CLASS_NAME;

    if(RegisterClass(&wc))
    {
        HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Windows Program", 
                    WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 
                    CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);
        if(hwnd) 
        {
            isRunning = true;
            RECT rc;
            GetClientRect(hwnd, &rc);

            p = std::filesystem::current_path().remove_filename();

            wchar_t fnameBuffer[MAX_PATH];
            GetModuleFileName(NULL, fnameBuffer, MAX_PATH);

            createResources(hwnd, &rc);

            // clean up these lines below.
            menu = std::make_unique<Menu>(&rc, hwnd);
            scene = std::make_unique<Scene>(&rc, hwnd);
            scene->assignBitmaps(playerBitmap, enemyBitmap, targetBitmap);
            
            scene->animator->explosionBitmaps[0] = explosion1Bitmap;
            scene->animator->explosionBitmaps[1] = explosion2Bitmap;
            scene->animator->explosionBitmaps[2] = explosion3Bitmap;
            
            // initialize controls
            e_Button = new FireButton();
            q_Button = new FireButton();
            r_Button = new FireButton();            
            w_Button = new FireButton();

            screenState = MAINMENU;
            int64_t startTime = GetTicks();
            int64_t endTime;
            
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

                endTime = GetTicks();

                switch(screenState)
                {
                    case MAINMENU:
                    {
                        menu->renderState(&rc, hwnd, renderTarget, brushes, button1Bitmap);
                        break;
                    }
                    case SCENE:
                    {
                        scene->updateState(hwnd, endTime, startTime);
                        scene->renderState(&rc, hwnd, renderTarget, brushes);
                        break;
                    }
                    case PAUSEMENU:
                    {
                        scene->renderState(&rc, hwnd, renderTarget, brushes);
                        break;
                    }
                    default:
                    {
                    }
                }
                startTime = endTime;
            }
            // game is no longer running here
        }
    }
    return 0;
}

