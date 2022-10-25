
/*
    ͣ������ϵͳ��ͣ������λ�ñ����ͣ���������ٽ�������ͣ��������Ϊ3���û�����ơ�
    ��ͣ�����г����뿪����ϵĳ�����ͣ������
*/

#include <iostream>
#include <iomanip>
#include <malloc.h>
#include <time.h>

using namespace std;    //��׼�����ռ�
#define Max 3           //ͣ��������
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
int InitStack(StackCar* S);                   //��ʼ��ջ
int InitQueue(QueueCar* Q);                   //��ʼ������
int findspace(StackCar* S);                  //�ҵ��յ�ͣ��λ
void DisplayStack(StackCar* S);               //��ʾͣ����ͣ�����
void DisplayQueue(QueueCar* Q);               //��ʾ���ͣ�����
int Push(StackCar* S, CarNode* p);            //��ջ����
int Pop(StackCar* S, CarNode* (&p));          //��ջ����
int EnQueue(QueueCar* Q, CarNode* p);         //�������
int PushStack(StackCar* S, CarNode* p);       //���ڵ�ѹջ
int DeQueue(QueueCar* Q, CarNode* (&q));      //��ջ����
void PriceCal(CarNode* p, int Location);      //����۸�
void InCarPark(StackCar* Enter, QueueCar* Q); //ͣ����վ
void OutCarPark(StackCar* Out, StackCar* Temp, QueueCar* Q); //�뿪ͣ����


void clear()                //���ܣ����������н���������������
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
int InitStack(StackCar* S)      //��ʼ��ջ
{
    S->top = 0;
    return 0;
}
int InitQueue(QueueCar* Q)      //��ʼ������
{
    Q->front = Q->rear = (QueueNode*)malloc(sizeof(QueueNode));
    if (!Q->front)              //����ռ�ʧ���˳�����
        exit(ERROR);
    Q->front->next = NULL;      //Ϊ��
    return 0;
}
int findspace(StackCar* S)     //�ҵ�ͣ���������λ��
{
    if (S->top == 1)            //��ͣ������ֻ��һ����λ��ռ��
    {
        switch (S->data[1]->weizi)
        {
        case 1: return 2; case 2: return 3; case 3: return 1;
        }
    }
    else if (S->top == 2)       //��ͣ������������λ�ñ�ռ��
    {
        if (S->data[1]->weizi == 1 && S->data[2]->weizi == 2) return 3;
        if (S->data[1]->weizi == 1 && S->data[2]->weizi == 3) return 2;
        if (S->data[1]->weizi == 2 && S->data[2]->weizi == 3) return 1;
    }
    else if (S->top == 3)        //û��ͣ��λ
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
    cout << endl << "ͣ������λ��������������ڱ����ͣ���ȴ�!" << endl;
    QueueNode* t;
    t = (QueueNode*)malloc(sizeof(QueueNode));  //Ϊ�ڵ�����ڴ�
    if (!t)   exit(ERROR);
    t->data = p;                                //�ڵ㸳ֵ
    t->next = NULL;                             //������е����һ���ڵ��nextΪNULL
    Q->rear->next = t;                          //��β�ڵ�nextָ���½ڵ�
    Q->rear = t;                                //��βָ��ָ���½ڵ�
    cout << "************�����ڱ����ͣ���ɹ�***********" << endl << endl;
    return 0;
}
int DeQueue(QueueCar* Q, CarNode* (&q))         //������
{
    QueueNode* t;
    t = Q->front->next;                         //��ʱ�ڵ�
    q = t->data;
    Q->front->next = t->next;                   //ͷ�ڵ��nextָ������еĵڶ����ڵ�
    if (Q->rear == t)                           //���һ���ڵ���Ҫ����ͷ�Ͷ�β�������Ƴ�ʼ��
        Q->rear = Q->front;
    free(t);                                    //�ͷű�ɾ���ڵ���ڴ�ռ�
    return 0;
}

//����۸�
//����24Сʱʱ��(23-a.h+l.h)*60 + (60 - r.m+l.m)
//24Сʱ�ڣ�(a.h-l.h)*60+(a.m-l.m)        
void PriceCal(CarNode* p, int Location)
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
    cout << "������Ӧ������Ϊ��<��λ��Ԫ>";         //fixed��setprecisimΪ����������ȡ�
    if ((p->leave.hour < p->reach.hour) || ((p->leave.hour == p->reach.hour) && (p->leave.min < p->reach.min)))
        cout << fixed << setprecision(2) << ((23 - p->reach.hour + p->leave.hour) * 60 + (60 - p->reach.min + p->leave.min)) * Price << endl << endl;
    else
        cout << fixed << setprecision(2) << ((p->leave.hour - p->reach.hour) * 60 + (p->leave.min - p->reach.min)) * Price << endl << endl;
    free(p);
}
void InCarPark(StackCar* Enter, QueueCar* Q)   //������Ϣ
{
    CarNode* p;
    p = (CarNode*)malloc(sizeof(CarNode));     //�����ڵ��ڴ�����
    cout << "�����뵽�������ĳ��ƺţ�";
    cin >> p->num;
    clear();
    if (Enter->top < Max)                      //ջû��
    {
        if (Enter->top == 0)                   //���ջ�գ��򳵽���ͣ������һ��λ��
            p->weizi = 1;
        else
            p->weizi = findspace(Enter);       //ջ���գ�����ճ�λ
        Push(Enter, p);                        //ѹջ
    }
    else EnQueue(Q, p);                        //ջ���������������

}
void OutCarPark(StackCar* Out, StackCar* Temp, QueueCar* Q)
{
    int Location = 0;
    int top = Out->top;
    CarNode* p, * q;
    DisplayStack(Out);                  //չʾĿǰͣ�����ڵĳ�����Ϣ
    if (Out->top > 0)
    {
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
        while (Out->top > Location)       //������λ�ú�ǰ������ջ�ڵ��ջ
        {
            Pop(Out, p);                //ջ��ջ����ջ������ʱջ
            PushStack(Temp, p);         //��ջ�ڵ������ʱջ
        }
        Pop(Out, p);                    //��Ҫ��ջ��Ԫ�س�ջ
        PriceCal(p, Location);          //�����뿪�ĳ�����ͣ����
        while (Temp->top >= 1)          //����ʱջ�Ľڵ����ѹ��ջ��
        {
            Pop(Temp, p);               //Temp,Temp->data[Temp->top];
            PushStack(Out, p);          //Out,Temp->data[Temp->top];
        }
        if ((Q->front != Q->rear) && Out->top < Max)
        {
            DeQueue(Q, q);              //�����н��tȡֵdata�������q��������;
            cout << "*************�����λλ��[1]������������ͣ����**************" << endl;
            q->weizi = findspace(Out);
            Push(Out, q);               //�����г��Ľڵ�ѹ��ջ��
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
    StackCar S, Temp;       //SΪͣ�����ڳ���ջ��tempΪ��ʱջ�������뿪��ջ��
    QueueCar Q;             //���У����ͣ��
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