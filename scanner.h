/*
 * scanner.h
 *
 *  Created on: Nov 16, 2022
 *      Author: phelp
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include <string.h>
#include <vector>
#include "fileHandling.h"
using namespace std;

struct Token
{
	string Value;
	string Type;
};

string getTokens(string input);


#endif /* SCANNER_H_ */
