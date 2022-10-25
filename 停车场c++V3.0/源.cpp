
/*
    停车管理系统。停车场有位置便进入停车场，否再进入便道。停车场容量为3便道没有限制。
    当停车场有车量离开便道上的车进入停车场。
*/

#include <iostream>
#include <iomanip>
#include <malloc.h>
#include <time.h>

using namespace std;    //标准命名空间
#define Max 3           //停车场容量
#define Price 0.10      //收费价格
#define ERROR -1

typedef struct              //时间结构体，
{
    int hour;
    int min;
}Time;
typedef struct Node         //车辆信息
{
    char num[20];           //车牌号
    int weizi;              //停车时的位置
    Time reach;             //到达时间
    Time leave;             //离开时间
}CarNode;
typedef struct stackNode    //停车结构————栈
{
    CarNode* data[Max + 1]; //车辆节点，使用数组栈
    int top;                //栈顶
}StackCar;
typedef struct LinkNode     //链队列
{
    CarNode* data;          //队列中的车辆节点
    struct LinkNode* next;  //指向下一个节点指针
}QueueNode;
typedef struct              //链队列
{
    QueueNode* front;       //头节指针
    QueueNode* rear;        //尾指针
}QueueCar;

//函数声明
void menu();                                  //菜单函数
void clear();                                 //清除输入流
void mytime();                                //显示时间函数
int InitStack(StackCar* S);                   //初始化栈
int InitQueue(QueueCar* Q);                   //初始化队列
int findspace(StackCar* S);                  //找到空的停车位
void DisplayStack(StackCar* S);               //显示停车场停车情况
void DisplayQueue(QueueCar* Q);               //显示便道停车情况
int Push(StackCar* S, CarNode* p);            //进栈操作
int Pop(StackCar* S, CarNode* (&p));          //出栈操作
int EnQueue(QueueCar* Q, CarNode* p);         //进入队列
int PushStack(StackCar* S, CarNode* p);       //将节点压栈
int DeQueue(QueueCar* Q, CarNode* (&q));      //出栈队列
void PriceCal(CarNode* p, int Location);      //计算价格
void InCarPark(StackCar* Enter, QueueCar* Q); //停车进站
void OutCarPark(StackCar* Out, StackCar* Temp, QueueCar* Q); //离开停车场


void clear()                //功能：再输入流中将错误的输入清除掉
{
    char c;
    while ((c = getchar()) != '\n');
}
void mytime()
{
    time_t timep;                                 //存储时间的类型变量
    time(&timep);                                 //获取当前时间
    cout << "现在时刻：" << ctime(&timep) << endl;  //将日历时间参数timep转换为一个表示本地当前时间的字符串
}
int InitStack(StackCar* S)      //初始化栈
{
    S->top = 0;
    return 0;
}
int InitQueue(QueueCar* Q)      //初始化队列
{
    Q->front = Q->rear = (QueueNode*)malloc(sizeof(QueueNode));
    if (!Q->front)              //申请空间失败退出程序
        exit(ERROR);
    Q->front->next = NULL;      //为空
    return 0;
}
int findspace(StackCar* S)     //找到停车场空余的位置
{
    if (S->top == 1)            //当停车场中只有一个车位被占用
    {
        switch (S->data[1]->weizi)
        {
        case 1: return 2; case 2: return 3; case 3: return 1;
        }
    }
    else if (S->top == 2)       //当停车场中有两个位置被占用
    {
        if (S->data[1]->weizi == 1 && S->data[2]->weizi == 2) return 3;
        if (S->data[1]->weizi == 1 && S->data[2]->weizi == 3) return 2;
        if (S->data[1]->weizi == 2 && S->data[2]->weizi == 3) return 1;
    }
    else if (S->top == 3)        //没有停车位
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
    S->data[S->top] = p;                    //节点入栈
    cout << "汽车停在停车场第" << S->data[S->top]->weizi << "个位置" << endl;
    cout << endl << "*************汽车进入停车场成功*************" << endl << endl;
    return 0;
}
int PushStack(StackCar* S, CarNode* p)          // 压栈
{
    S->top++;                                   //栈顶加一
    S->data[S->top] = p;                        //节点入栈
    return 0;
}
int Pop(StackCar* S, CarNode* (&p))             //出栈
{
    p = S->data[S->top];                        //节点栈
    S->top--;                                   //栈顶减一
    return 0;
}
int EnQueue(QueueCar* Q, CarNode* p)            //进入队列操作
{
    cout << endl << "停车场车位已满，请该汽车在便道上停靠等待!" << endl;
    QueueNode* t;
    t = (QueueNode*)malloc(sizeof(QueueNode));  //为节点分配内存
    if (!t)   exit(ERROR);
    t->data = p;                                //节点赋值
    t->next = NULL;                             //进入队列的最后一个节点的next为NULL
    Q->rear->next = t;                          //队尾节点next指向新节点
    Q->rear = t;                                //队尾指针指向新节点
    cout << "************汽车在便道上停靠成功***********" << endl << endl;
    return 0;
}
int DeQueue(QueueCar* Q, CarNode* (&q))         //出队列
{
    QueueNode* t;
    t = Q->front->next;                         //临时节点
    q = t->data;
    Q->front->next = t->next;                   //头节点的next指向队列中的第二个节点
    if (Q->rear == t)                           //最后一个节点需要将队头和队尾连接类似初始化
        Q->rear = Q->front;
    free(t);                                    //释放被删除节点的内存空间
    return 0;
}

