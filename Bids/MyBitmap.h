#ifndef  __MY__BITMAP_H_
#define  __MY__BITMAP_H_

class  CMyBitmap
{
public:
	CMyBitmap();
	~CMyBitmap();

	//Init
	BOOL  Init(char *FileName,int xNum,int yNum);
	//
	
	//绘制操作
	void  Draw(int x,int y,int idX = 0,int idY = 0);
	void  Stretch(int x,int y,int idX = 0,int idY = 0,int Times = 0/*代表扩大倍数*/);
	void  TransBit(int x,int y,int idX = 0,int idY = 0);
	//设备设置操作
	void  SetDevice(HDC hDest,HDC hSrc);
	void  SetHwnd(HWND hWnd);
	void  SetPos(int i,int j){ xPos = i;yPos = j;}
	void  SetTrans(DWORD  i){ TransParent = i; }

protected:
	//DC,
	//目的DC,临时DC
	DWORD	TransParent;
	int xPos,yPos;
	HDC  m_hDest;
	HDC  m_hSrc;
	HWND  m_hWnd;
	HBITMAP  m_Bit;
	BITMAP bm;
	int m_xNum,m_yNum;
	int m_Width,m_Height;
	BOOL  IsCreated;
};

#endif
