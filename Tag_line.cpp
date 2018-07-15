
#include "Tag_line.h"
#include <regex>

Tag_line::Tag_line(std::string input_filename)
		: _reader(input_filename),
		  _finished(false)
{
	_regexps[h1] = "(#)\\s+(.*)";
	_regexps[h2] = "(##)\\s+(.*)";
	_regexps[h3] = "(###)\\s+(.*)";
	_regexps[h4] = "(####)\\s+(.*)";
	_regexps[h5] = "(#####)\\s+(.*)";
	_regexps[h6] = "(######)\\s+(.*)";
	_regexps[ul] = " \\* (.*)";
	_regexps[ol] = "(.*)[ X|\tX]*[0-9]+. (.*)";
	go_to_next();
}

std::string Tag_line::get_next_paragraph()
{
	if (!_finished)
	{
		std::string ret = get_current();
		go_to_next();
		return ret;
	}
	else
		return std::string();
}

std::string Tag_line::get_current()
{
	return _current;
}

void Tag_line::go_to_next()
{
    std::string raw_line = _reader.give_next_line();
	if (raw_line.empty())
		_finished = true;
    else
    {
		raw_line = raw_line.substr(0,  raw_line.length() - 2);
        if (std::regex_match(raw_line, std::regex(_regexps[h1])))
            _current = "<h1>" + raw_line.substr(2, sizeof(raw_line)) + "</h1>";
		else if (std::regex_match(raw_line, std::regex(_regexps[h2])))
			_current = "<h2>" + raw_line.substr(3, sizeof(raw_line)) + "</h2>";
        else if (std::regex_match(raw_line, std::regex(_regexps[h3])))
            _current = "<h3>" + raw_line.substr(4, sizeof(raw_line)) + "</h3>";
        else if (std::regex_match(raw_line, std::regex(_regexps[h4])))
            _current = "<h4>" + raw_line.substr(5, sizeof(raw_line)) + "</h4>";
        else if (std::regex_match(raw_line, std::regex(_regexps[h5])))
            _current = "<h5>" + raw_line.substr(6, sizeof(raw_line)) + "</h5>";
        else if (std::regex_match(raw_line, std::regex(_regexps[h6])))
            _current = "<h6>" + raw_line.substr(7, sizeof(raw_line)) + "</h6>";
		else if (std::regex_match(raw_line, std::regex(_regexps[ul])))
		{
			_current = "<ul>" + raw_line + "</ul>";
			_current = make_ul(_current);
		}
        else
            _current = "<p>" + raw_line + "</p>";
		_current = check_ol(_current);
		_current = check_link(_current);
		_current = check_style( _current);
    }
}

std::string Tag_line::check_link(std::string str)
{
	auto pos = str.find("[");
	std::string start = str.substr(0, pos);
	std::string finish = str.substr(pos + 1, std::string::npos);
	if (pos != std::string::npos && str[pos - 1] != '!')
	{
		auto end = finish.find("]");
		std::string link_name = str.substr(pos + 1, end);
		std::string link = finish.substr(end + 2, std::string::npos);

		auto link_end = link.find(")");
		link = link.substr(0, link_end);
		link_end = finish.find(")");
		finish = finish.substr(link_end + 1, std::string::npos);
		str = start + "<a href=\"" + link + "\">" + link_name + "</a>" + finish;
	}
	return str;
}

std::string Tag_line::check_ol(std::string str)
{
	auto pos = str.find(". ");
	if (pos != std::string::npos && str[pos - 1] <= '9' && str[pos - 1] >= '0')
	{
		std::string small = str.substr(pos - 2, std::string::npos);
		str = str.substr(0, pos - 1) + "<ol><li>";
		pos = small.find("\n");
		std::string end = small.substr(pos + 3,  std::string::npos);
		small = small.substr(3, pos);
		pos = small.find("</");
		small = small.substr(0, pos) +  "</li></ol>" + small.substr(pos, std::string::npos);
		pos = small.find(". ");
		while ((pos < std::string::npos))
		{
			small = small.substr(0, pos - 2) + "</li><li>" + small.substr(pos + 1, std::string::npos);
			pos = small.find(". ");
		}
		str = str + small + end;
	}
	return str;
}

std::string Tag_line::check_style(std::string str)
{
	unsigned int i = 4;
	bool em_opened = false;
	bool bold_opened = false;
	while (i < str.length() - 3)
	{
		if (bold_opened == false && str[i] == '*' && str[i + 1] == '*' && str[i + 2] != ' ')
		{
			str = str.substr(0, i) + "<strong>" + str.substr(i + 2, str.length());
			bold_opened = true;
			i += 7;
		}
		else if (bold_opened == true && str[i] == '*' && str[i + 1] == '*' && str[i - 1] != ' ')
		{
			str = str.substr(0, i) + "</strong>" + str.substr(i + 2, str.length());
			bold_opened = false;
			i += 2;
		}
		else if (em_opened == false && str[i] == '*' && str[i + 1] != '*' && str[i + 1] != ' ')
		{
			str = str.substr(0, i - 1) + "<em>" + str.substr(i + 1, str.length());
			em_opened = true;
			i += 4;
		}
		else if (em_opened == true && str[i] == '*' && str[i - 1] != ' ')
		{
			str = str.substr(0, i) + "</em>" + str.substr(i + 1, str.length());
			em_opened = false;
			i += 5;
		}
		i++;
	}
	return str;
}

std::string Tag_line::make_ul(std::string str)
{
	unsigned int i = 6;
	str = str.substr(0, i - 1) + "\n\t<li>" + str.substr(i, std::string::npos);
	i += 6;
	while (i < str.length() - 6)
	{
		if (str[i] == '*' && str[i + 1] == ' ' && str[i - 1] == ' ')
		{
			str = str.substr(0, i - 1) + "</li>\n\t<li>" + str.substr(i + 1, str.length());
			i += 10;
		}
		i++;
	}
	str = str.substr(0, i + 1) + "</li>\n" + str.substr(i + 1, std::string::npos);
	return str;
}
