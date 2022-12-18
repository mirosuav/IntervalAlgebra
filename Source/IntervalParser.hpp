

class IntMatrixPArray
{
 private:
    vector < IntMatrix* > elements;

    int GetFirstNull()
    {
      for (int ind =0; ind<elements.size();ind++)
      if (elements[ind]== NULL ) return ind;

      return -1;
    }


 public:
        IntMatrixPArray(void)
        {
           elements.clear();
        }

        int Add(IntMatrix *NewElement)
        {
           int index= 0;
           index = this->GetFirstNull();

           if (index!= -1)
           {
             elements[index] = NewElement;
             return index;
           }

           int elSize = elements.size();
           elements.push_back();
           elements[elSize] = NewElement;
           return elSize;
        }


        void RemoveAt(int index)
        {
           if ( (index>=elements.size()) || (index<0) ) return;
           elements[index] = NULL;
        }


        IntMatrix *GetAt(int index)
        {
           if ( (index>=elements.size()) || (index<0) ) return NULL;
           return elements[index];
        }

        void Clear()
        {
           elements.clear();
        }


};

class IntervalParser
{
 public:
        IntervalParser(void)
        {

        }
                                           
        IntMatrixPArray varibles;


        bool TempRes;
        void OnTempResult(AnsiString text)
        {
          LogFrm->AppText(text);
        }

       



        //***************************************************************
        //           READ INTERVAL
        //***************************************************************
        Interval ReadInterval(XString& comm,int _st,int _en, XString& er )
        {
            Interval Result;
            int k=comm.indexOf(",",_st+1,_en-_st-1);
            if (k==-1)                     //one number typed only
            {
                    XString temp = ParseNumber(_st+1,_en-1,comm,er);
                    if (er!="") return Result;
                    Result = Interval(temp);
                    if (Result.empty())  {er="Empty interval!"; return Result;}
            }
            else                                     //both outskirts specified
            {
                    XString a=ParseNumber(_st+1,k-1,comm,er);
                    if (er!="") return Result;
                    XString b=ParseNumber(k+1,_en-1,comm,er);
                    if (er!="") return Result;
                    Result=Interval(a,b);
                    if (Result.empty())  {er="Empty interval!"; return Result;}
            }
            return Result;

        }








        //***************************************************************
        //           READ MATRIX DIMENSIONS
        //***************************************************************
        void ReadDimensions(XString& comm,int _st,int _en,int& _rows, int& _cols, XString& er )
        {
           if (comm.charAt(_st)!='<') {er="Syntax error!"; return; }

           int zR,ir=0,ic=0;
           _rows = 0;
           _cols = 100000;

           for (int i=_st+1;i<_en;)
           {
              if (BracketRight(i,_en,comm,zR,er)!='n')  //search for matrix element
              {
                  ic++;
                  if (ic>_cols) {er="Wrong matrix dimensions!"; break;}
                  i=zR+1;
              }
              else break;

              if (comm.charAt(i)==';') //new row detected
              {
                  ir++; i++;
                  _cols = ic;
                  ic=0;
                  if (i>=_en) {er="Unexpected end of matrix!"; break;}
              }

           }
           _rows = ir+1;
           _cols = ic;

        }




        //***************************************************************
        //           READ ALL MATRICES
        //***************************************************************
        void ReadMatrices(XString& comm,XString& er )
        {
           while (comm.contains("<"))
           {

             int _st = comm.indexOf("<");
             int _en;
             if (BracketRight(_st,comm.length()-1,comm,_en,er)=='n') return;
             int _rows,_cols;
             ReadDimensions(comm,_st,_en,_rows,_cols,er);
             if (er!="") break;

             IntMatrix Result = IntMatrix(_rows,_cols);

             int zR,zL=0,ir=0,ic=0;
             zR = _st+1;
             for (ir=0;ir<Result.RowCnt;ir++)
              {
                for (ic=0;ic<Result.ColCnt;ic++)
                {
                   zL = comm.indexOf("]",zR+1);
                   Result._el[ir][ic] = ReadInterval(comm,zR,zL,er);
                   if (er!="") break;
                   zR = comm.indexOf("[",zL);
                }
              }

             int index = varibles.Add(new IntMatrix(Result));
             comm = comm.remove(_st,_en);
             comm = comm.insert((XString)"#"+XString::fromInt(index),_st);

             if (TempRes) OnTempResult(" Value found: #"+XString::fromInt(index).ToAnsiString()+
                                       " = "+  Result.ToStr().ToAnsiString() +"\n");


           }

         }


