#pragma once
#ifndef H_TEXT
#define H_TEXT

const char PRINT = ';';

const std::string PROMPT = "> ";
const std::string EXIT = "exit";
const std::string QUITE = "quite";

struct Working_with_text
{
	Working_with_text() {}
	Working_with_text(char ch) : pr{ ch } {}
	Working_with_text(std::string i, double v) : ISBN{ i }, val{ v }  { }

	char pr;
	double val = 0.0;
	std::string ISBN;
};



class Working_with_text_stream
{
private:
	Working_with_text buffer;
	bool full;
	std::istream& strm;

public:
	Working_with_text_stream(std::istream& is = std::cin) : buffer{ 0 }, full{ 0 }, strm{ is } { }

	//надо сделать абстрактный класс
	Working_with_text get();
	Working_with_text get_add_names();
	Working_with_text get_add_numbers();


	void search(Working_with_text& b);
	Working_with_text creating_names(Working_with_text& b);
	Working_with_text  creating_numbers(Working_with_text& b);

	bool YES_NO(Working_with_text& b);
	void clean_up_mess(Working_with_text_stream& bs);



	void unget(Working_with_text& b) { buffer = b; full = true; };
	void ignore(char);
};

#endif