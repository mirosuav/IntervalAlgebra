//---------------------------------------------------------------------------

#ifndef LogFormH
#define LogFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TLogFrm : public TForm
{
__published:	// IDE-managed Components
        TRichEdit *rtbTempResults;
private:	// User declarations
public:		// User declarations
        __fastcall TLogFrm(TComponent* Owner);
        void AppText(AnsiString text);
};
//---------------------------------------------------------------------------
extern PACKAGE TLogFrm *LogFrm;
//---------------------------------------------------------------------------
#endif
