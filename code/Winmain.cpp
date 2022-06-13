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
  
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red),   &brushes[0]); 
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &brushes[1]); 
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Pink),  &brushes[2]); 

    // load images here
    IWICImagingFactory *pIWICFactory = NULL; 
    
    CoInitializeEx(NULL, COINIT_MULTITHREADED); 
    CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pIWICFactory));    

    p /= "assets";
    loadBitmapFile(pIWICFactory, "player.png", &playerBitmap);
    loadBitmapFile(pIWICFactory, "enemy.png", &enemyBitmap);
    loadBitmapFile(pIWICFactory, "projectile1.png", &projectile1Bitmap);
    loadBitmapFile(pIWICFactory, "ENTERTOPLAY.png", &button1Bitmap);
    loadBitmapFile(pIWICFactory, "target.png", &targetBitmap);
    
    loadBitmapFile(pIWICFactory, "explosion1.png", &explosion1Bitmap);
    loadBitmapFile(pIWICFactory, "explosion2.png", &explosion2Bitmap);
    loadBitmapFile(pIWICFactory, "explosion3.png", &explosion3Bitmap);

    loadBitmapFile(pIWICFactory, "one_01.png", &one_01);
    loadBitmapFile(pIWICFactory, "one_02.png", &one_02);
    loadBitmapFile(pIWICFactory, "one_03.png", &one_03);
    loadBitmapFile(pIWICFactory, "one_04.png", &one_04);
}

/*  THESE KEY FUNCTIONS BELOW ARE NOT FINAL  */
static void handleKeyDown(WPARAM wParam)
{
    if(wParam == VK_RETURN) // hitting ENTER starts the game
    {
        scene->player->isActive = true;
        scene->enemyManager->isActive = true;
        screenState = SCENE;
    }

    if(wParam == VK_UP)    scene->player->goingUp    = true;
    if(wParam == VK_RIGHT) scene->player->goingRight = true;
    if(wParam == VK_DOWN)  scene->player->goingDown  = true;
    if(wParam == VK_LEFT)  scene->player->goingLeft  = true;    

    if(wParam == 77) m_Button->execute(scene); // M, main menu right now
    if(wParam == 80) p_Button->execute(scene); // P
    if(wParam == 69) e_Button->execute(scene); // E
    if(wParam == 81) q_Button->execute(scene); // Q
    if(wParam == 82) r_Button->execute(scene); // R
    if(wParam == 87) w_Button->execute(scene); // W
}

static void handleKeyUp(WPARAM wParam)
{
    if(wParam == VK_UP)    scene->player->goingUp    = false;
    if(wParam == VK_RIGHT) scene->player->goingRight = false;
    if(wParam == VK_DOWN)  scene->player->goingDown  = false;
    if(wParam == VK_LEFT)  scene->player->goingLeft  = false;
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
            Projectile proj(lParam, scene->player->x,  scene->player->y, projectile1Bitmap); // dont forget to free
            scene->projectiles.push_back(proj);
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
    const wchar_t CLASS_NAME[]  = L"Robo Spiders in Space";
    
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
        HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Robo Spiders in Space", 
                    WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 
                    CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);
        if(hwnd) 
        {
            isRunning = true;
            RECT rc;
            GetClientRect(hwnd, &rc);

            // this is a cpp17 feature, try to get rid of it
            p = std::filesystem::current_path().remove_filename();
            // wchar_t fnameBuffer[MAX_PATH];
            // GetModuleFileName(NULL, fnameBuffer, MAX_PATH);

            createResources(hwnd, &rc);
            std::array<ID2D1Bitmap*, 10> bitmaps = {enemyBitmap, playerBitmap, targetBitmap, 
                        explosion1Bitmap, explosion2Bitmap, explosion3Bitmap, 
                        one_01, one_02, one_03, one_04};

            menu = std::make_unique<Menu>();
            scene = std::make_unique<Scene>(GetTicks(), false, bitmaps);

            // initialize control defaults. 
            e_Button = new FireButton();
            m_Button = new PauseButton();
            p_Button = new PauseButton();
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
