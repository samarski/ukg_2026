//---------------------------------------------------------------------------

#ifndef u_logicka_3d_tackaH
#define u_logicka_3d_tackaH
//---------------------------------------------------------------------------
class Logicka3DTacka {
public:
	float x, y, z;
	int index;

	Logicka3DTacka(): x(0.0), y(0.0), z(0.0), index(0) {};

	Logicka3DTacka(float aX, float aY, float aZ):
		x(aX), y(aY), z(aZ), index(0) {};

	Logicka3DTacka(float aX, float aY, float aZ, int aIndex):
		x(aX), y(aY), z(aZ), index(aIndex) {};

	Logicka3DTacka operator-() const {
        return Logicka3DTacka(-x, -y, -z);
    }
};
#endif
