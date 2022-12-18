//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UWstaw.h"



#include "Helpers.hpp"
#include "Interval.hpp"
#include "SimpleParser.h"
#include "UConstans.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TWstawFrm *WstawFrm;
TEdit *cells[100];
int _rows;
int _cols;

//---------------------------------------------------------------------------
__fastcall TWstawFrm::TWstawFrm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TWstawFrm::btnGenerujClick(TObject *Sender)
{
    GenerujKomorki();
}
//---------------------------------------------------------------------------
void TWstawFrm::GenerujKomorki()
{
   int trows = StrToInt(edtRows->Text);
   int tcols = StrToInt(edtCols->Text);

   if ((trows<=0) || (tcols<=0) || (trows>10) || (tcols>10))
   {
        ShowMessage("Niepoprawny wymiar macierzy!\nDopuszczalne tylko liczby ca�kowite z zakresu od 1 do 10.");
        return;
   }
   int ind = 0;


   if ((_rows!=0) || (_cols!=0))
   {
        for (int k=0; k<_rows*_cols;k++)
        {
           delete cells[k];
           cells[k] = NULL;
        }
   }

   _rows = trows;
   _cols = tcols;
    
   for (int i = 0;i<_rows;i++)
    for (int j = 0; j<_cols;j++)
     {
          ind=(i*_cols)+j;
          cells[ind] = new TEdit(pnlMain);

          cells[ind]->Width = 60;
          cells[ind]->Height = 20;
          cells[ind]->Left = 10+j*(60+5);
          cells[ind]->Top = 10+i*(20+5);
          cells[ind]->Name = "edtCell"+IntToStr(ind);
          cells[ind]->TabOrder = 3;
          cells[ind]->Text = "";
          cells[ind]->ShowHint = true;
          cells[ind]->Parent = pnlMain;
     }

}
void __fastcall TWstawFrm::btnOkClick(TObject *Sender)
{
  CzytajMacierz();
  Anulowane = false;
  this->Close();
}

