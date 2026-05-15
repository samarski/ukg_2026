//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <algorithm>
#pragma hdrstop

#include "U_Grafika.h"
#include "u_trid_operator.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


TGrafika *Grafika;
//---------------------------------------------------------------------------
__fastcall TGrafika::TGrafika(TComponent* Owner)
	: TFrame(Owner)
{
	centar_x = centar_y = 350;
	alfa_2d = 0;
	skaliraj_x = skaliraj_y = 1.0;

	vrsta_prikaza = TVrstaPrikaza::perspektiva;
    oko = Logicka3DTacka(10, 10, 2);
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
}


void TGrafika::trougao(float x1, float y1, float x2, float y2,
	float x3, float y3) {

	duz(x1, y1, x2, y2);
	duz(x2, y2, x3, y3);
	duz(x3, y3, x1, y1);
}

void TGrafika::trougao_u_boji(float x1, float y1, float x2, float y2,
	float x3, float y3, TColor boja) {

	auto X1 = iX(x1);
	auto Y1 = iY(y1);
	auto X2 = iX(x2);
	auto Y2 = iY(y2);
	auto X3 = iX(x3);
	auto Y3 = iY(y3);

	TPoint tacke[3] = {TPoint(X1,Y1), TPoint(X2,Y2), TPoint(X3,Y3)};

	auto c = img->Canvas;
	c->Pen->Color = clBlack;
	c->Brush->Style = bsSolid;
	c->Brush->Color = boja;
	c->Polygon(tacke, 2);
}



//---------------------------------------------------------------------------
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

//---------------------------------------------------------------------------
void TGrafika::obrisi() {
	auto c = img->Canvas;
	c->Brush->Style = bsSolid;
	c->Brush->Color = clInfoBk;
	c->FillRect(Rect(0, 0, this->Width, this->Height));

	// crtamo centar
	c->Ellipse(centar_x-2,centar_y-2,centar_x+2,centar_y+2);
}

