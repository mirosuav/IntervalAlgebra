

class RealMatrixPArray
{
 private:
    vector < RealMatrix* > elements;

    int GetFirstNull()
    {
      for (int ind =0; ind<elements.size();ind++)
      if (elements[ind]== NULL ) return ind;

      return -1;
    }


 public:
        RealMatrixPArray(void)
        {
           elements.clear();
        }

        int Add(RealMatrix *NewElement)
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


        RealMatrix *GetAt(int index)
        {
           if ( (index>=elements.size()) || (index<0) ) return NULL;
           return elements[index];
        }

        void Clear()
        {
           elements.clear();
        }


};



class RealParser
{
 public:

  RealParser(void)
  {
  }
                                         //wskazniki do IntMatrixow
  RealMatrixPArray varibles;

  bool TempRes;
  void OnTempResult(AnsiString text)
  {
    LogFrm->AppText(text);
  }






  

  //***************************************************************
  //           READ NUMBER
  //***************************************************************
  LDouble ReadNumber(XString& comm,int _st,int _en, XString& er )
  {
      LDouble Result=0.0;
      while (IsNumber(comm.charAt(_st)) || ((comm.charAt(_st)=='-') && (IsNumber(comm.charAt(_st+1)))))
      {

          XString temp = ParseNumber(_st,_en,comm,er);
          if (er!="") break;
          Result = temp.toLongDouble();
          return (Result);

      }
      return Result;

  }








