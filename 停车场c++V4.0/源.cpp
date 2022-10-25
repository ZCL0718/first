
/*
    ͣ������ϵͳ��ͣ������λ�ñ����ͣ���������ٽ�������ͣ��������Ϊ3���û�����ơ�
    ��ͣ�����г����뿪����ϵĳ�����ͣ������
*/

#include <iostream>
#include <iomanip>
#include <malloc.h>
#include <time.h>

using namespace std;    //��׼�����ռ�
#define Max 3           //ͣ�����ͱ��������ͣ������Ϊ1��2��3�������Ϊ4��5��6
#define Price 0.10      //�շѼ۸�
#define ERROR -1

typedef struct              //ʱ��ṹ�壬
{
    int hour;
    int min;
}Time;
typedef struct Node         //������Ϣ
{
    char num[20];           //���ƺ�
    int weizi;              //ͣ��ʱ��λ��
    Time reach;             //����ʱ��
    Time leave;             //�뿪ʱ��
}CarNode;
typedef struct stackNode    //ͣ���ṹ��������ջ
{
    CarNode* data[Max + 1]; //�����ڵ㣬ʹ������ջ
    int top;                //ջ��
}StackCar;
typedef struct LinkNode     //������
{
    CarNode* data;          //�����еĳ����ڵ�
    struct LinkNode* next;  //ָ����һ���ڵ�ָ��
}QueueNode;
typedef struct              //������
{
    QueueNode* front;       //ͷ��ָ��
    QueueNode* rear;        //βָ��
}QueueCar;

//��������
void menu();                                  //�˵�����
void clear();                                 //���������
void mytime();                                //��ʾʱ�亯��
int queueLen(QueueCar* Q);                    //��ʾ���г���
int InitStack(StackCar* S);                   //��ʼ��ջ
int InitQueue(QueueCar* Q);                   //��ʼ������
int FindspaceStack(StackCar* S);             //�ҵ��յ�ͣ��λ
void DisplayStack(StackCar* S);               //��ʾͣ����ͣ�����
void DisplayQueue(QueueCar* Q);               //��ʾ���ͣ�����
int Push(StackCar* S, CarNode* p);            //��ջ����
int Pop(StackCar* S, CarNode* (&p));          //��ջ����
int EnQueue(QueueCar* Q, CarNode* p);         //�������
int PushStack(StackCar* S, CarNode* p);       //���ڵ�ѹջ
int DeQueue(QueueCar* Q, CarNode* (&q));      //��ջ����
int PriceCal(CarNode* p, int Location);       //����۸�
void InCarPark(StackCar* Enter, QueueCar* Q); //ͣ����վ
void OutCarPark(StackCar* Out, StackCar* TempS, QueueCar* Q); //�뿪ͣ����


int queueLen(QueueCar* Q)
{
    if (Q->front->next == NULL) return 0;      //����Ϊ���򷵻�0
    LinkNode* t;
    int i;
    t = Q->front->next;                        //ָ���һ���ڵ�
    for (i = 1; t->next != NULL; i++) t = t->next;
    return i;
}

int FindSpaceQueue(QueueCar* Q, int len)       //�ҵ�����ϵĿճ�λ
{
    switch (len)
    {
    case 0:return 4;
    case 1:if (Q->front->next->data->weizi == 4) return 5; else return 4;
    default:if (Q->front->next->data->weizi == 4 && Q->rear->data->weizi == 5) return 6;
           else if (Q->front->next->data->weizi == 5 && Q->rear->data->weizi == 6) return 4;
           else return 5;
    }
}

