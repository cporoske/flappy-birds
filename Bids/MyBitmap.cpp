#include  "stdafx.h"

void TransparentBlt2( HDC hdc0,int nX0,int nY0,int nW0,int nH0,HDC hdc1,int nX1,int nY1,int nW1,int nH1,UINT Tcol);


CMyBitmap::CMyBitmap()
{
	IsCreated = FALSE;//初始化比不是调用GetDC()
}

CMyBitmap::~CMyBitmap()
{
	if( IsCreated )
		ReleaseDC( m_hWnd,m_hDest);
	if( m_hSrc )
		::DeleteDC( m_hSrc );

}



BOOL  CMyBitmap::Init(char *FileName, int xNum, int yNum)
{
  int ret = -1;

  m_Bit = (HBITMAP)::LoadImage(NULL,FileName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
  if( NULL == m_Bit )
	  return FALSE;

  ::GetObjectA( m_Bit,sizeof(bm),&bm);

  m_xNum = xNum;
  m_yNum = yNum;

  m_Width = bm.bmWidth / m_xNum;
  m_Height = bm.bmHeight / m_yNum;

  return TRUE;
}


void  CMyBitmap::Draw(int x, int y, int idX, int idY)
{
	::SelectObject( m_hSrc,m_Bit);
	//普通绘制
	::BitBlt( m_hDest,x,y,m_Width,m_Height,m_hSrc,idX*m_Width,idY*m_Height,SRCCOPY);
}

void  CMyBitmap::Stretch(int x, int y, int idX, int idY, int Times)
{
	::SelectObject( m_hSrc,m_Bit);
	::StretchBlt( m_hDest,x,y,m_Width * Times,m_Height * Times,
						m_hSrc,idX * m_Width,idY * m_Height,m_Width,m_Height,SRCCOPY);
}

void  CMyBitmap::SetDevice(HDC hDest,HDC hSrc)
{
	m_hDest = hDest;

	m_hSrc = hSrc;
}

void  CMyBitmap::SetHwnd(HWND hWnd)
{ 
	m_hWnd = hWnd;

	m_hDest = GetDC( m_hWnd);

	m_hSrc = ::CreateCompatibleDC( m_hDest );

}

void  CMyBitmap::TransBit(int x, int y, int idX, int idY)
{
	::SelectObject( m_hSrc,m_Bit);
	::TransparentBlt2(m_hDest,x,y,m_Width,m_Height,m_hSrc,idX * m_Width,idY * m_Height,m_Width,m_Height,TransParent);
}

/*******************
*函数说明:让一个位图透明显示
*参数:Tcol将要屏蔽的颜色 RGB型
*返回:无返回值
*******************/
void TransparentBlt2( HDC hdc0,int nX0,int nY0,int nW0,int nH0,HDC hdc1,int nX1,int nY1,int nW1,int nH1,UINT Tcol)
{
	HBITMAP hBMP   =CreateCompatibleBitmap(hdc0,nW0, nH0);//创建兼容位图
	HBITMAP mBMP   =CreateBitmap(nW0,nH0,1,1,NULL);	//创建黑白位图,0代表黑,1代表白

	HDC		hDC    =CreateCompatibleDC(hdc0);//创建
	HDC		mDC    =CreateCompatibleDC(hdc0);

	HBITMAP oldBMP =(HBITMAP)SelectObject(hDC, hBMP);
	HBITMAP oldmBMP=(HBITMAP)SelectObject(mDC, mBMP);

	if (nW0 == nW1  && nH0 == nH1 )//
		BitBlt(hDC,0,0,nW0,nH0,hdc1,nX1,nY1,SRCCOPY);
	else
		StretchBlt(hDC,0,0,nW0,nH0,hdc1,nX1,nY1,nW1,nH1,SRCCOPY);

	SetBkColor(hDC, Tcol);
	BitBlt(mDC,0,0,nW0,nH0,hDC,0,0,SRCCOPY);
	SetBkColor(hDC, RGB(0,0,0));
	SetTextColor(hDC, RGB(255,255,255));
	BitBlt(hDC,0,0,nW0,nH0,mDC,0,0,SRCAND);
	SetBkColor(hdc0,RGB(255,255,255));
	SetTextColor(hdc0,RGB(0,0,0));

	BitBlt(hdc0,nX0,nY0,nW0,nH0,mDC,0,0,SRCAND);//遮罩层与背景图片与 保留图片黑色
	BitBlt(hdc0,nX0,nY0,nW0,nH0,hDC,0,0,SRCPAINT);//相或

	SelectObject(hDC, oldBMP);				
	DeleteDC(hDC);
	SelectObject(mDC, oldmBMP);
	DeleteDC(mDC);
	DeleteObject(hBMP);
	DeleteObject(mBMP);
}