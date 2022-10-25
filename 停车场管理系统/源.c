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
	printf("�����뼴��ͣ���ĳ��ƺţ�");
	scanf("%s", &C);
	int i = s.top;
	while (i != -1) {
		if (0 == strcmp(s.Stop[i].Lincense, C)) {
			printf("�������󣬴������Ѵ��ڣ�\n");
			return;
		}
		i--;
	}
	int k = MAX_PAVE;
	while (k != 0) {
		if (0 == strcmp(p.Pave[k].Lincense, C)) {
			printf("�������󣬴������Ѵ��ڣ�\n");
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
		printf("����Ϊ%s������ͣ��ͣ��λ��%d��λ����ǰʱ�䣺%s\n", C, s.top + 1, t2);
	}
}


void Search() {
	printf("������Ҫ�����ĳ��ƺţ�\n");
	scanf("%s", &C);
	int i, j, k, flag = 0;
	time_t t1;
	long int t = time(&t1);
	if (s.top >= 0) {
		for (i = s.top; i >= 0; i--) {
			if (0 == strcmp(s.Stop[i].Lincense, C)) {
				printf("��������ͣ�����ڣ���Ϣ���£�\n");
				printf("\t���ƺ�\t\tͣ��λ��\t��ǰ����֧�����\t����ʱ��\t\n");
				printf("\t%s\t��%d��\t\t%0.fԪ\t\t\t%s", s.Stop[i].Lincense, i + 1, Price * (t - s.Stop[i].TimeIn), s.Stop[i].ct);
				flag = 1;
				break;
			}
		}
	}
	if (flag == 0 && p.count > 0) {
		i = p.front, k = 1, j = p.rear;
		while (i != j) {
			if (0 == strcmp(p.Pave[i].Lincense, C)) {
				printf("��������ͣ�����\n");
				printf("\t���ƺ�\t\tͣ��λ��\n");
				printf("\t%s\t��%d��", p.Pave[i].Lincense, k);
				flag = 2;
				break;
			}
			i++;
			k++;
		}
	}
	if (0 == flag)
		printf("ͣ�������ⲻ���ڸ�������Ϣ��\n");

}


void Car_Leave() {
	printf("�����뼴���뿪�ĳ��ƺţ�");
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
		printf("ͣ������û�и���������Ϣ��\n");
}


