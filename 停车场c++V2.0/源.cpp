#include <iostream>
#include <iomanip>
#include <malloc.h>
#include <time.h>
using namespace std;
#define Max 3           //停车场容量
#define Price 0.10      //收费价格
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
    time_t timep;                                 //存储时间的类型变量
    time(&timep);                                 //获取当前时间
    cout << "现在时刻：" << ctime(&timep) << endl;  //将日历时间参数timep转换为一个表示本地当前时间的字符串
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
    time_t nowtime;                         //首先创建一个time_t 类型的变量nowtime	
    struct tm* tmp;                         //然后创建一个新时间结构体指针 p 	
    time(&nowtime);                         //使用该函数就可得到当前系统时间，使用该函数需要将传入time_t类型变量nowtime的地址值。
    tmp = localtime(&nowtime);              //由于此时变量nowtime中的系统时间值为日历时间，我们需要调用本地时间函数p=localtime（time_t* nowtime）将nowtime变量中的日历时间转化为本地时间，存入到指针为p的时间结构体中。不改的话，可以参照注意事项手动改。
    p->reach.hour = tmp->tm_hour;           //将获取的时间存入节点中
    p->reach.min = tmp->tm_min;
    S->data[S->top] = p;
    cout << "汽车停在停车场第" << S->data[S->top]->weizi << "个位置" << endl;
    cout << endl << "*************汽车进入停车场成功*************" << endl << endl;
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
    cout << endl << "停车场车位已满，请该汽车在便道上停靠等待!" << endl;
    QueueNode* t;
    t = (QueueNode*)malloc(sizeof(QueueNode));
    if (!t)   exit(ERROR);
    t->data = p;
    t->next = NULL;
    Q->rear->next = t;
    Q->rear = t;
    cout << "************汽车在便道上停靠成功***********" << endl << endl;
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
void PriceCal(CarNode* p, int Location)      //计算价格
{
    time_t nowtime;                         //首先创建一个time_t 类型的变量nowtime	
    struct tm* tmp;                         //然后创建一个新时间结构体指针 p 	
    time(&nowtime);                         //使用该函数就可得到当前系统时间，使用该函数需要将传入time_t类型变量nowtime的地址值。
    tmp = localtime(&nowtime);              //由于此时变量nowtime中的系统时间值为日历时间，我们需要调用本地时间函数p=localtime（time_t* nowtime）将nowtime变量中的日历时间转化为本地时间，存入到指针为p的时间结构体中。不改的话，可以参照注意事项手动改。
    p->leave.hour = tmp->tm_hour;           //将获取的时间存入节点中
    p->leave.min = tmp->tm_min;
    cout << "离开汽车的车牌号为：";
    cout << p->num << endl;
    cout << "该汽车到达的时间为：";
    cout << p->reach.hour << ":" << p->reach.min << endl;
    cout << "该汽车离开的时间为：";
    cout << p->leave.hour << ":" << p->leave.min << endl;
    cout << "该汽车应交费用为：<单位：元>";
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
    cout << "请输入到达汽车的车牌号：";
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
    loop:   cout << "请输入汽车在停车场的位置<1-" << Max << ">：";
        cin >> Location;
        if (Location<1 || Location>Out->top)
        {
            cout << "停车场该车位还未停车，请重新输入!" << endl;
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
            DeQueue(Q, q);           //将队列结点t取值data赋给结点q并出队列;
            cout << "*************便道车位位置[1]的汽车将进入停车场**************" << endl;
            q->weizi = findspace(Out);
            Push(Out, q);
        }
        else
            cout << endl << "*******便道上没有汽车，停车场没有进入新的汽车!**********" << endl << endl;
    }
    else
        cout << "***********停车场里没有汽车可以选择离去!*************" << endl << endl;
}
void DisplayStack(StackCar* S)
{
    int i;
    cout << "你需要查看的停车场停车情况如下：" << endl;
    if (S->top > 0)
    {
        for (i = 1; i <= S->top; i++)
        {
            cout << "在停车场的车位位置：" << S->data[i]->weizi << endl;
            cout << "该车位汽车的车牌号：" << S->data[i]->num << endl;
            cout << "到达时间：" << S->data[i]->reach.hour << ":" << S->data[i]->reach.min << endl << endl;
        }
    }
    else
        cout << endl << "停车场里没有车,所以无法显示你要查看的停车信息!" << endl << endl;
}
void DisplayQueue(QueueCar* Q)
{
    QueueNode* t;
    int i;
    t = Q->front->next;
    if (Q->front != Q->rear)
    {
        cout << "你需要查看的便道停车情况如下：" << endl;
        for (i = 1; t != NULL; i++)
        {
            cout << "在便道上的车位位置：" << i << endl;
            cout << "该车位汽车的车牌号：" << t->data->num << endl << endl;
            t = t->next;
        }
    }
    else
        cout << "便道上没有车,所以无法显示你要查看的停车信息!" << endl << endl;
}
void menu()
{
    cout << "*****************欢迎来到停车场管理系统************** " << endl << endl;
    cout << "                  1.汽车到达停车场操作                " << endl;
    cout << "                  2.汽车离去停车场操作                " << endl;
    cout << "                  3.停车场停车信息显示                " << endl;
    cout << "                  4.便道停车信息显示                  " << endl;
    cout << "                  0.退出停车场管理系统                " << endl << endl;
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
        cout << "请输入你要选择的功能序号：";
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
        default: cout << "你的选择有误，此管理系统没有此项功能！" << endl << endl;
        }
    }
    system("pause");
}