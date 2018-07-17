
#ifndef TAG_LINE_H
#define TAG_LINE_H

#include "Reader.h"
#define REGS 8

enum E_tag
{
	h1,
	h2,
	h3,
	h4,
	h5,
	h6,
	ul,
	ol
};

class Tag_line
{
	public:
		Tag_line(std::string input_filename);
		std::string		get_next_paragraph();

	private:
		Reader			_reader;
		bool			_finished;
		std::string		_current;
		std::string		_regexps[REGS];

		std::string		get_current();
		void			go_to_next();
		std::string		make_ul(std::string str);
		std::string		check_style(std::string str);
		std::string		check_ol(std::string str);
		std::string		check_link(std::string str);
};

#endif
