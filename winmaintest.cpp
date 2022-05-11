
// #pragma comment(linker, "/subsystem:windows")

// #include <windows.h>
// #include <gl/gl.h>
// #include <gl/glu.h>

// HDC g_HDC;
// float angle = 0.0f;
// bool fullScreen = false;

// // void DrawCube(float xPos, float yPos, float zPos)
// // {
// //     glPushMatrix();
// //     glBegin(GL_POLYGON);
 
// //     /*      This is the top face*/
// //     glVertex3f(0.0f, 0.0f, 0.0f);
// //     glVertex3f(0.0f, 0.0f, -1.0f);
// //     glVertex3f(-1.0f, 0.0f, -1.0f);
// //     glVertex3f(-1.0f, 0.0f, 0.0f);
 
// //     /*      This is the front face*/
// //     glVertex3f(0.0f, 0.0f, 0.0f);
// //     glVertex3f(-1.0f, 0.0f, 0.0f);
// //     glVertex3f(-1.0f, -1.0f, 0.0f);
// //     glVertex3f(0.0f, -1.0f, 0.0f);
 
// //     /*      This is the right face*/
// //     glVertex3f(0.0f, 0.0f, 0.0f);
// //     glVertex3f(0.0f, -1.0f, 0.0f);
// //     glVertex3f(0.0f, -1.0f, -1.0f);
// //     glVertex3f(0.0f, 0.0f, -1.0f);
 
// //     /*      This is the left face*/
// //     glVertex3f(-1.0f, 0.0f, 0.0f);
// //     glVertex3f(-1.0f, 0.0f, -1.0f);
// //     glVertex3f(-1.0f, -1.0f, -1.0f);
// //     glVertex3f(-1.0f, -1.0f, 0.0f);
 
// //     /*      This is the bottom face*/
// //     glVertex3f(0.0f, 0.0f, 0.0f);
// //     glVertex3f(0.0f, -1.0f, -1.0f);
// //     glVertex3f(-1.0f, -1.0f, -1.0f);
// //     glVertex3f(-1.0f, -1.0f, 0.0f);
 
// //     /*      This is the back face*/
// //     glVertex3f(0.0f, 0.0f, 0.0f);
// //     glVertex3f(-1.0f, 0.0f, -1.0f);
// //     glVertex3f(-1.0f, -1.0f, -1.0f);
// //     glVertex3f(0.0f, -1.0f, -1.0f);
 
// //     glEnd();
// //     glPopMatrix();
// // }
 
 
// // void DrawHead(float xPos, float yPos, float zPos)
// // {
// //     glPushMatrix();
 
// //         /*      Sets color to white*/
// //         glColor3f(1.0f, 1.0f, 1.0f);
// //         glTranslatef(xPos, yPos, zPos);
 
// //         /*      Creates 2 x 2 x 2 cube*/
// //         glScalef(2.0f, 2.0f, 2.0f);
// //         DrawCube(0.0f, 0.0f, 0.0f);
 
// //     glPopMatrix();
// // }
 
 
// // void DrawRobot(float xPos, float yPos, float zPos)
// // {
// //     glPushMatrix();
// //     glTranslatef(xPos, yPos, zPos);
// //     DrawHead(1.0f, 2.0f, 0.0f);    
// //     glPopMatrix();
// // }
 
// // void Render()
// // {
// //     glEnable(GL_DEPTH_TEST);
// //     glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
// //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// //     glLoadIdentity();
 

// //     angle = angle + 1.0f;
 

// //     if (angle >= 360.0f)
// //     {
// //         angle = 0.0f;
// //     }
 
// //     glPushMatrix();
// //     glLoadIdentity();
 

// //     glTranslatef(0.0f, 0.0f, -30.0f);
// //     glRotatef(angle, 0.0f, 1.0f, 0.0f);
// //     DrawRobot(0.0f, 0.0f, 0.0f);
// //     glPopMatrix();
 
// //     glFlush();
 
// //     SwapBuffers(g_HDC);
// // }
 

// // void SetupPixelFormat(HDC hDC)
// // {

