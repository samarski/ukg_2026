//---------------------------------------------------------------------------

#ifndef U_GrafikaH
#define U_GrafikaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
/*
  Vaše deklaracije klasa idu ovdje
*/

class TGrafika : public TFrame
{
__published:	// IDE-managed Components
	TImage *img;
	void __fastcall FrameResize(TObject *Sender);
private:	// User declarations
	int centar_x, centar_y;

public:		// User declarations
	__fastcall TGrafika(TComponent* Owner);

	// X i Y su fizicke koordinate
	// x i y su logicke koordinate
	inline float fx(const int X) {
		return (X - centar_x);
	}
	inline float fy(const int Y) {
		return (centar_y - Y);
	}
	void postavi_centar(const int cx, const int cy) {
		centar_x = cx;
        centar_y = cy;
	}

	inline int iX(const float x) {
		return centar_x + x;
	}
	inline int iY(const float y) {
        return centar_y - y;
	}

	void duz(float x1, float y1, float x2, float y2);
	void tacka(float x, float y);
	void ispisi(float x, float y, String tekst);
    void obrisi();
};
//---------------------------------------------------------------------------
extern PACKAGE TGrafika *Grafika;
//---------------------------------------------------------------------------
#endif