void clear()                                      //���ܣ����������н���������������
{
    char c;
    while ((c = getchar()) != '\n');
}
void mytime()
{
    time_t timep;                                 //�洢ʱ������ͱ���
    time(&timep);                                 //��ȡ��ǰʱ��
    cout << "����ʱ�̣�" << ctime(&timep) << endl;  //������ʱ�����timepת��Ϊһ����ʾ���ص�ǰʱ����ַ���
}
int InitStack(StackCar* S)                        //��ʼ��ջ
{
    S->top = 0;
    return 0;
}
int InitQueue(QueueCar* Q)                        //��ʼ������
{
    Q->front = Q->rear = (QueueNode*)malloc(sizeof(QueueNode));
    if (!Q->front) exit(ERROR);                   //����ռ�ʧ���˳�����

    Q->front->next = NULL;                        //Ϊ��
    return 0;
}
int FindspaceStack(StackCar* S)                  //�ҵ�ͣ���������λ��
{
    if (S->top == 1)                              //��ͣ������ֻ��һ����λ��ռ��
        switch (S->data[1]->weizi)
        {
        case 1: return 2; case 2: return 3; case 3: return 1;
        }
    else if (S->top == 2)                         //��ͣ������������λ�ñ�ռ��
    {
        if (S->data[1]->weizi == 1 && S->data[2]->weizi == 2) return 3;
        if (S->data[1]->weizi == 1 && S->data[2]->weizi == 3) return 2;
        if (S->data[1]->weizi == 2 && S->data[2]->weizi == 3) return 1;
    }
    else if (S->top == 3) return 0;                //û��ͣ��λ   
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
    S->data[S->top] = p;                    //�ڵ���ջ
    cout << "����ͣ��ͣ������" << S->data[S->top]->weizi << "��λ��" << endl;
    cout << endl << "*************��������ͣ�����ɹ�*************" << endl << endl;
    return 0;
}
int PushStack(StackCar* S, CarNode* p)          // ѹջ
{
    S->top++;                                   //ջ����һ
    S->data[S->top] = p;                        //�ڵ���ջ
    return 0;
}
int Pop(StackCar* S, CarNode* (&p))             //��ջ
{
    p = S->data[S->top];                        //�ڵ�ջ
    S->top--;                                   //ջ����һ
    return 0;
}
int EnQueue(QueueCar* Q, CarNode* p)            //������в���
{
    QueueNode* t;
    time_t nowtime;                             //���ȴ���һ��time_t ���͵ı���nowtime	
    struct tm* tmp;                             //Ȼ�󴴽�һ����ʱ��ṹ��ָ�� p 	
    time(&nowtime);                             //ʹ�øú����Ϳɵõ���ǰϵͳʱ�䣬ʹ�øú�����Ҫ������time_t���ͱ���nowtime�ĵ�ֵַ��
    tmp = localtime(&nowtime);                  //���ڴ�ʱ����nowtime�е�ϵͳʱ��ֵΪ����ʱ�䣬������Ҫ���ñ���ʱ�亯��p=localtime��time_t* nowtime����nowtime�����е�����ʱ��ת��Ϊ����ʱ�䣬���뵽ָ��Ϊp��ʱ��ṹ���С����ĵĻ������Բ���ע�������ֶ��ġ�
    p->reach.hour = tmp->tm_hour;               //����ȡ��ʱ�����ڵ���
    p->reach.min = tmp->tm_min;
    t = (QueueNode*)malloc(sizeof(QueueNode));  //Ϊ�ڵ�����ڴ�
    if (!t)   exit(ERROR);
    t->data = p;                                //�ڵ㸳ֵ
    t->next = NULL;                             //������е����һ���ڵ��nextΪNULL
    Q->rear->next = t;                          //��β�ڵ�nextָ���½ڵ�
    Q->rear = t;                                //��βָ��ָ���½ڵ�
    return 0;
}
int DeQueue(QueueCar* Q, CarNode* (&q))         //������
{
    QueueNode* t;
    t = Q->front->next;                         //��ʱ�ڵ�
    q = t->data;
    Q->front->next = t->next;                   //ͷ�ڵ��nextָ������еĵڶ����ڵ�
    if (Q->rear == t) Q->rear = Q->front;       //���һ���ڵ���Ҫ����ͷ�Ͷ�β�������Ƴ�ʼ��                            
    free(t);                                    //�ͷű�ɾ���ڵ���ڴ�ռ�
    return 0;
}

