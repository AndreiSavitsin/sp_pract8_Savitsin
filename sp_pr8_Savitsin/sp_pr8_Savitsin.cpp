#include <iostream>

struct FileInfo {
	char name[60];
	long size;
	char extension[10];
};

struct Node
{
public:
	FileInfo fileInfo;
	Node* next;
	Node* prev;

	Node(FileInfo file) : fileInfo(file), next(nullptr), prev(nullptr) {}	
};

class LinkList 
{
private:
	Node* head;
	Node* tail;	

public:
	LinkList()
	{
		this->head = nullptr;
		this->tail = nullptr;
	}

	Node* push_front(FileInfo fileInfo) //Добавления элемента в начало
	{
		Node* ptr = new Node(fileInfo);

		ptr->next = head;
		if (head != nullptr)
		{
			head->prev = ptr;
		}
		if (tail == nullptr)
		{
			tail = ptr;
		}
		head = ptr;

		return ptr;
	}

	Node* push_back(FileInfo fileInfo) //Добавление элемента в конец
	{
		Node* ptr = new Node(fileInfo);

		ptr->prev = tail;
		if (tail != nullptr)
		{
			tail->next = ptr;
		}
		if (head == nullptr)
		{
			head = ptr;
		}
		tail = ptr;

		return ptr;
	}

	void pop_front() //Удалить первый элемент
	{
		if (head == nullptr) return;

		Node* ptr = head->next;

		if (ptr != nullptr)
		{
			head->prev = nullptr;
		}
		else
		{
			tail = nullptr;
		}

		delete head;
		head = ptr;
	}

	void pop_back() //Удалить последний элемент
	{
		if (tail == nullptr) return;

		Node* ptr = tail->prev;

		if (ptr != nullptr)
		{
			tail->next = nullptr;
		}
		else
		{
			head = nullptr;
		}

		delete tail;
		tail = ptr;
	}

	void display_forward() //Вывести список
	{
		for (Node* ptr = this->head; ptr != nullptr; ptr = ptr->next)
		{
			std::cout << "\nНазвание файла: " << ptr->fileInfo.name << "\n";
			std::cout << "Размер файла: " << ptr->fileInfo.size << "\n";
			std::cout << "Расширение файла: " << ptr->fileInfo.extension << "\n";
			std::cout << std::endl;
		}		
	}

	void display_backward() //Вывести список в обратном порядке
	{
		for (Node* ptr = this->tail; ptr != nullptr; ptr = ptr->prev)
		{
			std::cout << "\nНазвание файла: " << ptr->fileInfo.name << "\n";
			std::cout << "Размер файла: " << ptr->fileInfo.size << "\n";
			std::cout << "Расширение файла: " << ptr->fileInfo.extension << "\n";
			std::cout << std::endl;
		}		
	}

	void find_key_field() //Поиск элемента по ключевому полю
	{
		std::cout << "Введите название файла для поиска: ";
		std::string fileName;
		std::cin >> fileName;

		if (fileName == "")
		{
			std::cout << "Нельзя оставлять поле пустым\n";
			return;
		}

		for (Node* ptr = this->head; ptr != nullptr; ptr = ptr->next)
		{
			if (fileName == ptr->fileInfo.name)
			{
				std::cout << "\nФайл найден:\n";
				std::cout << "Название файла: " << ptr->fileInfo.name << "\n";
				std::cout << "Размер файла: " << ptr->fileInfo.size << "\n";
				std::cout << "Расширение файла: " << ptr->fileInfo.extension << "\n";
				std::cout << std::endl;
			}
		}
	}

	void del_mid() //Удаление найденного элемента из середины списка
	{
		std::cout << "Введите название файла для поиска: ";
		std::string fileName;
		std::cin >> fileName;

		if (fileName == "")
		{
			std::cout << "Нельзя оставлять поле пустым\n";
			return;
		}

		Node* ptr = head;
		while (ptr != nullptr)
		{
			if (fileName == ptr->fileInfo.name)
			{
				if (ptr == head)      pop_front();
				else if (ptr == tail) pop_back();
				else
				{
					ptr->prev->next = ptr->next;
					ptr->next->prev = ptr->prev;
					delete ptr;
				}
				return;
			}
			ptr = ptr->next;
		}
	}

	void clear() //Полная очистка списка
	{
		Node* ptr = head;
		while (ptr != nullptr)
		{
			Node* next = ptr->next;
			delete ptr;
			ptr = next;
		}
		head = nullptr;
		tail = nullptr;
	}

