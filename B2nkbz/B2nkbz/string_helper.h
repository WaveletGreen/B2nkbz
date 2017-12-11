/**
* @file string_helper.h
* @brief string utilities to help dealing with string
* @author James
* @history
* ===================================================================================
* Date             Name                   Description of Change
* 09-July-2008     James                  
*/

#ifndef STRING_HELPER
#define STRING_HELPER

#include <string>
#include <vector>
using namespace std;

string TrimString( string strArg );
void   Split( string strArg, char spliter, vector<string> &ans );
void   Split( string strArg, string spliter, vector<string> &ans );
void   RemoveLiner( string &in, string &out );
//string ws2s(wstring& inputws);
//wstring s2ws(const string& s);

#endif