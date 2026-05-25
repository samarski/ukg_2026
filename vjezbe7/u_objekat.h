//---------------------------------------------------------------------------

#ifndef u_objekatH
#define u_objekatH

#include <vector>
#include "u_logicka_3d_tacka.h"

//---------------------------------------------------------------------------
class Objekat {
public:
	std::vector<Logicka3DTacka> vrhovi;
	std::vector<std::vector<int>> poligoni;

	Objekat() {};

    bool procitaj(String fileName);

};
#endif
