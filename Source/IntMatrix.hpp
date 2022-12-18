


class IntMatrix
{
private:
  void allocElem(int rows,int cols)
  {
          _el = new Interval*[rows];       //alokuj wiersze

          for(int i=0;i<rows;i++)
                  _el[i] = new Interval[cols];  //alokuj kolumny

  }

public:

  int RowCnt, ColCnt;                // row count and cols count

  Interval** _el;   //elements of matrix - array of pointers to Interval type

  IntMatrix()
  {
          RowCnt=1;
          ColCnt=1;
          allocElem(RowCnt,ColCnt);    //alloc memory
          _el[0][0] = Interval(0.0);   //set values
  }


  IntMatrix(int _rows,int _cols)
  {
          RowCnt=_rows;
          ColCnt=_cols;
          allocElem(RowCnt,ColCnt);
          for (int i=0;i<RowCnt;i++)
           for (int j=0;j<ColCnt;j++)
            _el[i][j] = Interval(0.0);
  }


  IntMatrix(Interval x)
  {

          ColCnt=1;
          RowCnt=1;
          allocElem(RowCnt,ColCnt);
          _el[0][0]=x;
  }



  XString ToStr()
  {
          //if this is one by one matrix
          if ((this->ColCnt==1) && (this->RowCnt==1)) return (this->_el[0][0].ToStr());

          XString tmp = "<";
          int i,j;

          for (i=0; i<=this->RowCnt-1; i++)
          {
                  for (j=0; j<=this->ColCnt-1; j++)
                  {
                          tmp+=_el[i][j].ToStr();
                  }
                  if (i<this->RowCnt-1) tmp+=";";
          }

          tmp+=">";
          return tmp;
  };



  //Returns an square unit matrix of dimension n
  IntMatrix UnitMatrix(const int& n)
  {
          IntMatrix* tmp = new IntMatrix(n,n);
          int i,j;
          for (i=0;i<n;i++)
                  for (j=0;j<n;j++)
                          if (i==j) tmp->_el[i][j]=Interval(1.0);
                          else tmp->_el[i][j]=Interval(0.0);
                          return (*tmp);
  }



  //==============================================================================================
  //=============== GAUSS ELIMINATION ============================================================
  //==============================================================================================

  IntMatrix GaussElim(XString& er,IntMatrix& b)
  {
          if (ColCnt!=RowCnt)
          {
                  er="GaussElimination: Matrix must be square!";
                  return (IntMatrix()); //if matrix is not square
          }



          int i,j,k;
          Interval mul;
          int n=RowCnt;

          if (b.ColCnt!=n)
          {
                  if (b.RowCnt==n) b=b.Transpose();
                  else
                  {
                     er="GaussFullElimination: Wrong dimension of b vector!";
                     return (IntMatrix());
                  }
          }


          //
          //iterate through diagonal
          //
          for (k=0;k<n-1;k++)   
          {

                  //
                  //evaluate the rest of elements 
                  //
                  for (i=k+1;i<n;i++)
                  {
                          if (this->_el[k][k].iszero())
                          {
                                  er="GaussElimination: Division by zero!";
                                  return (IntMatrix()); //if matrix is not square
                          }

                          mul=_el[i][k]/_el[k][k];
                          for (j=k;j<n;j++)
                          {
                            if (j==k) _el[i][j]=Interval(0.0);
                            else
                            _el[i][j]= _el[i][j] - mul*_el[k][j];
                          }

                          b._el[0][i]=b._el[0][i]-mul*b._el[0][k]; //also in b vector
                  }


          }//end for(k... loop


          //
          //the elements under diagonal must be '0'
          //
          //for (j=0;j<n-1;j++)
          //       for (i=j+1;i<n;i++)
          //               this->_el[i][j]=Interval();

          return (*this);
  }





