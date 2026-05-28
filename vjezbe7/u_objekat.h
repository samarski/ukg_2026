//---------------------------------------------------------------------------

#ifndef u_objekatH
#define u_objekatH

#include <vector>
#include "u_logicka_3d_tacka.h"

//---------------------------------------------------------------------------
class Objekat {
private:
	std::vector<Logicka3DTacka> vrhovi;
	std::vector<std::vector<int>> poligoni;
public:
	Objekat() {};

	bool procitaj(String fileName);
	void saznaj_velicinu_i_centar(float& v, Logicka3DTacka& centar);

	inline std::vector<Logicka3DTacka> getVrhovi() { return vrhovi; }
    inline std::vector<std::vector<int>> getPoligoni() { return poligoni; }
};
#endif
