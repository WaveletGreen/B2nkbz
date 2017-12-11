/**
* @file string_helper.cpp
* @brief string utility functions' implemention
* @author James
* @history
* ===================================================================================
* Date                 Name                  Description of Change
* 09-July-2008         James      
* 14-Jau-2009          James                 modify Split functions, add trim blank characters
*/
#pragma warning(disable:4996)
#pragma warning(disable:4995 )
//
//#include <stdio.h>
//#include <iostream>
//#include <windows.h>
#include "string_helper.h"

string TrimString( string strArg )
{
	size_t index1 = 0;
	index1 = strArg.find_first_not_of( ' ');
	if( index1 != string::npos )
		strArg.erase( strArg.begin(), strArg.begin()+index1 );
	index1 = strArg.find_last_not_of( ' ');
	if( index1 != string::npos )
		strArg.erase( strArg.begin() + index1 + 1 );
	return strArg;
}

void Split( string strArg, char spliter, vector<string> &ans )
{
	ans.clear(); 
	size_t index0 = 0;
	string one_arg;
	if ( strArg.find_first_not_of(' ') == string::npos )
		strArg = "";
	while( strArg.size()>0 )
	{
		index0 = strArg.find_first_of( spliter );
		if( index0 != string::npos )
		{
			one_arg = strArg.substr( 0,index0 );
			strArg = strArg.substr( index0 + 1 );
			ans.push_back( one_arg );
		}
		else
		{
			ans.push_back( strArg );
			break;
		}
	}
}

void Split( string strArg, string spliter, vector<string> &ans )
{
	
	ans.clear();
	
	size_t index0;
	string one_arg;
	
	if ( strArg.find_first_not_of(" ") == string::npos )
		strArg = "";


	while( strArg.size()>0 )
	{
		
		index0 = strArg.find(spliter);
		
		if( index0 != string::npos )
		{
			
			one_arg = strArg.substr( 0, index0 );
			strArg = strArg.substr( index0 + spliter.size() );
			
			ans.push_back( one_arg );
		}
		else
		{
			
			ans.push_back( strArg );
			break;
		}
	}
}


void RemoveLiner( string &in, string &out )
{
	char buf[BUFSIZ] = "";
	for( int i=0; i<(int)in.size(); i++ )
	{
		if( in[i] == '\n')
			continue;
		else
			sprintf( buf,"%s%c", buf, in[i] );
	}
	out.assign(buf);
}

////Converting a WChar string to a Ansi string
//std::string WChar2Ansi(LPCWSTR pwszSrc)
//{
//	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
//
//	if (nLen<= 0) return std::string("");
//
//	char* pszDst = new char[nLen];
//	if (NULL == pszDst) return std::string("");
//
//	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
//	pszDst[nLen -1] = 0;
//
//	std::string strTemp(pszDst);
//	delete [] pszDst;
//
//	return strTemp;
//}
//
//string ws2s(wstring& inputws){ return WChar2Ansi(inputws.c_str()); }
//
////Converting a Ansi string to WChar string
//std::wstring Ansi2WChar(LPCSTR pszSrc, int nLen)
//{
//	int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, 0, 0);
//	if(nSize <= 0) return NULL;
//
//	WCHAR *pwszDst = new WCHAR[nSize+1];
//	if( NULL == pwszDst) return NULL;
//
//	MultiByteToWideChar(CP_ACP, 0,(LPCSTR)pszSrc, nLen, pwszDst, nSize);
//	pwszDst[nSize] = 0;
//
//	if( pwszDst[0] == 0xFEFF) // skip Oxfeff
//		for(int i = 0; i < nSize; i ++) 
//			pwszDst[i] = pwszDst[i+1]; 
//
//	wstring wcharString(pwszDst);
//	delete pwszDst;
//
//	return wcharString;
//}
//
//std::wstring s2ws(const string& s){ return Ansi2WChar(s.c_str(),s.size());}