// //     int nPixelFormat;
 
// //     static PIXELFORMATDESCRIPTOR pfd = {
// //         sizeof(PIXELFORMATDESCRIPTOR),      //size of structure
// //         1,                      //default version
// //         PFD_DRAW_TO_WINDOW |            //window drawing support
// //         PFD_SUPPORT_OPENGL |            //opengl support
// //         PFD_DOUBLEBUFFER,               //double buffering support
// //         PFD_TYPE_RGBA,              //RGBA color mode
// //         32,                     //32 bit color mode
// //         0, 0, 0, 0, 0, 0,               //ignore color bits
// //         0,                      //no alpha buffer
// //         0,                      //ignore shift bit
// //         0,                      //no accumulation buffer
// //         0, 0, 0, 0,                 //ignore accumulation bits
// //         16,                     //16 bit z-buffer size
// //         0,                      //no stencil buffer
// //         0,                      //no aux buffer
// //         PFD_MAIN_PLANE,             //main drawing plane
// //         0,                      //reserved
// //         0, 0, 0 };                  //layer masks ignored
 
// //         /*      Choose best matching format*/
// //         nPixelFormat = ChoosePixelFormat(hDC, &pfd);
 
// //         /*      Set the pixel format to the device context*/
// //         SetPixelFormat(hDC, nPixelFormat, &pfd);
// // }
 
// /*      Windows Event Procedure Handler
// */
// LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
// {

//     static HGLRC hRC;
//     static HDC hDC;
 
//     int width, height;
 
//     switch(message)
//     {
//         case WM_CREATE: //window being created
 
//             hDC = GetDC(hwnd);  //get current windows device context
//             g_HDC = hDC;
//             //SetupPixelFormat(hDC); //call our pixel format setup function
 
//             /*      Create rendering context and make it current
//             */
//             hRC = wglCreateContext(hDC);
//             wglMakeCurrent(hDC, hRC);
 
//             return 0;
//             break;
 

 
//         case WM_SIZE:
 
//             /*      Retrieve width and height*/
//             height = HIWORD(lParam);
//             width = LOWORD(lParam);
 
//             /*      Don't want a divide by 0*/
//             if (height == 0)
//             {
//                 height = 1;
//             }
 
//             /*      Reset the viewport to new dimensions*/
//             glViewport(0, 0, width, height);
 
//             /*      Set current Matrix to projection*/
//             glMatrixMode(GL_PROJECTION);
//             glLoadIdentity(); //reset projection matrix
 
//             /*      Time to calculate aspect ratio of
//                 our window.
//             */
//             gluPerspective(54.0f, (GLfloat)width/(GLfloat)height, 1.0f, 1000.0f);
 
//             glMatrixMode(GL_MODELVIEW); //set modelview matrix
//             glLoadIdentity(); //reset modelview matrix
 
//             return 0;
//             break;
        
//         case WM_CLOSE:  //window is closing
 
//             /*      Deselect rendering context and delete it*/
//             wglMakeCurrent(hDC, NULL);
//             wglDeleteContext(hRC);
 
//             DestroyWindow(hwnd);
 
//             return 0;
//             break;

//         case WM_DESTROY:
        
//             PostQuitMessage(0);
//             return 0;
//             break;
        
 
//         default:
 
//             break;
//     }
 
//     return (DefWindowProc(hwnd, message, wParam, lParam));
// }
 
// int APIENTRY WinMain(HINSTANCE hInstance,
//              HINSTANCE hPrevInstance,
//              LPSTR     lpCmdLine,
//              int       nCmdShow)
// {
//     WNDCLASSEX windowClass; //window class
//     HWND    hwnd;           //window handle
//     MSG         msg;            //message
//     bool    done;           //flag for completion of app
//     DWORD   dwExStyle;          //window extended style
//     DWORD   dwStyle;        //window style
//     RECT    windowRect;
 
//     /*      Screen/display attributes*/
//     int width = 800;
//     int height = 600;
//     int bits = 32;
 
