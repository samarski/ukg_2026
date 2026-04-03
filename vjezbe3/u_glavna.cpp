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

	if (cdsTacke->RecordCount == broj_cvorova) {
		// unijeli smo sve tacke
		// odredi_prost_poligon();
        pripadnost_poligonu();
	}
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

void __fastcall TForm1::actPoligonExecute(TObject *Sender)
{
// Ovdje radimo nas poligon
	auto odgovor = InputBox("Unesite n", "Unesite n", "10");
	broj_cvorova = StrToInt(odgovor);
}
//---------------------------------------------------------------------------

void TForm1::odredi_prost_poligon()
{
	std::vector<LogickaTacka> tacke;
	cdsTacke->First();
	while (!cdsTacke->Eof) {
		tacke.push_back(LogickaTacka(
			cdsTackex_koor->Value,
			cdsTackey_koor->Value,
			cdsTackeoznaka->Value));

		cdsTacke->Next();
	}

	// naci pivot, index pokazuje na index pivota
	int index = 0;
	for (auto i = 1; i < tacke.size(); i++) {
		if (tacke[i].x < tacke[index].x ||
			(tacke[i].x == tacke[index].x &&
			 tacke[i].y < tacke[index].y)) {

			index = i;
		}
	}

	// ShowMessage("Pivot je na poziciji " + IntToStr(index));
	std::swap(tacke[0], tacke[index]);

	std::sort(tacke.begin()+1,tacke.end(),
		[&](LogickaTacka &a, LogickaTacka &b) {
			return Grafika1->pozitivna_orijentacija(
				tacke[0], a, b);
		});

	/*
	Grafika1->duz(tacke[tacke.size()-1].x,
		tacke[tacke.size()-1].y,
		tacke[0].x,
		tacke[0].y);

	for (auto i = 0; i < tacke.size()-1; i++) {
		Grafika1->duz(tacke[i].x, tacke[i].y,
					  tacke[i+1].x, tacke[i+1].y);
	}
	*/

	std::vector<LogickaTacka> omotac;
	if (tacke.size() < 3)
		return;

	omotac.push_back(tacke[0]);
	omotac.push_back(tacke[1]);
	omotac.push_back(tacke[2]);

	auto p = 3;
	while (p < tacke.size()) {

		while ( (omotac.size() > 2) &&
			!Grafika1->pozitivna_orijentacija(
				omotac[omotac.size()-2],
				omotac[omotac.size()-1],
				tacke[p])) {

			omotac.pop_back();
		}

		omotac.push_back(tacke[p]);

		p++;
	}

	Grafika1->duz(omotac[omotac.size()-1].x,
		omotac[omotac.size()-1].y,
		omotac[0].x,
		omotac[0].y);

	for (auto i = 0; i < omotac.size()-1; i++) {
		Grafika1->duz(omotac[i].x, omotac[i].y,
					  omotac[i+1].x, omotac[i+1].y);
	}

}

void TForm1::pripadnost_poligonu()
{
	//
	std::vector<LogickaTacka> tacke;
	cdsTacke->First();
	while (!cdsTacke->Eof) {
		tacke.push_back(LogickaTacka(
			cdsTackex_koor->Value,
			cdsTackey_koor->Value,
			cdsTackeoznaka->Value));

		cdsTacke->Next();
	}
    tacke.pop_back();

	// naci pivot, index pokazuje na index pivota
	int index = 0;
	for (auto i = 1; i < tacke.size(); i++) {
		if (tacke[i].x < tacke[index].x ||
			(tacke[i].x == tacke[index].x &&
			 tacke[i].y < tacke[index].y)) {

			index = i;
		}
	}

	// ShowMessage("Pivot je na poziciji " + IntToStr(index));
	std::swap(tacke[0], tacke[index]);

	std::sort(tacke.begin()+1,tacke.end(),
		[&](LogickaTacka &a, LogickaTacka &b) {
			return Grafika1->pozitivna_orijentacija(
				tacke[0], a, b);
		});

	Grafika1->duz(tacke[tacke.size()-1].x,
		tacke[tacke.size()-1].y,
		tacke[0].x,
		tacke[0].y);

	for (auto i = 0; i < tacke.size()-1; i++) {
		Grafika1->duz(tacke[i].x, tacke[i].y,
					  tacke[i+1].x, tacke[i+1].y);
	}

	LogickaTacka P(cdsTackex_koor->Value,
		cdsTackey_koor->Value,
		cdsTackeoznaka->Value);

	auto prethodna = tacke.size()-1;
	auto tekuca = 0;
	bool u_unutrasnjosti = false;

	while (tekuca < tacke.size()) {

		if ((tacke[prethodna].y < P.y &&
			tacke[tekuca].y > P.y) ||
			(tacke[prethodna].y > P.y &&
			 tacke[tekuca].y < P.y)) {

			auto x_presjek = (tacke[tekuca].x - tacke[prethodna].x) /
				(tacke[tekuca].y - tacke[prethodna].y) *
				(P.y - tacke[tekuca].y) + tacke[tekuca].x;

			if (x_presjek > P.x) {
				u_unutrasnjosti = !u_unutrasnjosti;
			}
		}

		prethodna = tekuca;
		tekuca++;
	}

	if (u_unutrasnjosti) {
		ShowMessage("Tacka je u poligonu");
	} else {
        ShowMessage("Nije!");
    }

}

void __fastcall TForm1::actPripadnostPoligonuExecute(TObject *Sender)
{
	auto odgovor = InputBox("Unesite n", "Unesite n", "10");
	broj_cvorova = StrToInt(odgovor);
}
//---------------------------------------------------------------------------

