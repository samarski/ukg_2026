//---------------------------------------------------------------------------

#ifndef u_glavnaH
#define u_glavnaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "U_Grafika.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnlGornji;
	TPanel *pnlDonji;
	TPanel *pnlKoordinate;
	TPanel *pnlPovrsina;
	TGrafika *Grafika1;
	TPanel *Panel1;
	TButton *Button1;
	TActionList *ActionList1;
	TAction *actTest;
	void __fastcall actTestExecute(TObject *Sender);
	void __fastcall Grafika1imgMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
