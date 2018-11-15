#include "entitle.h"

/*---------------------------�����ƶ�����---------------------------*/
enum Direction {left = 1, right, up ,down};
/* �����ƶ� */
void CursorMove(const Link const link, Position p, Direction dir, int steps);
//����ͷ���link,Ҫ�ƶ��Ĺ��p, �ƶ�����left,right,up,down�����ƶ�����steps;

/*--------------------------ˢ���������----------------------------*/
/* ��������ı����� */
void PrintPara(const Link const link, PtrToNode start, PtrToNode end);
// ����ͷ���link, ˢ�¶������ʼ��start, ������end;

/* ���һ���ı����� */
void PrintLine(const Link const link, PtrToNode line);
// ����ͷ���link, ˢ�µ���line;

/* ���һ���ַ� */
void PrintChar(const Link const link, PtrToNode line);
// ����ͷ���link, ������ַ�������line;

/*---------------------------��ʼ��ҳ��-------------------------------*/
/* ��ʼ���ı��༭���� */
void WindowsInit(void);	