//计算价格
//超过24小时时：(23-a.h+l.h)*60 + (60 - r.m+l.m)
//24小时内：(a.h-l.h)*60+(a.m-l.m)        
void PriceCal(CarNode* p, int Location)
{
    time_t nowtime;                             //首先创建一个time_t 类型的变量nowtime	
    struct tm* tmp;                             //然后创建一个新时间结构体指针 p 	
    time(&nowtime);                             //使用该函数就可得到当前系统时间，使用该函数需要将传入time_t类型变量nowtime的地址值。
    tmp = localtime(&nowtime);                  //由于此时变量nowtime中的系统时间值为日历时间，我们需要调用本地时间函数p=localtime（time_t* nowtime）将nowtime变量中的日历时间转化为本地时间，存入到指针为p的时间结构体中。不改的话，可以参照注意事项手动改。
    p->leave.hour = tmp->tm_hour;               //将获取的时间存入节点中
    p->leave.min = tmp->tm_min;
    cout << "离开汽车的车牌号为：";
    cout << p->num << endl;
    cout << "该汽车到达的时间为：";
    cout << p->reach.hour << ":" << p->reach.min << endl;
    cout << "该汽车离开的时间为：";
    cout << p->leave.hour << ":" << p->leave.min << endl;
    cout << "该汽车应交费用为：<单位：元>";         //fixed和setprecisim为控制输出精度。
    if ((p->leave.hour < p->reach.hour) || ((p->leave.hour == p->reach.hour) && (p->leave.min < p->reach.min)))
        cout << fixed << setprecision(2) << ((23 - p->reach.hour + p->leave.hour) * 60 + (60 - p->reach.min + p->leave.min)) * Price << endl << endl;
    else
        cout << fixed << setprecision(2) << ((p->leave.hour - p->reach.hour) * 60 + (p->leave.min - p->reach.min)) * Price << endl << endl;
    free(p);
}
void InCarPark(StackCar* Enter, QueueCar* Q)   //车辆信息
{
    CarNode* p;
    p = (CarNode*)malloc(sizeof(CarNode));     //车辆节点内存申请
    cout << "请输入到达汽车的车牌号：";
    cin >> p->num;
    clear();
    if (Enter->top < Max)                      //栈没满
    {
        if (Enter->top == 0)                   //如果栈空，则车进入停车场第一个位置
            p->weizi = 1;
        else
            p->weizi = findspace(Enter);       //栈不空，分配空车位
        Push(Enter, p);                        //压栈
    }
    else EnQueue(Q, p);                        //栈满，车辆进入队列

}
void OutCarPark(StackCar* Out, StackCar* Temp, QueueCar* Q)
{
    int Location = 0;
    int top = Out->top;
    CarNode* p, * q;
    DisplayStack(Out);                  //展示目前停车场内的车辆信息
    if (Out->top > 0)
    {
        do
        {
            cout << "请输入汽车在停车场的位置<1-" << Max << ">：";
            cin.clear();                //清空cin的错误标记
            cin.sync();
            cin >> Location;
            clear();
            while (top <= 3 && Location)//判断输入的停车的位置是否存在
                if (Out->data[top]->weizi == Location) top = 4;
                else top++;             //标记加一，
            if (top == 4) break;        //位置信息输入正确，跳出循环
            else cout << "输入错误请重新输入" << endl;
        } while (1);
        while (Out->top > Location)       //将车辆位置号前的所有栈节点出栈
        {
            Pop(Out, p);                //栈从栈顶出栈进入临时栈
            PushStack(Temp, p);         //出栈节点进入临时栈
        }
        Pop(Out, p);                    //将要出栈的元素出栈
        PriceCal(p, Location);          //计算离开的车辆的停车费
        while (Temp->top >= 1)          //将临时栈的节点从新压入栈里
        {
            Pop(Temp, p);               //Temp,Temp->data[Temp->top];
            PushStack(Out, p);          //Out,Temp->data[Temp->top];
        }
        if ((Q->front != Q->rear) && Out->top < Max)
        {
            DeQueue(Q, q);              //将队列结点t取值data赋给结点q并出队列;
            cout << "*************便道车位位置[1]的汽车将进入停车场**************" << endl;
            q->weizi = findspace(Out);
            Push(Out, q);               //将队列出的节点压入栈内
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
    StackCar S, Temp;       //S为停车场内车辆栈，temp为临时栈，车辆离开出栈用
    QueueCar Q;             //队列，便道停车
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
        default:
        {
            clear();
            cout << "你的选择有误，此管理系统没有此项功能！" << endl << endl;
            system("pause");
            system("cls");
        }
        }
    }
    system("pause");
}