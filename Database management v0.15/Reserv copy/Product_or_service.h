#pragma once
#ifndef H_BASE
#define H_BASE


#include "Working_with_text.h"

struct Product_or_service
{
	Product_or_service() { }
	Product_or_service(std::string art, std::string human_name, std::string name_book, int yy, int st, int les, double pri) :
		ISBN{ art }, author_last_name{ human_name }, book_name{ name_book }, year{ yy }, stock{ st }, leased{ les }, price{ pri } {}

	void info(Working_with_text& b);
	Product_or_service search_for_purchase(Working_with_text& b);
	void delete_item_in_base(Working_with_text& b);
	void new_item_add(Working_with_text& b);
	void сhanging_product_data(Working_with_text& b);

	void removal_after_purchase_by_the_buyer(Product_or_service& full_cart);


	std::string ISBN;
	std::string author_last_name;
	std::string book_name;
	int year;
	int stock;
	int leased;
	double price;

	

};



std::ostream& operator<<(std::ostream& os, const Product_or_service& d);




#endif