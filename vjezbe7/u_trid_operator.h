//---------------------------------------------------------------------------

#ifndef u_trid_operatorH
#define u_trid_operatorH

#include "u_logicka_3d_tacka.h"

//---------------------------------------------------------------------------
class TriDOperator {
private:
	TriDOperator() {
		v11 = v12 = v13 = v14 = 0.0;
		v21 = v22 = v23 = v24 = 0.0;
		v31 = v32 = v33 = v34 = 0.0;
	}

public:
	float v11, v12, v13, v14;
	float v21, v22, v23, v24;
	float v31, v32, v33, v34;

	static TriDOperator translacija(float x, float y, float z) {
		TriDOperator T;
		T.v11 = T.v22 = T.v33 = 1.0;
		T.v14 = x;
		T.v24 = y;
		T.v34 = z;

		return T;
	}

	static TriDOperator translacija(Logicka3DTacka P) {
        return translacija(P.x, P.y, P.z);
	}

	// auto T = TriDOperator::translacija(10, 20, 30);

	static TriDOperator rotacija_oko_z(float phi) {
		TriDOperator R;
		auto aCosPhi = std::cos(phi);
		auto aSinPhi = std::sin(phi);

		R.v11 = R.v22 = aCosPhi;
		R.v12 = -aSinPhi;
		R.v21 = aSinPhi;
		R.v33 = 1.0;

		return R;
	}
	// auto R = TriDOperator::rotacija_oko_z(3.1415926 / 6);

	static TriDOperator rotacija_oko_x(float phi) {
		TriDOperator R;
		auto aCosPhi = std::cos(phi);
		auto aSinPhi = std::sin(phi);

		R.v11 = 1.0;
		R.v22 = R.v33 = aCosPhi;
		R.v23 = -aSinPhi;
		R.v32 = aSinPhi;

		return R;
	}
	// auto R = TriDOperator::rotacija_oko_z(3.1415926 / 6);

	friend TriDOperator operator*(TriDOperator A, TriDOperator B) {
		// TODO:
		TriDOperator C;
		C.v11 = A.v11 * B.v11 + A.v12 * B.v21 + A.v13 * B.v31;
		// ...

		C.v34 = A.v31 * B.v14 + A.v32 * B.v24 + A.v33 * B.v34 + A.v34;
	}


	Logicka3DTacka operator()(Logicka3DTacka P) {
		auto x = v11 * P.x + v12 * P.y + v13 * P.z + v14;
		auto y = v21 * P.x + v22 * P.y + v23 * P.z + v24;
		auto z = v31 * P.x + v32 * P.y + v33 * P.z + v34;

        return Logicka3DTacka(x, y, z);
    }

};
#endif
