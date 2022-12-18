// xstring.cpp
// The extended string class implementation
// Author: Vijay Mathew Pandyalakal
// 2003-12-08

#include <string.h>
#include <system.hpp>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <iomanip>
#include <iostream>


#include "xstring.h"
using namespace std;
using namespace openutils;

/* only two encodings are currently supported
ASCII and UNICODE */
const int XString::ASCII = 1;
const int XString::UNICODE = 2;

/** The default constructor initializes
the data buffers to a size of 2 with
the ASCII encoding
**/
XString::XString() {
	m_pAsciiBuffer = new char[2];
	strcpy(m_pAsciiBuffer,"");
	m_pUnicodeBuffer = new wchar_t[2];
	wcscpy(m_pUnicodeBuffer,L"");
	m_nEnc = XString::ASCII;
}

/** This constructor creates a XString object
with its contents as "str"	
ASCII encoding
**/
XString::XString(const char* str) {
	m_nEnc = XString::ASCII;
	int len = strlen(str);	
	m_pAsciiBuffer = new char[len+1];
	strcpy(m_pAsciiBuffer,str);
	m_pUnicodeBuffer = new wchar_t[2];
	wcscpy(m_pUnicodeBuffer,L"");
}

/** This constructor creates a XString object
with its contents as L"str"	
UNICODE encoding
**/
XString::XString(const wchar_t* str) {
	m_nEnc = XString::UNICODE;
	int len = wcslen(str);	
	m_pUnicodeBuffer = new wchar_t[len+1];
	wcscpy(m_pUnicodeBuffer,str);
	m_pAsciiBuffer = new char[2];
	strcpy(m_pAsciiBuffer,"");
}

/** This constructor creates a XString object
with its contents as a substring of "str"	
ASCII encoding
**/
XString::XString(const char* str,int offset,int length) {
	m_nEnc = XString::ASCII;
	int len = strlen(str);
	int tmp_len = length;
	int tmp_offset = offset;
	if(tmp_len >= len) {
		tmp_len = len;
	}
	if(tmp_offset > tmp_len) {
		tmp_offset = 0;
	}	
	int buffsz = tmp_len - tmp_offset + 1;
	m_pAsciiBuffer = new char[buffsz+1];
	int j = 0;
	int i = 0;
	for(i = tmp_offset;i<buffsz;i++) {
		m_pAsciiBuffer[j] = str[i];
		j++;
	}
	m_pAsciiBuffer[j] = '\0';
}

/** This constructor creates a XString object
with its contents as a substring of L"str"	
UNICODE encoding
**/
XString::XString(const wchar_t* str,int offset,int length) {
	m_nEnc = XString::UNICODE;
	int len = wcslen(str);
	int tmp_len = length;
	int tmp_offset = offset;
	if(tmp_len >= len) {
		tmp_len = len;
	}
	if(tmp_offset > tmp_len) {
		tmp_offset = 0;
	}		
	int buffsz = tmp_len - tmp_offset + 1;
	m_pUnicodeBuffer = new wchar_t[buffsz+1];
	int j = 0;
	int i = 0;
	for(i = tmp_offset;i<buffsz;i++) {
		m_pUnicodeBuffer[j] = str[i];
		j++;
	}
	m_pUnicodeBuffer[j] = '\0';
}

XString::XString(XString str,int offset,int length) {	
	m_pAsciiBuffer = new char[2];
	strcpy(m_pAsciiBuffer,"");
	m_pUnicodeBuffer = new wchar_t[2];
	wcscpy(m_pUnicodeBuffer,L"");
	m_nEnc = XString::ASCII;

	m_nEnc = str.encoding();
	int len = str.length();
	int tmp_len = length;
	int tmp_offset = offset;
	if(tmp_len >= len) {
		tmp_len = len;
	}
	if(tmp_offset > tmp_len) {
		tmp_offset = 0;
	}
	if(m_nEnc == XString::UNICODE) {		
		int buffsz = tmp_len - tmp_offset + 1;
		m_pUnicodeBuffer = new wchar_t[buffsz+1];
		int j = 0;
		int i = 0;
		for(i = tmp_offset;i<buffsz;i++) {
			m_pUnicodeBuffer[j] = str.wcharAt(i);
			j++;
		}
		m_pUnicodeBuffer[j] = '\0';
	}else {		
		int buffsz = tmp_len - tmp_offset + 1;
		m_pAsciiBuffer = new char[buffsz+1];
		int j = 0;
		int i = 0;
		for(i = tmp_offset;i<buffsz;i++) {
			m_pAsciiBuffer[j] = str.charAt(i);
			j++;
		}
		m_pAsciiBuffer[j] = '\0';
	}
}

