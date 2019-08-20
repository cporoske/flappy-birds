#ifndef   __MY_BKSKY__
#define   __MY_BKSKY__

class  CBkSky:public CMyBitmap
{
public:
	CBkSky();
	~CBkSky();

	void  SetPos(int i)
	{	xPos = i;	}
	void  DrawRollSky();

	void  MoveRoll(int Speed);
protected:
	int  xSplider;
};

#endif