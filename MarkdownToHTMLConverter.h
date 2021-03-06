
#ifndef MARKDOWN_TO_HTML_CONVERTER_H
#define MARKDOWN_TO_HTML_CONVERTER_H

#include "Tag_line.h"

class MarkdownToHTMLConverter
{
	public:
		MarkdownToHTMLConverter(std::string input_filename);
		void			write_to_htlm_file(std::string output_filename);

	private:
		Tag_line		_final_lines;
		void 			write_opening_tags(std::ofstream &output_file);
		void 			write_closing_tags(std::ofstream &output_file);
};

#endif