  //==============================================================================================
  //=============== GAUSS ELIMINATION PARTIAL ====================================================
  //==============================================================================================
  //Solves linear equation system with matrix "this" and vector b
  //Selecting major element is performed in column.
  //Matrix must by square and b must be a row.
  IntMatrix GaussPartElim(XString& er,IntMatrix& b)
  {
          if (ColCnt!=RowCnt)
          {
                  er="GaussElimination: Matrix must be square!";
                  return (IntMatrix()); //if matrix is not square
          }



          int i,j,k,max;
          Interval mul;
          int n=RowCnt;

          if (b.ColCnt!=n)
          {
                  if (b.RowCnt==n) b=b.Transpose();
                  else
                  {
                     er="GaussFullElimination: Wrong dimension of b vector!";
                     return (IntMatrix());
                  }
          }


          //
          //iterate through diagonal
          //
          for (k=0;k<n-1;k++)   
          {
                  //
                  //find the biggest element in column k
                  //
                  max=k;
                  for (i=k;i<n;i++)
                  {
                          if ( this->_el[i][k].iabs()._s > this->_el[max][k].iabs()._s)
                          { max=i; }
                  }

                  //
                  //check whether the maximal element is zero
                  //if so that means the matrix contains zero column - determinant equals zero
                  //
                  if (this->_el[max][k]==0.0)
                  {
                          er="GaussElimination: Matrix is curiosly!";
                          return (IntMatrix()); 
                  }

                  //
                  //swap row k with row max
                  //
                  if (k!=max)
                  {
                          for (j=k;j<n;j++)
                          {
                                  mul=this->_el[k][j];
                                  this->_el[k][j]=this->_el[max][j];
                                  this->_el[max][j]=mul;
                          }

                          //
                          //swap elements in b vector
                          //
                          mul=b._el[0][k];
                          b._el[0][k]=b._el[0][max];
                          b._el[0][max]=mul;
                  }

                  //
                  //evaluate the rest of elements 
                  //
                  for (i=k+1;i<n;i++)
                  {
                          mul=_el[i][k]/_el[k][k];
                          for (j=k;j<n;j++)
                          {
                            if (j==k) _el[i][j]=Interval(0.0);
                            else
                            _el[i][j]= _el[i][j] - mul*_el[k][j];
                          }

                          b._el[0][i]=b._el[0][i]-mul*b._el[0][k]; //also in b vector
                  }


          }//end for(k... loop


          //
          //the elements under diagonal must be '0'
          //
          //for (j=0;j<n-1;j++)
          //        for (i=j+1;i<n;i++)
          //                this->_el[i][j]=Interval();

          return (*this);
  }

  //example
  //  <[0][2][-1][-2];[2][-2][4][-1];[1][1][1][1];[-2][1][-2][1]>gauss<[-7][6][10][-2]>






