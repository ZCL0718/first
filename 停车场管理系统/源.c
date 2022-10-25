//
// Create by Ep on 2019/6/28 
//
#include <stdio.h>
#include <stdlib.h> 
#include <windows.h>		
#include <string.h>			
#include <time.h>			

#define Price     0.1		 
#define MAX_STOP  5
#define MAX_PAVE  4   


typedef struct {
	int TimeIn;
	int TimeOut;
	char ct[50];
	char Lincense[10];
}Car;

typedef struct {
	Car Stop[MAX_STOP];
	int top;
}Stopping;

typedef struct {
	Car Pave[MAX_PAVE];
	int count;
	int front, rear;
}Pavement;

typedef struct {
	Car Let[MAX_STOP];
	int top;
}Buffer;

typedef struct {
	Car Wait[MAX_PAVE];
	int count;
	int front, rear;
}Waiting;

Stopping s;
Pavement p;
Buffer   b;
Car      c;
Waiting  w;
char     C[10];

void Car_Come();
void Car_Leave();
void Stop_To_Pave();
void Stop_To_Buff();
void Leave_Pavement();
void DisPlay();
void DisPlayPave();
void Welcome();
void SmallWelcome();
void Car_Leave_menu();
void Search();


void Car_Come() {
	printf("请输入即将停车的车牌号：");
	scanf("%s", &C);
	int i = s.top;
	while (i != -1) {
		if (0 == strcmp(s.Stop[i].Lincense, C)) {
			printf("输入有误，此汽车已存在！\n");
			return;
		}
		i--;
	}
	int k = MAX_PAVE;
	while (k != 0) {
		if (0 == strcmp(p.Pave[k].Lincense, C)) {
			printf("输入有误，此汽车已存在！\n");
			return;
		}
		k--;
	}
	if (s.top >= MAX_STOP - 1) {
		Stop_To_Pave();
	}
	else {
		time_t t1;
		long int t = time(&t1);
		char* t2;
		t2 = ctime(&t1);
		s.Stop[++s.top].TimeIn = t;
		strcpy(s.Stop[s.top].ct, t2);
		strcpy(s.Stop[s.top].Lincense, C);
		printf("牌照为%s的汽车停入停车位的%d车位，当前时间：%s\n", C, s.top + 1, t2);
	}
}


void Search() {
	printf("请输入要搜索的车牌号：\n");
	scanf("%s", &C);
	int i, j, k, flag = 0;
	time_t t1;
	long int t = time(&t1);
	if (s.top >= 0) {
		for (i = s.top; i >= 0; i--) {
			if (0 == strcmp(s.Stop[i].Lincense, C)) {
				printf("此汽车在停车场内，信息如下：\n");
				printf("\t车牌号\t\t停车位序\t当前所需支付金额\t进入时间\t\n");
				printf("\t%s\t第%d个\t\t%0.f元\t\t\t%s", s.Stop[i].Lincense, i + 1, Price * (t - s.Stop[i].TimeIn), s.Stop[i].ct);
				flag = 1;
				break;
			}
		}
	}
	if (flag == 0 && p.count > 0) {
		i = p.front, k = 1, j = p.rear;
		while (i != j) {
			if (0 == strcmp(p.Pave[i].Lincense, C)) {
				printf("此汽车在停便道上\n");
				printf("\t车牌号\t\t停车位序\n");
				printf("\t%s\t第%d个", p.Pave[i].Lincense, k);
				flag = 2;
				break;
			}
			i++;
			k++;
		}
	}
	if (0 == flag)
		printf("停车场内外不存在该汽车信息！\n");

}


void Car_Leave() {
	printf("请输入即将离开的车牌号：");
	scanf("%s", &C);
	int i, j, flag = 1, flag2 = 1;
	if (s.top >= 0) {
		for (i = s.top; i >= 0; i--) {
			flag = flag * strcmp(s.Stop[i].Lincense, C);
			i--;
		}
	}

	if (0 == flag) {
		Stop_To_Buff();
	}

	if (flag != 0 /*&& flag2 != 0*/)
		printf("停车场内没有该汽车的信息！\n");
}