XString::XString(const XString &str) {
	m_pAsciiBuffer = new char[2];
	strcpy(m_pAsciiBuffer,"");
	m_pUnicodeBuffer = new wchar_t[2];
	wcscpy(m_pUnicodeBuffer,L"");
	m_nEnc = XString::ASCII;
	*this = str;
}


XString::XString(const AnsiString str)
{
  m_pAsciiBuffer = str.c_str(); 
}


XString::~XString() {
	if(m_pAsciiBuffer != 0) delete[] m_pAsciiBuffer;
	if(m_pUnicodeBuffer != 0) delete[] m_pUnicodeBuffer;
}

const char* XString::value() {
	if(m_nEnc != XString::ASCII) {
		throw XStringException("Encoding is not ASCII");
	}
	return m_pAsciiBuffer;
}

const wchar_t* XString::wvalue() {
	if(m_nEnc != XString::UNICODE) {
		throw XStringException("Encoding is not UNICODE");
	}
	return m_pUnicodeBuffer;
}

int XString::encoding() {
	return m_nEnc;
}

int XString::length() {
	if(m_nEnc == XString::ASCII) {
		return strlen(m_pAsciiBuffer);
	}else if(m_nEnc == XString::UNICODE) {
		return wcslen(m_pUnicodeBuffer);
	}else {
		throw XStringException("Unknown encoding!");
	}
}

void XString::setEncoding(int enc) {
	if(enc != XString::ASCII && enc != XString::UNICODE) {
		throw XStringException("Either ASCII(1) or UNICODE(2)");
	}
	m_nEnc = enc;
}



AnsiString XString::ToAnsiString()
{
   AnsiString res;
   res = AnsiString(this->value());
   return res;
}



char XString::charAt(int index) {
	if(m_nEnc != XString::ASCII) {
		throw XStringException("Encoding is not ASCII");
	}
	int len = strlen(m_pAsciiBuffer);
	if((index >= len) || (index < 0)) {
		throw XStringException("Invalid index");
	}
	return m_pAsciiBuffer[index];
}

wchar_t XString::wcharAt(int index) {
	if(m_nEnc != XString::UNICODE) {
		throw XStringException("Encoding is not UNICODE");
	}
	int len = wcslen(m_pUnicodeBuffer);
	if((index >= len) || (index < 0)) {
		throw XStringException("Invalid index");
	}
	return m_pUnicodeBuffer[index];
}

void XString::concat(const XString& str) {
	if(m_nEnc != str.m_nEnc) {
		throw XStringException("Different encodings found.");
	}
	if(m_nEnc == XString::ASCII) {
		int len = strlen(m_pAsciiBuffer);
		char* tmp = new char[len + 1];
		strcpy(tmp,m_pAsciiBuffer);
		delete[] m_pAsciiBuffer;
		m_pAsciiBuffer = new char[len + (strlen(str.m_pAsciiBuffer) + 1)];
		strcpy(m_pAsciiBuffer,tmp);
		delete[] tmp;
		strcat(m_pAsciiBuffer,str.m_pAsciiBuffer);
	}else if(m_nEnc == XString::UNICODE) {
		int len = wcslen(m_pUnicodeBuffer);
		wchar_t* tmp = new wchar_t[len + 1];
		wcscpy(tmp,m_pUnicodeBuffer);
		delete[] m_pUnicodeBuffer;
		m_pUnicodeBuffer = new wchar_t[len + (wcslen(str.m_pUnicodeBuffer) + 1)];
		wcscpy(m_pUnicodeBuffer,tmp);
		delete[] tmp;
		wcscat(m_pUnicodeBuffer,str.m_pUnicodeBuffer);
	}
}

int XString::indexOf(char c) {
	return indexOf(c,0);
}

int XString::indexOf(char c,int offset) {
	if(m_nEnc == XString::UNICODE) {
		throw XStringException("Excpected encoding is ASCII");
	}
	if(offset < 0) return -1;
	int len = strlen(m_pAsciiBuffer);
	if(offset >= len) return -1;
	for(int i=offset;i<len;i++) {
		if(m_pAsciiBuffer[i] == c) {
			return i;
		}
	}
	return -1;
}

int XString::indexOf(wchar_t c) {
	return indexOf(c,0);
}

int XString::indexOf(wchar_t c,int offset) {
	if(m_nEnc == XString::ASCII) {
		throw XStringException("Excpected encoding is UNICODE");
	}
	if(offset < 0) return -1;
	int len = wcslen(m_pUnicodeBuffer);
	if(offset >= len) return -1;
	for(int i=offset;i<len;i++) {
		if(m_pUnicodeBuffer[i] == c) {
			return i;
		}
	}
	return -1;
}

