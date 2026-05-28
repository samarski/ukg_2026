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

	e_theta = 0.3;
	e_phi = 1.3;
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

float TGrafika::povrsina2D(
	LogickaTacka p1,
	LogickaTacka p2,
	LogickaTacka p3) {

	auto ax = p2.x - p1.x;
	auto ay = p2.y - p1.y;

	auto bx = p3.x - p1.x;
	auto by = p3.y - p1.y;

	return (ax*by - ay*bx);
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

float TGrafika::udaljenost(LogickaTacka a, LogickaTacka b) {
	auto dx = a.x - b.x;
	auto dy = a.y - b.y;
	return std::sqrt(dx*dx + dy*dy);
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

void TGrafika::poligon(std::vector<Logicka3DTacka>& tacke) {
	int prethodna = tacke.size()-1;
	int tekuca = 0;
	while (tekuca < tacke.size()) {
		duz(tacke[prethodna], tacke[tekuca]);

		prethodna = tekuca;
		tekuca++;
	}

}

void TGrafika::nacrtaj(Objekat& obj) {
	// ako je lista poligona prazna vrati se

	// preuzmi tacke, izracunaj eye koordinate i projekcije na ekran
	float vel;
	Logicka3DTacka centar;
	obj.saznaj_velicinu_i_centar(vel, centar);
	// postavljamo defaultnu udaljenost

	/*
	l_tacke.clear();
	for (auto T: obj.getVrhovi()) {
		if (T.index > l_tacke.size()) {
			for (int i = l_tacke.size(); i <= T.index; i++) {
				l_tacke.push_back(Logicka3DTacka(0,0,0,0));
			}
		}
		l_tacke[T.index] = T;
	}
	*/

	// kopiranje tacaka
	l_tacke.clear();
	for (int k = 0; k < obj.getVrhovi().size(); k++) {
		auto T = obj.getVrhovi()[k];
		if (T.index >= l_tacke.size()) {
			for (int i = l_tacke.size(); i <= T.index; i++) {
				l_tacke.push_back(Logicka3DTacka(0,0,0,0));
			}
		}
		l_tacke[T.index] = T;
	}


	for (int i = 0; i < l_tacke.size(); i++) {
		l_tacke[i].x -= centar.x;
		l_tacke[i].y -= centar.y;
		l_tacke[i].z -= centar.z;
	}

	e_rho = 2 * vel;
	e_rho_min = 0.6 * e_rho;
	e_rho_max = 1000 * e_rho_min;
	// inicijalne vrijednosti za e_theta i e_phi date u konstruktoru

	l_init_persp();

	l_saznaj_koordinate();

    obrisi();

	// napravi skup duži
	l_napravi_skup_duzi(obj);

	// napravi poligone na osnovu definicije objekta
	l_poligoni.clear();
	for (auto& p: obj.getPoligoni()) {
		std::vector<Logicka3DTacka> tacke;
		for (auto idx: p) {
			auto t = obj.getVrhovi()[idx];
			// t.index = idx;
			tacke.push_back(t);
		}
		auto poligon = Poligon(tacke);

		// trebace nam koeficijenti za svaki poligon - plohu
		// poligon.izracunaj_koeficijente();
		{
			float koef_a, koef_b, koef_c, h;

			if (poligon.broj_vrhova() < 3) {
				koef_a = koef_b = koef_c = h = 0.0;
			}
			else {
				auto poltacke = poligon.getTacke();
				auto A = l_o_tacke[poltacke[0].index],
					 B = l_o_tacke[poltacke[1].index],
					 C = l_o_tacke[poltacke[2].index];

				float u1 = B.x - A.x;
				float u2 = B.y - A.y;
				float u3 = B.z - A.z;
				float v1 = C.x - A.x;
				float v2 = C.y - A.y;
				float v3 = C.z - A.z;

				auto a = u2 * v3 - u3 * v2;
				auto b = u3 * v1 - u1 * v3;
				auto c = u1 * v2 - u2 * v1;
				auto norma = std::sqrt(a * a + b * b + c * c);

				koef_a = a/norma;
				koef_b = b/norma;
				koef_c = c/norma;
				h = koef_a * A.x + koef_b * A.y + koef_c * A.z;
			}
			poligon.postaviKoefABCh(koef_a, koef_b, koef_c, h);
		}

		l_poligoni.push_back(poligon);
	}

	/*
	String s;
	for (auto& p: l_poligoni) {
		auto Pindex = p.getTacke()[p.broj_vrhova()-1].index;
		for (auto& T: p.getTacke()) {
			auto prva = l_e_tacke[Pindex];
			auto druga = l_e_tacke[T.index];
			s += IntToStr(int(prva.x)) + ";" + IntToStr(int(prva.y)) + " - " +
			   IntToStr(int(druga.x)) + ";" + IntToStr(int(druga.y)) +
			   ";" + IntToStr(Pindex) + "-" + IntToStr(T.index) + "\n";

			duz(prva.x, prva.y, druga.x, druga.y);
			// ShowMessage("OK");

			Pindex = T.index;
		}
	}

	ShowMessage(s);
	*/

	/*
	for (const auto& par: l_duzi) {
		for (auto& idx: par.second) {
			auto prva = l_e_tacke[par.first];
			auto druga = l_e_tacke[idx];

//			ShowMessage(IntToStr(par.first) + " to " + IntToStr(idx));

			// ShowMessage(FloatToStr(prva.x) + "," + FloatToStr(prva.y) + " - " +
			// FloatToStr(druga.x) + ";" + FloatToStr(druga.y));
			//
			duz(prva.x, prva.y, druga.x, druga.y);
			ShowMessage(IntToStr(par.first) + "-" + IntToStr(idx));
		}
	}
	*/



	/*
	postavi_centar(this->Width/2, this->Height/2);
	obrisi();
	auto faktor = this->Width / 10.0;
	faktor = faktor * 10;
	podesi(getAlfa2D(), faktor, faktor);

	auto oko_x = 5;
	auto oko_y = 5;
	auto oko_z = 5;
	postavi_oko(Logicka3DTacka(oko_x, oko_y, oko_z));

	for (const auto& par: l_duzi) {
		for (auto& idx: par.second) {
			ShowMessage(IntToStr(par.first) + "-" + IntToStr(idx));
			duz(l_tacke[par.first],l_tacke[idx]);
		}
	}

	return;
	*/


	// N.B. h_granica je negativan (veoma mali) broj relativno u odnosu na
	// velicinu
	auto h_granica = -1e-6 * vel;

	l_broj_trouglova = 0;
	l_tr.clear(); // lista trouglova
	l_refpol.clear(); // referenca na poligon kojem dati trougao pripada

	auto pol_idx = 0;
	for (auto& p: l_poligoni) {
		if ((p.broj_vrhova() > 2) && (p.getH() <= h_granica)) {
			p.trianguliraj();

			for (auto& t: p.getTrouglovi()) {
				l_tr.push_back(t);
				l_refpol.push_back(pol_idx);
			}
		}
		pol_idx++;
	}
	l_broj_trouglova = l_tr.size();
    ShowMessage("Broj trouglova=" + IntToStr(int(l_broj_trouglova)));

	for (const auto& par: l_duzi) {
		for (auto& idx: par.second) {
			nacrtaj_duz(l_o_tacke[par.first],l_o_tacke[idx],
				l_e_tacke[par.first],l_e_tacke[idx],par.first,idx,0);
			// ShowMessage(IntToStr(par.first) + "-" + IntToStr(idx));
		}
	}
}

void TGrafika::l_init_persp() {
	float costh = std::cos(e_theta);
	float sinth = std::sin(e_theta);
	float cosph = std::cos(e_phi);
	float sinph = std::sin(e_phi);
	e_v11 = -sinth;
	e_v12 = -cosph * costh;
	e_v13 = sinph * costh;

	e_v21 = costh;
	e_v22 = -cosph * sinth;
	e_v23 = sinph * sinth;

	e_v32 = sinph;
	e_v33 = cosph;
	e_v43 = -e_rho;
}


void TGrafika::l_saznaj_koordinate() {
	l_o_tacke.clear(); // ocne koordinate
	l_e_tacke.clear(); // ekranske koordinate

	float xScrMin = 1e30, xScrMax = -1e30, yScrMin = 1e30, yScrMax = -1e30;
	for (Logicka3DTacka& P: l_tacke) {
		float x = e_v11 * P.x + e_v21 * P.y;
		float y = e_v12 * P.x + e_v22 * P.y + e_v32 * P.z;
		float z = e_v13 * P.x + e_v23 * P.y + e_v33 * P.z + e_v43;

		auto Po = Logicka3DTacka(x, y, z);
		l_o_tacke.push_back(Po);
		float xScr = -Po.x / Po.z, yScr = -Po.y / Po.z;
		l_e_tacke.push_back(LogickaTacka(xScr, yScr));

		if (P.index != 0) {
			if (xScr < xScrMin) xScrMin = xScr;
			if (xScr > xScrMax) xScrMax = xScr;
			if (yScr < yScrMin) yScrMin = yScr;
			if (yScr > yScrMax) yScrMax = yScr;
		}
	}
	float rangeX = xScrMax - xScrMin, rangeY = yScrMax - yScrMin;

	e_d = 0.95 * std::min(this->Width / rangeX, this->Height / rangeY);

	auto centar_x = e_d * (xScrMin + xScrMax) / 2;
	auto centar_y = e_d * (yScrMin + yScrMax) / 2;
	postavi_centar(this->Width/2 - centar_x, this->Height/2 + centar_y);

	for (int i = 0; i < l_e_tacke.size(); i++) {
		l_e_tacke[i].x *= e_d;
		l_e_tacke[i].y *= e_d;
	}
	// return d * Math.max(rangeX, rangeY);
}


void TGrafika::l_napravi_skup_duzi(Objekat& obj) {
	// nakon izvrsavanja, l_duzi sadrzi za svaki vrh M
	// vektor vrhova N koji su povezani sa M, ali na nacin
	// da je indeks vrha M < indeks vrha N

	for (auto poligon: obj.getPoligoni()) {
		auto duzina = poligon.size();
		auto prethodni_vrh = poligon[duzina-1];
		for (auto tekuci_vrh: poligon) {
			auto od_vrha = prethodni_vrh;
			auto do_vrha = tekuci_vrh;
			if (od_vrha > do_vrha)
				std::swap(od_vrha, do_vrha);

			auto v = l_duzi[od_vrha];
			if (std::find(v.begin(), v.end(), do_vrha) == v.end()) {
				l_duzi[od_vrha].push_back(do_vrha);
			}
			prethodni_vrh = tekuci_vrh;
		}
	}

	/*
	// Build the array ’connect’, where connect[i] is a
	// Vector<Integer> containing all vertex numbers j,
	// such that (i, connect[i].elementAt(j).intValue())
	// is an edge of the 3D object.
	polyList = obj.getPolyList();
	nVertices = obj.getVScr().length;
	connect = new Vector[nVertices];
	for (int i=0; i<nVertices; i++)
		connect[i] = new Vector<Integer>();
	int nFaces = polyList.size();
	for (int j = 0; j < nFaces; j++) {
		Polygon3D pol = polyList.elementAt(j);
		int[] nrs = pol.getNrs();
		int n = nrs.length;
		if (n > 2 && pol.getH() > 0)
			continue;
		int ii = Math.abs(nrs[n - 1]);
		for (int k = 0; k < n; k++) {
			int jj = nrs[k];
			if (jj < 0) jj = -jj; // abs
			else {
				int i1 = Math.min(ii, jj),
					j1 = Math.max(ii, jj);
				Integer j1Int = new Integer(j1);
				if (connect[i1].indexOf(j1Int) == -1)
					connect[i1].addElement(j1Int);
			}
			ii = jj;
		}
	}
    */
}



void TGrafika::nacrtaj_duz(
	Logicka3DTacka p, Logicka3DTacka q,
	LogickaTacka pScr, LogickaTacka qScr, int iP, int iQ, int iStart) {

	double u1 = qScr.x - pScr.x, u2 = qScr.y - pScr.y;
	double minPQx = std::min(pScr.x, qScr.x);
	double maxPQx = std::max(pScr.x, qScr.x);
	double minPQy = std::min(pScr.y, qScr.y);
	double maxPQy = std::max(pScr.y, qScr.y);
	double zP = p.z, zQ = q.z; // p and q give eye-coordinates
	double minPQz = std::min(zP, zQ);

	auto e = l_o_tacke;
	auto vScr = l_e_tacke;
	for (int i = iStart; i < l_broj_trouglova; i++) {
		if (iP == 3 && iQ == 4 && i == 0) {
            ShowMessage("Pauza");
		}

		Logicki3DTrougao t = l_tr[i];
		int iA = std::abs(t.A.index);
		int iB = std::abs(t.B.index);
		int iC = std::abs(t.C.index);
		LogickaTacka aScr = vScr[iA], bScr = vScr[iB], cScr = vScr[iC];

		// 1. Minimax test za x i y ekranske koordinate:
		if ((maxPQx <= aScr.x && maxPQx <= bScr.x && maxPQx <= cScr.x) ||
			(minPQx >= aScr.x && minPQx >= bScr.x && minPQx >= cScr.x) ||
			(maxPQy <= aScr.y && maxPQy <= bScr.y && maxPQy <= cScr.y) ||
			(minPQy >= aScr.y && minPQy >= bScr.y && minPQy >= cScr.y))
			continue; // trougao ne sakriva PQ.

		// 2. Test ako je PQ ivica trougla ABC:
		if ((iP == iA || iP == iB || iP == iC) &&
			(iQ == iA || iQ == iB || iQ == iC))
			continue; // trougao ne sakriva PQ.

		// 3. Test ako je PQ blize od ABC:
		double zA = e[iA].z, zB = e[iB].z, zC = e[iC].z;
		if ((minPQz >= zA) && (minPQz >= zB) && (minPQz >= zC))
			continue; // trougao ne sakriva PQ.

		// 4. da li P i Q (u 2D) leze u poluravni definiranoj
		// sa duzi AB, na strani na kojoj nije C?
		// Slicno za stranice BC i CA.
		double eps = 0.1; // Relative to numbers of pixels
		if ((povrsina2D(aScr, bScr, pScr) < eps &&
			povrsina2D(aScr, bScr, qScr) < eps) ||
			(povrsina2D(bScr, cScr, pScr) < eps &&
			povrsina2D(bScr, cScr, qScr) < eps) ||
			(povrsina2D(cScr, aScr, pScr) < eps &&
			povrsina2D(cScr, aScr, qScr) < eps))
			continue; // trougao ne sakriva PQ.

		// 5. Test (2D) ako A, B i C leze sa iste strane
		// prave koja prolazi kroz P i Q:
		bool pqa = povrsina2D(pScr, qScr, aScr) > -eps;
		bool pqb = povrsina2D(pScr, qScr, bScr) > -eps;
		bool pqc = povrsina2D(pScr, qScr, cScr) > -eps;
		if ((!pqa && !pqb && !pqc) ||
			(pqa && pqb && pqc))
			continue; // trougao ne sakriva PQ.

		// 6. Test ako ni P ni Q ne leze iza
		// ravni koja prolazi kroz A, B and C:
		int iPol = l_refpol[i];
		Poligon pol = l_poligoni[iPol];

		double a = pol.getKoefA(), b = pol.getKoefB(), c = pol.getKoefC(),
			h = pol.getH(), eps1 = 1e-5 * std::abs(h),
			hP = a * p.x + b * p.y + c * p.z,
			hQ = a * q.x + b * q.y + c * q.z;
		if ((hP > h - eps1) && (hQ > h - eps1))
			continue; // trougao ne sakriva PQ.

		// 7. Test ako se i P i Q nalaze unutar ABC:
		bool pUnutra = tacka_pripada_ccw_trouglu(aScr, bScr, cScr, pScr);
		bool qUnutra = tacka_pripada_ccw_trouglu(aScr, bScr, cScr, qScr);
		if (pUnutra && qUnutra)
			return; // trougao SAKRIVA PQ.

		// 8. Ako je P blize od ABC i unutra, a PQ vidljivo;
		// isto za Q:
		double h1 = h + eps1;
		if ((hP > h1 && pUnutra) || (hQ > h1 && qUnutra))
			continue; // trougao ne sakriva PQ.

		// 9. Compute the intersections I and J of PQ
		// with ABC in 2D.
		// If, in 3D, such an intersection lies in front of
		// ABC, this triangle does not obscure PQ.
		// Otherwise, the intersections lie behind ABC and
		// this triangle obscures part of PQ:
		double lambdaMin = 1.0, lambdaMax = 0.0;
		for (int ii = 0; ii < 3; ii++) {
			double v1 = bScr.x - aScr.x, v2 = bScr.y - aScr.y,
				   w1 = aScr.x - pScr.x, w2 = aScr.y - pScr.y,
				   denom = u2 * v1 - u1 * v2;
			if (denom != 0) {
				double mu = (u1 * w2 - u2 * w1) / denom;
				// mu = 0 gives A and mu = 1 gives B.
				if (mu > -0.0001 && mu < 1.0001) {
					double lambda = (v1 * w2 - v2 * w1) / denom;
					// lambda = PI/PQ
					// (I is point of intersection)
					if (lambda > -0.0001 && lambda < 1.0001) {
						if (pUnutra != qUnutra && lambda > 0.0001 && lambda < 0.9999) {
							lambdaMin = lambdaMax = lambda; break; // Only one point of intersection }
						}
					}

					if (lambda < lambdaMin) lambdaMin = lambda;
					if (lambda > lambdaMax) lambdaMax = lambda;
				}
			}
			auto temp = aScr; aScr = bScr; bScr = cScr; cScr = temp;
		}

		if (!pUnutra && lambdaMin > 0.001) {
			double iScrx = pScr.x + lambdaMin * u1,
				   iScry = pScr.y + lambdaMin * u2;
			// Back from screen to eye coordinates:
			double zI = 1 / (lambdaMin / zQ + (1 - lambdaMin) / zP),
				   xI = -zI * iScrx / e_d,
				   yI = -zI * iScry / e_d;
			if (a * xI + b * yI + c * zI > h1)
				continue; // trougao ne sakriva PQ.

			auto iScr = LogickaTacka(iScrx, iScry);
			if (udaljenost(iScr, pScr) >= 1.0)
				nacrtaj_duz(p, Logicka3DTacka(xI, yI, zI), pScr, iScr, iP, -1, i + 1);
		}
		if (!qUnutra && lambdaMax < 0.999) {
			double jScrx = pScr.x + lambdaMax * u1,
				   jScry = pScr.y + lambdaMax * u2;
			double zJ = 1 / (lambdaMax / zQ + (1 - lambdaMax) / zP),
				   xJ = -zJ * jScrx / e_d,
				   yJ = -zJ * jScry / e_d;
			if (a * xJ + b * yJ + c * zJ > h1)
				continue; // trougao ne sakriva PQ.

			auto jScr = LogickaTacka((float) jScrx, (float) jScry);
			if (udaljenost(jScr, qScr) >= 1.0)
				nacrtaj_duz(q, Logicka3DTacka(xJ, yJ, zJ), qScr, jScr, iQ, -1, i + 1);
		}
		return;
		// if no continue-statement has been executed
	}

	// No triangle obscures PQ.
	duz(pScr.x, pScr.y, qScr.x, qScr.y);
}







