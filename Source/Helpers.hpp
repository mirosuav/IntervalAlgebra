


#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <vector>
#include "xstring.cpp"




typedef long double LDouble;     //double type name used in whole program



enum precisions { LOW24 = PC_24 , MEDIUM53 = PC_53, HIGH64 = PC_64 };




//=================KONTROLA ZAOKRAGLEN ==============================

inline void SetPrecision(precisions prec)
{
	_control87(prec , MCW_PC);
}

inline void  Rdef()                             //Tryb domyslny
{
	_control87( CW_DEFAULT , MCW_RC);
};

inline void  Rnear()                              // Do najblizszego
{
        SetPrecision(HIGH64);
	_control87( RC_NEAR , MCW_RC);
};

inline void  Rdown()                            // Zaokraglenie w dol
{
        SetPrecision(HIGH64);
        _control87( RC_DOWN, MCW_RC);
};

inline void  Rup()                              // Zaokraglenie w gore
{
       SetPrecision(HIGH64);
	_control87( RC_UP, MCW_RC);
};

inline void  Rtrunc()                              // Obcinanie
{
        SetPrecision(HIGH64);
	_control87( RC_CHOP , MCW_RC);
};

//=================================================================



//===== FUNKCJE POMOCNICZE ====================


inline LDouble minimum(LDouble a, LDouble b,LDouble c  , LDouble d )
{
	LDouble temp;
	temp= (a<=b)? a : b;
	temp= (temp<=c)? temp : c;
	temp= (temp<=d)? temp : d;
	return(temp);
};

inline LDouble maximum(LDouble a, LDouble b,LDouble c , LDouble d )
{
	LDouble temp;
	temp= (a>=b)? a : b;
	temp= (temp>=c)? temp : c;
	temp= (temp>=d)? temp : d;
	return(temp);
};


inline LDouble minimum(LDouble a, LDouble b)
{
	return((a<=b)? a : b);
};

inline LDouble maximum(LDouble a, LDouble b)
{
	return((a>=b)? a : b);
};



//Sprawdza parzystosc liczby
inline bool parzysta(int n)
{ return ( ((n % 2)==0) ? true : false ); };

inline bool parzysta(LDouble n)
{
	if ((n-(int)n)==0)	
		return ( (((int)n % 2)==0) ? true : false );
	else
		return (false);
};


inline LDouble sqr(LDouble a)
{ return(a*a); };

//rekuencyjne potegowanie naturalne metod¹ Dziel i rzadz liczby rzeczywistej
LDouble adon(LDouble a, int n)
{
	if (n<1) return(1);
	else
		if (n==1) return(a);
		else
			if (n==2) return(a*a);
			else
				if (parzysta(n)) return (sqr(adon(a,n/2)));
				else
					return (sqr(adon(a,(n-1)/2))*a);

}


//***************************************************************************
//                            CONVERT METHODS
//***************************************************************************

XString ConvertToInterval(XString value, XString& er)
{
	if (value.length()<=0) return "";
	if (value.contains("[")) return value;

	XString rcomm = value;

        rcomm=rcomm.replaceAll("e","E");
        rcomm=rcomm.replaceAll(",+",",");
        rcomm=rcomm.replaceAll(";+",";");

	rcomm=rcomm.replaceAll(",","][");
	rcomm=rcomm.replaceAll(";","];[");
        rcomm=rcomm.replaceAll("E+","E");
      //	rcomm=rcomm.replaceAll("+","]+[");

	rcomm=rcomm.replaceAll("*","]*[");
	rcomm=rcomm.replaceAll("/","]/[");


        rcomm=rcomm.replaceAll("<","<[");
        rcomm=rcomm.replaceAll(">","]>");


        //    rcomm= rcomm.insert("[",0);
        //    rcomm=rcomm.insert("]",rcomm.length());



	return rcomm;
}





XString  ConvertToReal(XString value, XString er)
{
	//   <[123.1,124.14][1241]>
	if (value.length()<=0) return "";

	XString rcomm = value;
	XString err = "";
	XString intstr = "";
	XString newintstr = "";

	int lb,rb;

	while (rcomm.contains("["))
	{
		lb = rcomm.indexOf("[");
		rb = rcomm.indexOf("]",lb+1);

		intstr = rcomm.subStrOfLen(lb,rb-lb+1);
		newintstr = intstr;

		if (intstr.contains(","))
		{
			newintstr = intstr.remove(intstr.indexOf(","),intstr.length()-1);
			newintstr=newintstr+"]";
		}

		rcomm = rcomm.remove(lb,rb);
		rcomm = rcomm.insert(newintstr,lb);

		rb = rcomm.indexOf("]",lb+1);

		if ((rb<rcomm.length()-1) && (rcomm.charAt(rb+1)== '['))
		{
			rcomm= rcomm.removeFrom(rb,1);
			rcomm=rcomm.insert(",",rb);
			rcomm=rcomm.removeFrom(lb,1);
		}
		else
		{
			rcomm= rcomm.removeFrom(rb,1);
			rcomm=rcomm.removeFrom(lb,1);
		}
	}


	return rcomm;
}






