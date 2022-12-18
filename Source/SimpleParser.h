






class SimpleParser
{
 public:

  SimpleParser(void)
  {
          index = 0;
  }
                                         //wskazniki do IntMatrixow
  LDouble *varibles[100];              //tablica zmiennych uzywanych
  int index;                             //do obliczen, w biezacym
                                         //poleceniu zapisywane jako
                                         // #i   gdzie i jest indeksem
                                         // w tablicy varibles




  

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
            tmp = tmp.fromInt(index);
            tmp = (XString)"#"+tmp;
            comm = comm.insert(tmp,i);
            varibles[index] = new LDouble(Result);

            index++;
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
  LDouble ParseCommand(XString& comm,XString& er )
  {
          index = 0;

          RemovePluses(comm);
          ReadNumbers(comm,er);
          if (er!="") return LDouble();
          LDouble Result;
          Result = IterateOperations(0,comm.length()-1 ,comm,er);
          return Result;
  }




  //***************************************************************
  //           ITERATE THROUGH COMMAND
  //***************************************************************
LDouble IterateOperations(int _st, int _en, XString comm,XString& er )
{
  LDouble Result;
  LDouble temp;
  LDouble templ;
  LDouble tempr;
  XString tmp;
  int i;
  int k;



  while  ( ((i=comm.indexOf("!",_st,_en-_st+1))!=-1)   //SILNIA
          )
  {

          int zL=0;  //start and end index of evaluated sequence

          //====================== parsing left side
          if (BracketLeft(_st,i-1,comm,zL,er)=='n') break;

          templ=IterateOperations(zL,i-1,comm,er);
          if (er!="") break; //leave the while loop

          temp =(long double)silnia((__int64)templ);



           comm = comm.remove(zL,i);
           tmp = (XString)"#" + tmp.fromInt(index);
           comm = comm.insert(tmp,zL);
           varibles[index] = new LDouble(temp);
           index++;
           _en=_en - (i-zL-tmp.length()+1);

  }


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
          ((i=comm.indexOf("g",_st,_en-_st+1))!=-1)      // Cotangens
          )
  {

          wchar_t fname = comm.charAt(i);   //the character representing corresponding function name

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
          case 'a': tempr = fabs(tempr); break;
          case 'q': tempr = sqrtl(tempr); break;
          case 'x': tempr = expl(tempr); break;
          case 'l': tempr = logl(tempr); break;
          case 's': tempr = sinl(tempr); break;
          case 'c': tempr = cosl(tempr); break;
          case 't': tempr = tanl(tempr); break;
          case 'g': tempr = 1.0/tanl(tempr); break;

          }
     if (er!="") break;


           comm = comm.remove(i,zakr);
           tmp = (XString)"#" + tmp.fromInt(index);
           comm = comm.insert(tmp,i);
           varibles[index] = new LDouble(tempr);
           index++;
           _en=_en - (zakr-i-tmp.length()+1);





  }
  if (er!="") return (Result);




  //====================================================================
  //============================ UNARY MINUS ===========================
  //====================================================================

  while (
        (((i=comm.indexOf("-(",_st,_en-_st+1))!=-1) && (i==_st)) ||
        (((i=comm.indexOf("-(",_st,_en-_st+1))!=-1) && (comm.charAt(i-1)=='(')) ||
        (((i=comm.indexOf("-#",_st,_en-_st+1))!=-1) && (i==_st)) ||
        (((i=comm.indexOf("-#",_st,_en-_st+1))!=-1) && (comm.charAt(i-1)=='('))
        )
  {



          int  zR=0;    //range of argument
          if (BracketRight(i+1,_en,comm,zR,er)=='n') break;
				
          tempr=IterateOperations(i+1,zR,comm,er);
          if (er!="") break;

          temp = (-tempr);
          comm = comm.remove(i,zR);
          tmp = (XString)"#" + tmp.fromInt(index);
          comm = comm.insert(tmp,i);
          varibles[index] = new LDouble(temp);
          index++;
          _en=_en - (zR-i-tmp.length()+1);

  }
  if (er!="") return (Result);







  //============================================================================
  //====================== TWO ARGUMENTS FUNCTIONS =============================
  //============================================================================

  while  (
          ((i=comm.indexOf("^",_st,_en-_st+1))!=-1) ||   // Power
          ((i=comm.indexOf("*",_st,_en-_st+1))!=-1) ||   // Multiplication
          ((i=comm.indexOf("/",_st,_en-_st+1))!=-1) ||   // Division
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


          wchar_t fname = comm.charAt(i);   //the character representing corresponding function name

          if ((i<=_st) || (i>=_en)) {er="Syntax error!"; break; }; //jesli brak czynnikow

          int zL=0, zR=0;  //start and end index of evaluated sequence


          //====================== parsing left side
          if (BracketLeft(_st,i-1,comm,zL,er)=='n') break;

          templ=IterateOperations(zL,i-1,comm,er);
          if (er!="") break; //leave the while loop



          //====================== parsing right side
          if (BracketRight(i+1,_en,comm,zR,er)=='n') break;

          tempr=IterateOperations(i+1,zR,comm,er);
          if (er!="") break; //leave the while loop


          //====================== evaluating functions
          switch (fname)
          {
          case '^': temp = adon(templ,(int)tempr); break;
          case '*': temp = (templ*tempr); break;
          case '/': temp = (templ/tempr); break;
          case '-': temp = (templ-tempr); break;
          case '+': temp = (templ+tempr); break;

          }

          if (er!="") break; //leave the while loop

          comm = comm.remove(zL,zR);
          tmp = (XString)"#" + tmp.fromInt(index);
          comm = comm.insert(tmp,zL);
          varibles[index] = new LDouble(temp);
          index++;
          _en=_en - (zR-zL-tmp.length()+1);



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
        Result = *varibles[indx.toInt()];
  }



  if (er!="") return (LDouble());


  //====================================================================
  //====================================================================
  //====================================================================


  return Result;//
}



};