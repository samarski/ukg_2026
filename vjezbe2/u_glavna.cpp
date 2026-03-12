//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "u_glavna.h"
#include "u_unos.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmGlavna *frmGlavna;
//---------------------------------------------------------------------------
__fastcall TfrmGlavna::TfrmGlavna(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmGlavna::actUnosExecute(TObject *Sender)
{
//
    frmUnos->Show();
}
//---------------------------------------------------------------------------

