//---------------------------------------------------------------------------

#pragma hdrstop

#include "u_poligon.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void Poligon::trianguliraj() {
    // TODO:
	if (tacke.size() > 2) {
		trouglovi.clear();
		trouglovi.push_back(Logicki3DTrougao(tacke[0], tacke[1], tacke[2]));

		if (tacke.size() > 3) {
			trouglovi.push_back(Logicki3DTrougao(tacke[0], tacke[2], tacke[3]));
		}
	}
}
