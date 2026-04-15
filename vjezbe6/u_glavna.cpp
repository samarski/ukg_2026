//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <algorithm>
#pragma hdrstop

#include "u_glavna.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "U_Grafika"
#pragma resource "*.dfm"
TfrmGlavna *frmGlavna;


//---------------------------------------------------------------------------
__fastcall TfrmGlavna::TfrmGlavna(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmGlavna::actTestExecute(TObject *Sender)
{
	// ShowMessage("Test");
}
//---------------------------------------------------------------------------
void __fastcall TfrmGlavna::Grafika1imgMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	auto x = Grafika1->fx(X);
	auto y = Grafika1->fy(Y);

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
void __fastcall TfrmGlavna::FormCreate(TObject *Sender)
{
	cdsTacke->CreateDataSet();
}
//---------------------------------------------------------------------------

void __fastcall TfrmGlavna::actOrijentacijaExecute(TObject *Sender)
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

void __fastcall TfrmGlavna::actObrisiExecute(TObject *Sender)
{
//
	cdsTacke->EmptyDataSet();
    Grafika1->obrisi();
}

//---------------------------------------------------------------------------
// vrati_tacke: vraæa vektor taèaka koje se nalaze u ClientDataSetu
//---------------------------------------------------------------------------
std::vector<LogickaTacka> TfrmGlavna::vrati_tacke() {
	std::vector<LogickaTacka> tacke;
	cdsTacke->First();
	while (!cdsTacke->Eof) {
		tacke.push_back(LogickaTacka(
			cdsTackex_koor->Value,
			cdsTackey_koor->Value,
			cdsTackeoznaka->Value));

		cdsTacke->Next();
	}

	return tacke;
}

//---------------------------------------------------------------------------
// Test sjeèenja duži
//---------------------------------------------------------------------------
void __fastcall TfrmGlavna::actSjecenjeExecute(TObject *Sender)
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
// Test prostog poligona
//---------------------------------------------------------------------------
void __fastcall TfrmGlavna::actPoligonExecute(TObject *Sender)
{
	auto tacke = vrati_tacke();

	auto prost_poligon = Grafika1->prost_poligon(tacke);

	Grafika1->poligon(prost_poligon);
}

//---------------------------------------------------------------------------
// Test pripadnosti taèke poligonu
//---------------------------------------------------------------------------
void __fastcall TfrmGlavna::actPripadnostPoligonuExecute(TObject *Sender)
{
	// podrazumijeva se da smo odabrali tacke koje se
	// nalaze u ClientDataSetu, a da je posljednja odabrana tacka
	// ona za koju isputujemo pripadnost poligonu
	auto tacke = vrati_tacke();
	tacke.pop_back();

	LogickaTacka P(cdsTackex_koor->Value, cdsTackey_koor->Value, cdsTackeoznaka->Value);

	tacke = Grafika1->prost_poligon(tacke);

    // nacrtaj prost poligon
	Grafika1->poligon(tacke);

	if (Grafika1->tacka_u_poligonu(tacke, P)) {
		ShowMessage("Tacka je u poligonu");
	} else {
        ShowMessage("Tacka nije u poligonu!");
	}
}

//---------------------------------------------------------------------------
// Test konveksnog omotaèa
//---------------------------------------------------------------------------
void __fastcall TfrmGlavna::actKonveksniOmotacExecute(TObject *Sender)
{
	auto tacke = vrati_tacke();

	auto omotac = Grafika1->konveksni_omotac(tacke);

	Grafika1->poligon(omotac);
}
//---------------------------------------------------------------------------