//     windowRect.left =(long)0;           //set left value to 0
//     windowRect.right =(long)width;  //set right value to requested width
//     windowRect.top =(long)0;        //set top value to 0
//     windowRect.bottom =(long)height;//set bottom value to requested height
 
//     /*      Fill out the window class structure*/
//     windowClass.cbSize              = sizeof(WNDCLASSEX);
//     windowClass.style               = CS_HREDRAW | CS_VREDRAW;
//     windowClass.lpfnWndProc     = WndProc;
//     windowClass.cbClsExtra      = 0;
//     windowClass.cbWndExtra      = 0;
//     windowClass.hInstance       = hInstance;
//     windowClass.hIcon               = LoadIcon(NULL, IDI_APPLICATION);
//     windowClass.hCursor             = LoadCursor(NULL, IDC_ARROW);
//     windowClass.hbrBackground       = NULL;
//     windowClass.lpszMenuName    = NULL;
//     windowClass.lpszClassName       = "MyClass";
//     windowClass.hIconSm             = LoadIcon(NULL, IDI_WINLOGO);
 
//     if(!RegisterClassEx(&windowClass))
//     {
//         return 0;
//     }
 
//     if(fullScreen)
//     {
//         DEVMODE dmScreenSettings;
//         memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
//         dmScreenSettings.dmSize = sizeof(dmScreenSettings);
//         dmScreenSettings.dmPelsWidth = width;   //screen width
//         dmScreenSettings.dmPelsHeight = height; //screen height
//         dmScreenSettings.dmBitsPerPel = bits;   //bits per pixel
//         dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
 
//         if(ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN != DISP_CHANGE_SUCCESSFUL))
//         {
//             MessageBox(NULL, "Display mode failed", NULL, MB_OK);
//             fullScreen = false;
//         }
//     }
 
//     if(fullScreen)
//     {
//         dwExStyle = WS_EX_APPWINDOW;    //window extended style
//         dwStyle = WS_POPUP;                 //windows style
//         ShowCursor(FALSE);                  //hide mouse pointer
//     }
 
//     else
//     {
//         dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; //window extended style
//         dwStyle = WS_OVERLAPPEDWINDOW;                  //windows style
//     }
 
//     AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);
 
//     /*      Class registerd, so now create our window*/
//     hwnd = CreateWindowEx(NULL, "MyClass",  //class name
//                           "OpenGL Robot",       //app name
//                           dwStyle |
//                           WS_CLIPCHILDREN |
//                           WS_CLIPSIBLINGS,
//                           0, 0,             //x and y coords
//                           windowRect.right - windowRect.left,
//                           windowRect.bottom - windowRect.top,//width, height
//                           NULL,         //handle to parent
//                           NULL,         //handle to menu
//                           hInstance,    //application instance
//                           NULL);        //no xtra params
 
//     if(!hwnd)
//     {
//         return 0;
//     }
 
//     ShowWindow(hwnd, SW_SHOW);      //display window
//     UpdateWindow(hwnd);             //update window
 
//     done = false;   //initialize loop condition variable
 
//     /*      Main message loop*/
//     while(!done)
//     {
//         PeekMessage(&msg, hwnd, NULL, NULL, PM_REMOVE);
 
//             if(msg.message == WM_QUIT) 
//             {
//                 done = true;
//             }
 
//             else
//             {
//                 //Render();
//                 TranslateMessage(&msg);
//                 DispatchMessage(&msg);
//             }
//     }
 
//     if(fullScreen)
//     {
//         ChangeDisplaySettings(NULL, 0);
//         ShowCursor(TRUE);
//     }
 
//     return msg.wParam;
 
// }



#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Sample Window Class";
    
    WNDCLASS wc = { };

    wc.style = 0;
    wc.lpfnWndProc   = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance     = hInstance;
    wc.hIcon = 0;
    wc.hCursor = 0;
    wc.hbrBackground = 0;
    wc.lpszMenuName = 0;
    wc.lpszClassName = CLASS_NAME;


  
     
      
      



    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

            EndPaint(hwnd, &ps);
        }
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}