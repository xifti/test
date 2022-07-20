/*
 TODO: Написать анализатор для проверки введенной Фамилии Автора



Расширить функционал:

1) Сделать режим проверки выдачи в аренду, товара (допилить в Serch)


 2) Добавить возможность заносить новые книги, при добавлении должен считываться штрих код, !!
(Можно только +овать) после чего должна быть проверка нет ли уже в DataBase такой книги, если есть то предложить добавить количество поступивших книг
Сотрудник должен иметь возможность изменять 'название книги' и 'Имя автора'



3) Добавить возможность удалять позиции, (чтобы можно было редактировать не верно введенные позиции)
Доступ к этой функции должен быть ID_Card (чтобы не каждый пользователь имел доступ к ней)



TODO: 4) Выдача в аренду
TODO: с занесением контактных данных человека (ФИО, Номер Телефона, дата оформления аренды, Дата возврата по аренде),
TODO: который взял в аренду товар,
TODO: с занесением даты выдачи и возможность внесения даты срока аренды



TODO: 4.1)функция продажи товара для сотрудника
TODO: 4.2) Функция просмотра дневной продажи у сотрудников (у админа и менеджера)

TODO: При продаже нужно уточнять оплата будет за наличные или за безнал,
TODO: если наличные, то кассир вводит сумму денег которую он получил от покупателя, а программа выдает ему сумму сдачи
TODO: если наличные, то нужно подсчитывать сколько денег должно быть в кассе по окончании рабочего дня


5) Реализовать вход в программу по ID_Card
5.1) Реализовать базу данных сотрудников

6) Реализовать администратора который сможет добавлять новых пользователей (присваивать им номер для ID_Card)
пофиксить права для новых пользователей
7) В админ меню добавить функцию добавления новых сотрудников.
в админ меню должна быть функция удалять пользователей;

8) Сделать возможность выхода из программы для сотрудников и администратора в меню ввода ID






TODO: админ должен иметь право менять количество денег в кассе

*/




#include <iostream>
#include <vector>
#include <windows.h>
#include "Access.h"
#include "Database.h"
#include "Shopping.h"
#include "Working_with_text.h"






const char PRINT = ';';

const std::string PROMPT = "> ";
const std::string EXIT = "exit";
const std::string QUITE = "quite";






struct Book
{
	Book() {}
	Book(char ch) : pr{ ch } {}
	Book(std::string i, double v) : ISBN{ i }, val{ v }  { }

	char pr;
	double val = 0.0;
	std::string ISBN;
};


struct Database
{
	Database() { }
	Database(std::string art, std::string human_name, std::string name_book, int yy, int st, int les, double pri) :
		ISBN{ art }, author_last_name{ human_name }, book_name{ name_book }, year{ yy }, stock{ st }, leased{ les }, price{ pri } {}


	std::string ISBN;
	std::string author_last_name;
	std::string book_name;
	int year;
	int stock;
	int leased;
	double price;
};

std::vector<Database> base{ { "123A","Lupovich","Pereputali",2015, 10, 1, 10.0 } , { "123B","Mujhik","Bipki",2012, 10, 0 , 10.0 }, { "123C","Greka","Cancer",1985, 10, 0 , 10.0 },
	{ "123D","Pisev","Vpopu",2000, 10, 2 , 10.0 }, { "123H","Unichtozhil","Gosudarstvo",1900 , 10, 0 , 10.0 } ,{ "123F","Dugin","Dasein",2020 , 10, 0 , 10.0 } ,
	{ "123G","POHUY","Jija",2001 , 10, 0 , 10.0 } ,{ "123H","Fil'kina","Gramota",1990 , 10, 0,10.0} };


struct Access
{
	Access() { }
	Access(std::string acc, std::string lastname_employee, std::string ID) :access_level{ acc }, employee_name{ lastname_employee }, ID_employee{ ID } { }

	std::string access_level;   // admin or employee
	std::string employee_name;  // фамилия работника
	std::string ID_employee;    // Код доступа
};

