//---------------------------------------------------------------------------

#ifndef u_logicki_3d_trougaoH
#define u_logicki_3d_trougaoH
//---------------------------------------------------------------------------
#include "u_logicka_3d_tacka.h"

class Logicki3DTrougao {
public:
	Logicka3DTacka A, B, C;
    int pol_index;
	Logicki3DTrougao(Logicka3DTacka& aA, Logicka3DTacka& aB, Logicka3DTacka& aC):
        A(aA), B(aB), C(aC) {};
};
#endif
