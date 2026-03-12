object frmUnos: TfrmUnos
  Left = 0
  Top = 0
  Caption = 'Unos podataka'
  ClientHeight = 353
  ClientWidth = 436
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnCreate = FormCreate
  TextHeight = 15
  object Button1: TButton
    Left = 296
    Top = 24
    Width = 107
    Height = 25
    Action = actOtvori
    TabOrder = 0
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 119
    Width = 436
    Height = 234
    Align = alBottom
    DataSource = dsrUnos
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -12
    TitleFont.Name = 'Segoe UI'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'od_x'
        Title.Caption = 'X1'
        Width = 79
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'od_y'
        Title.Caption = 'Y1'
        Width = 87
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'do_x'
        Title.Caption = 'X2'
        Width = 86
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'do_y'
        Title.Caption = 'Y2'
        Width = 105
        Visible = True
      end>
  end
  object DBNavigator1: TDBNavigator
    Left = 0
    Top = 88
    Width = 240
    Height = 25
    DataSource = dsrUnos
    TabOrder = 2
  end
  object Button2: TButton
    Left = 296
    Top = 64
    Width = 107
    Height = 25
    Action = actCrtaj
    TabOrder = 3
  end
  object ActionList1: TActionList
    Left = 40
    Top = 24
    object actOtvori: TAction
      Caption = 'Otvori fajl'
      OnExecute = actOtvoriExecute
    end
    object actCrtaj: TAction
      Caption = 'Crtaj'
      OnExecute = actCrtajExecute
    end
  end
  object cdsUnos: TClientDataSet
    Aggregates = <>
    FieldDefs = <
      item
        Name = 'od_x'
        DataType = ftInteger
      end
      item
        Name = 'od_y'
        DataType = ftInteger
      end
      item
        Name = 'do_x'
        DataType = ftInteger
      end
      item
        Name = 'do_y'
        DataType = ftInteger
      end>
    IndexDefs = <>
    Params = <>
    StoreDefs = True
    Left = 128
    Top = 24
    object cdsUnosod_x: TIntegerField
      FieldName = 'od_x'
    end
    object cdsUnosod_y: TIntegerField
      FieldName = 'od_y'
    end
    object cdsUnosdo_x: TIntegerField
      FieldName = 'do_x'
    end
    object cdsUnosdo_y: TIntegerField
      FieldName = 'do_y'
    end
  end
  object dsrUnos: TDataSource
    DataSet = cdsUnos
    Left = 216
    Top = 24
  end
  object OpenDialog1: TOpenDialog
    Filter = 'CSV files|*.csv|TXT files|*.txt'
    InitialDir = 'C:\UKG_2026\vjezbe2'
    Title = 'Odaberite fajl za unos'
    Left = 392
    Top = 96
  end
end