std::vector<Access> USERS{ { "admin","Mihail", "`"} , {"employee","Pupa","zarplata"} ,{"employee","Lupa","pereputali"}, {"unknown_user", "",""} };

class Shopping
{


	Database item;

	double total_purchase_price = 0.0;
	std::vector<Database>shopping_cart;
};


std::ostream& operator<<(std::ostream& os, const Database& d)
{

	return os << "\t# ISBN               \t: " << d.ISBN << '\n'
		<< "\t# Book title         \t: " << d.book_name << '\n'
		<< "\t# Author of the Book \t: " << d.author_last_name << '\n'
		<< "\t# Year of issue      \t: " << d.year << '\n'
		<< "\t# In stock           \t: " << d.stock << '\n'
		<< "\t# Leased             \t: " << d.leased << '\n'
		<< "\t# Price              \t: " << d.price
		<< std::endl;
}

/*

Условная база данных с хранящейся информацией по "книгам"

хранятся:
 TODO: ISBN, Название книги, Автор книги, год выпуска. (нужно доделать чтобы было больше параметров)

*/


class Book_stream
{
private:
	Book buffer;
	bool full;
	std::istream& strm;

public:
	Book_stream(std::istream& is = std::cin) : buffer{ 0 }, full{ 0 }, strm{ is } { }

	//надо сделать абстрактный класс
	Book get();
	Book get_add_names();
	Book get_add_numbers();


	void unget(Book& b) { buffer = b; full = true; };
	void ignore(char);
};
//оставляем
Book creating_names(Book& b);

bool YES_NO(Book& b)
{
	creating_names(b);

	if (b.ISBN == "Y" || b.ISBN == "y" || b.ISBN == "Yes" || b.ISBN == "YES" || b.ISBN == "yes")
	{
		return true;
	}
	if (b.ISBN == "N" || b.ISBN == "n" || b.ISBN == "No" || b.ISBN == "NO" || b.ISBN == "no")
	{
		std::cout << "Try Again or use comand 'exit':\n";
		return false;
	}
	else
	{
		std::cout << "Incorrect input\nTry Again or use comand 'exit':\n";
		return false;
	}
}

void Book_stream::ignore(char c)
{
	if (full && c == buffer.pr)
	{
		full = false;
		return;
	}
	full = false;

	char ch;
	while (strm >> ch)
	{
		if (ch == c) return;
	}
}

Book_stream bs;

void clean_up_mess(Book_stream& ts)
{
	ts.ignore(PRINT);
}


Book Book_stream::get() //Сделать что-то с вводом корректных значений, чтобы они разделялись между собой символом каким-то
{
	if (full)
	{
		full = false;
		return buffer;
	}

	char ch;
	strm >> ch;

	if (strm.eof())
	{
		std::cout << "gg_eof\n";
		return Book(EXIT, 0.0);
	}


	if (ch)
	{
		std::string s = "";

		if (iswdigit(ch))
		{
			s += ch;
			while (strm.get(ch) && s.size() != 3 && iswdigit(ch))
			{
				s += ch;
			}

			if (isupper(ch) || iswdigit(ch))
			{
				s += ch;
				return Book(s, 0.0);
			}

			if (islower(ch))
			{
				ch = ch - 32;
				s += ch;
				return Book(s, 0.0);
			}
		}

		if (s.size() != 4) //если пользователь ошибся при вводе, то отбраковываем это значение
		{
			s += ch;
			while (strm.get(ch) && isprint(ch))
			{
				s += ch;
			}

			if (s == EXIT) { return Book(EXIT, 0.0); }
			s = "unknown";
			return Book(s, 0.0);
		}
	}
}

void search(Book& b)
{

	try
	{
		std::cout << PROMPT;
		b = bs.get();
		while (b.pr == PRINT)
		{
			b = bs.get();
		}
	}

	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		clean_up_mess(bs);
	}

}