  //==============================================================================================
  //=============== GAUSS FULL ELIMINATION =======================================================
  //==============================================================================================
  //Full Gauss elimination where Rp is row permutation and Cp is column permutation
  IntMatrix GaussFullElim(XString& er,int& sign,IntMatrix& b,IntMatrix& Rp,IntMatrix& Cp)
  {
          if (ColCnt!=RowCnt)
          {
                  er="GaussFullElimination: Matrix must be square!";
                  return (IntMatrix()); //if matrix is not square
          }


          int n=RowCnt;

          if (b.ColCnt!=n)
          {
                  if (b.RowCnt==n) b=b.Transpose();
                  else
                  {
                     er="GaussFullElimination: Wrong dimension of b vector!";
                     return (IntMatrix());
                  }
          }

          int i,j,k,maxc,maxr;
          Interval mul;

          for (i=0;i<n;i++)
          {
                  Rp._el[0][i]=Interval(i);
                  Cp._el[0][i]=Interval(i);
          }

          //
          //iterate through diagonal
          //
          for (k=0;k<n-1;k++)   
          {
                  //
                  //find the biggest element in whole matrix
                  //
                  maxc=k;
                  maxr=k;
                  for (i=k;i<n;i++)
                          for (j=k;j<n;j++)
                          {
                                  if (_el[i][j].iabs()._s > _el[maxr][maxc].iabs()._s)
                                  { maxr=i; maxc=j; }
                          }

                          //
                          //check whether the maximal element is zero
                          //if so that means the matrix contains zero column - determinant equals zero
                          //
                          if (_el[maxr][maxc]==0.0)
                          {
                                  er="GaussFullElimination: Matrix is curiosity!";
                                  return (IntMatrix());
                          }

                          //
                          //swap row k with row maxr
                          //
                          if (k!=maxr)
                          {
                                  sign=-sign;    //change determinant sign
                                  for (j=k;j<n;j++)
                                  {
                                          mul=_el[k][j];
                                          _el[k][j]=_el[maxr][j];
                                          _el[maxr][j]=mul;
                                  }

                                  //
                                  //also swap the row permutation vector
                                  //
                                  mul=Rp._el[0][k];
                                  Rp._el[0][k]=Rp._el[0][maxr];
                                  Rp._el[0][maxr]=mul;


                                  //
                                  //swap elements in b vector
                                  //
                                  mul=b._el[0][k];
                                  b._el[0][k]=b._el[0][maxr];
                                  b._el[0][maxr]=mul;
                          }

                          //
                          //swap column k with column maxc
                          //
                          if (k!=maxc)
                          {
                                  sign=-sign;
                                  for (i=0;i<n;i++)
                                  {
                                          mul=this->_el[i][k];
                                          _el[i][k]=_el[i][maxc];
                                          _el[i][maxc]=mul;
                                  }

                                  //
                                  //also swap the col permutation vector
                                  //
                                  mul=Cp._el[0][k];
                                  Cp._el[0][k]=Cp._el[0][maxc];
                                  Cp._el[0][maxc]=mul;
                          }


                          //
                          //evaluate the rest of elements 
                          //
                          for (i=k+1;i<n;i++)
                          {

                              mul=_el[i][k]/_el[k][k];
                              for (j=k;j<n;j++)
                              {
                                if (j==k) _el[i][j]=Interval(0.0);
                                else
                                _el[i][j]= _el[i][j] - mul*_el[k][j];
                              }

                              b._el[0][i]=b._el[0][i]-mul*b._el[0][k]; //also in b vector
                          }


          }//end for(k... loop


          //
          //the elements under diagonal must be '0'
          //
          //for (j=0;j<n-1;j++)
          //        for (i=j+1;i<n;i++)
          //                _el[i][j]=Interval();


          return (*this);
  }


  //Methods for gauss elimination only
  IntMatrix Gauss(XString& er)
  {
     IntMatrix b;
     b = IntMatrix(this->RowCnt,1);
     return this->GaussElim(er,b);

  }

  IntMatrix GaussPart(XString& er)
  {
     IntMatrix b;
     b = IntMatrix(this->RowCnt,1);
     return this->GaussPartElim(er,b);
  }

  IntMatrix GaussFull(XString& er, int& sign)
  {
     IntMatrix b;
     IntMatrix RP;
     IntMatrix CP;
     RP  = IntMatrix(1,this->RowCnt);
     CP =  IntMatrix(1,this->RowCnt);
     b = IntMatrix(this->RowCnt,1);
     return this->GaussFullElim(er,sign,b,RP,CP);
  }



  //==============================================================================================
  //=========== SOLVE EQUATIONS SYSTEM ===========================================================
  //==============================================================================================

  //Solving linear equation system using Gauss elimination
  //method with in columns main element selection
  IntMatrix Solve(XString& er,IntMatrix& b)
  {
          *this=this->GaussElim(er,b);
          if (er!="") return (IntMatrix());

          int n = this->RowCnt;
          int i,j;
          Interval sum;

          for(i=n-1;i>=0;i--)
          {
                  sum=0.0;
                  for(j=i+1;j<n;j++)
                  {
                          sum=sum+this->_el[i][j]*b._el[0][j];
                  }
                  b._el[0][i]= (b._el[0][i]-sum)/this->_el[i][i];
          }

          b=b.Transpose();

          return(b);
  }

  //==============================================================================================
  //=========== SOLVE EQUATIONS SYSTEM ===========================================================
  //==============================================================================================

