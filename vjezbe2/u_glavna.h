//---------------------------------------------------------------------------

#ifndef u_glavnaH
#define u_glavnaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmGlavna : public TForm
{
__published:	// IDE-managed Components
	TActionList *ActionList1;
	TAction *actUnos;
	TButton *Button1;
	TMainMenu *MainMenu1;
	TMenuItem *Opcije1;
	TMenuItem *Drugakolona1;
	TMenuItem *reakolona1;
	TMenuItem *Unos1;
	TImage *Image1;
	void __fastcall actUnosExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmGlavna(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmGlavna *frmGlavna;
//---------------------------------------------------------------------------
#endif