Book Book_stream::get_add_names()
{
	if (full)
	{
		full = false;
		return buffer;
	}

	char ch;
	strm >> ch;

	if (strm.eof())
	{
		std::cout << "gg_eof\n";
		return Book(EXIT, 0.0);
	}
	std::string s;
	s += ch;
	while (strm.get(ch) && isprint(ch))
	{
		s += ch;
	}

	if (s == EXIT) { return Book(EXIT, 0.0); }
	return Book(s, 0.0);

}

Book creating_names(Book& b)
{

	try
	{
		std::cout << PROMPT;
		b = bs.get_add_names();
		while (b.pr == PRINT)
		{
			b = bs.get_add_names();
		}
	}

	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		clean_up_mess(bs);
	}

	return b;

}


Book Book_stream::get_add_numbers()
{
	if (full)
	{
		full = false;
		return buffer;
	}

	char ch;
	strm >> ch;

	switch (ch)
	{
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	strm.unget();
	double val;
	strm >> val;
	return Book("", val);
	}
	default:

		std::string s;
		s += ch;
		while (strm.get(ch) && (ispunct(ch) || isalpha(ch)))
		{
			s += ch;
		}

		if (s == EXIT) { return Book(EXIT, 0.0); }
		s = "unknown";
		return Book(s, -1000000.0);

	}

}

Book creating_numbers(Book& b)
{

	try
	{
		std::cout << PROMPT;
		b = bs.get_add_numbers();
		while (b.pr == PRINT)
		{
			b = bs.get_add_numbers();
		}
	}

	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		clean_up_mess(bs);
	}

	return b;

}


//нужно переместить в Database
void info(Book& b)
{
	for (const Database& item : base)
	{
		if (item.ISBN == b.ISBN)
		{
			std::cout << item;
			return;
		}
	}
	std::cout << "No such ISBN found\n";
	return;
}

//нужно переместить в Database
//не доредактирована
Database search_for_purchase(Book& b)
{
	for (const Database& item : base)
	{
		if (item.ISBN == b.ISBN)
		{
			std::cout << item.book_name << ' ';
			return item;
		}
	}

	Database fail;
	std::cout << "No such ISBN found\n";
	fail = { "UNKNOWN_ITEM","UNKNOWN_ITEM","UNKNOWN_ITEM",0, 0, 0, 0.0 };
	return fail;
}

//нужно переместить в Shopping
bool search_inside_the_shopping_cart(std::vector<Database>& shopping_cart, Book& b, double& total_purchase_price)
{
	bool confirm = false;

	for (Database& item : shopping_cart)
	{
		if (item.ISBN == b.ISBN)
		{
			std::cout << item.book_name << ' ' << "Price: " << item.price << '\n';
			item.price += item.price;
			++item.stock;
			total_purchase_price += item.price;
			std::cout << "Total price: " << total_purchase_price << '\n';

			confirm = true;
			return confirm;
		}
	}

	return confirm;

}

//нужно переместить в Shopping
 //bool??
void сhanging_the_quantity_in_a_position(Database& item, Book& b, double& total_purchase_price)
{
	bool confirm = false;
	double SAVE_b_val = 0.0;
	while (confirm != true)
	{
		std::cout << item.book_name << " | Price: " << item.price << " | Quantity: " << item.stock << '\n';

		if (item.stock > 1)
		{
			std::cout << "How many pieces need to be removed?\n";

			bool confirm = false;
			while (confirm != true)
			{
				creating_numbers(b);
				if (b.val <= item.stock && b.val > 0)
				{
					SAVE_b_val = b.val;

					std::cout << '>' << SAVE_b_val << '<' << " Confirm?\n ('Y' / 'N')\n";
					confirm = YES_NO(b);
				}
				if (b.ISBN == EXIT)
				{
					return;
				}
			}
			SAVE_b_val *= item.price;
			total_purchase_price -= SAVE_b_val;

			std::cout << "Done!\n"
				<< "Total Price now: " << total_purchase_price << std::endl;

		}
		else
		{
			SAVE_b_val = 1.0;
			SAVE_b_val *= item.price;
			std::cout << "Do you want to deduct the " << SAVE_b_val << " for " << item.book_name << " item from the " << total_purchase_price << " cost?";

			confirm = false;
			confirm = YES_NO(b);

			if (confirm == true)
			{
				total_purchase_price -= SAVE_b_val;
			}
			else
			{

			}
		}


	}
	std::cout << "Done!\n";
	return;
}

