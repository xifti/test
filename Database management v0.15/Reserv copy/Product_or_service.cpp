#include <iostream>
#include <vector>
#include "Working_with_text.h"
#include "Access.h"
#include "Product_or_service.h"
#include "Shopping.h"



std::vector<Product_or_service> base{ { "123A","Lupovich","Pereputali",2015, 10, 1, 10.0 } , { "123B","Mujhik","Bipki",2012, 10, 0 , 10.0 }, { "123C","Greka","Cancer",1985, 10, 0 , 10.0 },
{ "123D","Pisev","Vpopu",2000, 10, 2 , 10.0 }, { "123H","Unichtozhil","Gosudarstvo",1900 , 10, 0 , 10.0 } ,{ "123F","Dugin","Dasein",2020 , 10, 0 , 10.0 } ,
{ "123G","POHUY","Jija",2001 , 10, 0 , 10.0 } ,{ "123H","Fil'kina","Gramota",1990 , 10, 0,10.0} };


std::ostream& operator<<(std::ostream& os, const Product_or_service& d)
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

//нужно переместить в Product_or_service
void Product_or_service::info(Working_with_text& b)
{
	for (const Product_or_service& item : base)
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


//не доредактирована
Product_or_service Product_or_service::search_for_purchase(Working_with_text& b)
{
	for (const Product_or_service& item : base)
	{
		if (item.ISBN == b.ISBN)
		{
			return item;
		}
	}

	Product_or_service fail;
	std::cout << "No such ISBN found\n";
	fail = { "UNKNOWN_ITEM","UNKNOWN_ITEM","UNKNOWN_ITEM",0, 0, 0, 0.0 };
	return fail;
}

void Product_or_service::delete_item_in_base(Working_with_text& b)
{
	Working_with_text_stream a;
	for (std::vector<Product_or_service>::iterator it = base.begin(); it != base.end();)
	{
		Product_or_service del = *it;
		if (del.ISBN == b.ISBN)
		{
			std::cout << "\n\n" << del << "\n\nConfirm? ('Y' / 'N')\n";
			a.creating_names(b);

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

void Product_or_service::new_item_add(Working_with_text& b)
{
	Working_with_text_stream a;
	bool confirm = false;
	std::string save_ISBN = b.ISBN; //запомнили значение ISBN чтобы оно не потерялось при вызове creating_names(b)

	std::cout << "You want to add an    >" << b.ISBN << "<\n('Y' / 'N')\n";
	confirm = a.YES_NO(b);
	if (confirm == true)
	{
		Product_or_service add;

		add.ISBN = save_ISBN; //внесли ISBN

		std::cout << "Enter the author's last name:\n";
		confirm = false;
		while (confirm != true)
		{
			a.creating_names(b);
			save_ISBN = b.ISBN;

			if (b.ISBN == EXIT)
			{
				return;
			}

			std::cout << "Check for correctness:    >" << save_ISBN << "<\n('Y' / 'N')\n";

			confirm = a.YES_NO(b);
		}
		add.author_last_name = save_ISBN; //внесли Фамилию автора


		std::cout << "Enter book title:\n";
		confirm = false;
		while (confirm != true)
		{
			a.creating_names(b);
			save_ISBN = b.ISBN;

			if (b.ISBN == EXIT)
			{
				return;
			}

			std::cout << "Check for correctness:    >" << save_ISBN << "<\n('Y' / 'N')\n";
			confirm = a.YES_NO(b);
		}
		add.book_name = save_ISBN;


		std::cout << "Enter the year of the book:\n";
		int save_container = 0;
		confirm = false;
		while (confirm != true)
		{
			a.creating_numbers(b);
			save_container = b.val;

			if (b.ISBN == EXIT)
			{
				return;
			}

			if (b.val < 2023 && b.val > 1970) //устанавливаем рамки корректных значений для года выпуска
			{
				std::cout << "Check for correctness:    >" << save_container << "<\n('Y' / 'N')\n";
				confirm = a.YES_NO(b);
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
			a.creating_numbers(b);
			save_container = b.val;

			if (b.ISBN == EXIT)
			{
				return;
			}

			if (b.val > 0 && b.val < 10000) //устанавливаем рамки корректных значений для количества
			{
				std::cout << "Check for correctness:    >" << save_container << "<\n('Y' / 'N')\n";
				confirm = a.YES_NO(b);
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

void Product_or_service::сhanging_product_data(Working_with_text& b)
{
	Working_with_text_stream text;
	Product_or_service item;
	bool confirm = false;
	std::string save_ISBN = "";
	int save_container = 0;

	for (Product_or_service& product : base)
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

			text.creating_names(b);
			if (b.ISBN == "1")
			{
				std::cout << "Enter the author's last name to replace the existing one: " << product.author_last_name << '\n';

				confirm = false;
				while (confirm != true)
				{
					text.creating_names(b);
					save_ISBN = b.ISBN;

					if (b.ISBN == EXIT)
					{
						return;
					}

					std::cout << "Check for correctness:    >" << save_ISBN << "<\n('Y' / 'N')\n";

					confirm = text.YES_NO(b);
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
					text.creating_names(b);
					save_ISBN = b.ISBN;

					if (b.ISBN == EXIT)
					{
						return;
					}

					std::cout << "Check for correctness:    >" << save_ISBN << "<\n('Y' / 'N')\n";

					confirm = text.YES_NO(b);
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
					text.creating_numbers(b);
					save_container = b.val;
					if (b.ISBN == EXIT)
					{
						return;
					}
					if (b.val > 1800 && b.val < 2023) //устанавливаем рамки корректных значений для года
					{
						std::cout << "Check for correctness:    >" << save_container << "<\n('Y' / 'N')\n";
						confirm = text.YES_NO(b);
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
			else if (b.ISBN == "4")
			{

				std::cout << "Enter the number of unlisted books:\n";
				confirm = false;
				while (confirm != true)
				{
					text.creating_numbers(b);
					save_container = b.val;
					if (b.ISBN == EXIT)
					{
						return;
					}
					if (b.val > 0 && b.val < 10000) //устанавливаем рамки корректных значений для количества
					{
						std::cout << "Check for correctness:    >" << save_container << "<\n('Y' / 'N')\n";
						confirm = text.YES_NO(b);
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
		item.new_item_add(b);
	}
	else
	{
		std::cout << "Incorrect value. \n> Try again:\n";
	}
	return;

}



//нужна правильная сортировка и переделка этой функции
void Product_or_service::removal_after_purchase_by_the_buyer(Product_or_service& full_cart)
{
	for (Product_or_service& item : base)
	{
		if (item.ISBN == full_cart.ISBN)
		{
			item.stock -= full_cart.stock;
			return;
		}
	}
	

}


