#ifndef  __MYGAME__
#define  __MYGAME__



struct Role
{
	int x;
	int y;
	int Movey,Ay;;
	int Show;//是否显示
	int Frame;//当前帧
	int FrameMax;//最大帧
};


struct MapObject
{
	int x,y;
	int Show;
	int UpNum;
	int DownNum;
};

typedef enum
{
	GAME_MENU,//菜单
	GAME_PRE,//
	GAME_IN,
	GAME_FAIL,
	GAME_SUCCESS,
	GAME_FALL
}GameState;

class	CMyGame
{
public:
	CMyGame();
	~CMyGame();
	

	void  ChangeFrame(int Time); 
	BOOL  KeyProcUp(WPARAM	wParam);
	BOOL  KeyProcDown(WPARAM  wParam);
	BOOL  LButton(LPARAM	lParam);
	int   GetState(){ return m_State; }
public:
	GameState	m_State;
	struct Role MyRole;
	struct  MapObject  MyObj[MAP_OBJECT];
	int iCurObj;//柱子游标
	int view;
	int iNum;
public:
	// 移动视图
	void MoveView(void);
public:
	void ShowObj(void);
public:
	void DrawStone(int x, int y,int Num);
public:
	int iDirection;
public:
	// 是否失败
	BOOL IsFail(void);
public:
	void Init(void);
};

#endif