        //***************************************************************
        //           READ ALL INTERVALS
        //***************************************************************
        void ReadIntervals(XString& comm,XString& er )
        {

           while (comm.contains("["))
           {

             int _st = comm.indexOf("[");
             int _en;
             if (BracketRight(_st,comm.length()-1,comm,_en,er)=='n') return;

             Interval Result = ReadInterval(comm,_st,_en,er);
             if (er!="") return;

             int index = varibles.Add(new IntMatrix(Result));
             comm = comm.remove(_st,_en);
             comm = comm.insert((XString)"#"+XString::fromInt(index),_st);

             if (TempRes) OnTempResult(" Value found: #"+XString::fromInt(index).ToAnsiString()+
                                       " = "+  Result.ToStr().ToAnsiString() +"\n");


           }
        }


        //***************************************************************
        //           REMOVE UNNECESSARY PLUS SIGNS
        //***************************************************************
        void RemovePluses(XString& comm)
        {
              int i;
              //if + is placed at the beginning of the command
              if (comm.charAt(0)=='+')
              {
                      comm=comm.trimStart("+"); //Remove unary plus sign
              }

              //First remowe unnecessary plus signs
              while (
                      ((i=comm.indexOf("(+"))!=-1) ||
                      ((i=comm.indexOf("[+"))!=-1) ||
                      ((i=comm.indexOf("<+"))!=-1) ||
                      ((i=comm.indexOf(",+"))!=-1) ||
                      ((i=comm.indexOf(";+"))!=-1)
                    )
              {
              comm=comm.removeFrom(i+1,1); //Remove unary plus sign
              }
        }