  //Solving linear equation system using Gauss elimination
  //method with in columns main element selection
  IntMatrix SolvePart(XString& er,IntMatrix& b)
  {
          *this=this->GaussPartElim(er,b);
          if (er!="") return (IntMatrix());

          int n = this->RowCnt;
          int i,j;
          Interval sum;

          for(i=n-1;i>=0;i--)
          {
                  sum=0.0;
                  for(j=i+1;j<n;j++)
                  {
                          sum=sum+this->_el[i][j]*b._el[0][j];
                  }
                  b._el[0][i]= (b._el[0][i]-sum)/this->_el[i][i];
          }

          b=b.Transpose();

          return(b);
  }


  //Solving linear equation system using Gauss elimination 
  //method with full main element selection
  IntMatrix SolveFull(XString& er,IntMatrix& b)
  {
          int n = RowCnt;

          IntMatrix RP;
          IntMatrix CP;
          RP  = IntMatrix(1,n);
          CP =  IntMatrix(1,n);


          int znak;
          *this=this->GaussFullElim(er,znak,b,RP,CP);
          if (er!="") return (IntMatrix());


          int i,j;
          Interval sum;

          for(i=n-1;i>=0;i--)
          {
                  sum= Interval(0.0);
                  for(j=i+1;j<n;j++)
                  {
                          sum=sum+_el[i][j]*b._el[0][j];
                  }
                  b._el[0][i]= (b._el[0][i]-sum)/_el[i][i];
          }

          IntMatrix tmp;
          tmp=b;
          for (i=0;i<n;i++)
          {
                  tmp._el[0][(int)(CP._el[0][i]._i)]=b._el[0][i];
          }
          tmp=tmp.Transpose();

          return(tmp);
  }
  //example
  // <[0][2][-1][-2];[2][-2][4][-1];[1][1][1][1];[-2][1][-2][1]>solvef<[-7][6][10][-2]>


  //==============================================================================================
  //=============== INVERSE MATRIX ===============================================================
  //==============================================================================================

  //Computes an inverse matrix using Gauss algorithm
  // in form [A|I] to get [I|R] where R is a reversion of A
  IntMatrix Inverse(XString& er)
  {

    if (this->IsInterval()) return (Interval(1.0)/(this->_el[0][0]));

    if (ColCnt!=RowCnt)
    {
            er="Inverse: Matrix must be square!";
            return (IntMatrix()); //if matrix is not square
    }

    IntMatrix tmp = *this;

    if (tmp.Determinant(er).iszero())
    {
            er="Inverse: Determinant equal zero, inverse matrix does not exist!";
            return (IntMatrix()); //if matrix is not square
    }

    int i,j,k,max;
    Interval mul;
    int n;
    n=RowCnt;
    IntMatrix I=UnitMatrix(n);

    //
    //iterate through diagonal
    //
    for (k=0;k<n;k++)
    {

          //
          //find the biggest element in column k
          //
          max=k;
          for (i=k;i<n;i++)
          {
                  if ( this->_el[i][k].iabs()._s > this->_el[max][k].iabs()._s)
                  { max=i; }
          }


          //
          //swap row k with row max
          //
          if (k!=max)
                  for (j=k;j<n;j++)
                  {
                          mul=this->_el[k][j];
                          this->_el[k][j]=this->_el[max][j];
                          this->_el[max][j]=mul;
                          mul=I._el[k][j];
                          I._el[k][j]=I._el[max][j];
                          I._el[max][j]=mul;
                  }



                  //
                  //divide whole row by A[k,k]
                  //
                  mul=this->_el[k][k]; 
                  for (j=0;j<n;j++) 
                  {
                      if (j>k) this->_el[k][j]=this->_el[k][j]/mul;
                      I._el[k][j]= I._el[k][j]/mul;
                  }
                  this->_el[k][k]=Interval(1.0);

                  //
                  //compute elements under diagonal          //k                 |
                  //                                         //   k              |
                                                             //      k           |
                  for (i=k+1;i<n;i++)                        //    [i,k]k        |
                  {                                          //            k     |
                    mul = this->_el[i][k];                   //               k  |
                    for (j=0;j<n;j++)
                    {
                      if (j>k) _el[i][j] = _el[i][j] - (mul*_el[k][j]);
                      I._el[i][j]= I._el[i][j] - (mul*I._el[k][j]);
                    }

                  }


          }//end for(k... loop


    //
    //compute elements over diagonal
    //
    for (k=n-1;k>=0;k--)
            for (i=k-1;i>=0;i--)
            {
                    mul = this->_el[i][k];
                    for (j=0;j<n;j++)
                    {
                            I._el[i][j]= I._el[i][j] - (mul*I._el[k][j]);
                    }
            }

            return (I);
  }//inv<[7][4];[3][2]>
  //inv<[2][3][4][1][2];[-1][2][0][2][3];[2][3][4][1][0];[2][3][1][4][8];[3][2][4][-1][-2]>