//нужно переместить в Shopping
//TODO: создать it который удалит значение из вектора, разобраться с этой функцией до конца.!!!!!!!
bool search_inside_the_shopping_cart_for_delite(std::vector<Database>& shopping_cart, Book& b, double& total_purchase_price)
{

	for (Database& item : shopping_cart)
	{
		if (item.ISBN == b.ISBN)
		{
			сhanging_the_quantity_in_a_position(item, b, total_purchase_price);
			if (item.stock == 0)
			{
				shopping_cart.erase(item);
			}
		}
	}

	return;
}

//нужно переместить в Shopping
bool delite_inside_the_shopping_cart(std::vector<Database>& shopping_cart, Book& b, double& total_purchase_price)
{
	std::cout << "'1' - If you want to remove an item from the cart\n"
		<< "'2' - Proceed to checkout\n"
		<< "'3' - Refusal to buy" << std::endl;

	while (true)
	{
		creating_numbers(b);

		if (b.val == 1)
		{
			std::cout << "Scan the barcode of the item you want to remove from the cart:\n";
			search(b);
			search_inside_the_shopping_cart_for_delite(shopping_cart, b, total_purchase_price)

		}
		if (b.val == 2)
		{

		}
		if (b.val == 3)
		{

		}
	}
}


//нужно переместить в Database
void delite_item_in_base(Book& b)
{
	for (std::vector<Database>::iterator it = base.begin(); it != base.end();)
	{
		Database del = *it;
		if (del.ISBN == b.ISBN)
		{
			std::cout << "\n\n" << del << "\n\nConfirm? ('Y' / 'N')\n";
			creating_names(b);

			if (b.ISBN == "Y" || b.ISBN == "y" || b.ISBN == "Yes" || b.ISBN == "YES" || b.ISBN == "yes")
			{
				it = base.erase(it);
				std::cout << del.ISBN << " this object removed\nIf you have finished deleting, use the 'exit' command\n";
				return;
			}
			else
			{
				std::cout << "If you have finished deleting, use the 'exit' command\n";
				return;
			}
		}
		else
		{
			++it;
		}
	}

	std::cout << "This " << b.ISBN << " object not found\n";
}

//нужно переместить в Database
void delite_USERS_in_base(Book& b)
{
	for (std::vector<Access>::iterator it = USERS.begin(); it != USERS.end();)
	{
		Access del = *it;
		if (del.employee_name == b.ISBN)
		{
			std::cout << "\n\n\n"
				<< "You want to remove this user from the database:\n\n"
				<< "His access level     :      # " << del.access_level << '\n'
				<< "His employee name    :      # " << del.employee_name << '\n'
				<< "His password         :      # " << del.ID_employee << "\n\n"
				<< "Confirm? ('Y' / 'N')\n";
			creating_names(b);

			if (b.ISBN == "Y" || b.ISBN == "y" || b.ISBN == "Yes" || b.ISBN == "YES" || b.ISBN == "yes")
			{
				it = USERS.erase(it);
				std::cout << del.employee_name << " This user has been removed\nIf you have finished deleting, use the 'exit' command\n";
				return;
			}
			else
			{
				std::cout << "If you have finished deleting, use the 'exit' command\n";
				return;
			}
		}
		else
		{
			++it;
		}
	}

	std::cout << "This " << b.ISBN << " object not found\n";
}

void new_item_add(Book& b);

