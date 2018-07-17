
#ifndef READER_H
#define READER_H

#include <iostream>
#include <string>
#include <fstream>

class Reader
{
	public:
		Reader(std::string input_filename);
		std::string		give_next_line();

	private:
		bool 			_reading;
		std::ifstream	_file;
		std::string		_current;

		std::string		get_current();
		void			go_to_next();

};

#endif
