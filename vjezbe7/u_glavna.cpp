//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <algorithm>
#pragma hdrstop

#include "u_glavna.h"
#include "u_logicka_3d_tacka.h"

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

void __fastcall TfrmGlavna::actTriangulacijaExecute(TObject *Sender)
{
	auto tacke = vrati_tacke();
	Grafika1->poligon(tacke);

	auto trouglovi = Grafika1->triangulacija(tacke);

	std::vector<TColor> boje{clRed, clBlue, clGreen, clMaroon, clPurple, clLime};

	for (int i = 0; i < trouglovi.size(); i++) {
		auto t = trouglovi[i];
		Grafika1->trougao_u_boji(
			t.A.x, t.A.y,
			t.B.x, t.B.y,
			t.C.x, t.C.y,
			boje[i % boje.size()]);

		Grafika1->trougao(
			t.A.x, t.A.y,
			t.B.x, t.B.y,
			t.C.x, t.C.y);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmGlavna::act2DTestExecute(TObject *Sender)
{
//
	Grafika1->obrisi();

	std::vector<LogickaTacka> lik{
		LogickaTacka(100, 100, ""),
		LogickaTacka(300, 100, ""),
		LogickaTacka(300, 150, ""),
		LogickaTacka(100, 150, "")
	};

    Grafika1->poligon(lik);
}
//---------------------------------------------------------------------------

void __fastcall TfrmGlavna::actRotirajLijevoExecute(TObject *Sender)
{
	// Grafika1->podesi(Grafika1->getAlfa2D()-5, 1.0, 1.0);
	// act2DTest->Execute();
	Grafika1->podesi(Grafika1->getAlfa2D()-1, 100, 100);
	// ShowMessage(FloatToStr(Grafika1->getAlfa2D()));
	act3DGraf->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TfrmGlavna::actRotirajDesnoExecute(TObject *Sender)
{
//	Grafika1->podesi(Grafika1->getAlfa2D()+5, 1.0, 1.0);
//	act2DTest->Execute();
	Grafika1->podesi(Grafika1->getAlfa2D()+1, 100, 100);
	// ShowMessage(FloatToStr(Grafika1->getAlfa2D()));
	act3DGraf->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TfrmGlavna::act3DGrafExecute(TObject *Sender)
{
	Grafika1->postavi_centar(Grafika1->Width/2, Grafika1->Height/2);
	Grafika1->obrisi();
	auto faktor = Grafika1->Width / 10.0;

	faktor = faktor * 10;

	Grafika1->podesi(Grafika1->getAlfa2D(), faktor, faktor);

	auto oko_x = StrToFloat(edtOkoX->Text);
	auto oko_y = StrToFloat(edtOkoY->Text);
	auto oko_z = StrToFloat(edtOkoZ->Text);

    Grafika1->postavi_oko(Logicka3DTacka(oko_x, oko_y, oko_z));

	auto n = (int) Grafika1->Width / 25;
	auto f = [](float x, float y) {
		return std::exp(-0.3*(x*x+y*y)) * std::cos(x*x + y*y);
	};


	std::vector<std::vector<Logicka3DTacka>> mreza;
	for (int i = 0; i <= n; i++) {
		mreza.push_back(std::vector<Logicka3DTacka>());
		for (int j = 0; j <= n; j++) {
			auto x = -3.0 + 1.0 * i/n*6.0;
			auto y = -3.0 + 1.0 * j/n*6.0;
			auto z = f(x,y);
			mreza[i].push_back(Logicka3DTacka(x,y,z));
		}
	}

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {

			if (i < n)
				Grafika1->duz(mreza[i][j],mreza[i+1][j]);

			if (j < n)
				Grafika1->duz(mreza[i][j],mreza[i][j+1]);
		}
	}
}
//---------------------------------------------------------------------------

