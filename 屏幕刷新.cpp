#include <iostream>
#include <Windows.h>
#include "entitle.h"
using namespace std;

/* ��������ı����� */
void PrintPara(const Link const link, PtrToNode start, PtrToNode end);
// ����ͷ���link, ˢ�¶������ʼ��start, ������end;

/* ���һ���ı����� */
void PrintLine(const Link const link, PtrToNode line);
// ����ͷ���link, ˢ�µ���line;

/* �����ĩβ���һ���ַ� */
void PrintChar(const Link const link, PtrToNode line);
// ����ͷ���link, ������ַ�������line;

void PrintPara(const Link const link, PtrToNode start, PtrToNode end)
{
	PtrToHeap ph;
	PtrToNode pn;
	//����
	system("cls");
	//�������
}
void PrintLine(const Link const link, PtrToNode line)
{
	//ͳ�Ƶ�ǰ���ַ���

	//'\r',����� �����棨����ˢ�����������ٵ������

	//��\r������������µ�����
}
int main(void)
{
	HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO bInfo; // �洢������Ϣ
	COORD pos = { 0, 0 };
	// ��ȡ��׼����豸���
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// ��ȡ������Ϣ
	GetConsoleScreenBufferInfo(hOut, &bInfo);
	printf("\n\nThe soul selects her own society\n");
	printf("Then shuts the door\n");
	printf("On her devine majority\n");
	printf("Obtrude no more\n\n");
	// �򴰿�������ַ��Ի��������Ч��
	FillConsoleOutputCharacter(hOut, ' ', bInfo.dwSize.X * bInfo.dwSize.Y, pos, NULL);
	// �رձ�׼����豸���
	CloseHandle(hOut);
	return 0;
	system("pause");
	return 0;
}