//---------------------------------------------------------------------------
void TGrafika::poligon(std::vector<LogickaTacka>& tacke) {
	int prethodna = tacke.size()-1;
	int tekuca = 0;
	while (tekuca < tacke.size()) {
		duz(tacke[prethodna].x, tacke[prethodna].y,
			tacke[tekuca].x, tacke[tekuca].y);

		prethodna = tekuca;
		tekuca++;
	}

	// alternativno:
	// int prethodna = tacke.size() - 1
	// for (auto tekuca = 0; tekuca < tacke.size(); prethodna = tekuca++) {
	//     ...
	// }
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

bool TGrafika::duzi_se_sijeku(
		LogickaTacka a,
		LogickaTacka b,
		LogickaTacka c,
		LogickaTacka d) {

	return (pozitivna_orijentacija(a,b,c) != pozitivna_orijentacija(a,b,d))
		&&
		(pozitivna_orijentacija(c,d,a) != pozitivna_orijentacija(c,d,b));
}

std::vector<LogickaTacka> TGrafika::prost_poligon(std::vector<LogickaTacka>& arg_tacke) {

	auto tacke = arg_tacke;
	// naci pivot, index pokazuje na index pivota
	int index = 0;
	for (auto i = 1; i < tacke.size(); i++) {
		if (tacke[i].x < tacke[index].x ||
			(tacke[i].x == tacke[index].x && tacke[i].y < tacke[index].y)) {

			index = i;
		}
	}

	// pivot je na poziciji index
	std::swap(tacke[0], tacke[index]);

	std::sort(tacke.begin()+1,tacke.end(),
		[&](LogickaTacka &a, LogickaTacka &b) {
			return pozitivna_orijentacija(tacke[0], a, b);
		});

	return tacke;
}

bool TGrafika::tacka_u_poligonu(std::vector<LogickaTacka>& tacke, LogickaTacka& P) {

	bool u_unutrasnjosti = false;

	auto prethodna = tacke.size()-1;
	auto tekuca = 0;
	while (tekuca < tacke.size()) {

		if ((tacke[prethodna].y < P.y && tacke[tekuca].y > P.y) ||
			(tacke[prethodna].y > P.y && tacke[tekuca].y < P.y)) {

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

    return u_unutrasnjosti;
}

std::vector<LogickaTacka> TGrafika::konveksni_omotac(std::vector<LogickaTacka>& arg_tacke) {

	std::vector<LogickaTacka> omotac;

	if (arg_tacke.size() < 3)
		return omotac; // vrati prazan omotac

	auto tacke = arg_tacke;
	int index = 0;
	for (auto i = 1; i < tacke.size(); i++) {
		if (tacke[i].x < tacke[index].x ||
			(tacke[i].x == tacke[index].x && tacke[i].y < tacke[index].y)) {

			index = i;
		}
	}

	// pivot je na poziciji index
	std::swap(tacke[0], tacke[index]);

	std::sort(tacke.begin()+1,tacke.end(),
		[&](LogickaTacka &a, LogickaTacka &b) {
			return pozitivna_orijentacija(tacke[0], a, b);
		});

	omotac.push_back(tacke[0]);
	omotac.push_back(tacke[1]);
	omotac.push_back(tacke[2]);

	auto p = 3;
	while (p < tacke.size()) {

		while ( (omotac.size() > 2) &&
			!pozitivna_orijentacija(
				omotac[omotac.size()-2],
				omotac[omotac.size()-1],
				tacke[p])) {

			omotac.pop_back();
		}

		omotac.push_back(tacke[p]);

		p++;
	}

	return omotac;
}


bool TGrafika::tacka_pripada_ccw_trouglu(
	LogickaTacka A,
	LogickaTacka B,
	LogickaTacka C,
	LogickaTacka P) {

	return pozitivna_orijentacija(A, B, P) &&
		pozitivna_orijentacija(B, C, P) &&
		pozitivna_orijentacija(C, A, P);
}


std::vector<LogickiTrougao> TGrafika::triangulacija(
	std::vector<LogickaTacka>& arg_tacke) {


	// auto tacke = prost_poligon(arg_tacke);
    auto tacke = arg_tacke;
	std::vector<LogickiTrougao> rezultat;

	if (arg_tacke.size() < 3) {
		return rezultat;
	}

	if (arg_tacke.size() == 3) {
		auto t = LogickiTrougao(tacke[0], tacke[1], tacke[2]);
		rezultat.push_back(t);
		return rezultat;
	}

	auto n = tacke.size();
	while (n > 3) {
		//

		bool nasli_smo_uho = false;

		for (auto i = 0; i < n; i++) {

			auto prva = (i-1+n) % n;
			auto druga = i;
			auto treca = (i+1) % n;

			auto A = tacke[prva];
			auto B = tacke[druga];
			auto C = tacke[treca];

			if (pozitivna_orijentacija(A, B, C)) {

				 auto nema_tacaka = true;
				 for (auto j = 0; j < n; j++) {
					if (j == prva || j == druga || j == treca)
						continue;

					if (tacka_pripada_ccw_trouglu(A, B, C, tacke[j])) {
						nema_tacaka = false;
						break; // ovo je break j-petlje
					}
				 }

				 // nema_tacaka govori jesmo li nasli tacku u nasem
				 // trouglu A, B, C

				 if (nema_tacaka) {
					nasli_smo_uho = true;

					// nasli smo uho
					rezultat.push_back(LogickiTrougao(A, B, C));
					tacke.erase(tacke.begin() + i);
					n--;
					break; // ovo je break i-petlje
				 }
			} // end if pozitivna_orijentacija(A, B, C)
		}

		if (!nasli_smo_uho) {
			break; // nesto je ovdje problem
		}
	}

	rezultat.push_back(LogickiTrougao(tacke[0], tacke[1], tacke[2]));

	return rezultat;
}


void TGrafika::podesi(
	float aAlfa2D,
	float aSkalirajX,
	float aSkalirajY) {

	alfa_2d = aAlfa2D;
	skaliraj_x = aSkalirajX;
    skaliraj_y = aSkalirajY;
}

void TGrafika::duz(Logicka3DTacka A, Logicka3DTacka B) {
	auto A2 = trid_u_dvad(A);
	auto B2 = trid_u_dvad(B);

	duz(A2.x, A2.y, B2.x, B2.y);
}



LogickaTacka TGrafika::iso_3d_u_2d(Logicka3DTacka P) {
	auto ugao = 3.1415926 * alfa_2d / 180.0;
	auto rx = P.x * std::cos(ugao) - P.y * std::sin(ugao);
	auto ry = P.x * std::sin(ugao) + P.y * std::cos(ugao);
	auto rz = P.z;

	auto x = -rx * 0.7 + ry;
	auto y = -rx * 0.3 + rz;

	x = x * skaliraj_x;
	y = y * skaliraj_y;

	return LogickaTacka(x, y, "");
}

LogickaTacka TGrafika::persp_u_2d(Logicka3DTacka P) {
	// auto T = TriDOperator::translacija(-oko.x, -oko.y, -oko.z);
	auto T = TriDOperator::translacija(-oko);
	P = T(P);
	auto theta = std::atan2(oko.y, oko.x) + 3.1415926 / 2;
	auto Rz = TriDOperator::rotacija_oko_z(-theta);
	P = Rz(P);
	auto phi = std::atan2(std::sqrt(oko.x*oko.x + oko.y*oko.y), oko.z);
	auto Rx = TriDOperator::rotacija_oko_x(-phi);
	P = Rx(P);

	auto x = -skaliraj_x * P.x / P.z;
	auto y = -skaliraj_y * P.y / P.z;

    return LogickaTacka(x, y, "");
}


LogickaTacka TGrafika::trid_u_dvad(Logicka3DTacka P) {
	if (vrsta_prikaza == TVrstaPrikaza::iso3D) {
		return iso_3d_u_2d(P);
	} else if (vrsta_prikaza == TVrstaPrikaza::perspektiva) {
		return persp_u_2d(P);
	}
}