int XString::indexOf(XString str,int offset) {
	if(m_nEnc != str.m_nEnc) {
		throw XStringException("Different encodings found");
	}
	if(offset < 0) return -1;
	if(m_nEnc == XString::ASCII) {
		int len = strlen(m_pAsciiBuffer);
		if(offset >= len) return -1;
		int slen = str.length();
		if(slen > len) return -1;
		char* str_value = new char[str.length() + 1];
		strcpy(str_value,str.value());
		char firstChar = str_value[0];
		for(int i=offset;i<len;i++) {
			char c = m_pAsciiBuffer[i];
			if(c == firstChar) {
				int rem = len - i;
				if(rem >= slen) {
					int j = i;
					int k = 0;
					bool found = true;
					while(k < slen) {
						if(m_pAsciiBuffer[j] != str_value[k]) {
							found = false;
							break;
						}
						j++; k++;
					}
					if(found) {
						delete [] str_value;
						return i;
					}
				}
			}
		}
		delete[] str_value;		
	}else if(m_nEnc == XString::UNICODE) {
		int len = wcslen(m_pUnicodeBuffer);
		if(offset >= len) return -1;
		int slen = str.length();
		if(slen > len) return -1;
		wchar_t* str_value = new wchar_t[str.length() + 1];
		wcscpy(str_value,str.wvalue());
		wchar_t firstChar = str_value[0];
		for(int i=offset;i<len;i++) {
			wchar_t c = m_pUnicodeBuffer[i];
			if(c == firstChar) {
				int rem = len - i;
				if(rem >= slen) {
					int j = i;
					int k = 0;
					bool found = true;
					while(k<slen) {
						if(m_pUnicodeBuffer[j] != str_value[k]) {
							found = false;
							break;
						}
						j++; k++;
					}
					if(found) {
						delete [] str_value;
						return i;
					}
				}
			}
		}
		delete[] str_value;		
	}
	return -1;
}

int XString::indexOf(XString str) {
	return indexOf(str,0);
}


int XString::indexOf(XString str,int startIndex,int count)
{
   XString temp = this->subString(startIndex,startIndex+count-1);
   if (!temp.contains(str)) return -1;
   return temp.indexOf(str)+startIndex;

}

int XString::lastIndexOf(char c) {
	return lastIndexOf(c,0);
}

int XString::lastIndexOf(char c,int from) {
	if(m_nEnc == XString::UNICODE) {
		throw XStringException("Excpected encoding is ASCII");
	}
	if(from < 0) return -1;
	int len = strlen(m_pAsciiBuffer);
	if(from > len) return -1;	
	for(int i=(len-1);i>=from;i--) {
		if(m_pAsciiBuffer[i] == c) {
			return i;
		}
	}
	return -1;
}

int XString::lastIndexOf(wchar_t c) {
	return lastIndexOf(c,0);
}

int XString::lastIndexOf(wchar_t c,int from) {
	if(m_nEnc == XString::ASCII) {
		throw XStringException("Excpected encoding is UNICODE");
	}
	if(from < 0) return -1;
	int len = wcslen(m_pUnicodeBuffer);
	if(from >= len) return -1;	
	for(int i=(len-1);i>=from;i--) {
		if(m_pUnicodeBuffer[i] == c) {
			return i;
		}
	}
	return -1;
}

int XString::lastIndexOf(XString str,int from) {
	if(m_nEnc != str.m_nEnc) {
		throw XStringException("Different encodings found");
	}
	if(from < 0) return -1;
	if(m_nEnc == XString::ASCII) {
		int len = strlen(m_pAsciiBuffer);
		if(from >= len) return -1;
		int slen = str.length();
		if(slen > len) return -1;
		char* str_value = new char[str.length() + 1];
		strcpy(str_value,str.value());
		char firstChar = str_value[0];
		for(int i=(len-1);i>=from;i--) {
			char c = m_pAsciiBuffer[i];
			if(c == firstChar) {
				int rem = i;
				if(rem >= slen) {
					int j = i;
					int k = 0;
					bool found = true;
					while(k<slen) {
						if(m_pAsciiBuffer[j] != str_value[k]) {
							found = false;
							break;
						}
						j++; k++;
					}
					if(found) {
						delete [] str_value;
						return i;
					}
				}
			}
		}
		delete[] str_value;		
	}else if(m_nEnc == XString::UNICODE) {
		int len = wcslen(m_pUnicodeBuffer);
		if(from >= len) return -1;
		int slen = str.length();
		if(slen > len) return -1;
		wchar_t* str_value = new wchar_t[str.length() + 1];
		wcscpy(str_value,str.wvalue());
		wchar_t firstChar = str_value[0];
		for(int i=(len-1);i>=from;i--) {
			wchar_t c = m_pUnicodeBuffer[i];
			if(c == firstChar) {
				int rem = i;
				if(rem >= slen) {
					int j = i;
					int k = 0;
					bool found = true;
					while(k<slen) {
						if(m_pUnicodeBuffer[j] != str_value[k]) {
							found = false;
							break;
						}
						j++; k++;
					}
					if(found) {
						delete [] str_value;
						return i;
					}
				}
			}
		}
		delete[] str_value;		
	}
	return -1;
}

