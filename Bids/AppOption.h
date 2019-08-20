//--AppOption.h
//设置程序的各项参数

#ifndef  __APPOPTION_H__
#define  __APPOPTION_H__

//程序名称
#define  APP_NAME	"Flapy - Birds"

//程序窗口大小
//宽度，高度
#define  WIN_W	640
#define  WIN_H	480

//程序初始化显示坐标
#define  APP_X  200
#define  APP_Y	150

//程序的各个图片路径
//背景,人物,背景物品
#define  BK_BITMAP  "..\\res\\地面D.BMP"
#define  ROLE_BITMAP	"..\\res\\Role.bmp"
#define	 BKANI_BITMAP  "..\\res\\tile.bmp"

#define  MAX_PAGE  10
#define  TIME_ELAPSE  40
//物品移动速度
#define  BK_SPEED	3
#define  ROLE_SPEED	3
#define  ROLE_MOVESPEED	10
#define  ROLE_A  2

#define  MAP_OBJECT  30
#define  DISTANCE    32*4

#define RECT_HIT_RECT(x,y,w,h,x1,y1,w1,h1) ( (y)+(h)>(y1) && (y)<(y1)+(h1) \
                                        && (x)+(w)>(x1) && (x)<(x1)+(w1) )


#endif
