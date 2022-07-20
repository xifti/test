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



 4.1)функция продажи товара для сотрудника
TODO: 4.2) Функция просмотра дневной продажи у сотрудников (у админа и менеджера)

 При продаже нужно уточнять оплата будет за наличные или за безнал,
 если наличные, то кассир вводит сумму денег которую он получил от покупателя, а программа выдает ему сумму сдачи
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
#include "Product_or_service.h"
#include "Working_with_text.h"
#include "Shopping.h"



/*

Условная база данных с хранящейся информацией по "книгам"

хранятся:
 TODO: ISBN, Название книги, Автор книги, год выпуска. (нужно доделать чтобы было больше параметров)

*/


void functional_1(Working_with_text& b, Working_with_text_stream& text, Product_or_service& item)
{
	std::cout << "Enter the ISBN to search the database:\n";

	while (true)
	{
		text.search(b);
		if (b.ISBN == EXIT) { break; }
		item.info(b);
	}
	return;
}

void functional_2(Working_with_text& b, Working_with_text_stream& text, Product_or_service& item)
{

	std::cout << "Enter the ISBN to search the database:\n";
	while (true)
	{
		text.search(b);
		if (b.ISBN == EXIT) { break; }
		item.сhanging_product_data(b);
	}
	return;
}


void functional_3(Working_with_text& b, Working_with_text_stream& text, Access& user)
{
	Shopping cart;
	cart.employee_name = user.employee_name;

	cart.Scan(b, text, cart);

	return;
}


void functional_4(Working_with_text& b, Working_with_text_stream& text, Product_or_service& item)
{
	std::cout << "Enter the ISBN to search the database:\n";

	while (true)
	{
		text.search(b);
		if (b.ISBN == EXIT) { break; }
		item.delete_item_in_base(b);
	}
	return;
}

void functional_5(Working_with_text& b, Working_with_text_stream& text, Access& member)
{
	std::cout << "Enter new ID for new employee\n";

	while (true)
	{
		text.creating_names(b);
		if (b.ISBN == EXIT) { break; }
		member.new_employee(b);
	}
	return;
}

void functional_6(Working_with_text& b, Working_with_text_stream& text, Access& member)
{
	std::cout << "Enter the name of the employee you want to remove from the database:\n";

	while (true)
	{
		text.creating_names(b);
		if (b.ISBN == EXIT) { break; }
		member.delete_USERS_in_base(b);
	}
	return;
}

void simple_menu(Access& user)
{

std::cout << "You are in a simple menu\n"
	      << "Enter the ISBN to search the database:\n";

 while (true)
 {
	 Working_with_text b;
	 Working_with_text_stream text;
	 Product_or_service item;

	 text.search(b);
	 if (b.ISBN == EXIT) { break; }
	 item.info(b);
 }
 return;
}

std::string employee_menu(Access& user)
{
	clear_screen(' ');

	std::cout << "Menu:\n"
			  << "Enter '1' - Search;\n"
		      << "Enter '2' - Changing product data or entering a new product;\n"
		      << "Enter '3' - Sale of goods or services; \n\n";

	Working_with_text b;
	Working_with_text_stream text;
	Product_or_service item;

	text.creating_names(b);



	if (b.ISBN == "1")
	{
		functional_1(b,text,item);
	}

	if (b.ISBN == "2")
	{
		functional_2(b, text, item);
	}
	
	if (b.ISBN == "3") 
	{
		functional_3(b, text, user);
	}


	if (b.ISBN == QUITE)
	{
		clear_screen(' ');
		return b.ISBN;
	}
	else
	{
		b.ISBN = "again";
		return b.ISBN;
	}
}

std::string admin_menu(Access& user)
{

	clear_screen(' ');

	std::cout << "Menu:\n"
			  << "Enter '1' - Search;\n"
		      << "Enter '2' - Changing product data or entering a new product;\n"
			  << "Enter '3' - Sale of goods or services; \n"
			  << "Enter '4' - Deleting from the base of the product;\n"
			  << "Enter '5' - To add a new employee to the database;\n"
			  << "Enter '6' - To delete an employee from the database;\n\n";

	Working_with_text b;
	Working_with_text_stream text;
	Product_or_service item;

	text.creating_names(b);

	if (b.ISBN == "1")
	{
		functional_1(b, text, item);
	}

	if (b.ISBN == "2")
	{
		functional_2(b, text, item);
	}

	if (b.ISBN == "3")
	{
		functional_3(b, text, user);
	}

	if (b.ISBN == "4")
	{
		functional_4(b, text, item);
	}

	if (b.ISBN == "5")
	{
		Access member;
		functional_5(b, text, member);
	}

	if (b.ISBN == "6")
	{
		Access member;
		functional_6(b, text, member);
	}
	

	if (b.ISBN == QUITE)
	{
		clear_screen(' ');
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
		Working_with_text b;
		Product_or_service item;

		std::string s;
		for (int i = 0; i < argc; ++i) { s += argv[i]; }

		for (int i = s.size() - 4; i < s.size(); ++i) { b.ISBN += s[i]; }

		item.info(b);
		return 3;
	}

	while (true)
	{
		Access user=user.check_id();
		Working_with_text b;

		if (user.access_level == "unknown_user")
		{
			while (true) { simple_menu(user); }
		}

		if (user.access_level=="employee")
		{
			while (true) { b.ISBN = employee_menu(user); if (b.ISBN == QUITE) { break; } }
		}

		if (user.access_level == "admin")
		{
			while (true) { b.ISBN = admin_menu(user); if (b.ISBN == QUITE) { break; } }
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