int XString::lastIndexOf(XString str) {
	return lastIndexOf(str,0);
}

XString XString::subString(int beginIndex) {
	return subString(beginIndex,length()-1);
}

XString XString::subString(int from,int offset) {
	if(m_nEnc == XString::ASCII) {
		int len = strlen(m_pAsciiBuffer);
		if(offset > len) {
			throw XStringException("Invalid offset");
		}
		if(from < 0 || from >= len) {
			throw XStringException("Invalid from index");
		}
		int j = 0;
		char* tmp = new char[offset-from+2];
		for(int i=from;i<=offset;i++) {
			tmp[j++] = m_pAsciiBuffer[i];
		}
		tmp[j] = '\0';
		XString ret(tmp);
		delete[] tmp;
		return ret;
	}else if(m_nEnc == XString::UNICODE) {
		int len = wcslen(m_pUnicodeBuffer);
		if(offset > len) {
			throw XStringException("Invalid offset");
		}
		if(from < 0 || from >= len) {
			throw XStringException("Invalid from index");
		}
		int j = 0;
		wchar_t* tmp = new wchar_t[offset-from+2];
		for(int i=from;i<=offset;i++) {
			tmp[j++] = m_pUnicodeBuffer[i];
		}
		tmp[j] = '\0';
		XString ret(tmp);
		delete[] tmp;
		return ret;
	}
     return XString();   
}



XString XString::subStrOfLen(int beginIndex,int count)
{
   return subString(beginIndex,beginIndex+count-1);
}


XString XString::insert(XString str,int insertAt) {
	XString tmp_str = *this;
	XString ret = *this;
	int len = length();
	int str_len = str.length();
	int diff = 0;
	/*if(str_len > len) {
	diff = str_len - len;
	}
	int new_len = len + diff;*/
	int new_len = len + str_len;
	if(m_nEnc == XString::ASCII) {
		delete[] ret.m_pAsciiBuffer;
		ret.m_pAsciiBuffer = new char[new_len+1];
		int k = 0;
		for(int i=0;i<new_len;i++) {
			if(i == insertAt) {
				for(int j=0;j<str_len;j++) {
					ret.m_pAsciiBuffer[i] = str.value()[j];
					i++;
				}
				i--;
			}else {
				ret.m_pAsciiBuffer[i] = tmp_str.value()[k];
				k++;
			}
		}
		ret.m_pAsciiBuffer[i] = '\0';
	}else if(m_nEnc == XString::UNICODE) {
		delete[] ret.m_pUnicodeBuffer;
		ret.m_pUnicodeBuffer = new wchar_t[new_len+1];
		int k = 0;
		for(int i=0;i<new_len;i++) {
			if(i == insertAt) {				
				for(int j=0;j<str_len;j++) {
					ret.m_pUnicodeBuffer[i] = str.wvalue()[j];
					i++;
				}
				i--;
			}else {
				ret.m_pUnicodeBuffer[i] = tmp_str.wvalue()[k];
			}
		}
		ret.m_pUnicodeBuffer[i] = '\0';
	}
	return ret;
}

XString XString::replace(XString str,int replaceAt) {
	XString tmp_str = *this;
	XString ret = *this;
	int len = length();
	int str_len = str.length();
	int new_len = len;
	if((replaceAt+str_len) > len) {
		new_len = replaceAt + str_len;
	}	
	if(m_nEnc == XString::ASCII) {
		delete[] ret.m_pAsciiBuffer;
		ret.m_pAsciiBuffer = new char[new_len+1];
		for(int i=0;i<new_len;i++) {
			if(i == replaceAt) {
				for(int j=0;j<str_len;j++) {
					ret.m_pAsciiBuffer[i] = str.value()[j];
					i++;
				}
				i--;
			}else {
			ret.m_pAsciiBuffer[i] = tmp_str.value()[i];
			}
		}
		ret.m_pAsciiBuffer[i] = '\0';
	}else if(m_nEnc == XString::UNICODE) {
		delete[] ret.m_pUnicodeBuffer;
		ret.m_pUnicodeBuffer = new wchar_t[new_len+1];
		for(int i=0;i<new_len;i++) {
			if(i == replaceAt) {
				for(int j=0;j<str_len;j++) {
					ret.m_pUnicodeBuffer[i] = str.wvalue()[j];
					i++;
				}
				i--;
			}else {
				ret.m_pUnicodeBuffer[i] = tmp_str.wvalue()[i];
			}
		}
		ret.m_pUnicodeBuffer[i] = '\0';
	}	
	return ret;
}

