#include <iostream>
#include <vector>
#include "Working_with_text.h"
#include "Access.h"
#include <windows.h>


std::vector<Access> USERS{ { "admin","Mihail", "`"} , {"employee","Pupa","zarplata"} ,{"employee","Lupa","pereputali"}, {"unknown_user", "",""} };

void clear_screen(char fill)
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

Access Access::check_id()
{
	Working_with_text b;
	Working_with_text_stream a;
	int counter = 3; //для защиты от брута
	while (counter != 0)
	{
		a.creating_names(b);

		for (const Access& access_control : USERS)
		{
			if (access_control.ID_employee == b.ISBN)
			{
				clear_screen(' ');
				std::cout << "Welcome!\n";
				return access_control;
			}
		}
		std::cout << "Access for this user was not found\n";
		--counter;
		std::cout << "You have " << counter << " tries left\n";

	}
	clear_screen();
	Access user{ "unknown_user", "", "" };
	return user;
}

void Access::new_employee(Working_with_text& b)
{
	Working_with_text_stream a;
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
	confirm = a.YES_NO(b);

	if (confirm == true)
	{
		std::cout << "Ok!\n";
		user_new.ID_employee = ID_New_User;


		std::cout << "Enter the last name and initials of the new employee\n";

		confirm = false;
		while (confirm != true)
		{
			a.creating_names(b);
			ID_New_User = b.ISBN;
			std::cout << "Check for correctness:    >" << ID_New_User << "<\n('Y' / 'N')\n";
			confirm = a.YES_NO(b);
		}

		std::cout << "Ok!\n";
		user_new.employee_name = ID_New_User;

		std::cout << "Grant appropriate access to this employee\n"
			<< "'1' - employee\n"
			<< "'2' - admin\n";

		confirm = false;
		while (confirm != true)
		{
			a.creating_names(b);
			ID_New_User = b.ISBN;

			if (b.ISBN == "1" || b.ISBN == "employee")
			{
				std::cout << "Check for correctness:    >employee<\n('Y' / 'N')\n";
				ID_New_User = "employee";
				confirm = a.YES_NO(b);
			}
			else if (b.ISBN == "2" || b.ISBN == "admin")
			{
				std::cout << "Check for correctness:    >admin<\n('Y' / 'N')\n";
				ID_New_User = "admin";
				confirm = a.YES_NO(b);
			}
			else
			{
				confirm = a.YES_NO(b);
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


void Access::delete_USERS_in_base(Working_with_text& b)
{
	Working_with_text_stream a;
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
			a.creating_names(b);

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

