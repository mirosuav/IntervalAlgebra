//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LogForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLogFrm *LogFrm;
//---------------------------------------------------------------------------
__fastcall TLogFrm::TLogFrm(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void TLogFrm::AppText(AnsiString text)
{
   rtbTempResults->Text = rtbTempResults->Text + text;
   rtbTempResults->SelStart = rtbTempResults->Text.Length();
   SendMessageA(rtbTempResults->Handle,EM_SCROLLCARET,0,0);
}

//---------------------------------------------------------------------------

