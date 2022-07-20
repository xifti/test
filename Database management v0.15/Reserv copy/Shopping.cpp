#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include "Product_or_service.h"
#include "Access.h"
#include "Working_with_text.h"
#include "Shopping.h"




std::vector<Shopping> employee_sales;

//нужно переместить в Shopping
bool Shopping::search_inside_the_shopping_cart(std::vector<Product_or_service>& shopping_cart, Working_with_text& b, Working_with_text_stream& text, Shopping& cart)
{
	bool confirm = false;

	for (Product_or_service& item : shopping_cart)
	{
		if (item.ISBN == b.ISBN)
		{
			std::cout << item.book_name << ' ' << "Price: " << item.price << '\n';
			++item.stock;
			cart.total_purchase_price += item.price;
			std::cout << "Total price: " << cart.total_purchase_price << '\n'
					  << "If you want to remove an item from the shopping cart, use 'delete'\n"
					  << "To complete your purchase, use 'exit'\n";

			confirm = true;
			return confirm;
		}
	}

	return confirm;

}

//нужно переместить в Shopping
 //bool??
void Shopping::сhanging_the_quantity_in_a_position(Product_or_service& item, Working_with_text& b, Working_with_text_stream& text, Shopping& cart)
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
				text.creating_numbers(b);
				if (b.val <= item.stock && b.val > 0)
				{
					SAVE_b_val = b.val;

					std::cout << '>' << SAVE_b_val << '<' << " Confirm?\n ('Y' / 'N') or \n";
					confirm = text.YES_NO(b);
				}
				if (b.ISBN == EXIT)
				{
					std::cout << "If you want to continue filling the cart, then enter the following barcode\n"
						      << "If you want to remove an item from the shopping cart, use 'delete'\n"
							  << "To complete your purchase, use 'exit'\n";
					return;
				}
			}
			item.stock -= SAVE_b_val;
			SAVE_b_val *= item.price;
			cart.total_purchase_price -= SAVE_b_val;

			std::cout << "Done!\n"
				<< "Total Price now: " << cart.total_purchase_price << std::endl;

		}
		else
		{
			SAVE_b_val = 1.0;
			SAVE_b_val *= item.price;
			std::cout << "Do you want to deduct the " << SAVE_b_val << " for " << item.book_name << " item from the " << cart.total_purchase_price << " cost?\n";

			confirm = false;
			confirm = text.YES_NO(b);

			if (confirm == true)
			{
				cart.total_purchase_price -= SAVE_b_val;
			}
			else
			{
				std::cout << "If you want to continue filling the cart, then enter the following barcode\n"
						  << "If you want to remove an item from the shopping cart, use 'delete'\n"
						  << "To complete your purchase, use 'exit'\n";
				return;
			}
		}
	}
	std::cout << "Done!\n";
	return;
}

//нужно переместить в Shopping
//TODO: создать it который удалит значение из вектора, разобраться с этой функцией до конца.!!!!!!!
void Shopping::search_inside_the_shopping_cart_for_delete(std::vector<Product_or_service>& shopping_cart, Working_with_text& b, Working_with_text_stream& text, Shopping& cart)
{
	std::cout << "Scan the barcode of the item you want to remove from the cart:\n";
	text.search(b);
	std::string SAVE_ISBN=b.ISBN;
	for (Product_or_service& item : shopping_cart)
	{
		if (item.ISBN == b.ISBN)
		{
			сhanging_the_quantity_in_a_position(item, b, text, cart);
			if (item.stock == 0)
			{
				for (std::vector<Product_or_service>::iterator it = shopping_cart.begin(); it != shopping_cart.end();)
				{
					Product_or_service del = *it;
					if (del.ISBN == SAVE_ISBN)
					{
						it = shopping_cart.erase(it);
						return;
					}
					else
					{
						++it;
					}
				}
			}
			else
			{
				return;
			}
		}
	}

	std::cout << "You scanned a barcode that was not in the shopping cart\n";
	return;

}


//нужно переместить в Shopping


void Shopping::payment(std::vector<Product_or_service>&shopping_cart, Working_with_text& b, Working_with_text_stream& text, Shopping& cart)  //наличный расчёт 1(true), безналичный 0(false)
{
	bool confirm = false;
	std::cout << "Choose a payment method:\n"
			  << "'1'      - Cash\n"
			  << "'2'      - Bank transfer\n"
			  << "'delete' - If the buyer refuses to buy\n";

	text.creating_numbers(b);
		if (b.val == 1)
		{
			cart.payment_method = 1;
			std::cout << "Enter the amount to calculate the surrender\n";
			text.creating_numbers(b);
			b.val -= cart.total_purchase_price;
			std::cout << b.val<<'\n'
				<<"Has payment been made?\n";
			text.YES_NO(b);
			if (confirm == true)
			{
				std::cout << "Done!\n";
				return;
			}
		}
		else if (b.val == 2)
		{
			cart.payment_method = 0;
			std::cout << "Has payment been made?\n";
			text.YES_NO(b);
			if (confirm == true)
			{
				std::cout << "Done!\n";
				return;
			}
		}
		else if (b.ISBN == "delete")
		{
			std::cout << "Are you sure?\n";
			text.YES_NO(b);
			if (confirm == true)
			{
				shopping_cart.resize(0);
				std::cout << "Cart delete.\n";
				return;
			}
		}
}

void Shopping::Scan(Working_with_text& b, Working_with_text_stream& text,Shopping&cart)
{
	std::vector<Product_or_service> full_cart;
	Product_or_service item_serch;
	std::cout << "Scan customer product barcodes:\n";
	while (true)
	{
		text.search(b);
		if (b.ISBN == EXIT) { break; }
		if (b.ISBN == "delete")
		{
			search_inside_the_shopping_cart_for_delete(full_cart, b, text, cart);
		}

		bool confirm = search_inside_the_shopping_cart(full_cart, b, text, cart);
		if (confirm == false)
		{
			 item_serch = item_serch.search_for_purchase(b);
			if (item_serch.ISBN != "UNKNOWN_ITEM")
			{
				std::cout <<"Book: " << item_serch.book_name << ' ' << "Price: " << item_serch.price << '\n';
				item_serch.stock = 1;
				cart.total_purchase_price += item_serch.price;
				std::cout << "Total price: " << total_purchase_price << '\n'
						  << "If you want to remove an item from the shopping cart, use 'delete'\n"
						  << "To complete your purchase, use 'exit'\n";
				full_cart.push_back(item_serch);
				
			}
		}

	}

	payment(full_cart,b, text, cart);

	if (full_cart.size() == 0)
	{
		return;
	}
	else
	{
		cart.selling_time = time(0);
		for (int i = 0; i < full_cart.size(); ++i)
		{
			cart.product_and_quantity += full_cart[i].ISBN;
			cart.product_and_quantity += '/';
			cart.product_and_quantity += std::to_string(full_cart[i].stock);
			cart.product_and_quantity += ';';

			full_cart[i].removal_after_purchase_by_the_buyer(full_cart[i]);
		}

		employee_sales.push_back(cart);
		return;
	}
}

void Shopping::print_employee_sales()
{
	for (const Shopping& object : employee_sales)
	{
		std::cout << "Time: " << object.selling_time << " Name: " << object.employee_name << " Total price: " << object.total_purchase_price
			<< " metod: " << object.payment_method << "\nISBN+Quantity: " << object.product_and_quantity<<std::endl;
	}
}




