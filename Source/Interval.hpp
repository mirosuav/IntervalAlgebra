

class Interval
{
public:

	LDouble _i, _s;


	Interval()                 
	{ 
		_i=(long double)0.0;
		_s=(long double)0.0; 
	}
         
        //This mplementation used nominator/denominator method
	//Converts string to interval
	Interval(XString x, XString y)
	{


		if ((!(x.contains("."))) && (!(x.contains("e"))) && (!(x.contains("E"))) )   // if string represent the integer number
		{
			_i=ConvToDouble(x);
		}
		else
		{
                         SetPrecision(HIGH64);
			LDouble licz,mian;
			ToFrac(x,licz,mian);
			Rdown();
			_i=(long double)(licz/mian);
		};

		if ((!(y.contains("."))) && (!(y.contains("e"))) && (!(y.contains("E"))) )
		{
			_s=ConvToDouble(y);
		}
		else
		{
                         SetPrecision(HIGH64);
			LDouble licz,mian;
			ToFrac(y,licz,mian);
			Rup();
			_s=(long double)(licz/mian);
		};

		Rnear();



	};



	Interval(XString x)
	{
		if ((!(x.contains("."))) && (!(x.contains("e"))) && (!(x.contains("E"))) )   // if string represent the integer number
		{
			_i=ConvToDouble(x);
			_s=ConvToDouble(x);
		}
		else
		{
                        SetPrecision(HIGH64);
			LDouble licz,mian;
			ToFrac(x,licz,mian);

			Rdown();
			_i=(long double)(licz/mian);
			Rup();
			_s=(long double)(licz/mian);
		};
		Rnear();

                //bool equ = _i==_s;
                //bool les = _i<_s;
                //bool grt = _i>_s;
	}


         /*

        Interval(XString sa, XString sb)
	{
            SetPrecision(HIGH64);

            if ((!(sa.contains("."))) && (!(sa.contains("e"))) && (!(sa.contains("E"))) )   // if string represent the integer number
            {
                    _i=ConvToDouble(sa);
            }
            else
            {

                LDouble x = sa.toLongDouble();
                XString sx = XString::fromLongDouble(x);
                ToFixedPoint(sx);
                ToFixedPoint(sa);
                if (sx.ToAnsiString()==sa.ToAnsiString())
                {
                    _i=x;
                }
                else
                {
                     int exp = exponent(x);
                     _i= x - PowOfTwo(exp-63);
                }

            };




            if ((!(sb.contains("."))) && (!(sb.contains("e"))) && (!(sb.contains("E"))) )
            {
                    _s=ConvToDouble(sb);
            }
            else
            {

                LDouble y = sb.toLongDouble();
                XString sy = XString::fromLongDouble(y);
                ToFixedPoint(sy);
                ToFixedPoint(sb);
                if (sy.ToAnsiString()==sb.ToAnsiString())
                {
                    _s=y;
                }
                else
                {
                     int exp = exponent(y);
                     _s= y + PowOfTwo(exp-63);
                }
            };

            if (_i>_s)
            {
              LDouble t = _i;
              _i = _s;
              _s = t;
            }

	};

         Interval(XString sa)
	 {

		if ((!(sa.contains("."))) && (!(sa.contains("e"))) && (!(sa.contains("E"))) )   // if string represent the integer number
		{
			_i=ConvToDouble(sa);
			_s=ConvToDouble(sa);
		}
		else
		{
                        SetPrecision(HIGH64);

                        LDouble x = sa.toLongDouble();
                        XString sx = XString::fromLongDouble(x);
                        ToFixedPoint(sx);
                        ToFixedPoint(sa);

                        if (sx.ToAnsiString()==sa.ToAnsiString())
                           {
                             _i=x;
                             _s=x;
                             return;
                           }
                                                                //?

                        int exp = exponent(x);
                        long double eps = PowOfTwo(exp-63);

                        LDouble px = x - eps;
                        LDouble nx = x + eps;
                                                                //?   ---px----a---x---nx----
                        if (sa.charAt(0)=='-')
                        {
                         if (sx.ToAnsiString()>sa.ToAnsiString())
                           { _i=x; _s=nx; }
                         else
                           { _i=px; _s=x; }
                        }
                        else
                        {
                         if (sx.ToAnsiString()>sa.ToAnsiString())
                           { _i=px; _s=x; }
                          else
                          { _i=x; _s=nx; }
                        }


                }




	}

         */



	Interval(int a)
	{
		_i=(long double)a;
		_s=(long double)a;
	};


	Interval(__int64 a)
	{
		_i=(long double)a;
		_s=(long double)a;
	};


	Interval(long double a, long double b)
	{
		_i=(long double)a;
		_s=(long double)b;
	};

	Interval(long double a)
	{
		_i=(long double)a;
		_s=(long double)a;
	};


