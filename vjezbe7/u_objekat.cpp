//---------------------------------------------------------------------------

#pragma hdrstop

#include "u_objekat.h"
#include <fstream>
#include <sstream>

//---------------------------------------------------------------------------
#pragma package(smart_init)

bool Objekat::procitaj(String fileName) {
	std::ifstream file(fileName.c_str());

	std::string jednaLinija;
	bool citam_vrhove = false;
	bool citam_poligone = false;

	while (std::getline(file, jednaLinija)) {

		if (jednaLinija == "VRHOVI") {
			citam_vrhove = true;
			citam_poligone = false;
			continue;
		}

		if (jednaLinija == "POLIGONI") {
			citam_vrhove = false;
			citam_poligone = true;
			continue;
		}

		std::stringstream inputStream(jednaLinija);
		if (citam_vrhove) {
			int index;
			float x, y, z;
			inputStream >> index;
			inputStream >> x >> y >> z;
			for (int i = vrhovi.size() + 1; i < index; i++) {
				vrhovi.push_back(Logicka3DTacka(0.0, 0.0, 0.0));
			}
			vrhovi.push_back(Logicka3DTacka(x, y, z));

		} else if (citam_poligone) {
			std::vector<int> poligon;
			int vrh;
			while (inputStream >> vrh)
				poligon.push_back(vrh);

			poligoni.push_back(poligon);
		}
	}

	return true;
}
