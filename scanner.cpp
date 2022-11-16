/*
 * scanner.cpp
 *
 *  Created on: Nov 16, 2022
 *      Author: phelp
 */
#include"scanner.h"

//vector of tokens to store all tokens type and value
vector<Token>tokenList;

//global var to be used in all functions in the file
unsigned int g_Index = 0;

//=================================================
// to remove white spaces from the enf of the file
//==================================================
string strPreProcess(string str)
{
	int lastIndex ;
	for(int i = str.length() ; i>0 ;i--)
	{
		if(! (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ) )
		{
			lastIndex = i;
			break;
		}

	}
	return str.substr(0,lastIndex);
}

//=========================================
// check if it is a char
//its ascii between (96,123) or (64, 91)
//========================================
bool isChar(char c){
	return ((c > 96 && c < 123) || (c > 64 && c < 91));
}

//=============================
// check if it`s a number
//its ascii between (47,58)
//==============================
bool isNum(char c){
	return (c > 47 && c < 58);
}


//====================================
// check if it`s an operator ( , ), +,-,*,/,:,=
//====================================
bool isOp(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '(' || c == ')' || c == ';')
		return true;
	return false;
}


//==================================================
//check if it`s a reserved word in the tiny language
//==========================================
bool isReservedWord(string str){
	string Word[8] = {"if", "then", "else", "end", "repeat", "until", "read", "write"};
	for (int i = 0; i < 8; i++){
		if (str == Word[i])
			return true;
	}
	return false;
}

//=============================================================
//to check if it is the enf of identifier/number/reserved word
//=============================================================
bool isBreakChar(char in){
	if (in == '[' || in == ' ' || in == '\t' || in == '\n' || in == '{' || in == ']' || in == ':')
		return true;
	return false;
}

//=============================================
// to know what is the type of the operator
//=============================================
string get_Operator_name(char x){
	if (x == '+') return " - <addition>";
	if (x == '-') return " - <subtraction>";
	if (x == '*') return " - <multiply>";
	if (x == '/') return " - <division>";
	if (x == ';') return " - <semicolon>";
	if (x == '=') return " - <equal>";
	if (x == '<') return " - <less than>";
	if (x == '>') return " - <greater than>";
	if (x == '(') return " - <open bracket>";
	if (x == ')') return " - <close bracket>";
	return "";
}
string Special(string in) {
	if (in == "<=") return " - <less-equal>";
	if (in == ">=") return " - <greater-equal>";
	if (in == ":=") return " - <assign>";
	return "";
}


Token getToken(string Text)
{
	Token temp;
	int state = 0 ;
	int start;

	while(state !=13)
	{
		switch(state)
		{
		case 0:

			start = g_Index;
			if (isChar(Text[g_Index]))
				state = 1;	// CHAR STATE
			else if (isNum(Text[g_Index]))
				state = 3;	// NUM STATE
			else if (Text[g_Index] == '{')
				state = 4;	// COMMENT STATE
			else if (isOp(Text[g_Index]))
				state = 5;	// REGULAR OPERATOR STATE
			else if (Text[g_Index] == '<' || Text[g_Index] == '>')
				state = 6;	// GREATER OR LESS STATE
			else if (Text[g_Index] == ':')
				state = 7;	// ASSIGN STATE
			break;
			/*=========================================================================*/

		case 1:
			//check if the identifier contain numbers
			if(isNum(Text[g_Index]))
				state = 2; //identifier number state

			//check if its the last letter of the word
			if(isBreakChar(Text[g_Index]) || isOp(Text[g_Index]) || g_Index ==(Text.length() - 1) )
			{
				state = 13; //ACCEPTING STATE
				if(g_Index ==(Text.length() - 1))
					temp.Value= Text.substr(start , g_Index);
				else
					temp.Value= Text.substr(start , g_Index - 1);

				if(isReservedWord(temp.Value))
					temp.Type = "Reserved Word";
				else
					temp.Type = "Identifier";
			}
			break;

			//==================================================================


		case 2: //identifier number state
			if (isChar(Text[g_Index]))
				state = 1;	// CHAR STATE

			//check if its the last letter of the identifier
			if(isBreakChar(Text[g_Index]) || isOp(Text[g_Index]) || g_Index ==(Text.length() - 1) )
			{
				state = 13; //ACCEPTING STATE
				temp.Type = "Identifier";

				if(g_Index ==(Text.length() - 1))
					temp.Value= Text.substr(start , g_Index);
				else
					temp.Value= Text.substr(start , g_Index - 1);
			}
			break;

			//==================================================================


		case 3: //  Number state

			//check if the number followed by a letter it will be error state
			if (isChar(Text[g_Index]))
			{
				state = 12;	// Error state
				temp.Type = "Wrong constant";
				temp.Value= Text.substr(start , g_Index);

			}


			//check if its the last digit of the number
			if(isBreakChar(Text[g_Index]) || isOp(Text[g_Index]) || g_Index ==(Text.length() - 1) )
			{
				state = 13; //ACCEPTING STATE
				temp.Type = "Constant";

				if(g_Index ==(Text.length() - 1))
					temp.Value= Text.substr(start , g_Index);
				else
					temp.Value= Text.substr(start , g_Index - 1);
			}
			break;

			//==================================================================

		case 4:	// COMMENT STATE
			if (Text[g_Index] == '}')
				state = 0;	// START STATE
			if ((g_Index == (Text.length()-1)) && Text[g_Index] != '}') {
				state = 12;	// ERROR STATE
				temp.Value = "Incomplete Comment";
			}
			break;

			//=====================================================================

		case 5:	// OPERATOR STATE
			temp.Value = Text[g_Index-1];
			temp.Type = "Special Symbol" + get_Operator_name(temp.Value[0]);
			state = 13;	// ACCEPTING STATE
			break;

			//========================================================

		case 6:	// GREATER OR LESS STATE
			if (Text[g_Index] == '=')
				state = 8;	// COMPLETE EQUAL STATE
			else{
				temp.Value = Text[g_Index-1];
				temp.Type = "Special Symbol" + get_Operator_name(temp.Value[0]);
				state = 13;	// ACCEPTING STATE
			}
			break;

			//========================================

		case 7:	// ASSIGN STATE
			if (Text[g_Index] == '=')
				state = 8;	// COMPLETE EQUAL STATE
			else {
				state = 12;	// ERROR
				temp.Value = "Do you mean := (Assign Statement)";
			}
			break;

			//=================================

		case 8:	// COMPLETE EQUAL STATE
			state = 13;	// ACCEPTING STATE
			temp.Value = Text.substr(start, 2);
			temp.Type = "Special Symbol" + Special(temp.Value);
			break;

			//=======================================
		case 12:	// ERROR STATE
			state = 13;	// ACCEPTING STATE
			temp.Type = "ERROR";
			while (!(isBreakChar(Text[g_Index]) || (g_Index == (Text.length()-1))))
				g_Index++;
			break;
			/*=========================================================================*/
		default:
			break;
		}
		if (state != 13 && (g_Index != (Text.length()-1)))
			g_Index++;
	}
	return temp;
}


string getTokens(string input){
	string tokens = "";
	string str;
	str = strPreProcess(input);
	while ((g_Index != (input.length()-1)))
	{
		tokenList.push_back(getToken(str));
		tokens += (tokenList.back().Value + ", " + tokenList.back().Type + "\n");
	}

	g_Index = 0;
	return tokens;
}
