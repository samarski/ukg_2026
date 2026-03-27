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

	// ShowMessage("x=" + FloatToStr(x) + ", y=" + FloatToStr(y));
	Grafika1->tacka(x, y);
	cdsTacke->Append();
	cdsTackex_koor->Value = x;
	cdsTackey_koor->Value = y;
	int broj = cdsTacke->RecordCount;
	cdsTackeoznaka->Value = (char)(65+broj);
	cdsTacke->Post();

	Grafika1->ispisi(x, y, (char)(65+broj));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	cdsTacke->CreateDataSet();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::actOrijentacijaExecute(TObject *Sender)
{
	if (cdsTacke->RecordCount != 3) {
		ShowMessage("Morate imati tacno tri tacke");
		return;
	}

	cdsTacke->First();
	auto P1 = LogickaTacka(cdsTackex_koor->Value, cdsTackey_koor->Value,
							cdsTackeoznaka->Value);
	cdsTacke->Next();
	auto P2 = LogickaTacka(cdsTackex_koor->Value, cdsTackey_koor->Value,
							cdsTackeoznaka->Value);

	cdsTacke->Next();
	auto P3 = LogickaTacka(cdsTackex_koor->Value, cdsTackey_koor->Value,
							cdsTackeoznaka->Value);

	Grafika1->duz(P1.x, P1.y, P2.x, P2.y);
	Grafika1->duz(P2.x, P2.y, P3.x, P3.y);
	Grafika1->duz(P3.x, P3.y, P1.x, P1.y);

	if (Grafika1->pozitivna_orijentacija(P1,P2,P3)) {
		ShowMessage("Pozivna orijentacija");
	} else {
        ShowMessage("Negativna orijentacija");
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::actObrisiExecute(TObject *Sender)
{
//
	cdsTacke->EmptyDataSet();
    Grafika1->obrisi();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::actSjecenjeExecute(TObject *Sender)
{
	if (cdsTacke->RecordCount != 4) {
		ShowMessage("Morate imati tacno cetiri tacke");
		return;
	}

	cdsTacke->First();
	auto A = LogickaTacka(cdsTackex_koor->Value, cdsTackey_koor->Value,
							cdsTackeoznaka->Value);
	cdsTacke->Next();
	auto B = LogickaTacka(cdsTackex_koor->Value, cdsTackey_koor->Value,
							cdsTackeoznaka->Value);

	cdsTacke->Next();
	auto C = LogickaTacka(cdsTackex_koor->Value, cdsTackey_koor->Value,
							cdsTackeoznaka->Value);

	cdsTacke->Next();
	auto D = LogickaTacka(cdsTackex_koor->Value, cdsTackey_koor->Value,
							cdsTackeoznaka->Value);

	Grafika1->duz(A.x, A.y, B.x, B.y);
	Grafika1->duz(C.x, C.y, D.x, D.y);

	if (Grafika1->duzi_se_sijeku(A, B, C, D)) {
		ShowMessage("Duzi se sijeku!");
	} else {
        ShowMessage("Duzi se ne sijeku");
    }

}
//---------------------------------------------------------------------------

