#include <iostream>
#include "Working_with_text.h"





Working_with_text creating_names(Working_with_text& b);

bool Working_with_text_stream::YES_NO(Working_with_text& b)
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

void Working_with_text_stream::ignore(char c)
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

Working_with_text_stream bs;

void  Working_with_text_stream::clean_up_mess(Working_with_text_stream& bs)
{
	bs.ignore(PRINT);
}


Working_with_text Working_with_text_stream::get()
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
		return Working_with_text(EXIT, 0.0);
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
				return Working_with_text(s, 0.0);
			}

			if (islower(ch))
			{
				ch = ch - 32;
				s += ch;
				return Working_with_text(s, 0.0);
			}
		}

		if (s.size() != 4) //если пользователь ошибся при вводе, то отбраковываем это значение
		{
			s += ch;
			while (strm.get(ch) && isprint(ch))
			{
				s += ch;
			}

			if (s == EXIT) { return Working_with_text(EXIT, 0.0); }
			if (s== "delete") { return Working_with_text(s, 0.0); }
			s = "unknown";
			return Working_with_text(s, 0.0);
		}
	}
}

void  Working_with_text_stream::search(Working_with_text& b)
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


Working_with_text Working_with_text_stream::get_add_names()
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
		return Working_with_text(EXIT, 0.0);
	}
	std::string s;
	s += ch;
	while (strm.get(ch) && isprint(ch))
	{
		s += ch;
	}

	if (s == EXIT) { return Working_with_text(EXIT, 0.0); }
	return Working_with_text(s, 0.0);

}

Working_with_text Working_with_text_stream::creating_names(Working_with_text& b)
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


Working_with_text Working_with_text_stream::get_add_numbers()
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
	return Working_with_text("", val);
	}
	default:

		std::string s;
		s += ch;
		while (strm.get(ch) && (ispunct(ch) || isalpha(ch)))
		{
			s += ch;
		}

		if (s == EXIT) { return Working_with_text(EXIT, 0.0); }
		if (s == "delete") { return Working_with_text(s, 0.0); }
		s = "unknown";
		return Working_with_text(s, -1000000.0);

	}

}

Working_with_text  Working_with_text_stream::creating_numbers(Working_with_text& b)
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