#include"fileHandling.h"


string convert_file_into_str( )
{
	stringstream buffer;
	string input;
	std::ifstream file ("input.txt");
	if (!file.fail())
	{

		buffer << file.rdbuf();
		input = buffer.str();
		file.close();
	}
	return input;

}

void write_into_file(string str)
{
	std::ofstream out("output.txt");
	out << str;
	out.close();
}
