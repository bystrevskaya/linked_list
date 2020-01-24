#include <iostream>
#include <conio.h>

struct Elem
{
	int num;
	Elem* next;
	Elem* prev;
};

class List
{
private:
	Elem* Head;
	Elem* Tail;
	int count;
public:
	List() 
	{
		Head = Tail = NULL;
		count = -1;
	};
	typedef List* PList;
	void AddFirst(int digit)
	{
		Elem* temp = new Elem;
		temp->prev = NULL;
		temp->num = digit;
		temp->next = Head;
		if (Head != NULL)
			Head->prev = temp;
		if (count == -1)
			Head = Tail = temp;
		else Head = temp;
		count++;
	}
	void AddLast(int digit)
	{
		Elem* temp = new Elem;
		temp->next = NULL;
		temp->prev = Tail;
		temp->num = digit;
		if (Tail != NULL)
			Tail->next = temp;
		if (count == -1)
			Head = Tail = temp;
		else Tail = temp;
		count++;
	}
	void AddPosition(int pos, int digit)
	{
		if ((pos < 0) || (pos > count + 1))
		{
			std::cout << "ОШИБКА: некорректный номер позиции" << std::endl;
			return;
		}
		if (pos == count + 1)
		{
			AddLast(digit);
			return;
		}
		if (pos == 0)
		{
			AddFirst(digit);
			return;
		}
		int counter_ = 0;
		Elem* p = Head;
		while (counter_ < pos)
		{
			p = p->next;
			counter_++;
		}
		Elem* p_prev = p->prev;
		Elem* temp = new Elem;
		temp->num = digit;
		if ((p_prev != 0) && (count != 0))
			p_prev->next = temp;
		temp->next = p;
		temp->prev = p_prev;
		p->prev = temp;
		count++;
	}
	void DeletePosition(int pos_)
	{
		if (count == -1) 
		{
			std::cout << "ОШИБКА: использование функции невозможно, список пуст" << std::endl;
			return;
		}
		if ((pos_ < 0) || (pos_ > count))
		{
			std::cout << "ОШИБКА: некорректный номер позиции" << std::endl;
			return;
		}
		Elem* p = Head;
		int counter = 0;
		while (counter < pos_)
		{
			p = p->next;
			counter++;
		}
		Elem* p_next = p->next;
		Elem* p_prev = p->prev;
		if ((p_next != 0) && (count != 0))
			p_next->prev = p_prev;
		if ((p_prev != 0) && (count != 0))
			p_prev->next = p_next;
		if (pos_ == 0)
			Head = p_next;
		if (pos_ == count)
			Tail = p_prev;
		delete p;
		count--;
	}
	void ShowCount()
	{
		std::cout << "Число элементов в списке: " << count+1 << std::endl;
	}
	void ShowAll()
	{
		if (Head == NULL)
		{
			std::cout << "ОШИБКА: список пуст" << std::endl;
			return;
		}
		Elem* p = Head;
		while (p->next)
		{
			std::cout << p->num << " ";
			p = p->next;
		}
		std::cout << p->num << std::endl;
	}
	~List() {};
};

int Commands()
{
	setlocale(LC_ALL, "ru");
	char n[2];
	std::cout << "\nВыбери команду: \n1: Добавить элемент в начало списка \n2: Добавить элемент в конец списка \
    \n3: Ввести элемент на i-ю позицию \n4: Удалить элемент с i-й позиции \n5: Показать весь список \n6: Показать число элементов в списке \
	\n7: Выйти" << std::endl;
	std::cin >> n;
	return atoi(n); //перевод из char в int
};

void main()
{
	setlocale(LC_ALL, "ru");
	int num, comm, int_end = 7;
	List list;
	std::cout << "Добро пожаловать!" << std::endl;
	do
	{
		comm = Commands();
		switch (comm)
		{
		case 1: //добавить в начало
			std::cout << "Введите элемент: ";
			std::cin >> num;
			list.AddFirst(num);
			break;
		case 2: //добавить в конец
			std::cout << "Введите элемент: ";
			std::cin >> num;
			list.AddLast(num);
			break;
		case 3: //добавить на i позицию
			int pos;
			std::cout << "Введите номер позиции: ";
			std::cin >> pos;
			std::cout << "Введите элемент: ";
			std::cin >> num;
			list.AddPosition(pos, num);
			break;
		case 4: //удалить i-й элемент
			int pos_;
			std::cout << "Введите номер позиции: ";
			std::cin >> pos_;
			list.DeletePosition(pos_);
			break;
		case 5: //показать весь список
			list.ShowAll();
			break;
		case 6: //показать число элементов
			list.ShowCount();
			break;
		case 7: //выход
			std::cout << "До свидания!" << std::endl;
			return;
		default:
			std::cout << "Неверный номер команды! \nДаю еще попытку" << std::endl;
		}
	} while (comm != int_end);
	_getch();
}