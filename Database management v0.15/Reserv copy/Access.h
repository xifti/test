#pragma once
#ifndef H_ACCESS
#define H_ACCESS

#include "Working_with_text.h"


void clear_screen(char fill = ' ');

struct Access
{
	Access() { }
	Access(std::string acc, std::string lastname_employee, std::string ID) :access_level{ acc }, employee_name{ lastname_employee }, ID_employee{ ID } { }


	Access check_id();
	void new_employee(Working_with_text& b);
	void delete_USERS_in_base(Working_with_text& b);


	std::string access_level;   // admin or employee
	std::string employee_name;  // фамилия работника
	std::string ID_employee;    // Код доступа

	
};

#endif