
#include "MarkdownToHTMLConverter.h"

MarkdownToHTMLConverter::MarkdownToHTMLConverter(std::string input_filename)
	: _final_lines(input_filename)
{

}

void MarkdownToHTMLConverter::write_to_htlm_file(std::string output_filename) {
	std::ofstream output_file;

	output_file.open(output_filename, std::ios::out);
	if(!output_file.is_open())
	{
		std::cout << "ERROR: HTML FILE COULD NOT BE OPENED" << std::endl;
	}
	write_opening_tags(output_file);

	std::string line = "start text";
	while (!line.empty())
	{
		line = _final_lines.get_next_paragraph();
		output_file << line;
		output_file << "\n";
	}
	write_closing_tags(output_file);
}

void MarkdownToHTMLConverter::write_opening_tags(std::ofstream &output_file) {
    output_file << "<html>\n<body>\n";
}

void MarkdownToHTMLConverter::write_closing_tags(std::ofstream &output_file) {
    output_file << "\n</body>\n</html>";

    std::cout << "Check index.html file in same folder" << std::endl;
}