//нужно переместить в Shopping
void сhanging_product_data(Book& b) // дотестировать корректность работы
{
	bool confirm = false;
	std::string save_ISBN = "";
	int save_container = 0;

	for (Database& product : base)
	{
		if (product.ISBN == b.ISBN)
		{
			std::cout << product << '\n';

			//Что вы хотите изменить?
			std::cout << "What do you want to change?\n\n"
				<< "'1'    - >" << product.author_last_name << "<\n"
				<< "'2'    - >" << product.book_name << "<\n"
				<< "'3'    - >" << product.year << "<\n"
				<< "'4'    - >" << product.stock << "<\n"
				<< "'exit' - to exit\n";

			creating_names(b);
			if (b.ISBN == "1")
			{
				std::cout << "Enter the author's last name to replace the existing one: " << product.author_last_name << '\n';

				confirm = false;
				while (confirm != true)
				{
					creating_names(b);
					save_ISBN = b.ISBN;

					if (b.ISBN == EXIT)
					{
						return;
					}

					std::cout << "Check for correctness:    >" << save_ISBN << "<\n('Y' / 'N')\n";

					confirm = YES_NO(b);
				}

				product.author_last_name = save_ISBN;
				std::cout << "Done!\n"
					<< "The product map now looks like this:\n\n"
					<< product << "\n\n"
					<< "If u need go to menu use comand 'exit':\n";

				return;

			}
			else if (b.ISBN == "2")
			{
				std::cout << "Enter the name of the book to replace an existing: " << product.book_name << '\n';

				confirm = false;
				while (confirm != true)
				{
					creating_names(b);
					save_ISBN = b.ISBN;

					if (b.ISBN == EXIT)
					{
						return;
					}

					std::cout << "Check for correctness:    >" << save_ISBN << "<\n('Y' / 'N')\n";

					confirm = YES_NO(b);
				}

				product.book_name = save_ISBN;
				std::cout << "Done!\n"
					<< "The product map now looks like this:\n\n"
					<< product << "\n\n"
					<< "If u need go to menu use comand 'exit':\n";

				return;
			}
			else if (b.ISBN == "3")
			{

				std::cout << "Enter the number of unlisted books:\n";
				confirm = false;
				while (confirm != true)
				{
					creating_numbers(b);
					save_container = b.val;
					if (b.ISBN == EXIT)
					{
						return;
					}
					if (b.val > 1800 && b.val < 2023) //устанавливаем рамки корректных значений для года
					{
						std::cout << "Check for correctness:    >" << save_container << "<\n('Y' / 'N')\n";
						confirm = YES_NO(b);
					}
					else
					{
						std::cout << "Incorrect input\nTry Again or use comand 'exit':\n";
					}

				}

				product.year = save_container;
				std::cout << "\nWelldone!\n\n\n";
				std::cout << product << "\n\n\n";
				std::cout << "If u need go to menu use comand 'exit':\n";
				return;
			}
			else if (b.ISBN == "4") //TODO: тест отрицательный
			{

				std::cout << "Enter the number of unlisted books:\n";
				confirm = false;
				while (confirm != true)
				{
					creating_numbers(b);
					save_container = b.val;
					if (b.ISBN == EXIT)
					{
						return;
					}
					if (b.val > 0 && b.val < 10000) //устанавливаем рамки корректных значений для количества
					{
						std::cout << "Check for correctness:    >" << save_container << "<\n('Y' / 'N')\n";
						confirm = YES_NO(b);
					}
					else
					{
						std::cout << "Incorrect input\nTry Again or use comand 'exit':\n";
					}

				}

				product.stock += save_container;
				std::cout << "\nWelldone!\n\n\n";
				std::cout << product << "\n\n\n";
				std::cout << "If u need go to menu use comand 'exit':\n";
				return;

			}
			else if (b.ISBN == EXIT)
			{
				std::cout << "Enter the ISBN of the item you want to change or use 'exit' to exit the menu\n";
				return;
			}

		}
	}
	if (b.ISBN != "unknown")
	{
		new_item_add(b);
	}
	else
	{
		std::cout << "Incorrect value. \n> Try again:\n";
	}
	return;

}

