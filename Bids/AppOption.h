//--AppOption.h
//���ó���ĸ������

#ifndef  __APPOPTION_H__
#define  __APPOPTION_H__

//��������
#define  APP_NAME	"Flapy - Birds"

//���򴰿ڴ�С
//��ȣ��߶�
#define  WIN_W	640
#define  WIN_H	480

//�����ʼ����ʾ����
#define  APP_X  200
#define  APP_Y	150

//����ĸ���ͼƬ·��
//����,����,������Ʒ
#define  BK_BITMAP  "..\\res\\����D.BMP"
#define  ROLE_BITMAP	"..\\res\\Role.bmp"
#define	 BKANI_BITMAP  "..\\res\\tile.bmp"

#define  MAX_PAGE  10
#define  TIME_ELAPSE  40
//��Ʒ�ƶ��ٶ�
#define  BK_SPEED	3
#define  ROLE_SPEED	3
#define  ROLE_MOVESPEED	10
#define  ROLE_A  2

#define  MAP_OBJECT  30
#define  DISTANCE    32*4

#define RECT_HIT_RECT(x,y,w,h,x1,y1,w1,h1) ( (y)+(h)>(y1) && (y)<(y1)+(h1) \
                                        && (x)+(w)>(x1) && (x)<(x1)+(w1) )


#endif
