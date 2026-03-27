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
	TBitmap *bmp = new TBitmap();
	bmp->Assign(img->Picture->Bitmap);

	img->Picture->Bitmap->Width = this->Width;
	img->Picture->Bitmap->Height = this->Height;

	auto c = img->Canvas;
	c->Brush->Style = bsSolid;
	c->Brush->Color = clInfoBk;
	c->FillRect(Rect(0, 0, this->Width, this->Height));

	c->Draw(0, 0, bmp);
	delete bmp;

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
//	ShowMessage(IntToStr(X1)+";" + IntToStr(Y1) + ";" + IntToStr(X2) + ";" +
//		IntToStr(Y2));
}


void TGrafika::tacka(float x, float y) {
	auto X = iX(x);
	auto Y = iY(y);

	auto c = img->Canvas;
	c->Pen->Style = psSolid;
	c->Pen->Color = clBlack;
	c->Brush->Style = bsSolid;
	c->Brush->Color = clBlack;
	c->Ellipse(X-3,Y-3,X+3,Y+3);
}

const float EPSILON = 0.0000001;

bool TGrafika::pozitivna_orijentacija(
		LogickaTacka p1,
		LogickaTacka p2,
		LogickaTacka p3) {

	auto ax = p2.x - p1.x;
	auto ay = p2.y - p1.y;

	auto bx = p3.x - p1.x;
	auto by = p3.y - p1.y;

	return (ax*by - ay*bx) > EPSILON;
}

void TGrafika::ispisi(float x, float y, String tekst) {
	auto X = iX(x);
	auto Y = iY(y);

	auto c = img->Canvas;
	c->Pen->Style = psSolid;
	c->Pen->Color = clBlack;
    c->Brush->Style = bsClear;
	c->Font->Color = clRed;
	c->Font->Name = "Arial";
    c->Font->Size = 16;
    c->TextOut(X, Y, tekst);

}


void TGrafika::obrisi() {
	auto c = img->Canvas;
	c->Brush->Style = bsSolid;
	c->Brush->Color = clInfoBk;
	c->FillRect(Rect(0, 0, this->Width, this->Height));

	// crtamo centar
	c->Ellipse(centar_x-2,centar_y-2,centar_x+2,centar_y+2);
}


bool TGrafika::duzi_se_sijeku(
		LogickaTacka a,
		LogickaTacka b,
		LogickaTacka c,
		LogickaTacka d) {

	return (pozitivna_orijentacija(a,b,c) != pozitivna_orijentacija(a,b,d))
		&&
		(pozitivna_orijentacija(c,d,a) != pozitivna_orijentacija(c,d,b));
}