  //***************************************************************
  //           READ MATRIX DIMENSIONS
  //***************************************************************
  void ReadDimensions(XString& comm,int _st,int _en,int& _rows, int& _cols, XString& er )
  {
     if (comm.charAt(_st)!='<') {er="Syntax error!"; return; }

     int ir=1,ic=1;
     _rows = 0;
     _cols = 100000;       //< 1.2 , 2 , 3 ; 4 , 5.6 , 7 >

     for (int i=_st+1;i<_en;i++)
     {
         if  (comm.charAt(i)==',')
              {
                ic++;
                if (ic>_cols) {er="Wrong matrix dimensions!"; break;}
              }

         if  (comm.charAt(i)==';')
              {
               ir++;
               _cols = ic;
               ic=1;
              }


     }
     _rows = ir;
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

       RealMatrix Result = RealMatrix(_rows,_cols);

       int zR,zL=0,i=0;
       zL = _st+1;
       int ir = 0, ic = 0;

       for (i=zL;i<_en;)  //repeat to the end of matrix
          {

                  if (BracketRight(i,_en,comm,zR,er)!='n')  //search for matrix element
                  {
                          Result._el[ir][ic] = ReadNumber(comm,i,zR,er);
                          if (er!="") break;

                  }
                  else break;

                  i=zR+1;
                  if (comm.charAt(i)==',') { i++; ic++; }


                  if (comm.charAt(i)==';') //new row detected
                  {
                          ir++;
                          i++; ic=0;
                          if (i>=_en) {er="Unexpected end of matrix!"; break;}
                  } 

          }



       int index = varibles.Add(new RealMatrix(Result));
       comm = comm.remove(_st,_en);
       comm = comm.insert((XString)"#"+XString::fromInt(index),_st);

       if (TempRes) OnTempResult(" Value found: #"+XString::fromInt(index).ToAnsiString()+
                                       " = "+  Result.ToStr().ToAnsiString() +"\n");




     }

   }


  //***************************************************************
  //           READ ALL NUMBERS
  //***************************************************************
  void ReadNumbers(XString& comm,XString& er )
  {

     int i=0,zL,zR,_en;
     while (i<comm.length())
     {
       _en = comm.length()-1;
       if (comm.charAt(i)=='#')
        {
            if (BracketRight(i,_en,comm,zR,er)=='n') return;
            i = zR+1;
            continue;
        }

       if (IsNumber(comm.charAt(i)))
       {
            if (BracketRight(i,_en,comm,zR,er)=='n') return;
            LDouble Result = ReadNumber(comm,i,zR,er);
            comm = comm.remove(i,zR);
            XString tmp;
            int index = varibles.Add(new RealMatrix(Result));
            tmp = tmp.fromInt(index);
            tmp = (XString)"#"+tmp;
            comm = comm.insert(tmp,i);

            if (TempRes) OnTempResult(" Value found: #"+XString::fromInt(index).ToAnsiString()+
                                       " = "+  XString::fromLongDouble(Result).ToAnsiString() +"\n");


            i = i+tmp.length();
            continue;
        }

       i++;
       if (er!="") return;

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
  RealMatrix ParseCommand(XString& comm,XString& er, bool ShowTempRes, RealMatrix& lastResult)
  {
          TempRes = ShowTempRes;
          varibles = RealMatrixPArray();
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
             int index = varibles.Add(new RealMatrix(lastResult));
             comm = comm.removeFrom(k,1);
             comm = comm.insert((XString)"#"+XString::fromInt(index),k);

             if (TempRes) OnTempResult(" Value found: #"+XString::fromInt(index).ToAnsiString()+
                                       " = "+  lastResult.ToStr().ToAnsiString() +"\n");

         }


          RemovePluses(comm);
          ReadMatrices(comm,er);
          ReadNumbers(comm,er);
          if (er!="") return RealMatrix();
          RealMatrix Result;
          Result = IterateOperations(0,comm.length()-1 ,comm,er);
          return Result;
  }




  //***************************************************************
  //           ITERATE THROUGH COMMAND
  //***************************************************************
RealMatrix IterateOperations(int _st, int _en, XString comm,XString& er )
{
  RealMatrix Result;
  RealMatrix temp;
  RealMatrix templ;
  RealMatrix tempr;
  XString tmp;
  int i;
  int k;



  if (TempRes) OnTempResult("     Parsing: "+comm.subString(_st,_en).ToAnsiString()+"\n");







  //================================================================================
  //============================ ONE ARGUMENT FUNCTIONS ============================
  //================================================================================

  while  ( ((i=comm.indexOf("a",_st,_en-_st+1))!=-1) ||   // Absolute value
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
          ((i=comm.indexOf("p",_st,_en-_st+1))!=-1) ||   // Gauss partial
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


          if (i>=_en) {er="Syntax error!"; break; };

          int zakr=0;
          //
          //take the right hand argument if not find then rise error
          //
          if (BracketRight(i+1,_en,comm,zakr,er)=='n') {er="Syntax error!"; break; };

          tempr=IterateOperations(i+1,zakr,comm,er);
          if (er!="") break;


          switch (fname)
          {
          case 'a': tempr = tempr.rabs(er); break;
          case 'q': tempr = tempr.rsqrt(er); break;
          case 'x': tempr = tempr.rexp(er); break;
          case 'l': tempr = tempr.rlog(er); break;
          case 's': tempr = tempr.rsin(er); break;
          case 'c': tempr = tempr.rcos(er); break;
          case 't': tempr = tempr.rtan(er); break;
          case 'g': tempr = tempr.rctan(er); break;
          case 'i': tempr = tempr.Inverse(er); break;
          case 'n': tempr = tempr.Transpose(); break;
          case 'z': tempr = tempr.Determinant(er); break;
          case 'j': tempr = tempr.Cond(er); break;
          case 'k': tempr = tempr.Norm(); break;
          case 'u': tempr = tempr.Gauss(er); break;
          case 'p': tempr = tempr.GaussPart(er); break;
          case 'f': tempr = tempr.GaussFull(er,k); break;

          }
     if (er!="") break;

           int index = varibles.Add(new RealMatrix(tempr));
           comm = comm.remove(i,zakr);
           tmp = (XString)"#" + tmp.fromInt(index);
           comm = comm.insert(tmp,i);

           _en=_en - (zakr-i-tmp.length()+1);



          if (TempRes)
          {
                  AnsiString text = "#"+XString::fromInt(index).ToAnsiString()+
                                     " = "+tempr.ToStr().ToAnsiString()+"\n";
                  switch (fname)
                  {
                  case 'a': OnTempResult("         Abs: " + text); break;
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

  while (
        (((i=comm.indexOf("-(",_st,_en-_st+1))!=-1) && (i==_st)) ||
        (((i=comm.indexOf("-<",_st,_en-_st+1))!=-1) && (i==_st)) ||
        (((i=comm.indexOf("-(",_st,_en-_st+1))!=-1) && (comm.charAt(i-1)=='(')) ||
        (((i=comm.indexOf("-<",_st,_en-_st+1))!=-1) && (comm.charAt(i-1)=='(')) ||
        (((i=comm.indexOf("-#",_st,_en-_st+1))!=-1) && (i==_st)) ||
        (((i=comm.indexOf("-#",_st,_en-_st+1))!=-1) && (comm.charAt(i-1)=='('))
        )
  {

          if (TempRes) OnTempResult(" Unary minus: start\n");

          int  zR=0;    //range of argument                   
          if (BracketRight(i+1,_en,comm,zR,er)=='n') break;
				
          tempr=IterateOperations(i+1,zR,comm,er);
          if (er!="") break;

          temp = (-tempr);

          int index = varibles.Add(new RealMatrix(temp));
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

  while  (
          ((i=comm.indexOf("^",_st,_en-_st+1))!=-1) ||   // Power
          ((i=comm.indexOf("*",_st,_en-_st+1))!=-1) ||   // Multiplication
          ((i=comm.indexOf("/",_st,_en-_st+1))!=-1) ||   // Division
          ((i=comm.indexOf("h",_st,_en-_st+1))!=-1) ||   //Solve
          ((i=comm.indexOf("v",_st,_en-_st+1))!=-1) ||   //Solve part
          ((i=comm.indexOf("b",_st,_en-_st+1))!=-1) ||   //Solve full
          (
            ((i=comm.indexOf("-",_st,_en-_st+1))!=-1) &&              // Subtraction
             (i>_st) && (comm.charAt(i-1)!='e') && (comm.charAt(i-1)!='E') &&
             (comm.charAt(i-1)!='(') && (comm.charAt(i-1)!='<') && (comm.charAt(i-1)!=',') &&
             (comm.charAt(i-1)!=';')
          )     ||
      (((i=comm.indexOf("+",_st,_en-_st+1))!=-1) &&  // Addition
          (i>_st) && (comm.charAt(i-1)!='e') && (comm.charAt(i-1)!='E'))
          )
  {	 


          char fname = comm.charAt(i);   //the character representing corresponding function name

          if (TempRes)  //printing temporary result
          {
                  switch (fname)
                  {
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

          if ((i<=_st) || (i>=_en)) {er="Syntax error!"; break; }; //jesli brak czynnikow

          int zL=0, zR=0;  //start and end index of evaluated sequence


          //====================== parsing left side

          if (BracketLeft(_st,i-1,comm,zL,er)=='n') break;
          //====================== parsing right side
          if (BracketRight(i+1,_en,comm,zR,er)=='n') break;

          tempr=IterateOperations(i+1,zR,comm,er);
          if (er!="") break; //leave the while loop

          templ=IterateOperations(zL,i-1,comm,er);
          if (er!="") break; //leave the while loop


          //====================== evaluating functions
          switch (fname)
          {
          case '^': temp = templ.npoweri((int)tempr._el[0][0]); break;
          case '*': temp = (templ*tempr); break;
          case '/': temp = (templ/tempr); break;
          case '-': temp = (templ-tempr); break;
          case '+': temp = (templ+tempr); break;
          case 'h': temp = (templ.Solve(er,tempr)); break;
          case 'v': temp = (templ.SolvePart(er,tempr)); break;
          case 'b': temp = (templ.SolveFull(er,tempr)); break;
          }

          if (er!="") break; //leave the while loop

          int index = varibles.Add(new RealMatrix(temp));
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

   while ((comm.charAt(_st)=='[') && (comm.charAt(_en)==']'))
  {
          comm=comm.removeFrom(_st,1);
          _en=_en-1;
          comm=comm.removeFrom(_en,1);
          _en=_en-1;
  }



  //====================================================================
  //====================== NUMBER OR MATRIX ============================
  //====================================================================


  if (comm.charAt(_st)=='#') //if command is pure interval
  {
        XString indx = ParseNumber(_st+1,_en,comm,er);
        if (er!="") return Result;
        Result = *varibles.GetAt(indx.toInt());
        varibles.RemoveAt(indx.toInt());
  }



  if (er!="") return (RealMatrix());


  //====================================================================
  //====================================================================
  //====================================================================



  if (TempRes) OnTempResult(" Temp result: "+Result.ToStr().ToAnsiString()+"\n");



  return Result;//
}



};