//нужно переместить в Database
void new_item_add(Book& b)
{
	bool confirm = false;
	std::string save_ISBN = b.ISBN; //запомнили значение ISBN чтобы оно не потерялось при вызове creating_names(b)

	std::cout << "You want to add an    >" << b.ISBN << "<\n('Y' / 'N')\n";
	confirm = YES_NO(b);
	if (confirm == true)
	{
		Database add;

		add.ISBN = save_ISBN; //внесли ISBN

		std::cout << "Enter the author's last name:\n";
		confirm = false;
		while (confirm != true)
		{
			creating_names(b);
			save_ISBN = b.ISBN;

			if (b.ISBN == EXIT)
			{
				return;
			}

			std::cout << "Check for correctness:    >" << save_ISBN << "<\n('Y' / 'N')\n";

			confirm = YES_NO(b);
		}
		add.author_last_name = save_ISBN; //внесли Фамилию автора


		std::cout << "Enter book title:\n";
		confirm = false;
		while (confirm != true)
		{
			creating_names(b);
			save_ISBN = b.ISBN;

			if (b.ISBN == EXIT)
			{
				return;
			}

			std::cout << "Check for correctness:    >" << save_ISBN << "<\n('Y' / 'N')\n";
			confirm = YES_NO(b);
		}
		add.book_name = save_ISBN;


		std::cout << "Enter the year of the book:\n";
		int save_container = 0;
		confirm = false;
		while (confirm != true)
		{
			creating_numbers(b);
			save_container = b.val;

			if (b.ISBN == EXIT)
			{
				return;
			}

			if (b.val < 2023 && b.val > 1970) //устанавливаем рамки корректных значений для года выпуска
			{
				std::cout << "Check for correctness:    >" << save_container << "<\n('Y' / 'N')\n";
				confirm = YES_NO(b);
			}
			else
			{
				std::cout << "Incorrect input\nTry Again or use comand 'exit':\n";
			}

		}
		add.year = save_container; //должен не превышать текущий год +1


		std::cout << "Enter the number of pieces:\n";
		confirm = false;
		while (confirm != true)
		{
			creating_numbers(b);
			save_container = b.val;

			if (b.ISBN == EXIT)
			{
				return;
			}

			if (b.val > 0 && b.val < 10000) //устанавливаем рамки корректных значений для количества
			{
				std::cout << "Check for correctness:    >" << save_container << "<\n('Y' / 'N')\n";
				confirm = YES_NO(b);
			}
			else
			{
				std::cout << "Incorrect input\nTry Again or use comand 'exit':\n";
			}
		}
		add.stock = save_container;
		add.leased = 0; //при занесении автоматически выставляется 0
		base.push_back(add);


		std::cout << "Well done!\n"
			<< "To enter a new book, continue entering the ISBN\n"
			<< "To exit: 'exit'\n";
	}
	else
	{
		return;
	}
}

//оставляем
void clear_screen(char fill = ' ')
{
	COORD tl = { 0,0 };

	CONSOLE_SCREEN_BUFFER_INFO s;

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(console, &s);

	DWORD written, cells = s.dwSize.X * s.dwSize.Y;

	FillConsoleOutputCharacter(console, fill, cells, tl, &written);

	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);

	SetConsoleCursorPosition(console, tl);
}


std::string check_id()
{
	Book b;
	int counter = 3; //для защиты от брута
	while (counter != 0)
	{
		creating_names(b);

		for (const Access& access_control : USERS)
		{
			if (access_control.ID_employee == b.ISBN)
			{
				clear_screen();
				std::cout << "Welcome!\n";
				return access_control.access_level;
			}
		}
		std::cout << "Access for this user was not found\n";
		--counter;
		std::cout << "You have " << counter << " tries left\n";

	}
	clear_screen();
	b.ISBN = "unknown_user";
	return b.ISBN;
}


