#include "entitle.h"

/*---------------------------光标的移动操作---------------------------*/
enum Direction {left = 1, right, up ,down};
/* 光标的移动 */
void CursorMove(const Link const link, Position p, Direction dir, int steps);
//链表头结点link,要移动的光标p, 移动方向（left,right,up,down），移动步数steps;

/*--------------------------刷新输出操作----------------------------*/
/* 输出整段文本内容 */
void PrintPara(const Link const link, PtrToNode start, PtrToNode end);
// 链表头结点link, 刷新段落的起始行start, 结束行end;

/* 输出一行文本内容 */
void PrintLine(const Link const link, PtrToNode line);
// 链表头结点link, 刷新的行line;

/* 输出一个字符 */
void PrintChar(const Link const link, PtrToNode line);
// 链表头结点link, 输出的字符所在行line;

/*---------------------------初始化页面-------------------------------*/
/* 初始化文本编辑界面 */
void WindowsInit(void);	