#include <iostream>
#include <iomanip>
#include <malloc.h>
#include <time.h>
using namespace std;
#define Max 3           //ͣ��������
#define Price 0.10      //�շѼ۸�
#define ERROR -1

typedef struct
{
    int hour;
    int min;
}Time;
typedef struct Node
{
    char num[20];
    int weizi;
    Time reach;
    Time leave;
}CarNode;
typedef struct stackNode
{
    CarNode* data[Max + 1];
    int top;
}StackCar;
typedef struct LinkNode
{
    CarNode* data;
    struct LinkNode* next;
}QueueNode;
typedef struct
{
    QueueNode* front;
    QueueNode* rear;
}QueueCar;

void mytime()
{
    time_t timep;                                 //�洢ʱ������ͱ���
    time(&timep);                                 //��ȡ��ǰʱ��
    cout << "����ʱ�̣�" << ctime(&timep) << endl;  //������ʱ�����timepת��Ϊһ����ʾ���ص�ǰʱ����ַ���
}

int InitStack(StackCar* S)
{
    S->top = 0;
    return 0;
}
int InitQueue(QueueCar* Q)
{
    Q->front = Q->rear = (QueueNode*)malloc(sizeof(QueueNode));
    if (!Q->front)
        exit(ERROR);
    Q->front->next = NULL;
    return 0;
}

int findspace(StackCar* S)
{
    if (S->top == 1)
    {
        switch (S->data[1]->weizi)
        {
        case 1: return 2; case 2: return 3; case 3: return 1;
        }
    }
    else if (S->top == 2)
    {
        if (S->data[1]->weizi == 1 && S->data[2]->weizi == 2) return 3;
        if (S->data[1]->weizi == 1 && S->data[2]->weizi == 3) return 2;
        if (S->data[1]->weizi == 2 && S->data[2]->weizi == 3) return 1;
    }
    else if (S->top == 3)
        return 0;
    return -1;
}

int Push(StackCar* S, CarNode* p)
{
    S->top++;
    time_t nowtime;                         //���ȴ���һ��time_t ���͵ı���nowtime	
    struct tm* tmp;                         //Ȼ�󴴽�һ����ʱ��ṹ��ָ�� p 	
    time(&nowtime);                         //ʹ�øú����Ϳɵõ���ǰϵͳʱ�䣬ʹ�øú�����Ҫ������time_t���ͱ���nowtime�ĵ�ֵַ��
    tmp = localtime(&nowtime);              //���ڴ�ʱ����nowtime�е�ϵͳʱ��ֵΪ����ʱ�䣬������Ҫ���ñ���ʱ�亯��p=localtime��time_t* nowtime����nowtime�����е�����ʱ��ת��Ϊ����ʱ�䣬���뵽ָ��Ϊp��ʱ��ṹ���С����ĵĻ������Բ���ע�������ֶ��ġ�
    p->reach.hour = tmp->tm_hour;           //����ȡ��ʱ�����ڵ���
    p->reach.min = tmp->tm_min;
    S->data[S->top] = p;
    cout << "����ͣ��ͣ������" << S->data[S->top]->weizi << "��λ��" << endl;
    cout << endl << "*************��������ͣ�����ɹ�*************" << endl << endl;
    return 0;
}
int PushStack(StackCar* S, CarNode* p)
{
    S->top++;
    S->data[S->top] = p;
    return 0;
}
int Pop(StackCar* S, CarNode* (&p))
{
    p = S->data[S->top];
    S->top--;
    return 0;
}
int EnQueue(QueueCar* Q, CarNode* p)
{
    cout << endl << "ͣ������λ��������������ڱ����ͣ���ȴ�!" << endl;
    QueueNode* t;
    t = (QueueNode*)malloc(sizeof(QueueNode));
    if (!t)   exit(ERROR);
    t->data = p;
    t->next = NULL;
    Q->rear->next = t;
    Q->rear = t;
    cout << "************�����ڱ����ͣ���ɹ�***********" << endl << endl;
    return 0;
}
int DeQueue(QueueCar* Q, CarNode* (&q))
{
    QueueNode* t;
    t = Q->front->next;
    q = t->data;
    Q->front->next = t->next;
    if (Q->rear == t)
        Q->rear = Q->front;
    free(t);
    return 0;
}
void PriceCal(CarNode* p, int Location)      //����۸�
{
    time_t nowtime;                         //���ȴ���һ��time_t ���͵ı���nowtime	
    struct tm* tmp;                         //Ȼ�󴴽�һ����ʱ��ṹ��ָ�� p 	
    time(&nowtime);                         //ʹ�øú����Ϳɵõ���ǰϵͳʱ�䣬ʹ�øú�����Ҫ������time_t���ͱ���nowtime�ĵ�ֵַ��
    tmp = localtime(&nowtime);              //���ڴ�ʱ����nowtime�е�ϵͳʱ��ֵΪ����ʱ�䣬������Ҫ���ñ���ʱ�亯��p=localtime��time_t* nowtime����nowtime�����е�����ʱ��ת��Ϊ����ʱ�䣬���뵽ָ��Ϊp��ʱ��ṹ���С����ĵĻ������Բ���ע�������ֶ��ġ�
    p->leave.hour = tmp->tm_hour;           //����ȡ��ʱ�����ڵ���
    p->leave.min = tmp->tm_min;
    cout << "�뿪�����ĳ��ƺ�Ϊ��";
    cout << p->num << endl;
    cout << "�����������ʱ��Ϊ��";
    cout << p->reach.hour << ":" << p->reach.min << endl;
    cout << "�������뿪��ʱ��Ϊ��";
    cout << p->leave.hour << ":" << p->leave.min << endl;
    cout << "������Ӧ������Ϊ��<��λ��Ԫ>";
    if ((p->leave.hour < p->reach.hour) || ((p->leave.hour == p->reach.hour) && (p->leave.min < p->reach.min)))
        cout << fixed << setprecision(2) << ((23 - p->reach.hour + p->leave.hour) * 60 + (60 - p->reach.min + p->leave.min)) * Price << endl << endl;
    else
        cout << fixed << setprecision(2) << ((p->leave.hour - p->reach.hour) * 60 + (p->leave.min - p->reach.min)) * Price << endl << endl;
    free(p);
}

