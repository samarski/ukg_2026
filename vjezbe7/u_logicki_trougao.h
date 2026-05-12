//---------------------------------------------------------------------------

#ifndef u_logicki_trougaoH
#include "u_logicka_tacka.h"

#define u_logicki_trougaoH
//---------------------------------------------------------------------------
class LogickiTrougao {
public:
	LogickaTacka A, B, C;

	LogickiTrougao(LogickaTacka aA, LogickaTacka aB, LogickaTacka aC):
        A(aA), B(aB), C(aC) {};
};

#endif
