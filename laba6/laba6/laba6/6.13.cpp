#include <iostream>
#include <fstream>
using namespace std;

struct list
{
    int number;
    list* next;
};

void insert(list*&, int); 
float del(list*&, int);   
int IsEmpty(list*);       
void printList(list*);     
void menu(void);     
void arifm(list*);  
void toFile(list*& p);
void fromFile(list*& p);
void find(list*);

int main()
{
    setlocale(LC_CTYPE, "Russian");
    list* first = NULL;
    int choice = 0;
    int value;
    menu();     
    while (choice != 8)
    {
        cout << "��� �����: ";
        cin >> choice;
        switch (choice)
        {
            
        case 1:
            cout << "������� �����: "; 

            while (!(cin >> value) || cin.peek() != '\n') {
                cout << "������! ������� �����: ";
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            }
            insert(first, value);
            cout << "������� ��������." << endl; 

            break;

        case 2:
            printList(first);
            break;

           
        case 3:   if (!IsEmpty(first)) 
        {
            cout << "������� ��������� �����: ";
            cin >> value;
            if (del(first, value))
            {
                cout << "������� ����� " << value << endl;
                printList(first);
            }
            else
                cout << "����� �� �������!" << endl;
        }
              else
            cout << "������ ����:(" << endl;
            break;
        
        case 4:   arifm(first);    
           
        case 5: toFile(first);
            break;
           
        case 6: fromFile(first);
            break;
           
        case 7: find(first);
            break;

        default:  cout << "������������ �����!" << endl;
            menu();
            break;
        }
    }
    cout << "�����." << endl;
    return 0;
}

void menu(void)  //����� ���� 
{
    cout << "�������� �����:" << endl;
    cout << " 1 - ���� �����" << endl;
    cout << " 2 - ����� �����" << endl;
    cout << " 3 - �������� �����" << endl;
    cout << " 4 - ���������� ����� ������������� �����������" << endl;
    cout << " 5 - ������ � ����" << endl;
    cout << " 6 - ����� �� �����" << endl;
    cout << " 7 - ����� ��������" << endl;
    cout << " 8 - �����" << endl;
}
// -> ������ �� ���������
void insert(list*& p, int value) //���������� ����� value � ������ 
{
    list* newP = new list;
    if (newP != NULL)     //���� �� �����?  
    {
        newP->number = value;       // ����������� ��������� � ������� ������� ������������ ��������
        newP->next = p;
        p = newP;
    }
    else
        cout << "�������� ���������� �� ���������:(" << endl;
}

float del(list*& p, int value)  // �������� ����� 
{
    list* previous, * current, * temp;
    if (value == p->number)     //�������� ����������� �, ����� ������� ������ �
    {
        temp = p;
        p = p->next;    // ����������� ���� 
        delete temp;      
        return value;
    }
    else
    {
        previous = p;
        current = p->next;
        while (current != NULL && current->number != value) // ����������� ���� �� ������ ��������� ��������(2 ����� ��������������� ���������������)
        {
            previous = current;
            current = current->next; // ������� � ���������� 
        }
        if (current != NULL)
        {
            temp = current;     // ��, ��� ����� �������
            previous->next = current->next;     // �������������
            free(temp); // ��������
            return value;
        }
    }
    return 0;
}
int IsEmpty(list* p) //������  ������? (1-��, 0-���) 
{       // ��� ������� ����� ������� ���� bool
    return p == NULL;
}
void printList(list* p)  //����� ������ 
{
    list* temp = p; // ������� ��������� ��������� ��� ������ ������

    if (temp == NULL)
        cout << "������ ����" << endl;
    else
    {
        cout << "������:" << endl;
        while (temp != NULL) // ���������� ��������� ��������� ��� ������ ������
        {
            cout << "\t" << temp->number;
            temp = temp->next;
        }
        cout << "\tNULL" << endl;
    }
}

void arifm(list* p)  // ������� �����
{
    int sm = 0;
    bool found = false; // ���� ��� ����������� ������� ������������� ���������� �����
    if (p == NULL)      // ���� ��������� �� ������� ������ = NULL
        cout << "������ ����:(" << endl;
    else
    {
        while (p != NULL)   // ���� ��������� �� ����� NULL
        {
            if (p->number >= -99 && p->number <= -10)
            {
                sm += (p->number);
                found = true; // ������������� ����, ���� ������� ������������� ���������� �����
            }
            p = p->next;
        }
        if (found)
            cout << "����� ������������� ���������� �����: " << sm << endl;
        else
            cout << "������������� ���������� ����� ��� � ������" << endl;
    }
}


void toFile(list*& p)
{
    list* temp = p;
    ofstream file1("text.txt");     // ��������� ���� ��� ������
    if (file1.fail())           // ���� ���� �� ������
    {
        cout << "\n ������ �������� �����!";
        exit(1);
    }
    while (temp)        // ���� ������� ������ �� ����� NULL
    {
        int nn = temp->number;      // ���������� ��� ������
        file1 << nn << "\n";        // ����������
        temp = temp->next;          // ��������� �� ���������
    }
    file1.close();      // ��������� ����
    cout << "\n";
}

void fromFile(list*& p)
{
    char buf[10];       // �����

    ifstream file1("text.txt");     // ��������� ���� ��� ������

    if (file1.fail())           // ���� ���� �� ������
    {
        cout << "\n ������ �������� �����!";
        exit(1);
    }
    while (!file1.eof())        //���� �� �������� �� ����� �����
    {
        file1.getline(buf, 10);         //��������� ������� �� ���������
        if (strlen(buf))        //���� ����� > 0, �� 
            insert(p, atoi(buf));       //��������� � ������
        cout << "\t" << buf;
    }
    cout << "\tNULL" << endl;
    file1.close();
}

void find(list* p)      // ��� ������ ���������
{
    bool isFind = false;
    int element;
    cout << "������� �������:" << endl;
    cin >> element;
    list* find = p;//� ������
    while (find)        // ���� �������� ������ �� ����� NULL
    {
        if (find->number == element)        // ���� ������� ��������� � ���������
        {
            isFind = true;//�����
            printf("������� ������!\n");
            break;
        }
        find = find->next;          // ����� ���������� ��������
    }
    if (!isFind)
        printf("������� �� ������:(\n");
}
