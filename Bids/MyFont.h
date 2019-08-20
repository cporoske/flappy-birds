#ifndef  __MY__FONT__
#define  __MY__FONT__

class CMyFont
{
public:
	CMyFont();
	~CMyFont();

	BOOL  CreateFont(int nWidth,int nHeight,int Escape=0,int fnHeight = 100,
								DWORD fdwItalic=false,DWORD fdwUnderline=false,DWORD fdwStrikeOut = false,LPCTSTR lpszFace = "ËÎÌå");

	void  ShowXCenter(int y,char *Text);
	void  DrawText(int x,int y,char *Text);
	void  SetDevice(HDC hdest,int Width,int Height);
	void  SetMode(int i){ ::SetBkMode(m_hDest,i); }
	void  SetColor(COLORREF	 Color){ ::SetTextColor( m_hDest,Color); }

private:
	HFONT  m_Font;
	HDC m_hDest;
	int m_WinW,m_WinH;
};

CMyFont::CMyFont()
{
	m_Font = NULL;
}

CMyFont::~CMyFont()
{

}



BOOL  CMyFont::CreateFont(int nWidth,int nHeight,int Escape,int fnHeight,DWORD fdwItalic,DWORD fdwUnderline,DWORD fdwStrikeOut,LPCTSTR lpszFace)
{
	if( m_Font )
		::DeleteObject( m_Font);
	// CreateFontA(30, 30, 0, 800, 0, 0, 0, "¿¬Ìå");
	m_Font = ::CreateFont(nHeight,nWidth,Escape,0,fnHeight,fdwItalic,fdwUnderline,fdwStrikeOut,
								DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,lpszFace);
	if( !m_Font )
		return false;
	::SelectObject(m_hDest,m_Font);

	return true;
}

void  CMyFont::SetDevice(HDC hDest, int Width, int Height)
{
	m_hDest = hDest;
	m_WinW = Width;
	m_WinH = Height;
}

void  CMyFont::DrawText(int x, int y, char *Text)
{
	::TextOutA(m_hDest,x,y,Text,strlen(Text));
}

#endif
