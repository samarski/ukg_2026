//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "u_glavna.h"
#include <vector>
#include <algorithm>

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
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	cdsTacke->CreateDataSet();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::actObrisiExecute(TObject *Sender)
{
	cdsTacke->EmptyDataSet();
	Grafika1->obrisi();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Grafika1imgMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	auto x = Grafika1->fx(X);
	auto y = Grafika1->fy(Y);

	// x i y sadržavaju logicke koordinate pozicije na kojoj je mis
	Grafika1->tacka(x, y);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::actTestExecute(TObject *Sender)
{
	// primjeri upotrebe metoda
	Grafika1->obrisi();

	Grafika1->tacka(50.0, 50.0);
	Grafika1->ispisi(50.0, 50.0, "A");

	Grafika1->duz(5.0, 5.0, 250.0, 50.0);

	Grafika1->ispisi(100, 100, "Test");
}
//---------------------------------------------------------------------------

