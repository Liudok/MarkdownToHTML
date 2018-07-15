
#include "Reader.h"

Reader::Reader(std::string input_filename)
	: _reading(true),
	  _file(input_filename)
{
	if (!_file.is_open())
		std::cout << strerror(errno) << std::endl;
	else
		go_to_next();
}

std::string Reader::give_next_line()
{
	if (_reading)
	{
		std::string ret = get_current();
		go_to_next();
		return ret;
	}
	else
		return std::string();
}

std::string Reader::get_current()
{
	return _current;
}

void Reader::go_to_next()
{
    std::string line = "some text";
    _current = "";
    while(_reading && line != "")
    {
        if (!std::getline(_file, line))
            _reading = false;
        else
            _current += (line + " ");
    }
}