  //==============================================================================================
  //=============== DETERMINANT ==================================================================
  //==============================================================================================
  Interval Determinant(XString& er)
  {
          if (this->ColCnt!=this->RowCnt) {er="Determinant: Matrix must by square!"; return(Interval());}
          int n = this->RowCnt;

          if (n==1) return(_el[0][0]);
          if (n==2) return(_el[0][0]*_el[1][1]-_el[1][0]*_el[0][1]);
          if (n==3) return(_el[0][0]*_el[1][1]*_el[2][2]+
                  _el[0][1]*_el[1][2]*_el[2][0]+
                  _el[0][2]*_el[1][0]*_el[2][1]-
                  _el[2][0]*_el[1][1]*_el[0][2]-
                  _el[2][1]*_el[1][2]*_el[0][0]-
                  _el[2][2]*_el[1][0]*_el[0][1]);


          int znak=1;



          *this=GaussFull(er,znak);


          if (er!="")
                  if (er=="GaussElimination: Matrix is curiosity!")
                  {
                          er=(XString)"";
                          return (Interval(0.0));
                  }
                  else
                          return (Interval(0.0));

          int i;
          Interval det=Interval(1.0);

          for (i=0;i<this->RowCnt;i++)
                  det=det*this->_el[i][i];

          det*=znak;

          return (det);
  }



  //==============================================================================================
  //================ TRANSPOSE ===================================================================
  //==============================================================================================
  IntMatrix Transpose()
  {

          if (this->IsInterval()) return(*this);

          IntMatrix tmp = IntMatrix(this->ColCnt,this->RowCnt);
          int i,j;
          for (i=0;i<tmp.RowCnt;i++)
                  for (j=0;j<tmp.ColCnt;j++)
                          tmp._el[i][j]=this->_el[j][i];

          return (tmp);

  }



  //==============================================================================================
  //================ NORM ===================================================================
  //==============================================================================================
  Interval Norm()
  {

          if (this->IsInterval()) return(this->_el[0][0]);

          XString er;
          int i,j;
          Interval sum = Interval(0.0);
          Interval maxSum = Interval(0.0);
          for (i=0;i<RowCnt;i++)
          {
                  sum = Interval(0.0);
                  for (j=0;j<ColCnt;j++)
                          sum = sum + _el[i][j].iabs();
                  if (sum._s>maxSum._s) maxSum = sum;
          }

          return (maxSum);

  }


   //==============================================================================================
  //================ NORM ===================================================================
  //==============================================================================================
  Interval Cond(XString er)
  {

          if (this->IsInterval()) return(this->_el[0][0]);

          return (this->Norm()* this->Inverse(er).Norm());

  }

  //==============================================================================================
  //================== ISZERO ====================================================================
  //==============================================================================================
  bool iszero()
  {
          int i,j;
          for (i=0; i<=this->RowCnt-1; i++)
          {
                  for (j=0; j<=this->ColCnt-1; j++)
                  {
                          if (this->_el[i][j].iszero()) return (true);
                  }
          }

          return (false);
  }


  //==============================================================================================
  //================== ISINTERVAL ================================================================
  //==============================================================================================
  bool IsInterval()
  {
          return	( ((this->RowCnt==1) && (this->ColCnt==1)) ? true : false );	
  }

