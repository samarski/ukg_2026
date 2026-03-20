//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "U_Grafika.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGrafika *Grafika;
//---------------------------------------------------------------------------
__fastcall TGrafika::TGrafika(TComponent* Owner)
	: TFrame(Owner)
{
    centar_x = centar_y = 200;
}
//---------------------------------------------------------------------------
void __fastcall TGrafika::FrameResize(TObject *Sender)
{
/*
	img->Canvas->Brush->Color = clYellow;
*/
	img->Picture->Bitmap->Width = this->Width;
	img->Picture->Bitmap->Height = this->Height;

	auto c = img->Canvas;
	c->Brush->Style = bsSolid;
	c->Brush->Color = clYellow;
	c->FillRect(Rect(0, 0, this->Width, this->Height));

    // crtamo centar
	c->Ellipse(centar_x-2,centar_y-2,centar_x+2,centar_y+2);
}
//---------------------------------------------------------------------------
void TGrafika::duz(float x1, float y1, float x2, float y2) {
	auto X1 = iX(x1);
	auto Y1 = iY(y1);
	auto X2 = iX(x2);
	auto Y2 = iY(y2);

	auto c = img->Canvas;
    c->Pen->Color = clBlack;
	c->MoveTo(X1, Y1);
	c->LineTo(X2, Y2);
	ShowMessage(IntToStr(X1)+";" + IntToStr(Y1) + ";" + IntToStr(X2) + ";" +
		IntToStr(Y2));
}
