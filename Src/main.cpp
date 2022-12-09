//============================================================================
// Name        : TinyScanner.cpp
// Author      : Kyrillos Sawiris
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include"scanner.h"
#include"fileHandling.h"

using namespace std;

int main() {
	string str ;
	string tokens;
	str = convert_file_into_str();
	tokens = getTokens(str);
	cout<< getTokens(str);
	fflush(stdout);
	write_into_file(tokens);

}