  //==============================================================================================
  //================== ISVECTOR ==================================================================
  //==============================================================================================
  bool IsVector()
  {
          return	( (this->RowCnt==1)  ? true : false );
  }


  //==============================================================================================
  //================== ISCOLUMN ==================================================================
  //==============================================================================================
  bool IsColumn()
  {
          return	( ((this->ColCnt==1) && (this->RowCnt>1))  ? true : false );
  }


  //==============================================================================================
  //================== EMPTY =====================================================================
  //==============================================================================================
  //if contains at least one empty element
  bool empty()
  {

          int i,j;

          for (i=0; i<=this->RowCnt-1; i++)
          {
                  for (j=0; j<=this->ColCnt-1; j++)
                  {
                          if (this->_el[i][j].empty()) return (true);
                  }
          }

          return (false);

  }


  /*ELEMENT WISE FUNCTION*/
  IntMatrix FunElem(int par,XString& er)
  {
          IntMatrix tmp = IntMatrix(this->RowCnt,this->ColCnt);
          int i,j;

          for (i=0; i<=this->RowCnt-1; i++)
          {
                  for (j=0; j<=this->ColCnt-1; j++)
                  {
                          switch (par)
                          {
                          case (1): tmp._el[i][j]=this->_el[i][j].iabs(); break;
                          case (2): tmp._el[i][j]=this->_el[i][j].szerokosc(); break;
                          case (3): tmp._el[i][j]=this->_el[i][j].promien(); break;
                          case (4): tmp._el[i][j]=this->_el[i][j].srodek(); break;
                          case (5): tmp._el[i][j]=this->_el[i][j].isin(); break;
                          case (6): tmp._el[i][j]=this->_el[i][j].icos(); break;
                          case (7): tmp._el[i][j]=this->_el[i][j].itan(); break;
                          case (8): tmp._el[i][j]=this->_el[i][j].ictan(); break;
                          case (9): tmp._el[i][j]=this->_el[i][j].ilog(); break;
                          case (10): tmp._el[i][j]=this->_el[i][j].sqrti(er); break;
                          case (11): tmp._el[i][j]=this->_el[i][j].expi(); break;
                          }
                  }
          }
          return (tmp);

  }


  /*SZEROKOSC PRZEDZIALU*/
  IntMatrix szerokosc(XString& er)    
  { 
          return (this->FunElem(2,er)); 
  }; 

  /*PROMIEN PRZEDZIALU*/
  IntMatrix promien(XString& er)      
  { 
          return (this->FunElem(3,er)); 
  };    

  /*SRODEK PRZEDZIALU*/
  IntMatrix srodek(XString& er)       
  {
          return (this->FunElem(4,er)); 
  };


  //==============================================================================================
  //================== WIDTH =====================================================================
  //==============================================================================================

  static IntMatrix odleglosc(IntMatrix x, IntMatrix y)
  {

          if ((x.RowCnt!=y.RowCnt) || (x.ColCnt!=y.ColCnt)) return (IntMatrix());

          IntMatrix tmp = IntMatrix(x.RowCnt,x.ColCnt);
          int i,j;

          for (i=0; i<=x.RowCnt-1; i++)
          {
                  for (j=0; j<=x.ColCnt-1; j++)
                  {
                          tmp._el[i][j]=Interval::odleglosc(x._el[i][j],y._el[i][j]);
                  }
          }
          return (tmp);
  }


  //ABS Z PRZEDZIALU
  IntMatrix iabs(XString& er)         
  { 
          return this->FunElem(1,er); 
  };

  //TRYGONOMETRYCZNE
  IntMatrix isin(XString& er)         
  { return (this->FunElem(5,er)); 
  };

  IntMatrix icos(XString& er)         
  { 
          return (this->FunElem(6,er)); 
  };

  IntMatrix itan(XString& er)         
  { 
          return (this->FunElem(7,er)); 
  };

  IntMatrix ictan(XString& er)        
  { 
          return (this->FunElem(8,er)); 
  };