//����۸�
//����24Сʱʱ��(23-a.h+l.h)*60 + (60 - r.m+l.m)
//24Сʱ�ڣ�(a.h-l.h)*60+(a.m-l.m)        
int PriceCal(CarNode* p, int Location)
{
    time_t nowtime;                             //���ȴ���һ��time_t ���͵ı���nowtime	
    struct tm* tmp;                             //Ȼ�󴴽�һ����ʱ��ṹ��ָ�� p 	
    time(&nowtime);                             //ʹ�øú����Ϳɵõ���ǰϵͳʱ�䣬ʹ�øú�����Ҫ������time_t���ͱ���nowtime�ĵ�ֵַ��
    tmp = localtime(&nowtime);                  //���ڴ�ʱ����nowtime�е�ϵͳʱ��ֵΪ����ʱ�䣬������Ҫ���ñ���ʱ�亯��p=localtime��time_t* nowtime����nowtime�����е�����ʱ��ת��Ϊ����ʱ�䣬���뵽ָ��Ϊp��ʱ��ṹ���С����ĵĻ������Բ���ע�������ֶ��ġ�
    p->leave.hour = tmp->tm_hour;               //����ȡ��ʱ�����ڵ���
    p->leave.min = tmp->tm_min;
    cout << "�뿪�����ĳ��ƺ�Ϊ��";
    cout << p->num << endl;
    cout << "�����������ʱ��Ϊ��";
    cout << p->reach.hour << ":" << p->reach.min << endl;
    cout << "�������뿪��ʱ��Ϊ��";
    cout << p->leave.hour << ":" << p->leave.min << endl;
    if (p->weizi > 3)
    {
        free(p);
        return 0;
    }
    cout << "������Ӧ������Ϊ��<��λ��Ԫ>";         //fixed��setprecisimΪ����������ȡ�
    if ((p->leave.hour < p->reach.hour) || ((p->leave.hour == p->reach.hour) && (p->leave.min < p->reach.min)))
        cout << fixed << setprecision(2) << ((23 - p->reach.hour + p->leave.hour) * 60 + (60 - p->reach.min + p->leave.min)) * Price << endl << endl;
    else
        cout << fixed << setprecision(2) << ((p->leave.hour - p->reach.hour) * 60 + (p->leave.min - p->reach.min)) * Price << endl << endl;
    free(p);
    return 0;
}
void InCarPark(StackCar* Enter, QueueCar* Q)   //������Ϣ
{
    CarNode* p;
    int lenQ = 0;
    lenQ = queueLen(Q);
    p = (CarNode*)malloc(sizeof(CarNode));     //�����ڵ��ڴ�����
    cout << "�����뵽�������ĳ��ƺţ�";
    cin >> p->num;
    clear();
    if (Enter->top < Max)                      //ջû��
    {
        if (Enter->top == 0)                   //���ջ�գ��򳵽���ͣ������һ��λ��
            p->weizi = 1;
        else
            p->weizi = FindspaceStack(Enter);  //ջ���գ�����ճ�λ
        Push(Enter, p);                        //ѹջ
    }
    else if (lenQ < Max)                      //ջ���������������
    {
        cout << endl << "ͣ������λ��������������ڱ����ͣ���ȴ�!" << endl;
        p->weizi = FindSpaceQueue(Q, lenQ);     //�ҵ������еĿ���λ��
        EnQueue(Q, p);                         //�������
        cout << "************�����ڱ����ͣ���ɹ�***********" << endl << endl;
    }
    else
    {
        cout << "ͣ��������������" << endl;
        free(p);
    }
}
void OutCarPark(StackCar* Out, StackCar* TempS, QueueCar* Q, QueueCar* TempQ)
{
    int Location = 0;                   //Ҫ�뿪������λ��
    int top = Out->top;                 //ջ��Ԫ�ظ����������ж���
    int lenq = queueLen(Q);             //ͬ��
    CarNode* p, * q;
    char c;
    cout << "�����복���Ƿ���ͣ������(y or n):";
    cin >> c;
    clear();
    if (Out->top > 0 && c == 'y')         //ͣ�������г�
    {
        DisplayStack(Out);              //չʾĿǰͣ�����ڵĳ�����Ϣ
        do
        {
            cout << "������������ͣ������λ��<1-" << Max << ">��";
            cin.clear();                //���cin�Ĵ�����
            cin.sync();
            cin >> Location;
            clear();
            while (top <= 3 && Location)//�ж������ͣ����λ���Ƿ����
                if (Out->data[top]->weizi == Location) top = 4;
                else top++;             //��Ǽ�һ��
            if (top == 4) break;        //λ����Ϣ������ȷ������ѭ��
            else cout << "�����������������" << endl;
        } while (1);
        if (Location < 4)
        {
            while (Out->data[Out->top]->weizi != Location)
            {                           //������λ�ú�ǰ������ջ�ڵ��ջ
                Pop(Out, p);            //ջ��ջ����ջ������ʱջ
                PushStack(TempS, p);    //��ջ�ڵ������ʱջ
            }
            Pop(Out, p);                //��Ҫ��ջ��Ԫ�س�ջ
            PriceCal(p, Location);      //�����뿪�ĳ�����ͣ����
            while (TempS->top >= 1)    //����ʱջ�Ľڵ�����ѹ��ջ��
            {
                Pop(TempS, p);          // TempS,TempS->data[TempS->top];
                PushStack(Out, p);      // Out,TempS->data[TempS->top];
            }
        }
    }
    else if (c == 'y') cout << "***********ͣ������û����������ѡ����ȥ!*************" << endl << endl;
    else if (lenq && c == 'n')           //������г�
    {
        DisplayQueue(Q);                //��ʾ����ϵĳ�����Ϣ
        do
        {
            cout << "�����������ڱ����λ��<4-6" << ">��";
            cin.clear();                //���cin�Ĵ�����
            cin.sync();
            cin >> Location;
            clear();
            LinkNode* t;
            t = Q->front->next;
            while (t->next != NULL && Location)
            {
                if (t->data->weizi == Location)
                {
                    lenq = 1;           //�ٱ�����ҵ������ͱ�Ǽ�Ϊ1����ֹͣѰ��
                    break;
                }
                else t = t->next;       //��һ���ڵ㣬ֱ���ҵ�����ȫ���ڵ㶼������һ��
            }
            if (lenq == 1) break;       //λ����Ϣ������ȷ 
            else cout << "�����������������" << endl;
        } while (1);
        while (Q->front->next->data->weizi != Location)
        {
            DeQueue(Q, q);               //����������Ҫ�뿪�Ľڵ��ǰ�����ڵ�
            EnQueue(TempQ, q);           //�ȴ�����ʱ�ڵ㣬���Ϊ���е�һ���ڵ㣬���ѭ������ִ��
        }
        DeQueue(Q, q);                   //�����еĽڵ��뿪����
        PriceCal(q, Location);           //����뿪�ڵ����Ϣ���ͷ��ڴ�
        while (Q->front->next != NULL)
        {
            DeQueue(Q, q);               //�����еĺ����ڵ����������ʱ�ڵ���
            EnQueue(TempQ, q);
        }
        while (TempQ->front->next != NULL)
        {
            DeQueue(TempQ, q);           //����ʱ�ڵ������������ڵ���
            EnQueue(Q, q);
        }
    }
}
void DisplayStack(StackCar* S)
{
    int i;
    cout << "����Ҫ�鿴��ͣ����ͣ��������£�" << endl;
    cout << "��ͣ�����ĳ�λλ��\t�ó�λ�����ĳ��ƺ�\t����ʱ��" << endl << endl;
    if (S->top > 0)
        for (i = 1; i <= S->top; i++)
            cout << S->data[i]->weizi << " \t\t\t" << S->data[i]->num
            << "\t\t\t" << S->data[i]->reach.hour << ":" << S->data[i]->reach.min << endl << endl;
    else cout << endl << "ͣ������û�г�,�����޷���ʾ��Ҫ�鿴��ͣ����Ϣ!" << endl << endl;
}
void DisplayQueue(QueueCar* Q)
{
    QueueNode* t;
    int i;
    t = Q->front->next;
    if (Q->front != Q->rear)
    {
        cout << "����Ҫ�鿴�ı��ͣ��������£�" << endl;
        cout << "�ڱ���ϵĳ�λλ��\t�ó�λ�����ĳ��ƺ�\t����ʱ��" << endl << endl;
        for (i = 1; t != NULL; i++)
        {
            cout << t->data->weizi << " \t\t\t" << t->data->num << "\t\t\t"
                << t->data->reach.hour << ":" << t->data->reach.min << endl << endl;
            t = t->next;
        }
    }
    else cout << "�����û�г�,�����޷���ʾ��Ҫ�鿴��ͣ����Ϣ!" << endl << endl;
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
    StackCar S, TempS;       //SΪͣ�����ڳ���ջ��TempSΪ��ʱջ�������뿪��ջ��
    QueueCar Q, TempQ;       //���У����ͣ��,TempQΪ��ʱ���С������뿪��
    InitStack(&S);           //4����ʼ��
    InitStack(&TempS);
    InitQueue(&Q);
    InitQueue(&TempQ);
    char M;
    while (1)
    {
        menu();
        cout << "��������Ҫѡ��Ĺ�����ţ�";
        cin >> M;
        getchar();
        cout << endl;
        switch (M)
        {
        case '1':   InCarPark(&S, &Q);                 system("pause");  system("cls");       break;
        case '2':   OutCarPark(&S, &TempS, &Q, &TempQ); system("pause");  system("cls");       break;
        case '3':   DisplayStack(&S);                  system("pause");  system("cls");       break;
        case '4':   DisplayQueue(&Q);                  system("pause");  system("cls");       break;
        case '0':   return 0;
        default:
        {
            clear();
            cout << "���ѡ�����󣬴˹���ϵͳû�д���ܣ�" << endl << endl;
            system("pause");
            system("cls");
        }
        }
    }
    system("pause");
}