XString XString::remove(int beginIndex,int endIndex) {
	XString tmp_str = *this;
	XString ret = *this;
	if(beginIndex < 0) return ret;
	int len = length();
	if(endIndex >= len) return ret;
	if(beginIndex > endIndex) return ret;
	int new_len = len - (endIndex - beginIndex);
	if(m_nEnc == XString::ASCII) {
		delete[] ret.m_pAsciiBuffer;
		ret.m_pAsciiBuffer = new char[new_len+1];
		int k = 0;
		for(int i=0;i<len;i++) {
			if(i == beginIndex) {
				while(true) {
					if(i == endIndex) break;
					i++;
				}
			}else {
				ret.m_pAsciiBuffer[k] = tmp_str.value()[i];
				k++;
			}
		}
		ret.m_pAsciiBuffer[k] = '\0';
	}else if(m_nEnc == XString::UNICODE) {
		delete[] ret.m_pUnicodeBuffer;
		ret.m_pUnicodeBuffer = new wchar_t[new_len+1];
		int k = 0;
		for(int i=0;i<len;i++) {
			if(i == beginIndex) {
				while(true) {
					if(i == endIndex) break;
					i++;
				}
			}else {
				ret.m_pUnicodeBuffer[k] = tmp_str.wvalue()[i];
				k++;
			}
		}
		ret.m_pUnicodeBuffer[k] = '\0';
	}
	return ret;
}

XString XString::removeFrom(int beginIndex,int count)
{
  return remove(beginIndex,beginIndex+count-1);
}



XString XString::reverse() {
	XString ret = *this;
	int len = length();
	if(m_nEnc == XString::ASCII) {
		char* tmp = new char[len + 1];
		int j = len-1;
		for(int i=0;i<len;i++) {
			tmp[i] = ret.m_pAsciiBuffer[j];
			j--;
		}
		tmp[i] = '\0';
		strcpy(ret.m_pAsciiBuffer,tmp);
		delete[] tmp;
	}else if(m_nEnc == XString::UNICODE) {
		wchar_t* tmp = new wchar_t[len + 1];
		int j = len-1;
		for(int i=0;i<len;i++) {
			tmp[i] = ret.m_pUnicodeBuffer[j];
			j--;
		}
		tmp[i] = '\0';
		wcscpy(ret.m_pUnicodeBuffer,tmp);
		delete[] tmp;
	}
	return ret;
}


bool XString::contains(XString str,int startIndex)
{
    XString temp = *this;
    if (temp.indexOf(str,startIndex)==-1)
       return false;
    else
        return true;
}


bool XString::contains(XString str)
{
   return contains(str,0);
}


XString XString::removeAll(XString str,int startIndex)
{
   XString temp = *this;

   while (temp.contains(str,startIndex))
   {
     int stind = temp.indexOf(str,startIndex);
     temp = temp.remove(stind,stind+str.length()-1);
   }

   return temp;
}


XString XString::removeAll(XString str)
{
  return removeAll(str,0);
}



XString XString::replaceAll(XString oldStr,XString newStr,int startIndex)
{
   XString temp = *this;

   if (oldStr.length()==0) return temp;

   int stIndex = startIndex;

   while (temp.contains(oldStr,stIndex))
   {
     int stind = temp.indexOf(oldStr,stIndex);
     temp = temp.remove(stind,stind+oldStr.length()-1);
     temp = temp.insert(newStr,stind);
     stIndex = stind + newStr.length();
   }
    return temp;
}


XString XString::replaceAll(XString oldStr,XString newStr)
{
   return replaceAll(oldStr,newStr,0);
}




XString XString::trimStart(XString str)
{
   XString temp = *this;
   int strlen = str.length();
   while (temp.startsWith(str,true))
   {
     temp = temp.remove(0,strlen-1);
   }

   return temp;
}


XString XString::trimEnd(XString str)
{
  XString temp = *this;
  int strlen = str.length();
   while (temp.endsWith(str,true))
   {
     temp = temp.remove(temp.length()-strlen,temp.length()-1);
   }

   return temp;

}



