
class RealMatrix
{

private:
  void allocElem(int rows,int cols)
  {
          _el = new LDouble*[rows];       //alokuj wiersze

          for(int i=0;i<rows;i++)
                  _el[i] = new LDouble[cols];  //alokuj kolumny

  }

public:


  int RowCnt, ColCnt;                // row count and cols count

  LDouble **_el;   //elements of matrix

  RealMatrix()
  {	
          RowCnt=1;
          ColCnt=1;
          allocElem(RowCnt,ColCnt);
          _el[0][0] = 0.0;
  }



  RealMatrix(LDouble x)
  {

          ColCnt=1;
          RowCnt=1;
          allocElem(1,1);
          _el[0][0]=x;
  }




  RealMatrix(int _rows,int _cols)
  {
          RowCnt=_rows;
          ColCnt=_cols;
          allocElem(RowCnt,ColCnt);
          for (int i=0;i<RowCnt;i++)
           for (int j=0;j<ColCnt;j++)
            _el[i][j] = 0.0;
  }



  XString ToStr(AnsiString format = "0.0000000000000000000")
  {
          //if this is one by one matrix
          if (this->IsNumber())
          {
                  XString tmp = XString::fromLongDouble(this->_el[0][0],format);
                  tmp = tmp.replaceAll(",",".");
                  return tmp;
          }

          XString tmp = "<";
          int i,j;

          for (i=0; i<=this->RowCnt-1; i++)
          {
                  for (j=0; j<=this->ColCnt-1; j++)
                  {
                          tmp+=XString::fromLongDouble(_el[i][j],format).replaceAll(",",".");
                          if (j<this->ColCnt-1) tmp+=",";
                  }
                  if (i<this->RowCnt-1) tmp+=";";
          }

          tmp+=">";
          return tmp;
  };



  //Returns an square unit matrix of dimension n
  RealMatrix UnitMatrix(int n)
  {
          RealMatrix tmp = RealMatrix(n,n);
          int i,j;
          for (i=0;i<n;i++)
                  for (j=0;j<n;j++)
                          if (i==j) tmp._el[i][j]=1.0;
                          else tmp._el[i][j]=0.0;

          return (tmp);

  }





  //==============================================================================================
  //=============== GAUSS ELIMINATION ============================================================
  //==============================================================================================
  //Solves linear equation system with matrix "this" and vector b
  //Major element selection is not performed.
  //Matrix must by square and b must be a row.
  RealMatrix GaussElim(XString& er,RealMatrix& b)
  {
    if (ColCnt!=RowCnt)
    {
            er="GaussElimination: Matrix must be square!";
            return (RealMatrix()); //if matrix is not square
    }


    int i,j,k;
    LDouble mul;
    int n=RowCnt;

    if (b.ColCnt!=n)
    {
            if (b.RowCnt==n) b=b.Transpose();
            else
                  {
                     er="GaussFullElimination: Wrong dimension of b vector!";
                     return (RealMatrix());
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

          if (this->_el[k][k]==0.0)
          {
                  er="GaussElimination: Division by zero";
                  return (RealMatrix()); //if matrix is not square
          }
          mul=_el[i][k]/_el[k][k];
          for (j=k;j<n;j++)
          {
            if (j==k) _el[i][j]=0.0;
            else
            _el[i][j]= _el[i][j] - mul*_el[k][j];
          }

          b._el[0][i]=b._el[0][i]-mul*b._el[0][k]; //also in b vector
      }


    }//end for(k... loop


    //
    //the elements under diagonal must be '0'
    //
    for (j=0;j<n-1;j++)
            for (i=j+1;i<n;i++)
                    this->_el[i][j]=0.0;

    return (*this);
  }







