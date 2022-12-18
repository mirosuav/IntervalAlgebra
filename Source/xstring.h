// xstring.h
// The extended string class
// Author: Vijay Mathew Pandyalakal
// 2003-12-08

#ifndef XSTRING_H_
#define XSTRING_H_

namespace openutils {

	class XStringException;
	
	class XString {
		
	private:
		char* m_pAsciiBuffer; // contents of the string
		wchar_t* m_pUnicodeBuffer; // contents if unicode encoding
		int m_nEnc; // encoding type - ASCII or UNICODE. Default is ASCII

	public:
		// public constants
		static const int ASCII;
		static const int UNICODE;

	public:
		// constructors
		XString();
		XString(const char* str);
		XString(const wchar_t* str);		
		XString(const XString& str); // from another String,
		XString(XString str,int offset,int length); // from part of a String,
		XString(const char* str,int offset,int length);
		XString(const wchar_t* str,int offset,int length);
                XString(const AnsiString str);
		
		// destructor
		~XString();
		
		const char* value();
		const wchar_t* wvalue();
		int encoding();
		int length();
		void setEncoding(int enc);

                AnsiString ToAnsiString();

		char charAt(int index);
		wchar_t wcharAt(int index);
		
		void concat(const XString& str);
		
		// TODO: Implement from here till operators
		int indexOf(char c);
		int indexOf(char c,int offset);
		int indexOf(wchar_t c);
		int indexOf(wchar_t c,int offset);		
		int indexOf(XString str);
		int indexOf(XString str,int offset);
                int indexOf(XString str,int startIndex,int count);

		int lastIndexOf(char c);
		int lastIndexOf(char c,int offset);
		int lastIndexOf(wchar_t c);
		int lastIndexOf(wchar_t c,int offset);		
		int lastIndexOf(XString str);
		int lastIndexOf(XString str,int offset);
		
		XString subString(int beginIndex);
		XString subString(int beginIndex,int endIndex);
                XString subStrOfLen(int beginIndex,int count);
		
		XString insert(XString str,int insertAt);		
		XString replace(XString str,int replaceAt);
		XString remove(int beginIndex,int endIndex);
                XString removeFrom(int beginIndex,int count);
		XString reverse();

                //Own methods
                bool contains(XString str,int startIndex);
                bool contains(XString str);
                XString removeAll(XString str,int startIndex);
                XString removeAll(XString str);
                XString replaceAll(XString oldStr,XString newStr,int startIndex);
                XString replaceAll(XString oldStr,XString newStr);


                XString trimStart(XString str);
                XString trimEnd(XString str);
		XString rightTrim();
		XString leftTrim();
		XString trim();		
		
		XString toUpperCase();
		XString toLowerCase();
		XString capitalize();
		XString invertCase();
		
		int toInt();
                __int64 toInt64();
		long toLong();
		float toFloat();
	        double toDouble();
                long double toLongDouble();

                static XString fromInt(int number);
                static XString fromLong(long number);
                static XString fromFloat(float number);
                static XString fromDouble(double number,AnsiString format);
                static XString fromLongDouble(long double number,AnsiString format);
		
		bool equals(XString str);		
		bool equalsIgnoreCase(XString str);		
		
		bool startsWith(XString str,bool ignoreCase = false);
		bool endsWith(XString str,bool ignoreCase = false);
		
		void readFromFile(const char* file);
		void writeToFile(const char* file,bool append = false);

			
		void operator = (const XString& str);
		void operator = (const char* str);
		void operator = (const wchar_t* str);
                void operator = (const AnsiString& str);
                bool operator == (const AnsiString& str);
                bool operator != (const AnsiString& str);
		XString operator + (const XString& str);
                void operator +=(const XString& str){*this = *this + str; };
	};

	class XStringException {
	private:
		XString err;
	public:
		XStringException() { }
		XStringException(XString e) {
			err = e;
		}
		XString getMessage() {
			return err;
		}
	};
}// namespace openutils

#endif