  IntMatrix ilog(XString& er)         
  { 
          return (this->FunElem(9,er)); 
  };

  IntMatrix sqrti(XString& er)       
  { 
          return (this->FunElem(10,er)); 
  };

  IntMatrix expi(XString& er)         
  { 
          return (this->FunElem(11,er)); 
  };


  //==============================================================================================
  //================ NPOWERI =====================================================================
  //==============================================================================================

  static IntMatrix npoweri(IntMatrix x, int n)
  {
          IntMatrix tmp = IntMatrix(x.RowCnt,x.ColCnt);
          int i,j;

          for (i=0; i<=x.RowCnt-1; i++)
          {
                  for (j=0; j<=x.ColCnt-1; j++)
                  {
                          tmp._el[i][j]=Interval::npoweri(x._el[i][j],n);
                  }
          }
          return (tmp);
  }

  //==============================================================================================
  //================ OPERATOR = ==================================================================
  //==============================================================================================

  IntMatrix operator =(IntMatrix y)
  {
          this->RowCnt = y.RowCnt;
          this->ColCnt = y.ColCnt;
          allocElem(y.RowCnt,y.ColCnt);
          int i,j;

          for (i=0; i<=y.RowCnt-1; i++)
          {
                  for (j=0; j<=y.ColCnt-1; j++)
                  {
                          this->_el[i][j]=y._el[i][j];
                  }
          }
          return (*this);
  }


  IntMatrix operator =(Interval y)
  {
          this->RowCnt = 1;
          this->ColCnt = 1;
          allocElem(1,1);
          this->_el[0][0]=y;
          return (*this);
  }


  //==============================================================================================
  //============ LOGICAL OPERATORS ===============================================================
  //==============================================================================================


  bool operator ==(IntMatrix& y)
  {
          if ((this->RowCnt!=y.RowCnt) || (this->ColCnt!=y.ColCnt)) return (false);

          int i,j;

          for (i=0; i<=y.RowCnt-1; i++)
          {
                  for (j=0; j<=y.ColCnt-1; j++)
                  {
                          if (this->_el[i][j]!=y._el[i][j]) return (false);
                  }
          }
          return (true);
  }

  bool operator !=(IntMatrix y)
  {
          if ((this->RowCnt!=y.RowCnt) || (this->ColCnt!=y.ColCnt)) return (true);

          int i,j;

          for (i=0; i<=y.RowCnt-1; i++)
          {
                  for (j=0; j<=y.ColCnt-1; j++)
                  {
                          if (this->_el[i][j]!=y._el[i][j]) return (true);
                  }
          }
          return (false);
  }



  //==============================================================================================
  //================ OPERATOR + ==================================================================
  //==============================================================================================

  IntMatrix operator+(IntMatrix y)
  {
          if (y.IsInterval()) return (*this + y._el[0][0]); //if y is interval
          if (((this->RowCnt)!=y.RowCnt) || ((this->ColCnt)!=y.ColCnt)) //if matrices dimensions not match
          { return(*this); };

          IntMatrix* tmp = new IntMatrix(this->RowCnt,this->ColCnt);
          int j;


          for (int i=0;i<=this->RowCnt-1; i++ )
          {
                  for (j=0;j<=this->ColCnt-1; j++ )
                          tmp->_el[i][j]=this->_el[i][j]+y._el[i][j];
          }
          return (*tmp);
  }



  IntMatrix operator+(Interval y)
  {

          IntMatrix* tmp = new IntMatrix(this->RowCnt,this->ColCnt);
          int j;


          for (int i=0;i<=this->RowCnt-1; i++ )
          {
                  for (j=0;j<=this->ColCnt-1; j++ )
                          tmp->_el[i][j]=this->_el[i][j]+y;
          }
          return (*tmp);
  }


  IntMatrix operator+ ()
  {
          return (*this); 
  };

  //==============================================================================================
  //================ OPERATOR - ==================================================================
  //==============================================================================================