//***************************************************************************
//                        NUMBER PARSING
//***************************************************************************





bool IsNumber(char znak)
{
	if ((znak=='0') || (znak=='1') || (znak=='2') || (znak=='3')
		|| (znak=='4') || (znak=='5') || (znak=='6') || (znak=='7')
		|| (znak=='8') || (znak=='9'))
	{
		return true;
	}
	else
	{
		return false;
	}
}


XString ParseNumber(int _s,int _e,XString comm,XString& er)
{
	if (_s>_e) {er="ParseNumber: Syntax error"; return ("e");}

	LDouble temp;
	XString sL = comm.subStrOfLen(_s,_e-_s+1);

	try
	{
		temp=  sL.toLongDouble();
	}
	catch (EXCEPINFO ex)
	{
		er="ParseNumber: ";
		er += ex.bstrDescription;
		return ("");
	}


	return (sL);

}



//==============================================================================================
//============================== SEARCH BRACKETS RIGHT =========================================
//==============================================================================================

char BracketRight(int _s,int _e,XString comm, int& RRange, XString& er)  //= '[' or '(' or '<' 'n' (no brackets)
{
	int i=_s;
	int j;


	if (i>_e) { er="BracketRight:#1 Syntax error!"; return ('n'); };

	//------------------------------------------------------------- memory index
	if (comm.charAt(i)=='#')
	{
		j=i;
		do
		{
			j++;
			if (j>_e)  break;
		}
		while (IsNumber(comm.charAt(j)));

		RRange=j-1;
		return ('#');
	}

	//------------------------------------------------------------- interval
	if (comm.charAt(i)=='[')
	{
		j=i;
		do
		{
			j++;
			if (j>_e) {er="BracketRight:#2 Syntax error!"; return ('n'); };
		}
		while (comm.charAt(j)!=']');

		RRange=j;                              //indeks na ktorym stoi ']'
		return ('[');
	}

	//------------------------------------------------------------- interval matrix or vector
	if (comm.charAt(i)=='<')
	{
		j=i;
		do
		{
			j++;
			if (j>_e) {er="BracketRight:#3 Syntax error!"; return ('n'); };
		}
		while (comm.charAt(j)!='>');

		RRange=j;                              //indeks na ktorym stoi '>'                                              
		return ('<');
	}
	//------------------------------------------------------------- sequence

	if (comm.charAt(i)=='(')
	{

		int ilnw=1; //ilosc nawiasow wewnetrznych
		j=i;
		do
		{
			j++;
			if (j>_e) {er="BracketRight:#4 Syntax error!"; return ('n'); };
			if (comm.charAt(j)=='(') {ilnw++; };
			if (comm.charAt(j)==')') {ilnw--;};
		}
		while (ilnw>0);
		RRange=j;                                //indeks na ktorym stoi ')'
		return ('(');
	}


	//------------------------------------------------------------- real number
	if (IsNumber(comm.charAt(i)) || (comm.charAt(i)=='-') || (comm.charAt(i)=='+'))
	{
		j=i;
		do
		{
			j++;
			if (j>_e) break;
			if (comm.charAt(j)=='.')
			{
				j++;
				if (j>_e) {er="BracketRight:#5 Syntax error!"; return ('n'); };
			}
			if ((comm.charAt(j)=='e') || (comm.charAt(j)=='E'))
			{
				j++;
				if (j>_e) {er="BracketRight:#6 Syntax error!"; return ('n'); };
				if ((comm.charAt(j)=='-') || (comm.charAt(j)=='+'))
				{
					j++;
					if (j>_e) {er="BracketRight:#7 Syntax error!"; return ('n'); };
				}
			}

		}
		while ((j<=_e) && (IsNumber(comm.charAt(j))));

		RRange=j-1;
		return ('r');
	}

	//-------------------------------------------------------------------
	er="BracketRight:#8 Syntax error!";
	return('n');                                 //didn't find any bracket

}