	void find_biggest_file() //Найти самый большой файл
	{
		if (head == nullptr) {
			std::cout << "Список пуст\n";
			return;
		}

		Node* bigFile = this->head;
		for (Node* ptr = this->head; ptr != nullptr; ptr = ptr->next)
		{
			if (bigFile->fileInfo.size < ptr->fileInfo.size)
			{
				bigFile = ptr;
			}
		}

		std::cout << "\nСамый большой файл:\n";
		std::cout << "Название файла: " << bigFile->fileInfo.name << "\n";
		std::cout << "Размер файла: " << bigFile->fileInfo.size << "\n";
		std::cout << "Расширение файла: " << bigFile->fileInfo.extension << "\n";
		std::cout << std::endl;
	}


	void del_extension() //Удалить все файлы с указанным расширением
	{
		if (head == nullptr) {
			std::cout << "Список пуст\n";
			return;
		}

		std::cout << "\nВведите расширение: ";
		std::string exten;
		std::cin >> exten;

		if (exten == "")
		{
			std::cout << "Нельзя оставлять поле пустым\n";
			return;
		}

		Node* ptr = head;
		while (ptr != nullptr)
		{
			Node* next = ptr->next;

			if (exten == ptr->fileInfo.extension)
			{
				if (ptr == head)      pop_front();
				else if (ptr == tail) pop_back();
				else
				{
					ptr->prev->next = ptr->next;
					ptr->next->prev = ptr->prev;
					delete ptr;
				}
			}
			ptr = next;
		}
	}

	void move_biggest_file() //Переместить самый большой файл в конец списка
	{
		if (head == nullptr) {
			std::cout << "Список пуст\n";
			return;
		}


		Node* bigFile = head;
		for (Node* ptr = head; ptr != nullptr; ptr = ptr->next)
		{
			if (bigFile->fileInfo.size < ptr->fileInfo.size)
			{
				bigFile = ptr;
			}
		}

		if (bigFile == tail) return;

		if (bigFile->prev)
		{
			bigFile->prev->next = bigFile->next;
		}
		else
		{
			head = bigFile->next;
		}

		if (bigFile->next)
		{
			bigFile->next->prev = bigFile->prev;
		}
		else
		{
			tail = bigFile->prev;
		}

		bigFile->prev = tail;
		bigFile->next = nullptr;
		tail->next = bigFile;
		tail = bigFile;
	}
};

void PrintMenu() //Вывод меню
{	
	std::cout << "\n1. Добавить элемент в начало\n";
	std::cout << "2. Добавить элемент в конец\n";
	std::cout << "3. Удалить первый элемент\n";
	std::cout << "4. Удалить последний элемент\n";
	std::cout << "5. Вывести список\n";
	std::cout << "6. Вывести список в обратном порядке\n";
	std::cout << "7. Найти элемент\n";
	std::cout << "8. Удалить найденный элемент из середины списка\n";
	std::cout << "9. Найти самый большой файл\n";
	std::cout << "10. Удалить все файлы с указанным расширением\n";
	std::cout << "11. Переместить самый большой файл в конец списка\n";
	std::cout << "12. Полная очистка списка\n";
	std::cout << "13. Выход\n";
}


int main()
{
	setlocale(LC_ALL, "Russian");

	LinkList list;	
	FileInfo file;

	bool exit = false;
	int choice = 0;

	while (!exit)
	{
		PrintMenu();

		std::cin.clear();
		std::cin.ignore(10000, '\n');

		std::cout << "Выберите пункт из меню: ";
		std::cin >> choice;

		if (choice == 1 || choice == 2)
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "\nВведите название файла: ";
			std::cin >> file.name;

			std::cout << "Введите размер файла: ";
			std::cin >> file.size;

			std::cout << "Введите расширение файла: ";
			std::cin >> file.extension;
		}

		switch (choice)
		{
		case 1:
			list.push_front(file);
			break;
		case 2:
			list.push_back(file);
			break;
		case 3:
			list.pop_front();
			break;
		case 4:
			list.pop_back();
			break;
		case 5:
			list.display_forward();
			break;
		case 6:
			list.display_backward();
			break;
		case 7:
			list.find_key_field();
			break;
		case 8:
			list.del_mid();
			break;
		case 9:
			list.find_biggest_file();
			break;
		case 10:
			list.del_extension();
			break;
		case 11:
			list.move_biggest_file();
			break;
		case 12:
			list.clear();
			break;
		case 13:
			exit = true;
			break;
		default:
			std::cout << "Такого пункта нет в меню\n";
			break;
		}
	}
}