#include <iostream>
using namespace std;

template <typename T>
class MyList
{
public:
	MyList();
	~MyList();
	void push_back(T data);				// метод для вставки элемента в конец списка
	int GetSize() { return Size; }		// метод для подсчета элементов в списке
	T& operator[] (const int index);	// перегруженный оператор квадратных скобок
	void pop_front();					// метод для удаления элемента в начале списка
	void clear();						// метод для очистки всех элементов (pop_front в цикле)
	void push_front(T data);			// метод для вставки элемента в начало списка
	void insert(T value, int index);	// метод для вставки элемента по индексу
	void removeAt(int index);			// метод для удаления элемента по индексу
	void pop_back();					// метод для удаления последнего элемента

private:
	template <typename T>
	class Node
	{
	public:
		Node(T data = T(), Node *pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}

		Node *pNext;
		T data;
	};

	Node<T> *head;
	int Size;
};

template <typename T>
MyList<T>::MyList()
{
	Size = 0;
	head = nullptr;
}

template <typename T>
MyList<T>::~MyList()
{
	clear();
}

template<typename T>
void MyList<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node <T>(data);
	}
	else
	{
		Node <T> *current = this->head;
		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node <T>(data);
	}
	Size++;
}

template<typename T>
T& MyList<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}

template<typename T>
void MyList<T>::pop_front()
{
	Node<T> *temp = head;
	head = head->pNext;
	delete temp;
	Size--;
}

template<typename T>
void MyList<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
}

template<typename T>
void MyList<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	Size++;
}

template<typename T>
void MyList<T>::insert(T data, int index)
{
	if (index == 0)
	{
		push_front(data);
	}
	else
	{
		Node<T> *previous = this->head;

		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* newNode = new Node<T>(data, previous->pNext);

		previous->pNext = newNode;

		Size++;
	}
}

template<typename T>
void MyList<T>::removeAt(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* previous = this->head;

		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* toDelete = previous->pNext;

		previous->pNext = toDelete->pNext;

		delete toDelete;

		Size--;
	}
}

template<typename T>
void MyList<T>::pop_back()
{
	removeAt(Size - 1);
}

int main()
{
	setlocale(LC_ALL, "rus");

	MyList<int> mlst;

	mlst.push_back(3);	// вставка элемента в конец списка
	mlst.push_front(7);	// вставка элемента в начало списка
	mlst.push_back(2);

	cout << "Количество элементов: " << mlst.GetSize() << endl;

	for (int i = 0; i < mlst.GetSize(); i++)
	{
		cout << i + 1 << "-ый элемент: " << mlst[i] << endl;
	}

	return 0;
}