//==============================================================================================
//============================== SEARCH BRACKETS LEFT ==========================================
//==============================================================================================

char BracketLeft(int _s,int _e,XString comm, int& LRange, XString& er)
{
	int i=_e;
	int j;



	if (i<_s) {er="BracketLeft:#1 Syntax error!"; return ('n'); };


	//-------------------------------------------------------------------
	if (comm.charAt(i)==']')
	{
		j=i;
		do
		{
			j--;
			if (j<_s) {er="BracketLeft:#2 Syntax error!"; return ('n'); };
		}
		while (comm.charAt(j)!='[');

		LRange=j;                              //the index which ']' stays at
		return (']');
	}

	//-------------------------------------------------------------------
	if (comm.charAt(i)=='>')
	{
		j=i;
		do
		{
			j--;
			if (j<_s) {er="BracketLeft:#3 Syntax error!"; return ('n'); };
		}
		while (comm.charAt(j)!='<');

		LRange=j;                              //the index which '>' stays at                                              
		return ('>');
	}

	//-------------------------------------------------------------------
	if (comm.charAt(i)==')')
	{

		int ilnw=1; //count for inner brackets
		j=i;
		do
		{
			j--;
			if (j<_s) {er="BracketLeft:#4 Syntax error!"; return ('n'); };
			if (comm.charAt(j)==')') {ilnw++; };
			if (comm.charAt(j)=='(') {ilnw--;};
		}
		while (ilnw>0);
		LRange=j;                                //the index which ')' stays at

		return (')');
	}


	//------------------------------------------------------------- real number
	if (IsNumber(comm.charAt(i)))            //  7576.876876e-200 + 9879.09e-7
		//  76+90  1+1-2
	{                                     //  #123
		j=i;
		do
		{
			j--;
			if (j<_s) break;

			if ((comm.charAt(j)=='-') || (comm.charAt(j)=='+'))
			{
				if ((comm.charAt(j-1)=='e') || (comm.charAt(j-1)=='E'))
					j-=2;
				else break;
			}
			if (comm.charAt(j)=='.')
			{
				j--;
				if (j<_s) {er="BracketLeft:#5 Syntax error!"; return ('n'); };
			}
		}
		while ((j>=_s) && (IsNumber(comm.charAt(j))));

		if (comm.charAt(j)=='#')
		{
			LRange=j;
			return ('#');
		}
		else
		{
			LRange=j+1;
			return ('r');
		}
	}


	//-------------------------------------------------------------------
	er="BracketLeft:#6 Syntax error!";
	return('n');                                 //didn't find any bracket

}


long double silnia(__int64 n)
{
	if (n<=1) return (1.0);
	else return (n*silnia(n-1));
}




bool TryToLDouble(XString x)
{
	LDouble result;
	try
	{
		SetPrecision(HIGH64);
		result=x.toLongDouble();
	}
	catch (EXCEPINFO ex)
	{
		return false;
	}
        return true;
}



bool TryToInt64(XString x)
{
	__int64 result;
	try
	{
		SetPrecision(HIGH64);
		result=x.toInt64();
	}
	catch (EXCEPINFO ex)
	{
		return false;
	}
	return true;
}

LDouble ConvToDouble(XString x)
{
	LDouble result;
	try
	{
		SetPrecision(HIGH64);
		result=x.toLongDouble();
	}
	catch (EXCEPINFO ex)
	{
		throw ex;
	}
	return result;
}



int ConvToInt(XString x)
{
	int result;
	try
	{
		result=x.toInt();
	}
	catch (EXCEPINFO ex)
	{
		throw ex;
	}
	return result;
}



