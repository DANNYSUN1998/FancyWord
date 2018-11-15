#include <iostream>
#include <Windows.h>
#include "entitle.h"
using namespace std;

void Text(void);
/* 光标的移动 */
extern void CursorMove(const Link const link, Position p, char dir, int steps);
//链表头结点link,要移动的光标p, 移动方向（left,right,up,down），移动步数steps;
static void CursorMove2(HANDLE handle, COORD cursor, int x, int y);

//##全局变量
HANDLE handle;
COORD cursor;

void CursorMove(const Link const link, Position p, char dir, int steps)
{
	//计算当前光标所在的(x,y)  [左上角是(0,0)]
	int x = p.ptrPos*HEAPLENGTH + p.strPos;		//当前光标所在x
	int y = 0;
	PtrToNode q = link;
	while ((q->next != p.linkPos)&&(q->next)) {
		q = q->next;
		y++;
	}

	//光标跳转
	switch (dir) {
	case 'l':		//left
		x = x - steps;
		break;
	case 'r':		//right
		x = x + steps;
		break;
	case 'u':		//up
		y = y - steps;
		break;
	case 'd':		//down
		y = y + steps;
		break;
	default:
		break;
	}//switch
	//越界处理
	if (x < 0 || y < 0 || x >= 1000 || y >= 1000) {
		cout << "光标移动非法！" << endl;
		return;
	}
	CursorMove2(handle, cursor, x, y);
}

static void CursorMove2(HANDLE handle, COORD cursor, int x, int y)
{
	cursor.X = x;
	cursor.Y = y;
	//设置控制台光标位置
	SetConsoleCursorPosition(handle, cursor);

}

void Test(void)
{
	Link link = new Node();
	PtrToNode p = new Node();
	link->next = p;
	p->next = NULL;
	p->ptrRear = 0;
	p->strRear = 2;
	//row=1,col=3;
	Position pos;
	pos.linkPos = p;
	pos.ptrPos = 0;
	pos.strPos = 0;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "111";
	CursorMove(link, pos, 'r', 1);
	cout << '2';
	system("pause");
	delete(link);
	delete(p);
}


int main(void)
{
	Test();

	return 0;
}