  IntMatrix operator-()
  {

          int j;
          for (int i=0;i<=RowCnt-1; i++ )
          {
                  for (j=0;j<=ColCnt-1; j++ )
                          _el[i][j]=-(_el[i][j]);
          }

          return (*this);
  }



  IntMatrix operator-(IntMatrix y)
  {
          if (y.IsInterval()) return (*this - y._el[0][0]); //if y is interval
          if (((this->RowCnt)!=y.RowCnt) || ((this->ColCnt)!=y.ColCnt)) //if matrices dimensions not match
          { return(*this); };


          IntMatrix* tmp = new IntMatrix(this->RowCnt,this->ColCnt);

          int j;
          for (int i=0;i<=this->RowCnt-1; i++ )
          {
                  for (j=0;j<=this->ColCnt-1; j++ )
                          tmp->_el[i][j]=this->_el[i][j]-y._el[i][j];
          }

          return (*tmp);
  }



  IntMatrix operator-(Interval y)
  {

          IntMatrix* tmp = new IntMatrix(this->RowCnt,this->ColCnt);;
          int j;


          for (int i=0;i<=this->RowCnt-1; i++ )
          {
                  for (j=0;j<=this->ColCnt-1; j++ )
                          tmp->_el[i][j]=this->_el[i][j]-y;
          }
          return (*tmp);
  }


  //==============================================================================================
  //================ OPERATOR * ==================================================================
  //==============================================================================================

  IntMatrix operator*(IntMatrix y)
  {
          if (y.IsInterval()) return (*this * y._el[0][0]); //if y is interval
          if (this->ColCnt!=y.RowCnt) { return (*this); }
          IntMatrix* tmp = new IntMatrix(RowCnt,y.ColCnt);

          int j,i,k;

          for (i=0;i<tmp->RowCnt;i++)
                  for (j=0;j<tmp->ColCnt;j++)
                  {
                          tmp->_el[i][j]=0.0;
                          for (k=0;k<y.RowCnt;k++)
                                  tmp->_el[i][j]=tmp->_el[i][j]+_el[i][k]*y._el[k][j];
                  }
                  return (*tmp);
  }



  IntMatrix operator*(Interval y)
  {
          int j;
          IntMatrix* tmp = new IntMatrix(RowCnt,ColCnt);
          for (int i=0;i<RowCnt; i++ )
          {
                  for (j=0;j<ColCnt; j++ )
                          tmp->_el[i][j]=_el[i][j]*y;
          }

          return (*tmp);
  }




  //==============================================================================================
  //================ OPERATOR / ==================================================================
  //==============================================================================================

  //Right side division matrix by matrix
  IntMatrix operator/(IntMatrix y)
  {
          if (y.IsInterval()) return (*this / y._el[0][0]); //if y is interval

          XString er;
          *this=y.Inverse(er)*(*this);
          return (*this);
  }



  //Division every element of matrix by interval
  IntMatrix operator/(Interval y)
  {
          int j;
          IntMatrix* tmp = new IntMatrix(this->RowCnt,this->ColCnt);
          for (int i=0;i<RowCnt; i++ )
          {
                  for (j=0;j<ColCnt; j++ )
                          tmp->_el[i][j]=_el[i][j]/y;
          }

          return (*tmp);
  }

  IntMatrix operator+= ( IntMatrix y)
  { 
          *this = *this + y; 
          return(*this); 
  };
  IntMatrix operator-= ( IntMatrix y)
  { 
          *this = *this - y; 
          return(*this); 
  };
  IntMatrix operator*= ( IntMatrix y)
  {
          *this = *this * y;
          return(*this);
  };
  IntMatrix operator/= ( IntMatrix y)
  {
          *this = *this / y;
          return(*this);
  };
  IntMatrix operator+= ( Interval y)
  {
          *this = *this + y;
          return(*this);
  };
  IntMatrix operator-= ( Interval y)
  {
          *this = *this - y;
          return(*this);
  };
  IntMatrix operator*= ( Interval y)
  { 
          *this = *this * y;
          return(*this); 
  };
  IntMatrix operator/= ( Interval y)
  { 
          *this = *this / y; 
          return(*this);
  };

};