XString XString::rightTrim() {
	int len = length();
	if(m_nEnc == XString::ASCII) {
		int idx = lastIndexOf(' ');
		if(idx != (len-1)) {
			XString ret(value());
			return ret;
		}else {
			for(int i=(len-1);i>=0;i--) {
				if(m_pAsciiBuffer[i] != ' ') {
					idx = i;
					break;
				}
			}
			XString ret;
			ret.m_pAsciiBuffer = new char[idx+2];
			for(i=0;i<=idx;i++) {
				ret.m_pAsciiBuffer[i] = m_pAsciiBuffer[i];
			}
			ret.m_pAsciiBuffer[i] = '\0';
			return ret;
		}
	}else if(m_nEnc == XString::UNICODE) {
		int idx = lastIndexOf(L' ');
		if(idx != (len-1)) {
			XString ret(wvalue());
			return ret;
		}else {
			for(int i=(len-1);i>=0;i--) {
				if(m_pUnicodeBuffer[i] != L' ') {
					idx = i;
					break;
				}
			}
			XString ret;
			ret.m_pUnicodeBuffer = new wchar_t[idx+2];
			for(i=0;i<=idx;i++) {
				ret.m_pUnicodeBuffer[i] = m_pUnicodeBuffer[i];
			}
			ret.m_pUnicodeBuffer[i] = '\0';
			return ret;
		}
	}
}

XString XString::leftTrim() {
	int len = length();
	if(m_nEnc == XString::ASCII) {
		int idx = indexOf(' ');
		if(idx != 0) {
			XString ret(value());
			return ret;
		}else {
			for(int i=0;i<len;i++) {
				if(m_pAsciiBuffer[i] != ' ') {
					idx = i;
					break;
				}
			}
			XString ret;
			ret.m_pAsciiBuffer = new char[len-idx+2];
			int j = 0;
			for(i=idx;i<len;i++) {
				ret.m_pAsciiBuffer[j] = m_pAsciiBuffer[i];
				j++;
			}
			ret.m_pAsciiBuffer[j] = '\0';
			return ret;
		}
	}else if(m_nEnc == XString::UNICODE) {
		int idx = indexOf(L' ');
		if(idx != 0) {
			XString ret(wvalue());
			return ret;
		}else {
			for(int i=0;i<len;i++) {
				if(m_pUnicodeBuffer[i] != L' ') {
					idx = i;
					break;
				}
			}
			XString ret;
			ret.m_pUnicodeBuffer = new wchar_t[len-idx+2];
			for(i=idx;i<len;i++) {
				ret.m_pUnicodeBuffer[i] = m_pUnicodeBuffer[i];
			}
			ret.m_pUnicodeBuffer[i] = '\0';
			return ret;
		}
	}
}

XString XString::trim() {
	XString ret = rightTrim();
	ret = ret.leftTrim();
	return ret;
}

XString XString::toUpperCase() {
	XString ret = *this;
	int len = length();
	if(m_nEnc == XString::ASCII) {
		for(int i=0;i<len;i++) {
			ret.m_pAsciiBuffer[i] = toupper(m_pAsciiBuffer[i]);
		}
	}else if(m_nEnc == XString::UNICODE) {
		for(int i=0;i<len;i++) {
			ret.m_pUnicodeBuffer[i] = towupper(m_pUnicodeBuffer[i]);
		}
	}
	return ret;
}

XString XString::toLowerCase() {
	XString ret = *this;
	int len = length();
	if(m_nEnc == XString::ASCII) {
		for(int i=0;i<len;i++) {
			ret.m_pAsciiBuffer[i] = tolower(m_pAsciiBuffer[i]);
		}
	}else if(m_nEnc == XString::UNICODE) {
		for(int i=0;i<len;i++) {
			ret.m_pUnicodeBuffer[i] = towlower(m_pUnicodeBuffer[i]);
		}
	}
	return ret;
}

XString XString::capitalize() {
	XString ret = *this;	
	int len = length();	
	if(m_nEnc == XString::ASCII) {
		char pc = 0;
		for(int i=0;i<len;i++) {
			if(i == 0 || pc == ' ' || pc == '.') {
				ret.m_pAsciiBuffer[i] = toupper(m_pAsciiBuffer[i]);
			}else {
				ret.m_pAsciiBuffer[i] = tolower(m_pAsciiBuffer[i]);
			}
			pc = m_pAsciiBuffer[i];
		}		
	}else if(m_nEnc == XString::UNICODE) {
		wchar_t pc;
		for(int i=0;i<len;i++) {
			if(i == 0 || pc == L' ' || pc == L'.') {
				ret.m_pUnicodeBuffer[i] = towupper(m_pUnicodeBuffer[i]);
			}else {
				ret.m_pUnicodeBuffer[i] = towlower(m_pUnicodeBuffer[i]);
			}
			pc = m_pUnicodeBuffer[i];
		}
	}
	return ret;
}

