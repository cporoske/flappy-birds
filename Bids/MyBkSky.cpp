#include  "stdafx.h"

CBkSky::CBkSky()
{
	xSplider = 0;
	xPos = 0;
}

CBkSky::~CBkSky()
{
}

void   CBkSky::DrawRollSky()
{
	SelectObject( m_hSrc,m_Bit);

	::BitBlt( m_hDest,xPos,0,(m_Width-xSplider),m_Height,m_hSrc,xSplider,0,SRCCOPY);

	::BitBlt( m_hDest,xPos + (m_Width-xSplider),0,xSplider,m_Height,m_hSrc,0,0,SRCCOPY);
}


void  CBkSky::MoveRoll(int Speed)
{
	xSplider += Speed;

	if( xSplider > m_Width )
		xSplider = 0;

}