void new_employee(Book& b)
{
	std::string ID_New_User = b.ISBN;

	for (const Access add_new : USERS)
	{
		if (add_new.access_level == b.ISBN)
		{
			std::cout << b.ISBN << " Such an employee identifier already exists\nTry Again:\n";
			return;
		}
	}


	Access user_new;

	bool confirm = false;


	std::cout << "Check for correctness:    >" << ID_New_User << "<\n('Y' / 'N')\n";
	confirm = YES_NO(b);

	if (confirm == true)
	{
		std::cout << "Ok!\n";
		user_new.ID_employee = ID_New_User;


		std::cout << "Enter the last name and initials of the new employee\n";

		confirm = false;
		while (confirm != true)
		{
			creating_names(b);
			ID_New_User = b.ISBN;
			std::cout << "Check for correctness:    >" << ID_New_User << "<\n('Y' / 'N')\n";
			confirm = YES_NO(b);
		}

		std::cout << "Ok!\n";
		user_new.employee_name = ID_New_User;

		std::cout << "Grant appropriate access to this employee\n"
			<< "'1' - employee\n"
			<< "'2' - admin\n";

		confirm = false;
		while (confirm != true)
		{
			creating_names(b);
			ID_New_User = b.ISBN;

			if (b.ISBN == "1" || b.ISBN == "employee")
			{
				std::cout << "Check for correctness:    >employee<\n('Y' / 'N')\n";
				ID_New_User = "employee";
				confirm = YES_NO(b);
			}
			else if (b.ISBN == "2" || b.ISBN == "admin")
			{
				std::cout << "Check for correctness:    >admin<\n('Y' / 'N')\n";
				ID_New_User = "admin";
				confirm = YES_NO(b);
			}
			else
			{
				confirm = YES_NO(b);
			}
		}

		user_new.access_level = ID_New_User;

		std::cout << "Welldone\n"
			<< "You have added a new employee!\n\n\n"
			<< "Access level     : \t # " << user_new.access_level << '\n'
			<< "Employee name    : \t # " << user_new.employee_name << '\n'
			<< "Password         : \t # " << user_new.ID_employee << "\n\n\n"
			<< "To continue adding new employees to the database, simply enter a new ID\n"
			<< "If you want to exit, use the 'exit' command\n";

		USERS.push_back(user_new);
		return;

	}
	else
	{
		return;
	}
}


void functional_1(Book& b)
{
	std::cout << "Enter the ISBN to search the database:\n";

	while (true)
	{
		search(b);
		if (b.ISBN == EXIT) { break; }
		info(b);
	}
	return;
}

void functional_2(Book& b)
{
	std::cout << "Enter the ISBN to search the database:\n";
	while (true)
	{
		search(b);
		if (b.ISBN == EXIT) { break; }
		сhanging_product_data(b);
	}
	return;
}

void functional_3(Book& b, Database& item, double& total_purchase_price, std::vector<Database>& shopping_cart)
{
	std::cout << "Scan customer product barcodes:\n";
	while (true)
	{
		search(b);

		if (b.ISBN == EXIT) { break; }

		bool confirm = search_inside_the_shopping_cart(shopping_cart, b, total_purchase_price);
		if (confirm == false)
		{
			item = search_for_purchase(b);
			if (item.ISBN != "UNKNOWN_ITEM")
			{
				std::cout << item.book_name << ' ' << "Price: " << item.price << '\n';
				total_purchase_price += item.price;
				std::cout << "Total price: " << total_purchase_price << '\n';
				shopping_cart.push_back(item);
			}
		}
	}
	return;
}

void functional_4(Book& b)
{
	std::cout << "Enter the ISBN to search the database:\n";

	while (true)
	{
		search(b);
		if (b.ISBN == EXIT) { break; }
		delite_item_in_base(b);
	}
	return;
}

void functional_5(Book& b)
{
	std::cout << "Enter new ID for new employee\n";

	while (true)
	{
		creating_names(b);
		if (b.ISBN == EXIT) { break; }
		new_employee(b);
	}
	return;
}