XString XString::invertCase() {
	XString ret = *this;
	int len = length();	
	if(m_nEnc == XString::ASCII) {
		char pc = 0;
		for(int i=0;i<len;i++) {
			if(islower(m_pAsciiBuffer[i])) {
				ret.m_pAsciiBuffer[i] = toupper(m_pAsciiBuffer[i]);
			}else {
				ret.m_pAsciiBuffer[i] = tolower(m_pAsciiBuffer[i]);
			}
			pc = m_pAsciiBuffer[i];
		}
	}else if(m_nEnc == XString::UNICODE) {
		wchar_t pc;
		for(int i=0;i<len;i++) {
			if(iswlower(m_pUnicodeBuffer[i])) {
				ret.m_pUnicodeBuffer[i] = towupper(m_pUnicodeBuffer[i]);
			}else {
				ret.m_pUnicodeBuffer[i] = towlower(m_pUnicodeBuffer[i]);
			}
			pc = m_pUnicodeBuffer[i];
		}
	}
	return ret;
}

int XString::toInt() {
	if(m_nEnc == XString::ASCII) {
		return atoi(value());
	}else if(m_nEnc == XString::UNICODE) {
		return _wtoi(wvalue());
	}
}

__int64 XString::toInt64() {
	if(m_nEnc == XString::ASCII) {
		return _atoi64(value());
	}else if(m_nEnc == XString::UNICODE) {
		return _wtoi64(wvalue());
	}
}


long XString::toLong() {
	if(m_nEnc == XString::ASCII) {
		return atol(value());
	}else if(m_nEnc == XString::UNICODE) {
		return _wtol(wvalue());
	}
}

float XString::toFloat() {
	if(m_nEnc == XString::ASCII) {
		return (float)atof(value());
	}else if(m_nEnc == XString::UNICODE) {
		return (float)wcstod(wvalue(),0);
	}
}

double XString::toDouble() {
	if(m_nEnc == XString::ASCII) {
		return (double)strtod(value(),0);
	}else if(m_nEnc == XString::UNICODE) {
		return (double)wcstod(wvalue(),0);
	}
}

long double XString::toLongDouble() {
	if(m_nEnc == XString::ASCII) {
		return _atold(value());
	}else if(m_nEnc == XString::UNICODE) {
		return _wtold(wvalue());
	}
}



template <class T>
void to_string(string & result, const T & t)
{
 ostringstream oss; // create a stream
 oss << t; // insert value to stream
 result=oss.str(); // extract value and write it to result
}




XString XString::fromInt(int number)
{
   string temp;
   to_string(temp,number);
   XString res;
   res.setEncoding(XString::ASCII);
   res = temp.data();
   return res;
}


XString XString::fromLong(long number)
{
   string temp;
   to_string(temp,number);
   XString res;
   res.setEncoding(XString::ASCII);
   res = temp.data();
   return res;
}



XString XString::fromFloat(float number)
{
   string temp;
   to_string(temp,number);
   XString res;
   res.setEncoding(XString::ASCII);
   res = temp.data();
   return res;
}



XString XString::fromDouble(double number,AnsiString format = "0.00000000000000000000")
{
   //string temp;
   //to_string(temp,number);
   //XString res;
   //res.setEncoding(XString::ASCII);
   //res = temp.data();
   // return XString(AnsiString::FloatToStrF(number,1,20,20).c_str());
   XString tmp = XString(AnsiString::FormatFloat(format,number).c_str());
   tmp = tmp.replaceAll(",",".");
   return tmp;
}



XString XString::fromLongDouble(long double number,AnsiString format = "0.00000000000000000000")
{

   XString tmp = XString(AnsiString::FormatFloat(format,number).c_str());
   tmp = tmp.replaceAll(",",".");
   if ((tmp.charAt(0)!='-') && (tmp.charAt(0)!='+')) tmp = tmp.insert("+",0);
   return tmp;
  // ostringstream oss; // create a stream
   //oss << std::scientific;
   //oss << std::setprecision(22);
   //oss << number; // insert value to stream
   //return XString(oss.str().data());
}




bool XString::equals(XString str) {
	int len = length();
	int str_len = str.length();
	if(len != str_len) {
		return false;
	}
	if(m_nEnc == XString::ASCII) {
		for(int i=0;i<len;i++) {
			if(m_pAsciiBuffer[i] != str.m_pAsciiBuffer[i]) {
				return false;
			}
		}
	}else if(m_nEnc == XString::UNICODE) {
		for(int i=0;i<len;i++) {
			if(m_pUnicodeBuffer[i] != str.m_pUnicodeBuffer[i]) {
				return false;
			}
		}
	}
	return true;
}

