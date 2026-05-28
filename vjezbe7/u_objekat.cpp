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
				vrhovi.push_back(Logicka3DTacka(0.0, 0.0, 0.0, 0));
			}
			vrhovi.push_back(Logicka3DTacka(x, y, z, index));

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

void Objekat::saznaj_velicinu_i_centar(float& v, Logicka3DTacka& centar) {
	float x_max, y_max, z_max = -1e30;
	float x_min, y_min, z_min = +1e30;

	for (int i = 0; i < vrhovi.size(); i++) {
        auto T = vrhovi[i];
		if (T.x < x_min)
			x_min = T.x;

		if (T.x > x_max)
			x_max = T.x;

		if (T.y < y_min)
			y_min = T.y;

		if (T.y > y_max)
			y_max = T.y;

		if (T.z < z_min)
			z_min = T.z;

		if (T.z > z_max)
			z_max = T.z;
	}

	float dx = x_max - x_min, dy = y_max - y_min, dz = z_max - z_min;
	v = std::sqrt(dx * dx + dy * dy + dz * dz);

	centar.x = (x_min + x_max) / 2.0;
	centar.y = (y_min + y_max) / 2.0;
	centar.z = (z_min + z_max) / 2.0;
}
