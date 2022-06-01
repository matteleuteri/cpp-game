#include "Scene.h"


Scene::Scene(HWND hwnd, RECT* rc)
{
    projectiles = {};
    player = new Player();// dont forget to free
    createResources(hwnd, rc);
}
Scene::~Scene()
{
    delete player;
}
// template <class T> void Scene::SafeRelease(T **ppT)
// {
//     if (*ppT)
//     {
//         (*ppT)->Release();
//         *ppT = NULL;
//     }
// }
void Scene::updateProjectiles(int64_t timeElapsed)
{
    for(Projectile* proj : projectiles)
    {
        proj->x += (proj->direction[0]*10);
        proj->y += (proj->direction[1]*10);
        if(proj->y <= 0 || proj->y >= 720 || proj->x <= 0 || proj->x >= 1280)
        {
            // delete proj;
            proj->isActive = false;
        }
    }
}

void Scene::updateState(int64_t timeElapsed)
{
    player->updatePlayer(timeElapsed);
    updateProjectiles(timeElapsed);
}


void Scene::renderState(RECT* rc)
{
    renderTarget->BeginDraw();
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0,0));

    // draw black background
    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

    // draw border of window
    renderTarget->DrawRectangle(D2D1::RectF(rc->left, rc->top, rc->right, rc->bottom), brushes[0]);

    // darw border of playable area
    renderTarget->DrawRectangle(D2D1::RectF(rc->left + 100.0f, rc->top + 100.0f, rc->right - 100.0f, rc->bottom - 100.0f), brushes[1]);
               

    // draw grid lines:
    for(int i = 0; i < rc->right; i++)
    {
        if(i % 32 == 0)
            renderTarget->DrawLine(D2D1::Point2F((float)i, 0.0f), D2D1::Point2F((float)i, rc->bottom), brushes[0], 2.5f);
    }
    for(int i = 0; i < rc->bottom; i++)
    {
        if(i % 32 == 0)
            renderTarget->DrawLine(D2D1::Point2F(0.0f, (float)i), D2D1::Point2F(rc->right, (float)i), brushes[0], 2.5f);
    }



    // draw player
    // renderTarget->FillRectangle(D2D1::RectF(player->x, player->y, player->x + player->width, player->y + player->height), m_pBitmapBrush);
    D2D1_SIZE_F size = ppBitmap->GetSize();
    D2D1_POINT_2F upperLeftCorner = D2D1::Point2F(player->x, player->y);

renderTarget->DrawBitmap(
            ppBitmap,
            D2D1::RectF(
                upperLeftCorner.x,
                upperLeftCorner.y,
                upperLeftCorner.x + size.width,
                upperLeftCorner.y + size.height)
            );



    // draw projectiles
    for(Projectile* p : projectiles)
    {
        renderTarget->FillRectangle(D2D1::RectF(p->x, p->y, p->x + 10, p->y+10), brushes[0]);        
    }
    
    renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(player->x, player->y));
    renderTarget->FillGeometry(playerGeometry, brushes[0]);
    
    HRESULT hr = renderTarget->EndDraw();  
}



void Scene::createResources(HWND hwnd, RECT* rc)
{
    ID2D1Factory* pD2DFactory = NULL;

    // both lines below return HRESULT, I should make sure they succeez
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
    D2D1_SIZE_U clientSize = D2D1::SizeU(rc->right - rc->left, rc->bottom - rc->top);
    pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, clientSize), &renderTarget);
  
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &brushes[0]); 
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &brushes[1]); 
    renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Pink), &brushes[2]); 


    IWICImagingFactory *pIWICFactory = NULL; 
    
    CoInitializeEx(NULL, COINIT_MULTITHREADED); 
    HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pIWICFactory));    


    LPCWSTR uri = L"C:\\Users\\meleu\\OneDrive\\Desktop\\cpp-game\\code\\player.png"; // Image to be decoded

    hr = LoadBitmapFromFile(pIWICFactory, uri, 0, 0, &ppBitmap);



    // player's geomery is defined here for now 
    pD2DFactory->CreatePathGeometry(&playerGeometry); // is this the right parameter
    ID2D1GeometrySink *pSink = NULL;
    playerGeometry->Open(&pSink);

    pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
    pSink->BeginFigure(D2D1::Point2F(0,0), D2D1_FIGURE_BEGIN_FILLED);
    D2D1_POINT_2F points[6] = 
    {
        D2D1::Point2F(-10, -10),
        D2D1::Point2F(0, -7.5),
        D2D1::Point2F(10, -10),
        D2D1::Point2F(10, 10),
        D2D1::Point2F(-10, 10), 
        D2D1::Point2F(-10, -10),
    };
    pSink->AddLines(points, ARRAYSIZE(points));
    pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
    pSink->Close();

}





HRESULT Scene::LoadBitmapFromFile(IWICImagingFactory *pIWICFactory, LPCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap **ppBitmap)
{
    IWICBitmapDecoder *pDecoder = NULL;
    IWICBitmapFrameDecode *pSource = NULL;
    IWICStream *pStream = NULL;
    IWICFormatConverter *pConverter = NULL;
    IWICBitmapScaler *pScaler = NULL;


    // why is this failing
    HRESULT hr = pIWICFactory->CreateDecoderFromFilename(uri, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
    if (SUCCEEDED(hr))
    {
        // Create the initial frame.
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
        // this is reading invalid memory
        hr = renderTarget->CreateBitmapFromWicBitmap(pConverter, ppBitmap);
    }
    else
    {
        OutputDebugString("no 4\n");        
    }
    return hr;
}

