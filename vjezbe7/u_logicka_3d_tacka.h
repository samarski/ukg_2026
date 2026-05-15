//---------------------------------------------------------------------------

#ifndef u_logicka_3d_tackaH
#define u_logicka_3d_tackaH
//---------------------------------------------------------------------------
class Logicka3DTacka {
public:
	float x, y, z;

	Logicka3DTacka(): x(0.0), y(0.0), z(0.0) {};

	Logicka3DTacka(float aX, float aY, float aZ):
		x(aX), y(aY), z(aZ) {};

	Logicka3DTacka operator-() const {
        return Logicka3DTacka(-x, -y, -z);
    }
};
#endif