bool XString::equalsIgnoreCase(XString str) {
	int len = length();
	int str_len = str.length();
	if(len != str_len) {
		return false;
	}
	if(m_nEnc == XString::ASCII) {
		for(int i=0;i<len;i++) {
			if(tolower(m_pAsciiBuffer[i]) != tolower(str.m_pAsciiBuffer[i])) {
				return false;
			}
		}
	}else if(m_nEnc == XString::UNICODE) {
		for(int i=0;i<len;i++) {
			if(towlower(m_pUnicodeBuffer[i]) != towlower(str.m_pUnicodeBuffer[i])) {
				return false;
			}
		}
	}
	return true;
}

bool XString::startsWith(XString str,bool ignoreCase) {
	if(str.length() > length()) return false;
	XString substr = subString(0,str.length()-1);
	if(ignoreCase) {
		return substr.equalsIgnoreCase(str);
	}else {
		return substr.equals(str);
	}
}

bool XString::endsWith(XString str,bool ignoreCase) {
	if(str.length() > length()) return false;
	int offset = length() - str.length();
	XString substr = subString(offset,length()-1);
	if(ignoreCase) {
		return substr.equalsIgnoreCase(str);
	}else {
		return substr.equals(str);
	}
}

void XString::readFromFile(const char* file) {
	FILE *fp = fopen(file,"r");
	if(fp == 0) {
		throw XStringException("File open error");
	}
	fseek(fp,0,SEEK_END);
	long fs = ftell(fp);
	rewind(fp);
	if(m_nEnc == XString::ASCII) {
		delete[] m_pAsciiBuffer;
		m_pAsciiBuffer = new char[fs + 1];
		char tmp[2];
		int i = 0;
		while(i<fs) {									
			m_pAsciiBuffer[i] = fgetc(fp);
			i++;
		}
		m_pAsciiBuffer[i] = '\0';
	}else if(m_nEnc == XString::UNICODE) {
		delete[] m_pUnicodeBuffer;
		m_pUnicodeBuffer = new wchar_t[fs + 1];
		wchar_t tmp[2];
		int i = 0;
		while(i<fs) {						
			m_pUnicodeBuffer[i] = fgetwc(fp);
			i++;
		}
		m_pUnicodeBuffer[i] = '\0';
	}
	fclose(fp);
}

void XString::writeToFile(const char* file,bool append) {
	FILE *fp = 0;
	if(append) {
		fp = fopen(file,"a");
	}else {
		fp = fopen(file,"w");
	}
	if(fp == 0) {
		throw XStringException("File open error");
	}	
	if(m_nEnc == XString::ASCII) {		
		fprintf(fp,"%s",m_pAsciiBuffer);
	}else if(m_nEnc == XString::UNICODE) {		
		fwprintf(fp,L"%s",m_pUnicodeBuffer);
	}
	fclose(fp);
}

// overloaded assignment operators

void XString::operator = (const XString& str) {
	m_nEnc = str.m_nEnc;
	int len = 0;
	if(m_nEnc == XString::ASCII) {
		len = strlen(str.m_pAsciiBuffer);
		delete[] m_pAsciiBuffer;
		m_pAsciiBuffer = new char[len + 1];
		strcpy(m_pAsciiBuffer,str.m_pAsciiBuffer);
	}else if(m_nEnc == XString::UNICODE) {
		len = wcslen(str.m_pUnicodeBuffer);
		delete[] m_pUnicodeBuffer;
		m_pUnicodeBuffer = new wchar_t[len + 1];
		wcscpy(m_pUnicodeBuffer,str.m_pUnicodeBuffer);
	}								
}
void XString::operator = (const char* str) {
	m_nEnc = XString::ASCII;
	int len = 0;
	len = strlen(str);
	delete[] m_pAsciiBuffer;
	m_pAsciiBuffer = new char[len + 1];
	strcpy(m_pAsciiBuffer,str);			
}
void XString::operator = (const wchar_t* str) {
	m_nEnc = XString::UNICODE;
	int len = 0;
	len = wcslen(str);
	delete[] m_pUnicodeBuffer;
	m_pUnicodeBuffer = new wchar_t[len + 1];
	wcscpy(m_pUnicodeBuffer,str);
}


void XString::operator = (const AnsiString& str)
{
  *this = (XString)str;
}

bool XString::operator == (const AnsiString& str)
{
  return *this->value() == *str.c_str() ? true : false;

}

bool XString::operator != (const AnsiString& str)
{
  return *this->value() != *str.c_str() ? true : false;
}


XString XString::operator + (const XString& str) {
	XString ret = *this;
	ret.concat(str);
	return ret;
}

