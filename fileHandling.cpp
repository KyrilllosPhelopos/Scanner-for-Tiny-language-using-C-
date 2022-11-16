#include"fileHandling.h"


string convert_file_into_str( )
{
	stringstream buffer;
	string input;
	std::ifstream file ("input.txt"); // this is equivalent to the above method
	if (!file.fail())
	{

		buffer << file.rdbuf();
		input = buffer.str();
		file.close();
	}
	return input;

}
