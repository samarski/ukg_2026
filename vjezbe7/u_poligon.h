//---------------------------------------------------------------------------

#ifndef u_poligonH
#define u_poligonH

#include "u_logicka_3d_tacka.h"
#include "u_logicki_3d_trougao.h"
#include <vector>
//---------------------------------------------------------------------------
class Poligon {
private:
	std::vector<Logicka3DTacka> tacke;
	float koef_a, koef_b, koef_c, h;
    std::vector<Logicki3DTrougao> trouglovi;

public:
	Poligon() {};
	Poligon(std::vector<Logicka3DTacka> aTacke):
		tacke(aTacke) {};

	inline float getKoefA() { return koef_a; }
	inline float getKoefB() { return koef_b; }
	inline float getKoefC() { return koef_c; }
	inline float getH() { return h; }

	inline size_t broj_vrhova() { return tacke.size(); }

    inline std::vector<Logicka3DTacka> getTacke() { return tacke; }

	void trianguliraj();

	inline std::vector<Logicki3DTrougao> getTrouglovi() { return trouglovi; }

	void postaviKoefABCh(float aKoefA, float aKoefB, float aKoefC, float aH) {
		koef_a = aKoefA;
		koef_b = aKoefB;
		koef_c = aKoefC;
        h = aH;
    }
};
#endif
