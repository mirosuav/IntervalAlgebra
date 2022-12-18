//---------------------------------------------------------------------------

#ifndef UAboutH
#define UAboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TAboutFrm : public TForm
{
__published:	// IDE-managed Components
        TImage *imgAbout;
        TBitBtn *btnOk;
        TLabel *lblOpis;
        TLabel *lblCel;
        void __fastcall btnOkClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TAboutFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutFrm *AboutFrm;
//---------------------------------------------------------------------------
#endif