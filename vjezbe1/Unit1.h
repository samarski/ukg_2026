//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmGlavna : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnlGornji;
	TPanel *pnlSredina;
	TButton *btnPravougaonik;
	TImage *Image1;
	TEdit *edtOdX;
	TEdit *edtOdY;
	TEdit *edtDoX;
	TEdit *edtDoY;
	TButton *btnTacka;
	void __fastcall btnPravougaonikClick(TObject *Sender);
	void __fastcall btnTackaClick(TObject *Sender);
	void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);

private:	// User declarations
    bool PritisnutMis;
public:		// User declarations
	__fastcall TfrmGlavna(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmGlavna *frmGlavna;
//---------------------------------------------------------------------------
#endif
