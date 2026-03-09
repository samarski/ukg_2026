//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmGlavna *frmGlavna;
//---------------------------------------------------------------------------
__fastcall TfrmGlavna::TfrmGlavna(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmGlavna::btnPravougaonikClick(TObject *Sender)
{
	auto c = Image1->Canvas;

	c->Pen->Color = clGreen;
	c->Pen->Width = 3;

/*
	// c->Brush->Style = bsSolid;
	c->Brush->Style = bsClear;
	c->Brush->Color = clRed;

	// c->MoveTo(100,50);
	// c->LineTo(250,100);

	// c->Rectangle(100, 50, 250, 100);

	c->Ellipse(100, 50, 250, 100);
*/
	int odX = StrToInt(edtOdX->Text);
	int odY = StrToInt(edtOdY->Text);
	int doX = StrToInt(edtDoX->Text);
	int doY = StrToInt(edtDoY->Text);

	c->Rectangle(odX, odY, doX, doY);

}
//---------------------------------------------------------------------------
void __fastcall TfrmGlavna::btnTackaClick(TObject *Sender)
{
	auto c = Image1->Canvas;

	int X = StrToInt(edtOdX->Text);
	int Y = StrToInt(edtOdY->Text);

//	c->Pixels[X][Y] = clRed;
	c->Brush->Style = bsSolid;
	c->Brush->Color = clRed;
    c->Pen->Color = clRed;
    c->Ellipse(X-10,Y-10,X+10,Y+10);
}
//---------------------------------------------------------------------------
void __fastcall TfrmGlavna::Image1MouseDown(
	TObject *Sender,
	TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
//	ShowMessage("X = " + IntToStr(X) + ";Y = " + IntToStr(Y));
    PritisnutMis = true;

}
//---------------------------------------------------------------------------
void __fastcall TfrmGlavna::Image1MouseMove(
	TObject *Sender,
	TShiftState Shift,
	int X, int Y)
{
	if (PritisnutMis) {
		auto c = Image1->Canvas;

		c->Brush->Style = bsSolid;
		c->Brush->Color = clRed;
		c->Pen->Color = clRed;
		c->Ellipse(X-5,Y-5,X+5,Y+5);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmGlavna::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
    PritisnutMis = false;
}
//---------------------------------------------------------------------------
