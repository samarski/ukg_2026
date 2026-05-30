//---------------------------------------------------------------------------

#ifndef U_GrafikaH
#define U_GrafikaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include <vector>
#include <unordered_map>
#include "u_logicka_tacka.h"
#include "u_logicki_trougao.h"
#include "u_logicka_3d_tacka.h"
#include "u_objekat.h"
#include "u_poligon.h"

enum class TVrstaPrikaza {
	iso3D,
    perspektiva
};

class TGrafika : public TFrame
{
__published:	// IDE-managed Components
	TImage *img;
	void __fastcall FrameResize(TObject *Sender);
private:	// User declarations
	int centar_x, centar_y;

	float alfa_2d;
	float skaliraj_x;
	float skaliraj_y;

	TVrstaPrikaza vrsta_prikaza;
    Logicka3DTacka oko;

public:		// User declarations
	__fastcall TGrafika(TComponent* Owner);

	// X i Y su fizicke koordinate
	// x i y su logicke koordinate
	inline float fx(const int X) {
		return (X - centar_x);
	}

	inline float fy(const int Y) {
		return (centar_y - Y);
	}

	void postavi_centar(const int cx, const int cy) {
		centar_x = cx;
        centar_y = cy;
	}

	void postavi_oko(Logicka3DTacka E) {
        oko = E;
    }

	inline int iX(const float x) {
		return centar_x + x;
	}
	inline int iY(const float y) {
        return centar_y - y;
	}

	void podesi(
		float aAlfa2D,
		float aSkalirajX,
		float aSkalirajY);

    float getAlfa2D() { return alfa_2d; };

	void tacka(float x, float y);
	void duz(float x1, float y1, float x2, float y2);
	void trougao(float x1, float y1, float x2, float y2,
		float x3, float y3);
	void trougao_u_boji(float x1, float y1, float x2, float y2,
		float x3, float y3, TColor boja);

	void ispisi(float x, float y, String tekst);
	void obrisi();

	void poligon(std::vector<LogickaTacka>& tacke);

	bool pozitivna_orijentacija(
		LogickaTacka p1,
		LogickaTacka p2,
		LogickaTacka p3);

	float povrsina2D(
		LogickaTacka p1,
		LogickaTacka p2,
		LogickaTacka p3);

	bool tacka_pripada_ccw_trouglu(
		LogickaTacka A,
		LogickaTacka B,
		LogickaTacka C,
		LogickaTacka P);

	bool duzi_se_sijeku(
		LogickaTacka a,
		LogickaTacka b,
		LogickaTacka c,
		LogickaTacka d);

	float udaljenost(LogickaTacka a, LogickaTacka b);

	std::vector<LogickaTacka> prost_poligon(std::vector<LogickaTacka>& arg_tacke);

	bool tacka_u_poligonu(std::vector<LogickaTacka>& tacke, LogickaTacka& p);

	std::vector<LogickaTacka> konveksni_omotac(std::vector<LogickaTacka>& arg_tacke);

    std::vector<LogickiTrougao> triangulacija(std::vector<LogickaTacka>& arg_tacke);

	// 3D grafika

	void duz(Logicka3DTacka A, Logicka3DTacka B);
	void poligon(std::vector<Logicka3DTacka>& tacke);

	LogickaTacka iso_3d_u_2d(Logicka3DTacka P);
	LogickaTacka persp_u_2d(Logicka3DTacka P);
	LogickaTacka trid_u_dvad(Logicka3DTacka P);

	// 3D crtanje sa sakrivanjem linija
private:
	std::vector<Logicka3DTacka> l_tacke;
	std::vector<Logicka3DTacka> l_o_tacke; // koordinate iz "oka"
	std::vector<LogickaTacka> l_e_tacke; // koordinate taèaka na ekranu
	std::vector<Poligon> l_poligoni;

    // hash lista duzi koje je potrebno prikazati
	std::unordered_map<int, std::vector<int>> l_duzi;

	int l_broj_trouglova;
	std::vector<Logicki3DTrougao> l_tr;
	std::vector<int> l_refpol;

	float e_v11, e_v12, e_v13;
	float e_v21, e_v22, e_v23;
	float e_v32, e_v33, e_v43;

	float e_rho_min, e_rho_max;
	float e_d;

	float l_vel;

    bool l_podesi_dimenzije_ekrana;

	void l_napravi_skup_duzi(Objekat& obj);
    void l_napravi_skup_poligona(Objekat& obj);
	void l_init_persp();
	void l_saznaj_koordinate();
	void l_saznaj_abch_za_poligone();
    void l_trianguliraj();

	void nacrtaj_duz(
		Logicka3DTacka p, Logicka3DTacka q,
		LogickaTacka pScr, LogickaTacka qScr,
		int iP, int iQ, int iStart);

private:
    TColor p_vrati_boju(const int idx);

public:
	// privremeno
	float e_rho, e_theta, e_phi;

	void postavi_objekat(Objekat& obj);
	void nacrtaj_objekat();
    void oboji_objekat();
};
//---------------------------------------------------------------------------
extern PACKAGE TGrafika *Grafika;
//---------------------------------------------------------------------------
#endif
