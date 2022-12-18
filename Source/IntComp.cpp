//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("UIntComp.cpp", IntCompFrm);
USEFORM("UAbout.cpp", AboutFrm);
USEFORM("LogForm.cpp", LogFrm);
USEFORM("UWstaw.cpp", WstawFrm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "IntComp";


                 Application->CreateForm(__classid(TIntCompFrm), &IntCompFrm);
                 Application->CreateForm(__classid(TLogFrm), &LogFrm);
                 Application->CreateForm(__classid(TAboutFrm), &AboutFrm);
                 Application->CreateForm(__classid(TWstawFrm), &WstawFrm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
