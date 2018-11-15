#include <iostream>
#include <Windows.h>
#include "entitle.h"
using namespace std;

/* 输出整段文本内容 */
void PrintPara(const Link const link, PtrToNode start, PtrToNode end);
// 链表头结点link, 刷新段落的起始行start, 结束行end;

/* 输出一行文本内容 */
void PrintLine(const Link const link, PtrToNode line);
// 链表头结点link, 刷新的行line;

/* 向改行末尾输出一个字符 */
void PrintChar(const Link const link, PtrToNode line);
// 链表头结点link, 输出的字符所在行line;

void PrintPara(const Link const link, PtrToNode start, PtrToNode end)
{
	PtrToHeap ph;
	PtrToNode pn;
	//清屏
	system("cls");
	//重新输出
}
void PrintLine(const Link const link, PtrToNode line)
{
	//统计当前行字符数

	//'\r',输出‘ ’代替（处理刷新行字数较少的情况）

	//‘\r’，输出该行新的内容
}
int main(void)
{
	HANDLE hOut;
	CONSOLE_SCREEN_BUFFER_INFO bInfo; // 存储窗口信息
	COORD pos = { 0, 0 };
	// 获取标准输出设备句柄
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// 获取窗口信息
	GetConsoleScreenBufferInfo(hOut, &bInfo);
	printf("\n\nThe soul selects her own society\n");
	printf("Then shuts the door\n");
	printf("On her devine majority\n");
	printf("Obtrude no more\n\n");
	// 向窗口中填充字符以获得清屏的效果
	FillConsoleOutputCharacter(hOut, ' ', bInfo.dwSize.X * bInfo.dwSize.Y, pos, NULL);
	// 关闭标准输出设备句柄
	CloseHandle(hOut);
	return 0;
	system("pause");
	return 0;
}