//---------------------------------------------------------------------------

#ifndef UIntCompH
#define UIntCompH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TIntCompFrm : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu;
        TMenuItem *mnuPlik;
        TMenuItem *mnuOpcje;
        TMenuItem *mnuArytmetyka;
        TMenuItem *mnuPomoc;
        TMenuItem *mnuZapisz;
        TMenuItem *mnuWyjdz;
        TMenuItem *mnuPrzedzialowa;
        TMenuItem *mnuRzeczywista;
        TMenuItem *mnuWynikiPosr;
        TMenuItem *mnuZaokr;
        TMenuItem *mnuZaokAuto;
        TMenuItem *mnuZaokDonajbl;
        TMenuItem *mnuZaokrObcinaj;
        TMenuItem *mnuZaokrWDol;
        TMenuItem *mnuZaokrWGore;
        TMenuItem *mnuCzysc;
        TMenuItem *mnuCzcionka;
        TMenuItem *mnuKolorTla;
        TMenuItem *mnuOprogramie;
        TMenuItem *mnuPomocPomoc;
        TMenuItem *mnuWstaw;
        TMenuItem *mnuMacierz;
        TMenuItem *mnuPoprzednie;
        TMenuItem *mnuOstWynik;
        TRichEdit *tekran;
        TFontDialog *dlgFont;
        TSaveDialog *dlgSave;
        TColorDialog *dlgColor;
        TMenuItem *mnuFormatuj;
        TMenuItem *mnuNaPrzedz;
        TMenuItem *mnuNaRzecz;
        TMenuItem *mnuJezyk;
        TMenuItem *mnuPolski;
        TMenuItem *mnuAngielski;
        TMenuItem *mnuFormatFormat;
        TMenuItem *mnuPrecision;
        TMenuItem *mnuFormatLong;
        TMenuItem *mnuFormatShort;
        TMenuItem *mnuPrecFloat;
        TMenuItem *mnuPrecFixed;

        void __fastcall mnuOprogramieClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall mnuWyjdzClick(TObject *Sender);
        void __fastcall mnuCzcionkaClick(TObject *Sender);
        void __fastcall mnuKolorTlaClick(TObject *Sender);
        void __fastcall mnuCzyscClick(TObject *Sender);
        void __fastcall tekranKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall mnuNaPrzedzClick(TObject *Sender);
        void __fastcall mnuNaRzeczClick(TObject *Sender);
        void __fastcall mnuPomocPomocClick(TObject *Sender);
        void __fastcall mnuPrzedzialowaClick(TObject *Sender);
        void __fastcall mnuRzeczywistaClick(TObject *Sender);
        void __fastcall mnuPoprzednieClick(TObject *Sender);
        void __fastcall mnuZaokAutoClick(TObject *Sender);
        void __fastcall mnuZaokDonajblClick(TObject *Sender);
        void __fastcall mnuZaokrObcinajClick(TObject *Sender);
        void __fastcall mnuZaokrWDolClick(TObject *Sender);
        void __fastcall mnuZaokrWGoreClick(TObject *Sender);
        void __fastcall mnuWynikiPosrClick(TObject *Sender);
        void __fastcall mnuMacierzClick(TObject *Sender);
        void __fastcall mnuOstWynikClick(TObject *Sender);
        void __fastcall mnuPolskiClick(TObject *Sender);
        void __fastcall mnuAngielskiClick(TObject *Sender);
        void __fastcall mnuZapiszClick(TObject *Sender);
        void __fastcall mnuFormatLongClick(TObject *Sender);
        void __fastcall mnuFormatShortClick(TObject *Sender);
        void __fastcall mnuPrecFloatClick(TObject *Sender);
        void __fastcall mnuPrecFixedClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);


private:

public:
         void WriteTempResult(XString message);
         void WriteIntervalResult(IntMatrix& result);
         void WriteRealResult(RealMatrix& result);
         void AppText(XString text);
         void AppText(AnsiString text);
         void EvaluateCommand(XString command);
        __fastcall TIntCompFrm(TComponent* Owner);
        AnsiString WstawMacierz(bool OnInt);
        void ReloadCaptions();
        void LoadUserSettings();
        void SaveUserSettings();
        void GenerateFormatString();
        void TempResFrmShow();
        void TempResFrmHide();
};
//---------------------------------------------------------------------------
extern PACKAGE TIntCompFrm *IntCompFrm;
//---------------------------------------------------------------------------
#endif
