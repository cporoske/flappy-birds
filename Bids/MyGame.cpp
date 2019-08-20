
#include  "stdafx.h"
#include  "MyGame.h"
#include  "stdio.h"
#include  "stdlib.h"
#include  "time.h"



extern CBkSky g_Back;
extern CMyBitmap g_Obj;



CMyGame::CMyGame()
: iDirection(0)
{
	srand( time(0));
	m_State = GAME_MENU;
	iNum = (WIN_H - DISTANCE) / 32 - 2;//(-2) 是 柱子头
	Init();
}

CMyGame::~CMyGame()
{

}

BOOL  CMyGame::KeyProcDown(WPARAM wParam)
{
	switch(m_State)
	{
	case GAME_MENU:
		switch(wParam)
		{
		case  VK_RETURN:
			  m_State = GAME_PRE;
		break;
		}
		break;
	}

	return true;
}

BOOL CMyGame::KeyProcUp(WPARAM wParam)
{

	return false;
}

void  CMyGame::ChangeFrame(int Time)
{
	int i;
	int temp;

	if( iCurObj < MAP_OBJECT - 1 )
	{
		for( ;iCurObj < MAP_OBJECT;iCurObj++)
		{
			temp = rand() % iNum + 1 - 1 ;
			MyObj[iCurObj].UpNum = temp;
			MyObj[iCurObj].DownNum = iNum - temp;
			if( iCurObj == 0 )
			{
				MyObj[iCurObj].x = 800;
			}
			else
				MyObj[iCurObj].x =MyObj[iCurObj-1].x + 64*3;
			MyObj[iCurObj].y = MyObj[iCurObj].UpNum*32 + 32;
		}
	}

	for(i=0;i<MAP_OBJECT;i++)
	{
		if( MyObj[i].x + 32 < view )
		{
			MyObj[i].Show = FALSE;
			for(int j = i;j<MAP_OBJECT-1;j++)
			{
				MyObj[j] = MyObj[j+1];
			}
			iCurObj--;
		}
		else if( MyObj[i].x < view+WIN_W+100 )
			MyObj[i].Show = 1;
	}

}

BOOL	CMyGame::LButton(LPARAM lParam)
{
	int xPos = LOWORD( lParam),yPos = HIWORD(lParam);
	
	switch(this->m_State)
	{
	case GAME_PRE:
		this->m_State = GAME_IN;
		iDirection = 1;
		MyRole.Movey = -ROLE_MOVESPEED;
		MyRole.Ay = ROLE_A;
		break;
	case GAME_IN:
		iDirection = 1;
		MyRole.Movey = -ROLE_MOVESPEED;
		MyRole.Ay = ROLE_A;
		break;
	}
	
	return true;
}
// 移动视图
void CMyGame::MoveView(void)
{
	view+=4;
	g_Back.SetPos( view );
	
	MyRole.x += 4;//跟随试图

	if( iDirection )//如果上升
	{
		MyRole.y += MyRole.Movey;
		MyRole.Movey += MyRole.Ay;

		if( MyRole.Movey> 0 )
		{
			iDirection = 0;
			MyRole.Movey = ROLE_MOVESPEED;
			MyRole.Ay = ROLE_A;
		}
	}

	else if( 0 == iDirection )
	{
		MyRole.y += MyRole.Movey-10;
		MyRole.Movey += MyRole.Ay-1;
		
	}

}

void CMyGame::ShowObj(void)
{

	int i;
	int temp;

	for( i = 0;i<MAP_OBJECT;i++)
	{
		if( MyObj[i].Show )
		{
			DrawStone(MyObj[i].x,0,MyObj[i].UpNum);//绘制上面的柱子
			temp = MyObj[i].UpNum * 32;//计算坐标
			g_Obj.TransBit(MyObj[i].x,temp,0,1);//绘制柱子顶
			g_Obj.TransBit(MyObj[i].x+32,temp,1,1);
			//计算坐标,32是柱子头,64是空地
			temp += 32+DISTANCE;
			//绘制下面柱子头
			g_Obj.TransBit(MyObj[i].x,temp,0,1);
			g_Obj.TransBit(MyObj[i].x+32,temp,1,1);
			temp += 32;
			DrawStone(MyObj[i].x,temp,MyObj[i].DownNum);
		}
	}

}

void CMyGame::DrawStone(int x, int y,int Num)
{
	int i;
	int Temp = y;

	for( i = 0;i<Num;i++)
	{
		g_Obj.TransBit(x,Temp,14,0);
		g_Obj.TransBit(x+32,Temp,15,0);
		Temp += 32;
	}

}

// 是否失败
BOOL CMyGame::IsFail(void)
{	
	if( MyRole.y > WIN_H )
	{
		return TRUE;
	}

	int i;

	for( i =0;i<MAP_OBJECT;i++)
	{
		if( MyObj[i].Show )//在屏幕范围内
		{
			if( RECT_HIT_RECT(MyRole.x,MyRole.y,28,48,MyObj[i].x,0,64,MyObj[i].y)  ||  RECT_HIT_RECT(MyRole.x,MyRole.y,28,48,MyObj[i].x,MyObj[i].y+DISTANCE,64,WIN_H -MyObj[i].y - DISTANCE) )
			{
				return TRUE;
			}
		}
	}

	return false;
}

void CMyGame::Init(void)
{
	g_Back.SetPos(0);
	view = 0;
	MyRole.x = 200;
	MyRole.y = 200;
	MyRole.Frame = 0;
	MyRole.FrameMax = 2;
	MyRole.Show = 1;
	MyRole.Movey = 0;
	MyRole.Ay = 0;
	this->iCurObj  = 0;
	view = 0;
	memset(MyObj,NULL,sizeof(MyObj));

}
