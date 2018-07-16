
#include "MarkdownToHTMLConverter.h"

int main()
{
	try
	{
		MarkdownToHTMLConverter	converter("file.txt");

		converter.write_to_htlm_file("index.html");
	}
	catch (const std::runtime_error&  e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}