void Leave_Pavement() {
	int i, j, flag = 0;
	printf("�����뼴���뿪�ĳ��ƺţ�");
	scanf("%s", &C);
	if (p.count <= 0) {
		printf("����ϲ���������!\n");
		return;
	}
	while (p.count > 0) {
		i = p.front;
		if (0 == strcmp(p.Pave[i].Lincense, C)) {
			break;
		}
		printf("����Ϊ%s��������ʱ�ӱ��������ʱ���\n", p.Pave[p.front].Lincense);
		strcpy(w.Wait[w.rear].Lincense, p.Pave[p.front].Lincense);
		p.front = (p.front + 1) % MAX_PAVE;
		w.rear = (w.rear + 1) % MAX_PAVE;
		w.count++;
		p.count--;
	}
	printf("\n����Ϊ%s�������ӱ���Ͽ��ߣ�����ȡ�κη��ã�\n\n", p.Pave[i].Lincense);
	p.front = (p.front + 1) % MAX_PAVE;
	p.count--;
	while (p.count > 0) {
		printf("����Ϊ%s��������ʱ�ӱ��������ʱ���\n", p.Pave[p.front].Lincense);
		strcpy(w.Wait[w.rear].Lincense, p.Pave[p.front].Lincense);
		p.front = (p.front + 1) % MAX_PAVE;
		w.rear = (w.rear + 1) % MAX_PAVE;
		w.count++;
		p.count--;
	}
	while (w.count > 0) {
		printf("\n����Ϊ%s���������ر��\n", w.Wait[w.front].Lincense);
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
		printf("����Ϊ%s��������ʱ�˳�ͣ����\n", s.Stop[s.top--].Lincense);
	}
	printf("����Ϊ%s��������ͣ��������\n", s.Stop[s.top].Lincense);
	time_t t1;
	long int t = time(&t1);
	s.Stop[s.top].TimeOut = t;
	char* t2;
	t2 = ctime(&t1);
	printf("�뿪ʱ��%s\n�踶��%.0fԪ\n", t2, Price * (s.Stop[s.top].TimeOut - s.Stop[s.top].TimeIn));
	s.top--;
	while (b.top > 0) {
		strcpy(s.Stop[++s.top].Lincense, b.Let[--b.top].Lincense);
		printf("����Ϊ%s������ͣ��ͣ��λ%d��λ\n", b.Let[b.top].Lincense, s.top + 1);
	}
	while (s.top < MAX_STOP - 1) {
		if (0 == p.count)
			break;
		else {
			strcpy(s.Stop[++s.top].Lincense, p.Pave[p.front].Lincense);
			printf("����Ϊ%s�������ӱ���н���ͣ��λ��%d��λ\n", p.Pave[p.front].Lincense, s.top + 1);
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
		printf("������������´�������\n");
	else {
		strcpy(p.Pave[p.rear].Lincense, C);
		p.rear = (p.rear + 1) % MAX_PAVE;
		p.count++;
		printf("����Ϊ%s������ͣ������\n", C);
	}
}


void DisPlay() {
	int i = s.top;
	if (-1 == i)
		printf("ͣ����ĿǰΪ��\n");
	time_t t1;
	long int t = time(&t1);
	printf("\t���ƺ�\t\tͣ��ʱ��\t��ǰ����֧�����\tͣ��λ��\n");
	while (i != -1) {
		printf("\t%s\t%d��%d��\t\t%.0fԪ\t\t\t��%d��\n", s.Stop[i].Lincense,
			(t - s.Stop[i].TimeIn) / 60, (t - s.Stop[i].TimeIn) % 60, Price * (t - s.Stop[i].TimeIn), i + 1);
		i--;
	}
}


void DisPlayPave() {
	int i = p.front;
	int k = 1;
	if (0 == p.count)
		printf("���ĿǰΪ��\n");
	printf("\t���ƺ�\t\tͣ��λ��\n");
	while (i != p.rear && k <= p.count) {
		printf("\t%s\t��%d��\n", p.Pave[i].Lincense, k++);
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
		printf("\n����������0\n");
	top:
		scanf("%d", &cho);
		if (0 == cho) {
			continue;
		}
		else {
			printf("����������������������\n");
			goto top;
		}
	}
}

void SmallWelcome() {
	printf("\t*******************Ŀǰͣ����״��***********************\n");
	printf("\tͣ��������%d����λ,��ǰͣ��������%d����,�Ⱥ�������%d/%d����\n",
		MAX_STOP, s.top + 1, (p.rear + MAX_PAVE - p.front) % MAX_PAVE, MAX_PAVE - 1);
	printf("\t********************************************************\n");
	printf("\t---------Welcome to Ep's Car Parking next time----------\n");
	printf("\t*                                                      *\n");
	printf("\t*                   1.��ͣ������ʻ������               *\n");
	printf("\t*                   2.�ӱ����ʻ������                 *\n");
	printf("\t*                   3.�˳��ӹ���ϵͳ                   *\n");
	printf("\t*��ע�⣺��ͣ������ʻ�����������%.0fԪ/���ӼƷ�          *\n", 60 * Price);
	printf("\t*����֪���ӱ����ʻ�����������ȡ����                  *\n");
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
	printf("\t*******************Ŀǰͣ����״��***********************\n");
	printf("\tͣ��������%d����λ,��ǰͣ��������%d����,�Ⱥ�������%d/%d����\n",
		MAX_STOP, s.top + 1, (p.rear + MAX_PAVE - p.front) % MAX_PAVE, MAX_PAVE - 1);
	printf("\t********************************************************\n");
	printf("\t--------------Welcome to Ep's Car Parking---------------\n");
	printf("\t*                                                      *\n");
	printf("\t*                   1.ͣ����ͣ����Ϣ��ʾ               *\n");
	printf("\t*                   2.�����ͣ����Ϣ��ʾ               *\n");
	printf("\t*                   3.��������ͣ��������               *\n");
	printf("\t*                   4.������ȥͣ��������               *\n");
	printf("\t*                   5.������������                     *\n");
	printf("\t*                   6.�˳�����ϵͳ                     *\n");
	printf("\t*�շѱ�׼����ͣ��������%.0fԪ/���ӼƷѣ�����֪            *\n", 60 * Price);
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
			printf("\n��ӭ���ٴ�ʹ�ñ�ϵͳ�� ��=��=��=(~������)~\n\n");
			break;
		}
		printf("\n����������0\n");
	begin:
		scanf("%d", &cho);
		if (0 == cho) {
			continue;
		}
		else {
			printf("����������������������\n");
			goto begin;
		}
	}
	return 0;
}


