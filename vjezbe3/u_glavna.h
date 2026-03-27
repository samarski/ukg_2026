//---------------------------------------------------------------------------

#ifndef u_glavnaH
#define u_glavnaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "U_Grafika.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnlGornji;
	TPanel *pnlDonji;
	TPanel *pnlKoordinate;
	TPanel *pnlPovrsina;
	TGrafika *Grafika1;
	TPanel *Panel1;
	TButton *Button1;
	TActionList *ActionList1;
	TAction *actTest;
	TClientDataSet *cdsTacke;
	TDataSource *dsrTacke;
	TDBGrid *DBGrid1;
	TFloatField *cdsTackex_koor;
	TFloatField *cdsTackey_koor;
	TStringField *cdsTackeoznaka;
	TAction *actOrijentacija;
	TMainMenu *MainMenu1;
	TMenuItem *estovi1;
	TMenuItem *Orijentacija1;
	TAction *actObrisi;
	TMenuItem *Obriisve1;
	TAction *actSjecenje;
	TMenuItem *Sjeenje1;
	TMenuItem *N1;
	void __fastcall actTestExecute(TObject *Sender);
	void __fastcall Grafika1imgMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall actOrijentacijaExecute(TObject *Sender);
	void __fastcall actObrisiExecute(TObject *Sender);
	void __fastcall actSjecenjeExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
