//---------------------------------------------------------------------------

#ifndef u_unosH
#define u_unosH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TfrmUnos : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TActionList *ActionList1;
	TAction *actOtvori;
	TClientDataSet *cdsUnos;
	TIntegerField *cdsUnosod_x;
	TIntegerField *cdsUnosod_y;
	TIntegerField *cdsUnosdo_x;
	TIntegerField *cdsUnosdo_y;
	TDataSource *dsrUnos;
	TDBGrid *DBGrid1;
	TDBNavigator *DBNavigator1;
	TOpenDialog *OpenDialog1;
	TAction *actCrtaj;
	TButton *Button2;
	void __fastcall actOtvoriExecute(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall actCrtajExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmUnos(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmUnos *frmUnos;
//---------------------------------------------------------------------------
#endif