void Leave_Pavement() {
	int i, j, flag = 0;
	printf("请输入即将离开的车牌号：");
	scanf("%s", &C);
	if (p.count <= 0) {
		printf("便道上不存在汽车!\n");
		return;
	}
	while (p.count > 0) {
		i = p.front;
		if (0 == strcmp(p.Pave[i].Lincense, C)) {
			break;
		}
		printf("牌照为%s的汽车暂时从便道进入临时便道\n", p.Pave[p.front].Lincense);
		strcpy(w.Wait[w.rear].Lincense, p.Pave[p.front].Lincense);
		p.front = (p.front + 1) % MAX_PAVE;
		w.rear = (w.rear + 1) % MAX_PAVE;
		w.count++;
		p.count--;
	}
	printf("\n牌照为%s的汽车从便道上开走，不收取任何费用！\n\n", p.Pave[i].Lincense);
	p.front = (p.front + 1) % MAX_PAVE;
	p.count--;
	while (p.count > 0) {
		printf("牌照为%s的汽车暂时从便道进入临时便道\n", p.Pave[p.front].Lincense);
		strcpy(w.Wait[w.rear].Lincense, p.Pave[p.front].Lincense);
		p.front = (p.front + 1) % MAX_PAVE;
		w.rear = (w.rear + 1) % MAX_PAVE;
		w.count++;
		p.count--;
	}
	while (w.count > 0) {
		printf("\n牌照为%s的汽车返回便道\n", w.Wait[w.front].Lincense);
		strcpy(p.Pave[p.rear].Lincense, w.Wait[w.front].Lincense);
		w.front = (w.front + 1) % MAX_PAVE;
		p.rear = (p.rear + 1) % MAX_PAVE;
		w.count--;
		p.count++;
	}
}


void Stop_To_Buff() {
	while (s.top >= 0) {
		if (0 == strcmp(s.Stop[s.top].Lincense, C)) {
			break;
		}
		strcpy(b.Let[b.top++].Lincense, s.Stop[s.top].Lincense);
		printf("牌照为%s的汽车暂时退出停车场\n", s.Stop[s.top--].Lincense);
	}
	printf("牌照为%s的汽车从停车场开走\n", s.Stop[s.top].Lincense);
	time_t t1;
	long int t = time(&t1);
	s.Stop[s.top].TimeOut = t;
	char* t2;
	t2 = ctime(&t1);
	printf("离开时间%s\n需付费%.0f元\n", t2, Price * (s.Stop[s.top].TimeOut - s.Stop[s.top].TimeIn));
	s.top--;
	while (b.top > 0) {
		strcpy(s.Stop[++s.top].Lincense, b.Let[--b.top].Lincense);
		printf("牌照为%s的汽车停回停车位%d车位\n", b.Let[b.top].Lincense, s.top + 1);
	}
	while (s.top < MAX_STOP - 1) {
		if (0 == p.count)
			break;
		else {
			strcpy(s.Stop[++s.top].Lincense, p.Pave[p.front].Lincense);
			printf("牌照为%s的汽车从便道中进入停车位的%d车位\n", p.Pave[p.front].Lincense, s.top + 1);
			time_t t1;
			long int t = time(&t1);
			char* t2;
			s.Stop[s.top].TimeIn = t;
			p.front = (p.front + 1) % MAX_PAVE;
			p.count--;
		}
	}
}

void Stop_To_Pave() {
	if (p.count > 0 && (p.front == (p.rear + 1) % MAX_PAVE))
		printf("便道已满，请下次再来！\n");
	else {
		strcpy(p.Pave[p.rear].Lincense, C);
		p.rear = (p.rear + 1) % MAX_PAVE;
		p.count++;
		printf("牌照为%s的汽车停入便道上\n", C);
	}
}


void DisPlay() {
	int i = s.top;
	if (-1 == i)
		printf("停车场目前为空\n");
	time_t t1;
	long int t = time(&t1);
	printf("\t车牌号\t\t停放时间\t当前所需支付金额\t停放位序\n");
	while (i != -1) {
		printf("\t%s\t%d分%d秒\t\t%.0f元\t\t\t第%d个\n", s.Stop[i].Lincense,
			(t - s.Stop[i].TimeIn) / 60, (t - s.Stop[i].TimeIn) % 60, Price * (t - s.Stop[i].TimeIn), i + 1);
		i--;
	}
}