void functional_6(Book& b)
{
	std::cout << "Enter the name of the employee you want to remove from the database:\n";

	while (true)
	{
		creating_names(b);
		if (b.ISBN == EXIT) { break; }
		delite_USERS_in_base(b);
	}
	return;
}

void simple_menu()
{

	std::cout << "You are in a simple menu\n";

	std::cout << "Enter the ISBN to search the database:\n";

	while (true)
	{
		Book b;
		search(b);
		if (b.ISBN == EXIT) { break; }
		info(b);
	}


}



std::string employee_menu()
{

	clear_screen();

	std::cout << "Menu:\n"
		<< "Enter '1' - Search;\n"
		<< "Enter '2' - Changing product data or entering a new product;\n"
		<< "Enter '3' - Sale of goods or services; \n\n";

	Book b;
	creating_names(b);



	if (b.ISBN == "1")
	{
		functional_1(b);
	}

	if (b.ISBN == "2")
	{
		functional_2(b);
	}

	if (b.ISBN == "3")
	{
		Database item;
		double total_purchase_price = 0.0;
		std::vector<Database>shopping_cart;

		while (true)
		{
			functional_3(b, item, total_purchase_price, shopping_cart);



			bool confirm = delite_inside_the_shopping_cart(shopping_cart, b, total_purchase_price);

		}
	}


	if (b.ISBN == QUITE)
	{
		clear_screen();
		return b.ISBN;
	}
	else
	{
		b.ISBN = "again";
		return b.ISBN;
	}
}

std::string admin_menu()
{

	clear_screen();

	std::cout << "Menu:\n"
		<< "Enter '1' - Search;\n"
		<< "Enter '2' - Changing product data or entering a new product;\n"
		<< "Enter '3' - Sale of goods or services; \n"
		<< "Enter '4' - Deleting from the base of the product;\n"
		<< "Enter '5' - To add a new employee to the database;\n"
		<< "Enter '6' - To delete an employee from the database;\n\n";

	Book b;
	creating_names(b);


	if (b.ISBN == "1")
	{
		functional_1(b);
	}

	if (b.ISBN == "2")
	{
		functional_2(b);
	}

	if (b.ISBN == "3")
	{
		functional_3(b);
	}

	if (b.ISBN == "4")
	{
		functional_4(b);
	}

	if (b.ISBN == "5")
	{
		functional_5(b);
	}

	if (b.ISBN == "6")
	{
		functional_6(b);
	}


	if (b.ISBN == QUITE)
	{
		clear_screen();
		return b.ISBN;
	}
	else
	{
		b.ISBN = "again";
		return b.ISBN;
	}
}

int main(int argc, char* argv[])
try
{
	if (argc > 1)
	{
		Book b;
		std::string s;
		for (int i = 0; i < argc; ++i) { s += argv[i]; }

		for (int i = s.size() - 4; i < s.size(); ++i) { b.ISBN += s[i]; }

		info(b);
		return 3;
	}

	while (true)
	{
		std::string s;
		s = check_id();

		if (s == "unknown_user")
		{
			while (true) { simple_menu(); }
		}

		if (s == "employee")
		{
			while (true) { s = employee_menu(); if (s == QUITE) { break; } }
		}

		if (s == "admin")
		{
			while (true) { s = admin_menu(); if (s == QUITE) { break; } }
		}
	}

	return 0;
}
catch (std::exception& e)
{
	std::cerr << "exception: " << e.what() << std::endl;
	char c;
	while (std::cin >> c && c != ';');
	return 1;
}
catch (...)
{
	std::cerr << "exception\n";
	char c;
	while (std::cin >> c && c != ';');
	return 2;
}








// сделать массив где будут храниться книги с их значениями           ГАЛОЧКА
// реализовать поиск по массиву                                       ГАЛОЧКА        
// глобальный оператор вывода значений книг                           ГАЛОЧКА
// протестить что будет, если get() запишет в s мусор с размером 4    ГАЛОЧКА








