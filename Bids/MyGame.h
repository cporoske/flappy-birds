#ifndef  __MYGAME__
#define  __MYGAME__



struct Role
{
	int x;
	int y;
	int Movey,Ay;;
	int Show;//�Ƿ���ʾ
	int Frame;//��ǰ֡
	int FrameMax;//���֡
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
	GAME_MENU,//�˵�
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
	int iCurObj;//�����α�
	int view;
	int iNum;
public:
	// �ƶ���ͼ
	void MoveView(void);
public:
	void ShowObj(void);
public:
	void DrawStone(int x, int y,int Num);
public:
	int iDirection;
public:
	// �Ƿ�ʧ��
	BOOL IsFail(void);
public:
	void Init(void);
};

#endif