	XString ToStr(AnsiString format = "0.0000000000000000000")
	{
                SetPrecision(HIGH64);
		XString resi,ress;
                (_i<0)?Rup():Rdown();
		resi = resi.fromLongDouble(_i,format);
                resi = resi.replaceAll(",",".");
	       	(_s<0)?Rdown():Rup();
		ress = ress.fromLongDouble(_s,format);
                ress = ress.replaceAll(",",".");
	       	Rnear();
		return ((XString)"["+resi+(XString)","+ress+(XString)"]");
	};



	//========== OPERATORY ==============================


	//==== OPERATOR PRZYPISANIA ====
	Interval operator =(Interval y)
	{
		_i=y._i;
		_s=y._s;
		return(*this);
	};



	Interval operator =(LDouble y)
	{ 
		*this=Interval(y);
		return(*this); 
	};

	Interval operator =(int y)
	{ 
		*this=Interval(y); 
		return(*this); 
	};

	//========== LOGICZNE =================

        
        bool operator ==(LDouble a)      //ROWNE
	{
		return(((_i==a) &&  (_s==a)) ? true : false);
	};

	bool operator ==(Interval y)      //ROWNE
	{
		return(((_i==y._i) &&  (_s==y._s)) ? true : false);
	};

	bool operator !=(Interval y)    //ROZNE
	{
		return (((_i!=y._i) || (_s!=y._s)) ? true : false);
	};


	//=========== ARYTMETYCZNE ===========

	Interval operator +(Interval y) //DODAWANIE
	{
		Interval* temp = new Interval();

		Rdown();
		temp->_i = _i + y._i;
		Rup();
		temp->_s = _s + y._s;
		Rnear();

		return(*temp);
	};



	Interval operator -( Interval y)  //ODEJMOWANIE
	{
		Interval* temp = new Interval();

		Rdown();
		temp->_i = _i - y._s;
		Rup();
		temp->_s = _s - y._i;
		Rnear();

		return(*temp);
	};


	Interval operator *( Interval y)  //MNOZENIE
	{
		Interval* temp = new Interval();
		Rdown();
		temp->_i = minimum(_i*y._i , _i*y._s , _s*y._i , _s*y._s);
		Rup();
		temp->_s = maximum(_i*y._i , _i*y._s , _s*y._i , _s*y._s);
		Rnear();
		return(*temp);
	};


	Interval operator /(Interval y)  //DZIELENIE
	{

		if (y.iszero())
		{
			return( *(new Interval(0.0)));
		}
		else
		{
                  Interval* tmp = new Interval();
                  Rdown();
                  tmp->_i=minimum(_i/y._i,_i/y._s,_s/y._i,_s/y._s);

                  Rup();
                  tmp->_s=maximum(_i/y._i,_i/y._s,_s/y._i,_s/y._s);

                  Rnear();

                  return (*tmp);


		}

	};


	Interval operator+ ()
	{ 
		return *this;
	};

	Interval operator- ()
	{
                LDouble t = 0.0;
                 t = -(_s);
                _s = -(_i);
                _i = t;
		return *this;
	};

	Interval operator+= (Interval y)
	{
		*this = *this + y; 
		return(*this); 
	};

	Interval operator-= (Interval y)
	{ 
		*this = *this - y; 
		return(*this); 
	};

	Interval operator*= (Interval y)
	{ 
		*this = *this * y; 
		return(*this); 
	};

	Interval operator/= (Interval y)
	{ 
		*this = *this / y; 
		return(*this); 
	};


	Interval IntervalZero(void)
	{
		return(*(new Interval(0.0,0.0)));
	};


	//==== WARTOSC BEZWZGLEDNA INTERWALU ===

	Interval iabs()
	{
		LDouble ai=fabsl(_i);
		LDouble as=fabsl(_s);
                Interval* tmp = new Interval();


		if (!iszero())  
		{
                        tmp->_i =  (ai<as) ? ai : as ;
                        tmp->_s =  (ai<as) ? as : ai ;
		}
		else
		{
                        tmp->_i =  0.0;
                        tmp->_s =  (ai<as) ? as : ai ;
		}

                return *tmp;
	};