//---------------------------------------------------------------------------
void TWstawFrm::CzytajMacierz()
{
 int i=0,j=0,ind=0;

 if (this->OnIntervals)
 {
      if ((_rows==1) && (_cols==1))
      {
              _macierz = "["+cells[0]->Text+"]";
      }
      else
      {
              _macierz="<";
              for (i=0;i<_rows;i++)
              {
                      for (j=0;j<_cols;j++)
                      {
                              ind=(i*_cols)+j;
                              if (cells[ind]->Text=="") _macierz+="[0,0]";
                              else
                              _macierz += "["+cells[ind]->Text+"]";
                      }
                      if (i<_rows-1) _macierz +=";";
              }
              _macierz += ">";
      }
 }
 else
 {
      if ((_rows==1) && (_cols==1))
      {
              _macierz = cells[0]->Text;
      }
      else
      {
              _macierz="<";
              for (i=0;i<_rows;i++)
              {
                      for (j=0;j<_cols;j++)
                      {
                              ind=(i*_cols)+j;
                              if (cells[ind]->Text=="") _macierz+="0";
                              else
                              _macierz +=cells[ind]->Text;

                              if (j<_cols-1) _macierz +=",";
                      }
                      if (i<_rows-1) _macierz +=";";
              }
              _macierz += ">";
      }
 }


}
void __fastcall TWstawFrm::btnAnulujClick(TObject *Sender)
{
   Anulowane = true;
   this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TWstawFrm::btnBoothroydClick(TObject *Sender)
{
   edtCols->Text = edtPredefSize->Text;
   edtRows->Text = edtPredefSize->Text;
   GenerujKomorki();
   if ((_rows<=0) || (_rows>10)) return;

   int i,j,ind,n;
   n = _rows;

   XString temp;

   if (this->OnIntervals)
   {
          LDouble tmp;

           for (i=0;i<n;i++)
           {
                   for (j=0;j<n;j++)
                   {
                           ind=(i*n)+j;
                           tmp=  (silnia(n+i)/silnia(i)) * (1.0/silnia(n-j-1)) * (1.0/silnia(j)) * (1.0/(i+j+1));
                           //silnia(n+i)/( silnia(i)*silnia(n-j-1)*silnia(j)*(i+j+1) );
                           temp = temp.fromLongDouble(tmp);
                           cells[ind]->Text= temp.replaceAll(",",".").ToAnsiString();
                           cells[ind]->Hint = cells[ind]->Text;
                   }
           }
   }
   else
           {

           LDouble tmp;

           for (i=0;i<n;i++)
           {
                   for (j=0;j<n;j++)
                   {
                           ind=(i*n)+j;
                           tmp= (silnia(n+i)/silnia(i)) * (1.0/silnia(n-j-1)) * (1.0/silnia(j)) * (1.0/(i+j+1));
                           cells[ind]->Text=XString::fromLongDouble(tmp).replaceAll(",",".").ToAnsiString();
                           cells[ind]->Hint = cells[ind]->Text;
                   }
           }
   }
}
//---------------------------------------------------------------------------

void __fastcall TWstawFrm::btnMatrixOneClick(TObject *Sender)
{
   edtCols->Text = edtPredefSize->Text;
   edtRows->Text = edtPredefSize->Text;
   GenerujKomorki();
   if ((_rows<=0) || (_rows>10)) return;

   int i,j,ind,n;
   n = _rows;

   if (this->OnIntervals)
   {
   Interval tmp;
   XString temp;
   for (i=0;i<n;i++)
   {
           for (j=0;j<n;j++)
           {
            ind=(i*n)+j;
            tmp=Interval(1.0)/Interval(i+j+1);
            temp = tmp.ToStr();
            temp = temp.remove(0,0);
            temp = temp.remove(temp.length()-1,temp.length()-1);
            cells[ind]->Text=temp.ToAnsiString();
            cells[ind]->Hint = cells[ind]->Text;
           }
   }
   }
   else
           {
   LDouble tmp;
   for (i=0;i<n;i++)
   {
           for (j=0;j<n;j++)
           {
            ind=(i*n)+j;
            tmp=(1.0/(i+j+1));
            cells[ind]->Text=XString::fromLongDouble(tmp).replaceAll(",",".").ToAnsiString();
            cells[ind]->Hint = cells[ind]->Text;
           }
   }
   }

}
//---------------------------------------------------------------------------


void __fastcall TWstawFrm::btnGenaijClick(TObject *Sender)
{
   GenerujKomorki();
   if ((_rows<=0) || (_rows>10)) return;

   int i,j,ind;

   SimpleParser *parser = new SimpleParser();
   XString commd = XString(edtCommand->Text.c_str());
   XString comm;

   commd=commd.trim();
   commd=commd.replaceAll(" ","");


   commd=commd.replaceAll("abs","a");
   commd=commd.replaceAll("sqrt","q");
   commd=commd.replaceAll("exp","x");
   commd=commd.replaceAll("log","l");
   commd=commd.replaceAll("sin","s");
   commd=commd.replaceAll("cos","c");
   commd=commd.replaceAll("ctg","g");
   commd=commd.replaceAll("tg","t");

   commd = commd.replaceAll((XString)"m",XString::fromInt(_rows));
   commd = commd.replaceAll((XString)"n",XString::fromInt(_cols));

   LDouble tmp;
   XString er;
   for (i=0;i<_rows;i++)
   {
           for (j=0;j<_cols;j++)
           {
            ind=(i*_cols)+j;
            comm = commd;
            comm = comm.replaceAll((XString)"i",XString::fromInt(i+1));
            comm = comm.replaceAll((XString)"j",XString::fromInt(j+1));
            tmp = parser->ParseCommand(comm,er);
            if (er!="")
            {
              ShowMessage(er.ToAnsiString());
              return;
            }
            cells[ind]->Text=XString::fromLongDouble(tmp).replaceAll(",",".").ToAnsiString();
            cells[ind]->Hint = cells[ind]->Text;
           }
   }


}
//---------------------------------------------------------------------------

void __fastcall TWstawFrm::edtCommandKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if (Key==13)
   {
      btnGenaij->Click();
   }
}
//---------------------------------------------------------------------------
void TWstawFrm::ReloadCaptions()
{

 if (LangId == 0)
 {

   WstawFrm->Caption = WstawFrm_CaptionPL;
   btnAnuluj->Caption = btnAnuluj_CaptionPL;
   gbGenerated->Caption = gbGenerated_CaptionPL;
   edtCommand->Hint =  edtCommand_HintPL;
   gbPredef->Caption = gbPredef_CaptionPL;
   btnBoothroyd->Caption == btnBoothroyd_CaptionPL;
   btnBoothroyd->Hint =  btnBoothroyd_HintPL;
   btnMatrixOne->Caption =  btnMatrixOne_CaptionPL;
   btnMatrixOne->Hint =  btnMatrixOne_HintPL;
   lblRozmiar->Caption = lblRozmiar_CaptionPL;
   gbRozmiary->Caption = gbRozmiary_CaptionPL;
   btnGeneruj->Caption =  btnGeneruj_CaptionPL;
   btnGenaij->Caption =  btnGenaij_CaptionPL;
  }
  else
  {
    WstawFrm->Caption = WstawFrm_CaptionEN;
   btnAnuluj->Caption = btnAnuluj_CaptionEN;
   gbGenerated->Caption = gbGenerated_CaptionEN;
   edtCommand->Hint =  edtCommand_HintEN;
   gbPredef->Caption = gbPredef_CaptionEN;
   btnBoothroyd->Caption == btnBoothroyd_CaptionEN;
   btnBoothroyd->Hint =  btnBoothroyd_HintEN;
   btnMatrixOne->Caption =  btnMatrixOne_CaptionEN;
   btnMatrixOne->Hint =  btnMatrixOne_HintEN;
   lblRozmiar->Caption = lblRozmiar_CaptionEN;
   gbRozmiary->Caption = gbRozmiary_CaptionEN;
   btnGeneruj->Caption =  btnGeneruj_CaptionEN;
   btnGenaij->Caption =  btnGenaij_CaptionEN;
  }



}
//---------------------------------------------------------------------------
void __fastcall TWstawFrm::FormShow(TObject *Sender)
{
  ReloadCaptions();        
}
//---------------------------------------------------------------------------
