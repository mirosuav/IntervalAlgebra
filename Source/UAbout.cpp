//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutFrm *AboutFrm;
//---------------------------------------------------------------------------
__fastcall TAboutFrm::TAboutFrm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAboutFrm::btnOkClick(TObject *Sender)
{
  this->Close();        
}
//---------------------------------------------------------------------------
