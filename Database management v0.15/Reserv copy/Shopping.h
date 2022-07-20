#pragma once
#ifndef H_SHOPPING
#define H_SHOPPING

#include "Working_with_text.h"



struct Shopping
{

	Shopping() {}
	Shopping(time_t t, std::string name, double total_val, bool pay, std::string itm) : selling_time{ t }, employee_name{ name }
		, total_purchase_price{ total_val }, payment_method{ pay }, product_and_quantity{ itm }{ }

	bool search_inside_the_shopping_cart(std::vector<Product_or_service>& shopping_cart, Working_with_text& b, Working_with_text_stream& text, Shopping& cart);

	void сhanging_the_quantity_in_a_position(Product_or_service& item, Working_with_text& b, Working_with_text_stream& text, Shopping& cart);

	void search_inside_the_shopping_cart_for_delete(std::vector<Product_or_service>& shopping_cart, Working_with_text& b, Working_with_text_stream& text, Shopping& cart);

	void Scan(Working_with_text& b, Working_with_text_stream& text, Shopping& cart);

	void payment(std::vector<Product_or_service>& shopping_cart, Working_with_text& b, Working_with_text_stream& text, Shopping& cart);

	void print_employee_sales();





	time_t selling_time;
	std::string employee_name;
	double total_purchase_price = 0.0;
	bool payment_method;              //наличный расчёт 1(true), безналичный 0(false)
	std::string product_and_quantity;

};









#endif