void DisPlayPave() {
	int i = p.front;
	int k = 1;
	if (0 == p.count)
		printf("便道目前为空\n");
	printf("\t车牌号\t\t停放位序\n");
	while (i != p.rear && k <= p.count) {
		printf("\t%s\t第%d个\n", p.Pave[i].Lincense, k++);
		i = (i + 1) % MAX_PAVE;
	}
}


void Car_Leave_menu() {
	while (1) {
		system("cls");
		SmallWelcome();
		int i, cho;
		scanf("%d", &i);
		if (1 == i)  Car_Leave();
		if (2 == i)  Leave_Pavement();
		if (3 == i)  return;
		printf("\n返回请输入0\n");
	top:
		scanf("%d", &cho);
		if (0 == cho) {
			continue;
		}
		else {
			printf("您的输入有误，请重新输入\n");
			goto top;
		}
	}
}

void SmallWelcome() {
	printf("\t*******************目前停车场状况***********************\n");
	printf("\t停车场共有%d个车位,当前停车场共有%d辆车,等候区共有%d/%d辆车\n",
		MAX_STOP, s.top + 1, (p.rear + MAX_PAVE - p.front) % MAX_PAVE, MAX_PAVE - 1);
	printf("\t********************************************************\n");
	printf("\t---------Welcome to Ep's Car Parking next time----------\n");
	printf("\t*                                                      *\n");
	printf("\t*                   1.从停车场内驶出汽车               *\n");
	printf("\t*                   2.从便道上驶出汽车                 *\n");
	printf("\t*                   3.退出子管理系统                   *\n");
	printf("\t*请注意：从停车场内驶离的汽车按照%.0f元/分钟计费          *\n", 60 * Price);
	printf("\t*望周知：从便道上驶离的汽车不收取费用                  *\n");
	printf("\t*                                                      *\n");
	printf("\t*------------------------------------------------------*\n");
	printf("\t--------Press key(1/2/3) to continue the program--------\n");
}
void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Welcome() {
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("\t\t\t%s", asctime(timeinfo));
	HideCursor();
	printf("\t*******************目前停车场状况***********************\n");
	printf("\t停车场共有%d个车位,当前停车场共有%d辆车,等候区共有%d/%d辆车\n",
		MAX_STOP, s.top + 1, (p.rear + MAX_PAVE - p.front) % MAX_PAVE, MAX_PAVE - 1);
	printf("\t********************************************************\n");
	printf("\t--------------Welcome to Ep's Car Parking---------------\n");
	printf("\t*                                                      *\n");
	printf("\t*                   1.停车场停车信息显示               *\n");
	printf("\t*                   2.便道上停车信息显示               *\n");
	printf("\t*                   3.汽车到达停车场操作               *\n");
	printf("\t*                   4.汽车离去停车场操作               *\n");
	printf("\t*                   5.查找汽车功能                     *\n");
	printf("\t*                   6.退出管理系统                     *\n");
	printf("\t*收费标准：本停车场按照%.0f元/分钟计费，望周知            *\n", 60 * Price);
	printf("\t*                                                      *\n");
	printf("\t*------------------------------------------------------*\n");
	printf("\t---------Press key(1/2/3/4/5/6) to run program----------\n");

}

int main() {
	s.top = -1;
	b.top = 0;
	p.rear = 0;
	p.count = 0;
	p.front = 0;
	w.count = 0;
	w.front = 0;
	w.rear = 0;
	while (1) {
		system("color 0B");
		system("cls");
		Welcome();
		int i, cho;
		scanf("%d", &i);
		if (1 == i)  DisPlay();
		if (2 == i)  DisPlayPave();
		if (3 == i)  Car_Come();
		if (4 == i)  Car_Leave_menu();
		if (5 == i)  Search();
		if (6 == i) {
			printf("\n欢迎您再次使用本系统呦 ε=ε=ε=(~￣▽￣)~\n\n");
			break;
		}
		printf("\n返回请输入0\n");
	begin:
		scanf("%d", &cho);
		if (0 == cho) {
			continue;
		}
		else {
			printf("您的输入有误，请重新输入\n");
			goto begin;
		}
	}
	return 0;
}