	//Sine
	Interval isin()
	{
		// split domain into parts of width pi
		// 
		//      0      1      2      3
		// -+------+------+------+------+-
		// -pi/2  pi/2   3pi/2  5pi/2  7pi/2
		//
		// even part -> sine increasing
		// odd part -> sine decreasing

		Interval parts = *this/Interval(M_PI) + Interval(0.5);
		LDouble infP = floorl( parts._i );
		LDouble supP = floorl( parts._s );

		// If there is a whole part between inf and sup, the result is [-1,1]

		if (supP - infP > 1)
		{
			return (Interval(-1,1));
		}

		// If inf and sup are in consecutive parts, either -1 either 1 has been
		// reached in between

		if (supP == infP + 1)
		{
			Interval result;

			if (parzysta(infP))
			{
				// 1 reached
				result._s = 1;
				Rdown();
				LDouble infsin = sinl(_i);
				LDouble supsin = sinl(_s);
				Rnear();
				result._i = minimum(infsin,supsin);
			}
			else
			{
				// -1 reached
				result._i = -1;
				Rup();
				LDouble infsin = sinl(this->_i);
				LDouble supsin = sinl(this->_s);
				Rnear();
				result._s = maximum(infsin,supsin);
			}
			return result;
		}

		// Otherwise inf and sup are in the same part, and we just have to
		// figure out whether sin is increasing or decreading

		Interval result;
		if (parzysta(infP))
		{
			Rdown();
			result._i = sinl(_i);
			Rup();
			result._s = sinl(_s);
			Rnear();
		}
		else
		{
			Rdown();
			result._i = sinl(_s);
			Rup();
			result._s = sinl(_i);
			Rnear();
		}

		return result;
	}


	//Cosine
	Interval icos()
	{
		return ( (Interval(M_PI/2.0)- *this).isin() );
	}



	//Tangens
	Interval itan()
	{
		Interval temp;

		Rdown();
		temp._i = tanl(_i);
		Rup();
		temp._s = tanl(_s);
		Rnear();

		return(temp);
	}


	//Cotangens
	Interval ictan()
	{
		return (Interval(1.0)/itan());
	}




	//Logarytm naturalny
	Interval ilog()
	{
		Interval temp;

		Rdown();
		temp._i = logl(_i);
		Rup();
		temp._s = logl(_s);
		Rnear();

		return(temp);
	}



	//PIERWIASTEK Z PRZEDZIALU
	Interval sqrti(XString& er)
	{
		if (_i<0)
		{
			er="Square root: Negative interval!";	 
			return(Interval());
		}
		else
		{
			Interval temp;
			Rdown();
			temp._i=sqrtl(_i);
			Rup();
			temp._s=sqrtl(_s);
			Rnear();
			return (temp);
		}

	};


	//EXPONENT PRZEDZIALU
	Interval expi()
	{
		Interval temp;
		Rdown();
		temp._i=expl(_i);
		Rup();
		temp._s=expl(_s);
		Rnear();
		return (temp);
	};



	/*SZEROKOSC PRZEDZIALU*/
	Interval szerokosc()
	{
		Interval tmp;
		tmp._i=_s-_i;
		tmp._s=_s-_i;
		return (tmp);
	};


	/*PROMIEN PRZEDZIALU*/
	Interval promien()
	{
		Interval tmp; 
		tmp._i=(_s-_i)/2; 
		tmp._s=(_s-_i)/2; 
		return (tmp); 
	};

	/*SRODEK PRZEDZIALU*/
	Interval srodek()              
	{ 
		Interval tmp; 
		tmp._i=(_i+_s)/2; 
		tmp._s=(_i+_s)/2; 
		return (tmp); 
	};


	/*CZY PRZEDZIAL ZAWIERA ZERO*/
	bool iszero()              
	{ 
		return ((_i<=0.0)&&(_s>=0.0)); 
	};

	/*CZY PRZEDIZAL PUSTY*/
	bool empty()  
	{ 
		return ((_s<_i) ? true : false); 
	};


	//ODLEGLOSC MIEDZY DWOMA PRZEDZIALAMI

	static Interval odleglosc(Interval& x, const Interval& y)
	{
		Interval* tmp = new Interval();
		tmp->_i = abs(x._i-y._i)>abs(x._s-y._s) ?  abs(x._i-y._i)  :  abs(x._s-y._s);
		tmp->_s = tmp->_i;
		return(*tmp);
	};


	//POTEGA N PRZEDZIALU N - NATURALNE
	static Interval npoweri(Interval& x,const int& n)
	{
		LDouble dol;
		LDouble gora;
		if (n<0) { return (Interval(1,1)/npoweri(x,-n));};
		if (!(n<0))
		{
			if ((!parzysta(n)) || (x._i >= 0))
			{
				Rdown();
				dol=adon(x._i,n);
				Rup();
				gora=adon(x._s,n);
				Rnear();
			}
			if (parzysta(n) && (x._s <= 0))
			{
				Rdown();
				dol=adon(x._s,n);
				Rup();
				gora=adon(x._i,n);
				Rnear();
			}
			if (parzysta(n) && (x.iszero()))
			{
				Rdown();
				dol=0.0;
				Rup();
				gora=( (fabs(x._i)>fabs(x._s)) ? adon(fabs(x._i),n) : adon(fabs(x._s),n) );
				Rnear();
			}
		}   
		return (*(new Interval(dol,gora)));
	}

};