// Converts a string representing floating-point number to partial fraction
void ToFrac(XString x, LDouble& licznik, LDouble& mianownik)
{
	int point,signE;           // position of decimal point and 'E' sign if exist
	XString intpart;
	XString decpart;  // integer part and decimal part
	XString mian;      // divisor; includes the value in 0.aE-b format
	XString licz;

	point=x.indexOf('.');
	signE=x.indexOf('E');
	if (signE<0) {signE=x.indexOf('e'); }; //if there is no big E check for the small e

	//====================================================================
	if ((point!=-1) && (signE<0))       //case  -ddd.ddd   d in {0..9}
	{
		intpart=x.subStrOfLen(0,point);
		decpart=x.subStrOfLen(point+1,x.length()-point-1);

		mian="1";
		for (int i=1; i<=decpart.length(); i++) mian=mian+(XString)"0";

		licz= (intpart+decpart);  //adding strings


		mianownik=ConvToDouble(mian);
		licznik=ConvToDouble(licz);

	}

	//====================================================================
	if ((point!=-1) && (signE!=-1))   //case  -ddd.dddE+-ddd    d in {0..9}
	{
		intpart=x.subStrOfLen(0,point);
		decpart=x.subStrOfLen(point+1,signE-point-1);

		int expn;


		expn = ConvToInt(x.subStrOfLen(signE+1,x.length()-signE-1)); //is dddE-ddd or dddE+ddd


		int i,mianPow;

		mian="1";
		for (i=1; i<=decpart.length(); i++) mian=mian+(XString)"0";

		mianPow=mian.length()-1;   //power of ten in divider

		if (expn<0)
		{
			for (i=1; i<=(-expn); i++) mian=mian+(XString)"0";
		}

		if (expn>0)
		{
			mian="1";
			if (expn > mianPow)
			{					
				for (i=1; i<=(expn-mianPow); i++) decpart=decpart+(XString)"0";
			}
			else
			{
				for (i=1; i<=(mianPow-expn); i++) mian=mian+(XString)"0";
			}
		}

		licz= (intpart+decpart);  //adding strings


		mianownik=ConvToDouble(mian);
		licznik=ConvToDouble(licz);

	}


	//====================================================================
	if ((point<0) && (signE!=-1))   //case  -dddE+-ddd    d in {0..9}
	{
		intpart=x.subStrOfLen(0,signE);

		int expn;


		expn =ConvToInt(x.subStrOfLen(signE+1,x.length()-signE-1));

		int i;

		mian="1";
		if (expn<0)
		{
			for (i=1; i<=(-expn); i++) mian=mian+(XString)"0";
		}

		if (expn>0)
		{
			for (i=1; i<=expn; i++) intpart=intpart+(XString)"0";
		}


		mianownik=ConvToDouble(mian);
		licznik=ConvToDouble(intpart);

	}


}


void ToFixedPoint(XString& number)
{
   number = number.replaceAll("e","E");
   number = number.replaceAll(",",".");
   if (IsNumber(number.charAt(0)))
         number = number.insert("+",0);


   int diff = 0;
   int expoint = 0;

   if (!number.contains("E"))     //  -1.23438612453200000000E-0006
   {
       number = number.insert((XString)"E+0000",number.length());
   }

   if (!number.contains("."))
   {
       number = number.insert((XString)".0",number.indexOf('E'));
   }


   int point = number.indexOf('.');
   //if (point!=2)
   //{
     number = number.remove(point,point);
     int i=0;
     for ( i =1;i<number.length();i++)
     {
        if (number.charAt(i)!='0') break;
     }
     diff = point - i - 1;

     number = number.remove(1,i-1);
     number = number.insert(".",2);
  // }


    expoint = number.indexOf('E');
    XString exp = number.subString(expoint+1,number.length()-1);
    int exponent = exp.toInt();
    exponent = exponent + diff;
    exp = exp.fromInt(exponent);
    if (IsNumber(exp.charAt(0))) exp = exp.insert("+",0);
    while (exp.length()<5) exp = exp.insert("0",1);         //-0003
    number = number.remove(expoint+1,number.length()-1);
    number = number.insert(exp,expoint+1);
    while (number.length()<29) number = number.insert("0",expoint);

    if (number.charAt(0)=='+') number = number.remove(0,0);

}



long double PowOfTwo(int n)   // 2^n
{
 asm
  {
   FILD n
   FLD1
   FSCALE
   FSTP ST(1)
  }
}


int exponent(long double x)
{
 int expo;

 if (x==0.0) return 0;

asm
 {
  FLD x
  FXTRACT
  FSTP ST(0)
  FISTP expo
  MOV EAX, expo
 }
}

long double mantissa(long double x)
{

 if (x==0.0) return 0;

 asm
 {
  FLD x
  FXTRACT
  FXCH
  FSTP ST(0)
 }
}


int StrLastIndexOf(AnsiString& source, AnsiString key)
{
  if (source.IsEmpty()) return -1;
  if (key.IsEmpty()) return -1;

  int slen = source.Length();
  int klen = key.Length();
  int res = -1;

  for (int i=slen-klen-1;i>=0;i--)
  {
    if (source.c_str()[i]==key.c_str()[0])
    {
       for (int j=0;j<klen;j++)
       {
         if (source.c_str()[i+j]!=key.c_str()[j])
         res = -1;
         else
         res = i;
       }
    }

    if (res>-1) return res;
  }

  return res;

}



