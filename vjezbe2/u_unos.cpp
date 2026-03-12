//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "u_unos.h"
#include "u_glavna.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmUnos *frmUnos;
//---------------------------------------------------------------------------
__fastcall TfrmUnos::TfrmUnos(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmUnos::actOtvoriExecute(TObject *Sender)
{
//	auto c = frmGlavna->Image1->Canvas;
//    c->Rectangle(50, 50, 250, 250);

	if (OpenDialog1->Execute()) {
		String fn = OpenDialog1->FileName;

		TStringList* linije = new TStringList();
		linije->LoadFromFile(fn);
		for (int i = 0; i < linije->Count; i++) {
			// ShowMessage(linije->Strings[i]);

			TStringList* red = new TStringList();
			red->Delimiter = ',';
			red->DelimitedText = linije->Strings[i];

			cdsUnos->Append();
			cdsUnosod_x->Value = StrToInt(red->Strings[0]);
			cdsUnosod_y->Value = StrToInt(red->Strings[1]);
			cdsUnosdo_x->Value = StrToInt(red->Strings[2]);
			cdsUnosdo_y->Value = StrToInt(red->Strings[3]);
			cdsUnos->Post();

            delete red;
		}

        delete linije;
	}

}
//---------------------------------------------------------------------------
void __fastcall TfrmUnos::FormCreate(TObject *Sender)
{
	cdsUnos->CreateDataSet();
}
//---------------------------------------------------------------------------
void __fastcall TfrmUnos::actCrtajExecute(TObject *Sender)
{
	auto c = frmGlavna->Image1->Canvas;

	cdsUnos->First();
	while (!cdsUnos->Eof) {
		c->Rectangle(
			cdsUnosod_x->AsInteger,
			cdsUnosod_y->AsInteger,
			cdsUnosdo_x->AsInteger,
			cdsUnosdo_y->AsInteger);

		cdsUnos->Next();
    }

}
//---------------------------------------------------------------------------
