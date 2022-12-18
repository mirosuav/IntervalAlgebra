//---------------------------------------------------------------------------

#ifndef UWstawH
#define UWstawH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TWstawFrm : public TForm
{
__published:	// IDE-managed Components
        TPanel *pnlHead;
        TGroupBox *gbRozmiary;
        TLabel *Label1;
        TButton *btnGeneruj;
        TPanel *pnlMain;
        TPanel *pnlFoot;
        TButton *btnOk;
        TButton *btnAnuluj;
        TGroupBox *gbPredef;
        TLabel *lblRozmiar;
        TBitBtn *btnBoothroyd;
        TBitBtn *btnMatrixOne;
        TCSpinEdit *edtRows;
        TCSpinEdit *edtCols;
        TCSpinEdit *edtPredefSize;
        TBitBtn *btnnone;
        TBitBtn *BitBtn2;
        TGroupBox *gbGenerated;
        TEdit *edtCommand;
        TButton *btnGenaij;
        void __fastcall btnGenerujClick(TObject *Sender);
        void __fastcall btnOkClick(TObject *Sender);
        void __fastcall btnAnulujClick(TObject *Sender);
        void __fastcall btnBoothroydClick(TObject *Sender);
        void __fastcall btnMatrixOneClick(TObject *Sender);
        void __fastcall btnGenaijClick(TObject *Sender);
        void __fastcall edtCommandKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TWstawFrm(TComponent* Owner);
        void GenerujKomorki();
        bool Anulowane;
        AnsiString _macierz;
        bool OnIntervals;
        void CzytajMacierz();
        void ReloadCaptions();
        int LangId;

};
//---------------------------------------------------------------------------
extern PACKAGE TWstawFrm *WstawFrm;
//---------------------------------------------------------------------------
#endif