  //==============================================================================================
  //=============== GAUSS ELIMINATION PARTIAL ====================================================
  //==============================================================================================
  //Solves linear equation system with matrix "this" and vector b
  //Selecting major element is performed in column.
  //Matrix must by square and b must be a row.
  RealMatrix GaussPartElim(XString& er,RealMatrix& b)
  {
          if (ColCnt!=RowCnt)
          {
                  er="GaussElimination: Matrix must be square!";
                  return (RealMatrix()); //if matrix is not square
          }



          int i,j,k,max;
          LDouble mul;
          int n=RowCnt;

          if (b.ColCnt!=n)
          {
                  if (b.RowCnt==n) b=b.Transpose();
                  else
                  {
                     er="GaussFullElimination: Wrong dimension of b vector!";
                     return (RealMatrix());
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
                          if ( fabs(this->_el[i][k]) > fabs(this->_el[max][k]))
                          { max=i; }
                  }

                  //
                  //check whether the maximal element is zero
                  //if so that means the matrix contains zero column - determinant equals zero
                  //
                  if (this->_el[max][k]==0.0)
                  {
                          er="GaussElimination: Matrix is curiosity!";
                          return (RealMatrix()); 
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
                            if (j==k) _el[i][j]=0.0;
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
          //                this->_el[i][j]=0.0;

          return (*this);
  }


  //example
  //  <[0][2][-1][-2];[2][-2][4][-1];[1][1][1][1];[-2][1][-2][1]>gauss<[-7][6][10][-2]>



  //==============================================================================================
  //=============== GAUSS FULL ELIMINATION =======================================================
  //==============================================================================================
  //Full Gauss elimination where Rp is row permutation and Cp is column permutation
  RealMatrix GaussFullElim(XString& er,int& sign,RealMatrix& b,RealMatrix& Rp,RealMatrix& Cp)
  {
          if (ColCnt!=RowCnt)
          {
                  er="GaussFullElimination: Matrix must be square!";
                  return (RealMatrix()); //if matrix is not square
          }


          int n=RowCnt;

          if (b.ColCnt!=n)
          {
                  if (b.RowCnt==n) b=b.Transpose();
                  else
                  {
                     er="GaussFullElimination: Wrong dimension of b vector!";
                     return (RealMatrix());
                  }
          }

          int i,j,k,maxc,maxr;
          LDouble mul;

          for (i=0;i<n;i++)
          {
                  Rp._el[0][i]=(LDouble)i;
                  Cp._el[0][i]=(LDouble)i;
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
                                  if ( fabs(this->_el[i][j]) > fabs(this->_el[maxr][maxc]))
                                  { maxr=i; maxc=j; }
                          }

                          //
                          //check whether the maximal element is zero
                          //if so that means the matrix contains zero column - determinant equals zero
                          //
                          if (this->_el[maxr][maxc]==0.0)
                          {
                                  er="GaussFullElimination: Matrix is curiosity!";
                                  return (RealMatrix()); 
                          }

                          //
                          //swap row k with row maxr
                          //
                          if (k!=maxr)
                          {
                                  sign=-sign;    //change determinant sign
                                  for (j=k;j<n;j++)
                                  {
                                          mul=this->_el[k][j];
                                          this->_el[k][j]=this->_el[maxr][j];
                                          this->_el[maxr][j]=mul;
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
                                          this->_el[i][k]=this->_el[i][maxc];
                                          this->_el[i][maxc]=mul;
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
                                if (j==k) _el[i][j]=0.0;
                                else
                                _el[i][j]= _el[i][j] - mul*_el[k][j];
                              }

                              b._el[0][i]=b._el[0][i]-mul*b._el[0][k]; //also in b vector
                          }


          }//end for(k... loop


          //
          //the elements under diagonal must be '0'
          //
          for (j=0;j<n-1;j++)
                  for (i=j+1;i<n;i++)
                          this->_el[i][j]=0.0;


          return (*this);
  }



  
  //Methods for gauss elimination only
  RealMatrix Gauss(XString& er)
  {
     RealMatrix b;
     b = RealMatrix(this->RowCnt,1);
     return this->GaussElim(er,b);

  }

  RealMatrix GaussPart(XString& er)
  {
     RealMatrix b;
     b = RealMatrix(this->RowCnt,1);
     return this->GaussPartElim(er,b);
  }

  RealMatrix GaussFull(XString& er, int& sign)
  {
     RealMatrix b;
     RealMatrix RP;
     RealMatrix CP;
     RP  = RealMatrix(1,this->RowCnt);
     CP =  RealMatrix(1,this->RowCnt);
     b = RealMatrix(this->RowCnt,1);
     return this->GaussFullElim(er,sign,b,RP,CP);
  }




  //==============================================================================================
  //=========== SOLVE EQUATIONS SYSTEM ===========================================================
  //==============================================================================================

  //Solving linear equation system using Gauss elimination
  //method with in columns main element selection
  RealMatrix Solve(XString& er,RealMatrix& b)
  {
          *this=this->GaussElim(er,b);
          if (er!="") return (RealMatrix());

          int n = this->RowCnt;
          int i,j;
          LDouble sum;

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
  //method with in columns main element selection
  RealMatrix SolvePart(XString& er,RealMatrix& b)
  {
          *this=this->GaussPartElim(er,b);
          if (er!="") return (RealMatrix());

          int n = this->RowCnt;
          int i,j;
          LDouble sum;

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
  RealMatrix SolveFull(XString& er,RealMatrix b)
  {
          int n = this->RowCnt;

          RealMatrix RP,CP;
          RP = RealMatrix(1,n);
          CP = RealMatrix(1,n);
          int znak;
          *this=this->GaussFullElim(er,znak,b,RP,CP);
          if (er!="") return (RealMatrix());


          int i,j;
          LDouble sum;

          for(i=n-1;i>=0;i--)
          {
                  sum=0.0;
                  for(j=i+1;j<n;j++)
                  {
                          sum=sum+this->_el[i][j]*b._el[0][j];
                  }
                  b._el[0][i]= (b._el[0][i]-sum)/this->_el[i][i];
          }

          RealMatrix tmp;
          tmp=b;
          for (i=0;i<n;i++)       // CP [0,2,1]
          {
                  tmp._el[0][(int)(CP._el[0][i])]=b._el[0][i];
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
RealMatrix Inverse(XString& er)
{

if (this->IsNumber()) return (1.0/(this->_el[0][0]));

if (ColCnt!=RowCnt)
{
    er="Inverse: Matrix must be square!";
    return (RealMatrix()); //if matrix is not square
}

RealMatrix tmp;
tmp = *this;

if (tmp.Determinant(er)==0.0)
{
    er="Inverse: Determinant equal zero, inverse matrix does not exist!";
    return (RealMatrix()); //if matrix is not square
}

int i,j,k,max;
LDouble mul;
int n=RowCnt;
RealMatrix I=UnitMatrix(n);

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
            if ( fabsl(_el[i][k]) > fabsl(_el[max][k]))
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
            this->_el[k][k]=1.0;

            //
            //compute elements under diagonal                  //k                 |
            //                                                 //   k              |
            //      k           |
            for (i=k+1;i<n;i++)                                //    [i,k]k        |
            {                                                  //            k     |
              mul = this->_el[i][k];                         //               k  |
              for (j=0;j<n;j++)
              {
                if (j>k) this->_el[i][j]= this->_el[i][j] - (mul*this->_el[k][j]);
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
  LDouble Determinant(XString& er)
  {
          if (this->ColCnt!=this->RowCnt) {er="Determinant: Matrix must by square!"; return(0.0);}
          int n = RowCnt;

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
                          er="";
                          return (0.0);
                  }
                  else
                          return (0.0);

          int i;
          LDouble det=1.0;

          for (i=0;i<this->RowCnt;i++)
                  det=det*this->_el[i][i];

          det*=znak;

          return (det);
  }




  //==============================================================================================
  //================ TRANSPOSE ===================================================================
  //==============================================================================================
  RealMatrix Transpose()
  {

          if (this->IsNumber()) return(*this);

          RealMatrix* tmp = new RealMatrix(ColCnt,RowCnt);
          int i,j;
          for (i=0;i<tmp->RowCnt;i++)
                  for (j=0;j<tmp->ColCnt;j++)
                          tmp->_el[i][j]=this->_el[j][i];

          return (*tmp);

  }

  //==============================================================================================
//================ NORM ===================================================================
//==============================================================================================
LDouble Norm()
{

    if (this->IsNumber()) return(this->_el[0][0]);

    XString er;
    int i,j;
    LDouble sum = 0.0;
    LDouble maxSum = 0.0;
    for (i=0;i<RowCnt;i++)
    {
            sum = 0.0;
            for (j=0;j<ColCnt;j++)
                    sum = sum + fabsl(_el[i][j]);
            if (sum>maxSum) maxSum = sum;
    }

    return (maxSum);

}


//==============================================================================================
//================ NORM ===================================================================
//==============================================================================================
LDouble Cond(XString er)
{

    if (this->IsNumber()) return(this->_el[0][0]);

    return (this->Norm()*this->Inverse(er).Norm());

}





  //==============================================================================================
  //================== ISNUMBER ==================================================================
  //==============================================================================================
  bool IsNumber()
  {
          return	( ((this->RowCnt==1) && (this->ColCnt==1)) ? true : false );	
  }


  //==============================================================================================
  //================== ISVECTOR ==================================================================
  //==============================================================================================
  bool IsVector()
  {
          return	( ((this->RowCnt==1) && (this->ColCnt>1))  ? true : false );
  }


  //==============================================================================================
  //================== ISCOLUMN ==================================================================
  //==============================================================================================
  bool IsColumn()
  {
          return	( ((this->ColCnt==1) && (this->RowCnt>1))  ? true : false );
  }







  RealMatrix rabs(XString& er)
  {
          RealMatrix *tmp = new RealMatrix(RowCnt,ColCnt);
          int i,j;
          for (i=0; i<=RowCnt-1; i++)
          {
                  for (j=0; j<=ColCnt-1; j++)
                          tmp->_el[i][j]=fabsl(_el[i][j]);
          }

          return (*tmp);
  }



  RealMatrix rsin(XString& er)
  {
          RealMatrix *tmp = new RealMatrix(RowCnt,ColCnt);
          int i,j;
          for (i=0; i<=RowCnt-1; i++)
          {
                  for (j=0; j<=ColCnt-1; j++)
                          tmp->_el[i][j]=sinl(_el[i][j]);
          }

          return (*tmp);
  }



  RealMatrix rcos(XString& er)
  {
          RealMatrix *tmp = new RealMatrix(RowCnt,ColCnt);
          int i,j;
          for (i=0; i<=RowCnt-1; i++)
          {
                  for (j=0; j<=ColCnt-1; j++)
                          tmp->_el[i][j]=cosl(_el[i][j]);
          }

          return (*tmp);
  }



  RealMatrix rtan(XString& er)
  {
          RealMatrix *tmp = new RealMatrix(RowCnt,ColCnt);
          int i,j;
          for (i=0; i<=RowCnt-1; i++)
          {
                  for (j=0; j<=ColCnt-1; j++)
                          tmp->_el[i][j]=tanl(_el[i][j]);
          }

          return (*tmp);
  }



  RealMatrix rctan(XString& er)
  {
          RealMatrix* tmp = new RealMatrix(RowCnt,ColCnt);
          int i,j;
          for (i=0; i<=RowCnt-1; i++)
          {
                  for (j=0; j<=ColCnt-1; j++)
                          tmp->_el[i][j]=1.0/(tanl(_el[i][j]));
          }

          return (*tmp);
  }



  RealMatrix rlog(XString& er)
  {
          RealMatrix* tmp = new RealMatrix(RowCnt,ColCnt);
          int i,j;
          for (i=0; i<=RowCnt-1; i++)
          {
                  for (j=0; j<=ColCnt-1; j++)
                          tmp->_el[i][j]=logl(_el[i][j]);
          }

          return (*tmp);
  }



  RealMatrix rsqrt(XString& er)
  {
          RealMatrix* tmp = new RealMatrix(RowCnt,ColCnt);
          int i,j;
          for (i=0; i<=RowCnt-1; i++)
          {
                  for (j=0; j<=ColCnt-1; j++)
                  {
                          if (_el[i][j]<(0.0))
                          {er="SQRT: Negative argument!"; return(RealMatrix());}
                          tmp->_el[i][j]=sqrtl(_el[i][j]);
                  }
          }

          return (*tmp);
  }



  RealMatrix rexp(XString& er)
  {
          RealMatrix* tmp = new RealMatrix(RowCnt,ColCnt);
          int i,j;
          for (i=0; i<=RowCnt-1; i++)
          {
                  for (j=0; j<=ColCnt-1; j++)
                          tmp->_el[i][j]=expl(_el[i][j]);
          }

          return (*tmp);
  }


  //==============================================================================================
  //================ OPERATOR = ==================================================================
  //==============================================================================================

  RealMatrix operator =(RealMatrix y)
  {
          RowCnt = y.RowCnt;
          ColCnt = y.ColCnt;
          allocElem(y.RowCnt,y.ColCnt);
          int i,j;

          for (i=0; i<y.RowCnt; i++)
          {
                  for (j=0; j<y.ColCnt; j++)
                  {
                          this->_el[i][j]=y._el[i][j];
                  }
          }
          return (*this);
  }


  RealMatrix operator =(LDouble y)
  {
          RowCnt = 1;
          ColCnt = 1;
          allocElem(1,1);
          _el[0][0]=y;
          return (*this);
  }


  //==============================================================================================
  //============ LOGICAL OPERATORS ===============================================================
  //==============================================================================================


  bool operator ==(RealMatrix& y)
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

  bool operator !=(RealMatrix& y)
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

  RealMatrix& operator+(RealMatrix& y)
  {
          if (y.IsNumber()) return (*this + y._el[0][0]); //if y is LDouble
          if (((this->RowCnt)!=y.RowCnt) || ((this->ColCnt)!=y.ColCnt)) //if matrices dimensions not match
          { return(*this); };

          RealMatrix* tmp = new RealMatrix(this->RowCnt,this->ColCnt);
          int j;


          for (int i=0;i<=this->RowCnt-1; i++ )
          {
                  for (j=0;j<=this->ColCnt-1; j++ )
                          tmp->_el[i][j]=this->_el[i][j]+y._el[i][j];
          }
          return (*tmp);
  }



  RealMatrix& operator+( LDouble& y)
  {

          RealMatrix* tmp = new RealMatrix(this->RowCnt,this->ColCnt);
          int j;


          for (int i=0;i<=this->RowCnt-1; i++ )
          {
                  for (j=0;j<=this->ColCnt-1; j++ )
                          tmp->_el[i][j]=this->_el[i][j]+y;
          }
          return (*tmp);
  }


  RealMatrix& operator+ ()      
  {
          return (*this); 
  };

  //==============================================================================================
  //================ OPERATOR - ==================================================================
  //==============================================================================================


  RealMatrix& operator-()
  {

          int j;
          for (int i=0;i<=this->RowCnt-1; i++ )
          {
                  for (j=0;j<=this->ColCnt-1; j++ )
                          this->_el[i][j]=-(this->_el[i][j]);
          }

          return (*this);
  }



  RealMatrix& operator-(RealMatrix& y)
  {
          if (y.IsNumber()) return (*this - y._el[0][0]); //if y is LDouble
          if (((this->RowCnt)!=y.RowCnt) || ((this->ColCnt)!=y.ColCnt)) //if matrices dimensions not match
          { return(*this); };


          RealMatrix* tmp = new RealMatrix(this->RowCnt,this->ColCnt);
          int j;

          for (int i=0;i<=this->RowCnt-1; i++ )
          {
                  for (j=0;j<=this->ColCnt-1; j++ )
                          tmp->_el[i][j]=this->_el[i][j]-y._el[i][j];
          }

          return (*tmp);
  }



  RealMatrix& operator-( LDouble& y)
  {

          RealMatrix* tmp = new RealMatrix(this->RowCnt,this->ColCnt);
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

  RealMatrix& operator*(RealMatrix& y)
  {
          if (y.IsNumber()) return (*this * y._el[0][0]); //if y is LDouble
          if (this->ColCnt!=y.RowCnt) { return (*this); }
          RealMatrix* tmp = new RealMatrix(this->RowCnt,y.ColCnt);


          int j,i,k, col,row;
          col= tmp->ColCnt;
          row = tmp->RowCnt;

          for (i=0;i<row;i++)

                  for (j=0;j<col;j++)
                  {
                          tmp->_el[i][j]=0.0;
                          for (k=0;k<row;k++)
                          {
                                  tmp->_el[i][j]=tmp->_el[i][j]+this->_el[i][k]*y._el[k][j];
                          }
                  }

                  return (*tmp);
  }



  RealMatrix& operator*( LDouble& y)
  {
          RealMatrix* tmp = new RealMatrix(this->RowCnt,this->ColCnt);
          int j;
          for (int i=0;i<this->RowCnt; i++ )
          {
                  for (j=0;j<this->ColCnt; j++ )
                          tmp->_el[i][j]=this->_el[i][j]*y;
          }

          return (*tmp);
  }




  //==============================================================================================
  //================ OPERATOR / ==================================================================
  //==============================================================================================

  //Right side division matrix by matrix
  RealMatrix& operator/(RealMatrix& y)
  {
          if (y.IsNumber()) return (*this / y._el[0][0]); //if y is LDouble

          XString er;
          *this=y.Inverse(er)*(*this);
          return (*this);
  }



  //Division every element of matrix by LDouble
  RealMatrix& operator/( LDouble& y)
  {
          RealMatrix* tmp = new RealMatrix(this->RowCnt,this->ColCnt);
          int j;

          for (int i=0;i<this->RowCnt; i++ )
          {
                  for (j=0;j<this->ColCnt; j++ )
                          tmp->_el[i][j]=this->_el[i][j]/y;
          }

          return (*tmp);
  }


  RealMatrix& operator+= (RealMatrix& y)     
  { 
          *this = *this + y; 
          return(*this); 
  };

  RealMatrix& operator-= (RealMatrix& y)     
  { 
          *this = *this - y; 
          return(*this); 
  };
  RealMatrix& operator*= (RealMatrix& y)     
  { 
          *this = *this * y; 
          return(*this); 
  };
  RealMatrix& operator/= (RealMatrix& y)     
  { 
          *this = *this / y; 
          return(*this); 
  };
  RealMatrix& operator+= (LDouble& y)     
  { 
          *this = *this + y; 
          return(*this); 
  };
  RealMatrix& operator-= (LDouble& y)    
  { 
          *this = *this - y; 
          return(*this); 
  };
  RealMatrix& operator*= (LDouble& y)     
  { 
          *this = *this * y; 
          return(*this); 
  };
  RealMatrix& operator/= (LDouble& y)     
  { 
          *this = *this / y; 
          return(*this); 
  };

  //==============================================================================================
  //================ NPOWERI =====================================================================
  //==============================================================================================

  RealMatrix& npoweri(int n)
  {

          if (this->IsNumber())
          {
                  RealMatrix* tmp = new RealMatrix();
                  tmp->_el[0][0] =  adon(this->_el[0][0],n);
                  return(*tmp);
          }

          RealMatrix* tmp = new RealMatrix(this->RowCnt,this->ColCnt);
          int i,j;

          for (i=0; i<this->RowCnt; i++)
          {
                  for (j=0; j<this->ColCnt; j++)
                  {
                          tmp->_el[i][j]=adon(this->_el[i][j],n);
                  }
          }

          return (*tmp);
  }




};