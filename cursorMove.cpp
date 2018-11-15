#include <iostream>
#include <Windows.h>
#include "entitle.h"
using namespace std;

void Text(void);
/* �����ƶ� */
extern void CursorMove(const Link const link, Position p, char dir, int steps);
//����ͷ���link,Ҫ�ƶ��Ĺ��p, �ƶ�����left,right,up,down�����ƶ�����steps;
static void CursorMove2(HANDLE handle, COORD cursor, int x, int y);

//##ȫ�ֱ���
HANDLE handle;
COORD cursor;

void CursorMove(const Link const link, Position p, char dir, int steps)
{
	//���㵱ǰ������ڵ�(x,y)  [���Ͻ���(0,0)]
	int x = p.ptrPos*HEAPLENGTH + p.strPos;		//��ǰ�������x
	int y = 0;
	PtrToNode q = link;
	while ((q->next != p.linkPos)&&(q->next)) {
		q = q->next;
		y++;
	}

	//�����ת
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
	//Խ�紦��
	if (x < 0 || y < 0 || x >= 1000 || y >= 1000) {
		cout << "����ƶ��Ƿ���" << endl;
		return;
	}
	CursorMove2(handle, cursor, x, y);
}

static void CursorMove2(HANDLE handle, COORD cursor, int x, int y)
{
	cursor.X = x;
	cursor.Y = y;
	//���ÿ���̨���λ��
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