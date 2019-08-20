// Bids.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Bids.h"
#include  "MyFont.h"
#include  "MyGame.h"

#define MAX_LOADSTRING 100

HWND  g_hWnd = NULL;
HDC	  hWindow,hScreen,Mem;
CMyGame  g_Game;
CMyBitmap	g_Role;
CMyBitmap  g_Obj;
CBkSky  g_Back;
CMyClock	g_Clock;//计时类
CMyFont  g_Font;
HBITMAP  hMap = NULL;


// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);



int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_BIDS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}
	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

	}

	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BIDS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject( BLACK_BRUSH );
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, APP_NAME, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
      APP_X, APP_Y,WIN_W, WIN_H, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
	
   g_hWnd = hWnd;
////////////////////////////////////////// 
   hWindow = GetDC( g_hWnd );
   hScreen = ::CreateCompatibleDC( hWindow );
   Mem = ::CreateCompatibleDC( hWindow );
//////////////////////////////////////////
   hMap = ::CreateCompatibleBitmap( hWindow,WIN_W * MAX_PAGE,WIN_H);
   ::SelectObject( hScreen,hMap);
   ::SelectObject( Mem,hMap);//初始化DC
	::ReleaseDC( hWnd,hWindow);
	
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   if( !g_Back.Init( BK_BITMAP,1,1) )
   {
	   MessageBox(hWnd,"图片加载错误","Error!",MB_OK);
   }
   g_Back.SetDevice(hScreen,Mem);

   if( !g_Role.Init( ROLE_BITMAP,6,2) )
   {
	   MessageBox(hWnd,"图片加载错误","Error!",MB_OK);
   }	
   g_Role.SetDevice(hScreen,Mem);
   g_Role.SetTrans( RGB(255,60,174));

   if( !g_Obj.Init( BKANI_BITMAP,16,2) )
   {
	   MessageBox(hWnd,"图片加载错误","Error!",MB_OK);
   }	
   g_Obj.SetDevice(hScreen,Mem);
   g_Obj.SetTrans( RGB(255,60,174));

   g_Clock.Begin(g_hWnd,30,4);
   g_Font.SetDevice(hScreen,WIN_W,WIN_H);
   g_Font.CreateFontA(30,30,0,1000,0,0,0,"黑体");
   g_Font.SetMode(TRANSPARENT);
   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		::SelectObject(hScreen,hMap);
		switch(g_Game.GetState() )
		{
		case GAME_MENU:
			g_Back.DrawRollSky();
			g_Font.SetColor(RGB(0,0,0));
			g_Font.DrawTextA(80,60,"Flappy - Birds");
			g_Font.SetColor(RGB(0,0,0));
			g_Font.DrawTextA(40,240,"请按下ENTER键开始!");
			break;
		case GAME_PRE:
			g_Back.DrawRollSky();
			g_Font.CreateFontA(20,20,0,800,0,0,0,"宋体");
			g_Font.SetColor(RGB(20,30,200));
			g_Font.DrawTextA(140,180,"单击鼠标左键开始!");
			g_Role.TransBit(g_Game.MyRole.x,g_Game.MyRole.y,g_Game.MyRole.Frame,1);
			break;
		case GAME_IN:
			g_Back.DrawRollSky();
			g_Game.ShowObj();
			g_Role.TransBit(g_Game.MyRole.x,g_Game.MyRole.y,g_Game.MyRole.Frame,1);
			break;
		case GAME_FALL:
			 g_Back.DrawRollSky();
			 g_Game.ShowObj();
			 g_Role.TransBit(g_Game.MyRole.x,g_Game.MyRole.y,g_Game.MyRole.Frame,1);
			 break;
		case GAME_FAIL:
			 g_Back.DrawRollSky();
			 g_Font.DrawTextA(g_Game.view + 70,200,"游戏失败，稍后重新开始!!!");
			 break;
		}

		::BitBlt(hdc,0,0,WIN_W,WIN_H,hScreen,g_Game.view,0,SRCCOPY);//
		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER:
		 switch( g_Game.GetState() )
		 {
		 case GAME_MENU:
			 g_Clock.DecCount();
			 g_Back.MoveRoll(BK_SPEED);
			 ::InvalidateRect(hWnd,NULL,FALSE);
			 break;
		 case GAME_PRE:
			 g_Clock.DecCount();
			 g_Back.MoveRoll(BK_SPEED);
			 if( 0 == g_Clock.iNum % ROLE_SPEED )
				 g_Game.MyRole.Frame = (++g_Game.MyRole.Frame) % g_Game.MyRole.FrameMax; 
			 ::InvalidateRect(hWnd,NULL,FALSE);
			 break;
		 case GAME_IN:
			 //移动背景
			 //更新柱子
			 //更新人物坐标
			 //通知绘制
			 g_Clock.DecCount();
			 if( 0 == g_Clock.iNum % ROLE_SPEED )
				 g_Game.MyRole.Frame = (++g_Game.MyRole.Frame) % g_Game.MyRole.FrameMax; 
			 g_Back.MoveRoll( BK_SPEED );
			 g_Game.ChangeFrame( g_Clock.iNum );
			 g_Game.MoveView();
			 if( g_Game.IsFail() )
			 {
				 g_Clock.ReStart( 2 );
				 g_Game.m_State = GAME_FALL;//下落状态
			 }
			 ::InvalidateRect( hWnd,NULL,FALSE);
			 break;
		 case GAME_FALL:
			 g_Game.MyRole.y += 5;
			 if( g_Game.MyRole.y > WIN_H )
				 g_Game.m_State = GAME_FAIL;
			 ::InvalidateRect(hWnd,NULL,FALSE);
			 break;
		 case GAME_FAIL:
			 if( g_Clock.DecCount() )
			 {
				 g_Game.Init();
				 g_Game.m_State = GAME_PRE;
			 }
			 ::InvalidateRect(hWnd,NULL,FALSE);
			  break;
		 }
		 break;
	case WM_KEYDOWN:
		g_Game.KeyProcDown(wParam);
		break;
	case WM_LBUTTONDOWN:
		g_Game.LButton(lParam);
		break;
	case WM_DESTROY:
		g_Clock.Destroy();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}