        //***************************************************************
        //           PARSE COMMAND
        //***************************************************************
        IntMatrix ParseCommand(XString& comm,XString& er, bool ShowTempRes, IntMatrix& lastResult)
        {
                TempRes = ShowTempRes;
                varibles = IntMatrixPArray();

                if (TempRes)
                {
                        OnTempResult(" \n----------------------------------------------------\n");
                        OnTempResult(" Parsing started at: "+ TimeToStr(Now())+" \n");
                        OnTempResult(" command: "+comm.ToAnsiString()+"\n");
                        OnTempResult(" \n");
                }
                
                // replace all '%' characters with last result
                while (comm.contains((XString)"%"))
                {
                   int k = comm.indexOf('%');
                   comm = comm.removeFrom(k,1);
                   int index = varibles.Add(new IntMatrix(lastResult));
                   comm = comm.insert((XString)"#"+XString::fromInt(index),k);

                   if (TempRes) OnTempResult(" Value found: #"+XString::fromInt(index).ToAnsiString()+
                                             " = "+  lastResult.ToStr().ToAnsiString() +"\n");

               }


                RemovePluses(comm);
                ReadMatrices(comm,er);
                ReadIntervals(comm,er);
                if (er!="") return IntMatrix();
                IntMatrix Result;
                Result = IterateOperations(0,comm.length()-1, comm,er);
                return Result;
        }





IntMatrix IterateOperations(int _st,int _en,XString comm,XString& er )
//=====================================================================
//================= PARSE INTERVAL SEQUENCE ===========================
//=====================================================================
{



IntMatrix Result;
IntMatrix temp;
IntMatrix templ;
IntMatrix tempr;
XString tmp;
int i;
int k;
int index=0;

if (TempRes) OnTempResult("     Parsing: "+comm.subString(_st,_en).ToAnsiString()+"\n");
if (IsNumber(comm.charAt(0))) {er=(XString)"Wrong number format!"; return (Result); };



//================================================================================
//============================ ONE ARGUMENT FUNCTIONS ============================
//================================================================================

while  ( ((i=comm.indexOf("a",_st,_en-_st+1))!=-1) ||   // Absolute value
        ((i=comm.indexOf("w",_st,_en-_st+1))!=-1) ||   // Width of interval
        ((i=comm.indexOf("m",_st,_en-_st+1))!=-1) ||   // Midpoint
        ((i=comm.indexOf("r",_st,_en-_st+1))!=-1) ||   // Radius
        ((i=comm.indexOf("q",_st,_en-_st+1))!=-1) ||   // Square root
        ((i=comm.indexOf("x",_st,_en-_st+1))!=-1) ||   // Exponent
        ((i=comm.indexOf("l",_st,_en-_st+1))!=-1) ||   // Natural logarithm
        ((i=comm.indexOf("s",_st,_en-_st+1))!=-1) ||   // Sinus
        ((i=comm.indexOf("c",_st,_en-_st+1))!=-1) ||   // Cosinus
        ((i=comm.indexOf("t",_st,_en-_st+1))!=-1) ||   // Tangens
        ((i=comm.indexOf("i",_st,_en-_st+1))!=-1) ||   // Inverse
        ((i=comm.indexOf("n",_st,_en-_st+1))!=-1) ||   // Transpose
        ((i=comm.indexOf("z",_st,_en-_st+1))!=-1) ||   // Determinant
        ((i=comm.indexOf("j",_st,_en-_st+1))!=-1) ||   // Cond
        ((i=comm.indexOf("k",_st,_en-_st+1))!=-1) ||   // Norm
        ((i=comm.indexOf("u",_st,_en-_st+1))!=-1) ||   // Gauss elimination
        ((i=comm.indexOf("p",_st,_en-_st+1))!=-1) ||   // Gauss Partial elimination
        ((i=comm.indexOf("f",_st,_en-_st+1))!=-1) ||   // Gauss full elimination
        ((i=comm.indexOf("g",_st,_en-_st+1))!=-1)      // Cotangens
        )
{	

        wchar_t fname = comm.charAt(i);   //the character representing corresponding function name

        if (TempRes)
        {
                switch (fname)
                {
                case 'a': OnTempResult("         Abs: start\n"); break;
                case 'w': OnTempResult("       Width: start\n"); break;
                case 'm': OnTempResult("    Midpoint: start\n"); break;
                case 'r': OnTempResult("      Radius: start\n"); break;
                case 'q': OnTempResult("        Sqrt: start\n"); break;
                case 'x': OnTempResult("         Exp: start\n"); break;
                case 'l': OnTempResult("         Log: start\n"); break;
                case 's': OnTempResult("         Sin: start\n"); break;
                case 'c': OnTempResult("         Cos: start\n"); break;
                case 't': OnTempResult("         Tan: start\n"); break;
                case 'g': OnTempResult("       Cotan: start\n"); break;
                case 'i': OnTempResult("     Inverse: start\n"); break;
                case 'n': OnTempResult("   Transpose: start\n"); break;
                case 'z': OnTempResult(" Determinant: start\n"); break;
                case 'j': OnTempResult("   Condition: start\n"); break;
                case 'k': OnTempResult("        Norm: start\n"); break;
                case 'u': OnTempResult("       Gauss: start\n"); break;
                case 'p': OnTempResult("  Gauss part: start\n"); break;
                case 'f': OnTempResult("  Gauss full: start\n"); break;
                }

        }


        if (i<=_en-1)
        {
                int zakr=0;
                if (BracketRight(i+1,_en,comm,zakr,er)!='n') //take the right hand argument
                {
                        tempr=IterateOperations(i+1,zakr,comm,er);
                        if (er!="") break;
                        if (tempr.empty())  {er="Empty interval!"; break;}


                        switch (fname)
                        {
                        case 'a': temp = tempr.iabs(er); break;
                        case 'w': temp = tempr.szerokosc(er); break;
                        case 'm': temp = tempr.srodek(er); break;
                        case 'r': temp = tempr.promien(er); break;
                        case 'q': temp = tempr.sqrti(er); break;
                        case 'x': temp = tempr.expi(er); break;
                        case 'l': temp = tempr.ilog(er); break;
                        case 's': temp = tempr.isin(er); break;
                        case 'c': temp = tempr.icos(er); break;
                        case 't': temp = tempr.itan(er); break;
                        case 'g': temp = tempr.ictan(er); break;
                        case 'i': temp = tempr.Inverse(er); break;
                        case 'n': temp = tempr.Transpose(); break;
                        case 'z': temp = tempr.Determinant(er); break;
                        case 'j': temp = tempr.Cond(er); break;
                        case 'k': temp = tempr.Norm(); break;
                        case 'u': temp = tempr.Gauss(er); break;
                        case 'p': temp = tempr.GaussPart(er); break;
                        case 'f': temp = tempr.GaussFull(er,k); break;

                        }
                        if (er!="") break;

                }
                else
                {er="Syntax error!"; break; };

                index = varibles.Add(new IntMatrix(temp));
                comm = comm.remove(i,zakr);
                tmp = (XString)"#" + tmp.fromInt(index);
                comm = comm.insert(tmp,i);

                _en=_en - (zakr-i-tmp.length()+1);

						
        }
        else
        {er=(XString)"Syntax error!"; break; };


        if (TempRes)
        {
                AnsiString text = "#"+XString::fromInt(index).ToAnsiString()+
                                     " = "+temp.ToStr().ToAnsiString()+"\n";
                switch (fname)
                {
                case 'a': OnTempResult("         Abs: " + text); break;
                case 'w': OnTempResult("       Width: " + text); break;
                case 'm': OnTempResult("    Midpoint: " + text); break;
                case 'r': OnTempResult("      Radius: " + text); break;
                case 'q': OnTempResult("        Sqrt: " + text); break;
                case 'x': OnTempResult("         Exp: " + text); break;
                case 'l': OnTempResult("         Log: " + text); break;
                case 's': OnTempResult("         Sin: " + text); break;
                case 'c': OnTempResult("         Cos: " + text); break;
                case 't': OnTempResult("         Tan: " + text); break;
                case 'g': OnTempResult("       Cotan: " + text); break;
                case 'i': OnTempResult("     Inverse: " + text); break;
                case 'n': OnTempResult("   Transpose: " + text); break;
                case 'z': OnTempResult(" Determinant: " + text); break;
                case 'j': OnTempResult("   Condition: " + text); break;
                case 'k': OnTempResult("        Norm: " + text); break;
                case 'u': OnTempResult("       Gauss: " + text); break;
                case 'p': OnTempResult("  Gauss part: " + text); break;
                case 'f': OnTempResult("  Gauss full: " + text); break;
                }

        }


        }
if (er!="") return (Result);




      //====================================================================
      //============================ UNARY MINUS ===========================
      //====================================================================

      while ( ((i=comm.indexOf("-",_st,_en-_st+1))!=-1) &&    //unary minus is placed at the beginning
              ((i==_st) || (comm.charAt(i-1)=='(')) )                 // of command or next to opening bracket '('
      {

              if (TempRes) OnTempResult(" Unary minus: start\n");

              int  zR=0;    //range of argument
              if (BracketRight(i+1,_en,comm,zR,er)!='n')
              {
                      tempr=IterateOperations(i+1,zR,comm,er);
                      if (er!="") break;
                      if (tempr.empty())  {er="Empty interval!"; break;}
                      temp = (-tempr);
              }
              else
              { break; };


              index = varibles.Add(new IntMatrix(temp));
              comm = comm.remove(i,zR);
              tmp = (XString)"#" + tmp.fromInt(index);
              comm = comm.insert(tmp,i);

              _en=_en - (zR-i-tmp.length()+1);
              if (TempRes) OnTempResult(" Unary minus: #"+XString::fromInt(index).ToAnsiString()+
                                                " = "+temp.ToStr().ToAnsiString()+"\n");

      }
       if (er!="") return (Result);







//============================================================================
//====================== TWO ARGUMENTS FUNCTIONS =============================
//============================================================================

while  ( ((i=comm.indexOf("d",_st,_en-_st+1))!=-1) ||   // Distance
      ((i=comm.indexOf("^",_st,_en-_st+1))!=-1) ||   // Power
      ((i=comm.indexOf("*",_st,_en-_st+1))!=-1) ||   // Multiplication
      ((i=comm.indexOf("/",_st,_en-_st+1))!=-1) ||   // Division
      ((i=comm.indexOf("-",_st,_en-_st+1))!=-1) ||   // Subtraction
      ((i=comm.indexOf("v",_st,_en-_st+1))!=-1) ||
      ((i=comm.indexOf("h",_st,_en-_st+1))!=-1) ||
      ((i=comm.indexOf("b",_st,_en-_st+1))!=-1) ||
      ((i=comm.indexOf("+",_st,_en-_st+1))!=-1)    // Addition
      )
{

      //the following condition is necessary to check wheather the
      //minus sign is really representing subtraction or is just a sign of number
      //see also the condition in while loop above
      if (comm.charAt(i)==')')  {i++;};

      wchar_t fname = comm.charAt(i);   //the character representing corresponding function name

      if (TempRes)  //printing temporary result
      {
              switch (fname)
              {
              case 'd': OnTempResult("    Distance: start\n"); break;
              case '^': OnTempResult("       Power: start\n"); break;
              case '*': OnTempResult("    Multiply: start\n"); break;
              case '/': OnTempResult("    Division: start\n"); break;
              case '-': OnTempResult(" Subtraction: start\n"); break;
              case '+': OnTempResult("    Addition: start\n"); break;
              case 'h': OnTempResult("       Solve: start\n"); break;
              case 'v': OnTempResult("  Solve part: start\n"); break;
              case 'b': OnTempResult("  Solve full: start\n"); break;
              }

      }

      if ((i-1<=_st) || (i+1>=_en)) {er="Syntax error!"; break; }; //jesli brak czynnikow

      int zL=0, zR=0;  //start and end index of evaluated sequence


      //====================== parsing left side
      if (BracketLeft(_st,i-1,comm,zL,er)!='n')
      {
              templ=IterateOperations(zL,i-1,comm,er);
              if (templ.empty())  {er="Empty interval!"; break;}
      }
      else break;


      //====================== parsing right side
      if (BracketRight(i+1,_en,comm,zR,er)!='n')
      {
              tempr=IterateOperations(i+1,zR,comm,er);
              if (tempr.empty())  {er="Empty interval!"; break;}
      }
      else break;

                                         
      //====================== evaluating functions
      switch (fname)
  {
      case 'd': temp = IntMatrix::odleglosc(templ,tempr); break;
      case '^': temp = IntMatrix::npoweri(templ,(int)tempr._el[0][0]._i); break;
      case '*': temp = (templ*tempr); break;
      case '/': if (tempr.iszero())  {er="Dividing by interval including zero!"; break;}
                    temp = (templ/tempr); break;
      case '-': temp = (templ-tempr); break;
      case '+': temp = (templ+tempr); break;
      case 'h': temp = (templ.Solve(er,tempr)); break;
      case 'v': temp = (templ.SolvePart(er,tempr)); break;
      case 'b': temp = (templ.SolveFull(er,tempr)); break;
      }

      if (er!="") break; //leave the while loop

      index = varibles.Add(new IntMatrix(temp));
      comm = comm.remove(zL,zR);
      tmp = (XString)"#" + tmp.fromInt(index);
      comm = comm.insert(tmp,zL);

      _en=_en - (zR-zL-tmp.length()+1);



      if (TempRes)    //Printing temporary result
      {
              AnsiString text = "#"+XString::fromInt(index).ToAnsiString()+
                                     " = "+temp.ToStr().ToAnsiString()+"\n";
              switch (fname)
              {
              case 'a': OnTempResult("    Distance: " + text); break;
              case '^': OnTempResult("       Power: " + text); break;
              case '*': OnTempResult("    Multiply: " + text); break;
              case '/': OnTempResult("    Division: " + text); break;
              case '-': OnTempResult(" Subtraction: " + text); break;
              case '+': OnTempResult("    Addition: " + text); break;
              case 'h': OnTempResult("       Solve: " + text); break;
              case 'v': OnTempResult("  Solve part: " + text); break;
              case 'b': OnTempResult("  Solve full: " + text); break;
              }

      }
      }
      if (er!="") return (Result);



    //======================= Delete unimportant brackets ====================

    while ((comm.charAt(_st)=='(') && (comm.charAt(_en)==')'))
    {
            comm=comm.removeFrom(_st,1);
            _en=_en-1;
            comm=comm.removeFrom(_en,1);
            _en=_en-1;
    }




    //====================================================================
    //==================== INTERVALS OR MATRICES =========================
    //====================================================================


    if (comm.charAt(_st)=='#') //if command is pure interval
    {
          XString indx = ParseNumber(_st+1,_en,comm,er);
          if (er!="") return Result;
          Result = *varibles.GetAt(indx.toInt());
          varibles.RemoveAt(indx.toInt());
    }



if (TempRes) OnTempResult(" Temp result: "+Result.ToStr().ToAnsiString()+"\n");

return Result;
}


};