void InCarPark(StackCar* Enter, QueueCar* Q)
{
    CarNode* p;
    p = (CarNode*)malloc(sizeof(CarNode));
    cout << "�����뵽�������ĳ��ƺţ�";
    cin >> p->num;
    if (Enter->top < Max)
    {
        if (Enter->top == 0)
            p->weizi = 1;
        else
            p->weizi = findspace(Enter);
        Push(Enter, p);
    }
    else EnQueue(Q, p);

}
void OutCarPark(StackCar* Out, StackCar* Temp, QueueCar* Q)
{
    int Location;
    CarNode* p, * q;
    if (Out->top > 0)
    {
    loop:   cout << "������������ͣ������λ��<1-" << Max << ">��";
        cin >> Location;
        if (Location<1 || Location>Out->top)
        {
            cout << "ͣ�����ó�λ��δͣ��������������!" << endl;
            goto loop;
        }
        while (Out->top > Location)
        {
            Pop(Out, p);              //Out,Out->data[Out->top];
            PushStack(Temp, p);       //Temp,Out->data[Out->top];
        }
        Pop(Out, p);
        PriceCal(p, Location);
        while (Temp->top >= 1)
        {
            Pop(Temp, p);            //Temp,Temp->data[Temp->top];
            PushStack(Out, p);       //Out,Temp->data[Temp->top];
        }
        if ((Q->front != Q->rear) && Out->top < Max)
        {
            DeQueue(Q, q);           //�����н��tȡֵdata�������q��������;
            cout << "*************�����λλ��[1]������������ͣ����**************" << endl;
            q->weizi = findspace(Out);
            Push(Out, q);
        }
        else
            cout << endl << "*******�����û��������ͣ����û�н����µ�����!**********" << endl << endl;
    }
    else
        cout << "***********ͣ������û����������ѡ����ȥ!*************" << endl << endl;
}
void DisplayStack(StackCar* S)
{
    int i;
    cout << "����Ҫ�鿴��ͣ����ͣ��������£�" << endl;
    if (S->top > 0)
    {
        for (i = 1; i <= S->top; i++)
        {
            cout << "��ͣ�����ĳ�λλ�ã�" << S->data[i]->weizi << endl;
            cout << "�ó�λ�����ĳ��ƺţ�" << S->data[i]->num << endl;
            cout << "����ʱ�䣺" << S->data[i]->reach.hour << ":" << S->data[i]->reach.min << endl << endl;
        }
    }
    else
        cout << endl << "ͣ������û�г�,�����޷���ʾ��Ҫ�鿴��ͣ����Ϣ!" << endl << endl;
}
void DisplayQueue(QueueCar* Q)
{
    QueueNode* t;
    int i;
    t = Q->front->next;
    if (Q->front != Q->rear)
    {
        cout << "����Ҫ�鿴�ı��ͣ��������£�" << endl;
        for (i = 1; t != NULL; i++)
        {
            cout << "�ڱ���ϵĳ�λλ�ã�" << i << endl;
            cout << "�ó�λ�����ĳ��ƺţ�" << t->data->num << endl << endl;
            t = t->next;
        }
    }
    else
        cout << "�����û�г�,�����޷���ʾ��Ҫ�鿴��ͣ����Ϣ!" << endl << endl;
}
void menu()
{
    cout << "*****************��ӭ����ͣ��������ϵͳ************** " << endl << endl;
    cout << "                  1.��������ͣ��������                " << endl;
    cout << "                  2.������ȥͣ��������                " << endl;
    cout << "                  3.ͣ����ͣ����Ϣ��ʾ                " << endl;
    cout << "                  4.���ͣ����Ϣ��ʾ                  " << endl;
    cout << "                  0.�˳�ͣ��������ϵͳ                " << endl << endl;
    cout << "******************************************************" << endl;
    mytime();
}
int main()
{
    StackCar S, Temp;
    QueueCar Q;
    char M;
    InitStack(&S);
    InitStack(&Temp);
    InitQueue(&Q);
    while (1)
    {
        menu();
        cout << "��������Ҫѡ��Ĺ�����ţ�";
        cin >> M;
        getchar();
        cout << endl;
        switch (M)
        {
        case '1':   InCarPark(&S, &Q);         system("pause");  system("cls");       break;
        case '2':   OutCarPark(&S, &Temp, &Q); system("pause");  system("cls");       break;
        case '3':   DisplayStack(&S);          system("pause");  system("cls");       break;
        case '4':   DisplayQueue(&Q);          system("pause");  system("cls");       break;
        case '0':   return 0;
        default: cout << "���ѡ�����󣬴˹���ϵͳû�д���ܣ�" << endl << endl;
        }
    }
    system("pause");
}