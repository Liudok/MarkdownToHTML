
#include "MarkdownToHTMLConverter.h"

int main()
{
	MarkdownToHTMLConverter	converter("../file.txt");

	converter.write_to_htlm_file("index.html");

    return 0;
}