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
        cout << "Ваш выбор: ";
        cin >> choice;
        switch (choice)
        {
            
        case 1:
            cout << "Введите число: "; 

            while (!(cin >> value) || cin.peek() != '\n') {
                cout << "Ошибка! Введите число: ";
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            }
            insert(first, value);
            cout << "Элемент добавлен." << endl; 

            break;

        case 2:
            printList(first);
            break;

           
        case 3:   if (!IsEmpty(first)) 
        {
            cout << "Введите удаляемое число: ";
            cin >> value;
            if (del(first, value))
            {
                cout << "Удалено число " << value << endl;
                printList(first);
            }
            else
                cout << "Число не найдено!" << endl;
        }
              else
            cout << "Список пуст:(" << endl;
            break;
        
        case 4:   arifm(first);    
           
        case 5: toFile(first);
            break;
           
        case 6: fromFile(first);
            break;
           
        case 7: find(first);
            break;

        default:  cout << "Неправильный выбор!" << endl;
            menu();
            break;
        }
    }
    cout << "Конец." << endl;
    return 0;
}

void menu(void)  //Вывод меню 
{
    cout << "Сделайте выбор:" << endl;
    cout << " 1 - Ввод числа" << endl;
    cout << " 2 - Вывод числа" << endl;
    cout << " 3 - Удаление числа" << endl;
    cout << " 4 - Вычисление суммы отрицательных двухзначных" << endl;
    cout << " 5 - Запись в файл" << endl;
    cout << " 6 - Вывод из файла" << endl;
    cout << " 7 - Поиск элемента" << endl;
    cout << " 8 - Выход" << endl;
}
// -> доступ по указателю
void insert(list*& p, int value) //Добавление числа value в список 
{
    list* newP = new list;
    if (newP != NULL)     //есть ли место?  
    {
        newP->number = value;       // присваиваем введенное в главной функции вещественное значение
        newP->next = p;
        p = newP;
    }
    else
        cout << "Операция добавления не выполнена:(" << endl;
}

float del(list*& p, int value)  // Удаление числа 
{
    list* previous, * current, * temp;
    if (value == p->number)     //удаление предыдущего р, чтобы удалить первый р
    {
        temp = p;
        p = p->next;    // отсоединить узел 
        delete temp;      
        return value;
    }
    else
    {
        previous = p;
        current = p->next;
        while (current != NULL && current->number != value) // выполняется пока не найдем введенное значение(2 штуки перебрасываются последовательно)
        {
            previous = current;
            current = current->next; // перейти к следующему 
        }
        if (current != NULL)
        {
            temp = current;     // то, что будем удалять
            previous->next = current->next;     // переадресация
            free(temp); // удаление
            return value;
        }
    }
    return 0;
}
int IsEmpty(list* p) //Список  пустой? (1-да, 0-нет) 
{       // эту функцию можно сделать типа bool
    return p == NULL;
}
void printList(list* p)  //Вывод списка 
{
    list* temp = p; // Создаем временный указатель для обхода списка

    if (temp == NULL)
        cout << "Список пуст" << endl;
    else
    {
        cout << "Список:" << endl;
        while (temp != NULL) // Используем временный указатель для обхода списка
        {
            cout << "\t" << temp->number;
            temp = temp->next;
        }
        cout << "\tNULL" << endl;
    }
}

void arifm(list* p)  // Подсчет суммы
{
    int sm = 0;
    bool found = false; // Флаг для обозначения наличия отрицательных двузначных чисел
    if (p == NULL)      // если указатель на элемент списка = NULL
        cout << "Список пуст:(" << endl;
    else
    {
        while (p != NULL)   // пока указатель не равен NULL
        {
            if (p->number >= -99 && p->number <= -10)
            {
                sm += (p->number);
                found = true; // Устанавливаем флаг, если найдено отрицательное двузначное число
            }
            p = p->next;
        }
        if (found)
            cout << "Сумма отрицательных двузначных равна: " << sm << endl;
        else
            cout << "Отрицательных двузначных чисел нет в списке" << endl;
    }
}


void toFile(list*& p)
{
    list* temp = p;
    ofstream file1("text.txt");     // открываем файл для записи
    if (file1.fail())           // если файл не открыт
    {
        cout << "\n Ошибка открытия файла!";
        exit(1);
    }
    while (temp)        // пока элемент списка не равен NULL
    {
        int nn = temp->number;      // переменная для записи
        file1 << nn << "\n";        // записываем
        temp = temp->next;          // переходим на следующий
    }
    file1.close();      // закрываем файл
    cout << "\n";
}

void fromFile(list*& p)
{
    char buf[10];       // буфер

    ifstream file1("text.txt");     // открываем файл для чтения

    if (file1.fail())           // если файл не открыт
    {
        cout << "\n Ошибка открытия файла!";
        exit(1);
    }
    while (!file1.eof())        //пока не дочитали до конца файла
    {
        file1.getline(buf, 10);         //считываем строчку со значением
        if (strlen(buf))        //если длина > 0, то 
            insert(p, atoi(buf));       //добавляем в список
        cout << "\t" << buf;
    }
    cout << "\tNULL" << endl;
    file1.close();
}

void find(list* p)      // для поиска элементов
{
    bool isFind = false;
    int element;
    cout << "Введите элемент:" << endl;
    cin >> element;
    list* find = p;//с начала
    while (find)        // пока элементы списка не равны NULL
    {
        if (find->number == element)        // если элемент совпадает с введенным
        {
            isFind = true;//нашли
            printf("Элемент найден!\n");
            break;
        }
        find = find->next;          // иначе перебираем значения
    }
    if (!isFind)
        printf("Элемент не найден:(\n");
}
