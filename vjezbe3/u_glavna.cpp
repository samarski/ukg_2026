//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "u_glavna.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "U_Grafika"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::actTestExecute(TObject *Sender)
{
	// ShowMessage("Test");
	Grafika1->duz(5.0, 5.0, 250.0, 50.0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Grafika1imgMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	auto x = Grafika1->fx(X);
	auto y = Grafika1->fy(Y);

    ShowMessage("x=" + FloatToStr(x) + ", y=" + FloatToStr(y));
}
//---------------------------------------------------------------------------
