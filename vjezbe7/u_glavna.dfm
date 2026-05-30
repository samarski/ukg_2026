object frmGlavna: TfrmGlavna
  Left = 0
  Top = 0
  Caption = 'Glavna forma'
  ClientHeight = 369
  ClientWidth = 576
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Menu = MainMenu1
  OnCreate = FormCreate
  TextHeight = 15
  object pnlGornji: TPanel
    Left = 0
    Top = 0
    Width = 576
    Height = 113
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitWidth = 574
    object Panel1: TPanel
      Left = 391
      Top = 0
      Width = 185
      Height = 113
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      ExplicitLeft = 389
      object Button1: TButton
        Left = 64
        Top = 24
        Width = 75
        Height = 25
        Action = actTest
        TabOrder = 0
      end
    end
    object edtOkoX: TEdit
      Left = 304
      Top = 16
      Width = 121
      Height = 23
      TabOrder = 1
    end
    object edtOkoY: TEdit
      Left = 304
      Top = 45
      Width = 121
      Height = 23
      TabOrder = 2
    end
    object edtOkoZ: TEdit
      Left = 304
      Top = 72
      Width = 121
      Height = 23
      TabOrder = 3
    end
  end
  object pnlDonji: TPanel
    Left = 0
    Top = 113
    Width = 576
    Height = 256
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitWidth = 574
    ExplicitHeight = 248
    object pnlKoordinate: TPanel
      Left = 336
      Top = 0
      Width = 240
      Height = 256
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      ExplicitLeft = 334
      ExplicitHeight = 248
      object DBGrid1: TDBGrid
        Left = 0
        Top = 0
        Width = 240
        Height = 256
        Align = alClient
        DataSource = dsrTacke
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -12
        TitleFont.Name = 'Segoe UI'
        TitleFont.Style = []
        Columns = <
          item
            Expanded = False
            FieldName = 'x_koor'
            Title.Caption = 'x'
            Width = 75
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'y_koor'
            Title.Caption = 'y'
            Width = 68
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'oznaka'
            Visible = True
          end>
      end
    end
    object pnlPovrsina: TPanel
      Left = 0
      Top = 0
      Width = 336
      Height = 256
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
      ExplicitWidth = 334
      ExplicitHeight = 248
      inline Grafika1: TGrafika
        Left = 0
        Top = 0
        Width = 336
        Height = 256
        Align = alClient
        TabOrder = 0
        ExplicitWidth = 334
        ExplicitHeight = 248
        inherited img: TImage
          Width = 336
          Height = 256
          OnMouseDown = Grafika1imgMouseDown
          ExplicitLeft = -6
          ExplicitTop = 6
          ExplicitWidth = 391
          ExplicitHeight = 251
        end
      end
    end
  end
  object ActionList1: TActionList
    Left = 32
    Top = 32
    object actTest: TAction
      Caption = 'Test'
      Hint = 'Ovo je test...'
      ShortCut = 16468
      OnExecute = actTestExecute
    end
    object actOrijentacija: TAction
      Caption = 'Orijentacija'
      OnExecute = actOrijentacijaExecute
    end
    object actObrisi: TAction
      Caption = 'Obri'#353'i sve'
      OnExecute = actObrisiExecute
    end
    object actSjecenje: TAction
      Caption = 'Sje'#269'enje'
      OnExecute = actSjecenjeExecute
    end
    object actPoligon: TAction
      Caption = 'Poligon'
      OnExecute = actPoligonExecute
    end
    object actPripadnostPoligonu: TAction
      Caption = 'Pripadnost poligonu'
      OnExecute = actPripadnostPoligonuExecute
    end
    object actKonveksniOmotac: TAction
      Caption = 'Konveksni omota'#269
      OnExecute = actKonveksniOmotacExecute
    end
    object actTriangulacija: TAction
      Caption = 'Triangulacija'
      OnExecute = actTriangulacijaExecute
    end
    object act2DTest: TAction
      Category = '2D'
      Caption = '2D test'
      OnExecute = act2DTestExecute
    end
    object actRotirajLijevo: TAction
      Category = '2D'
      Caption = 'Rotiraj lijevo'
      ShortCut = 16449
      OnExecute = actRotirajLijevoExecute
    end
    object actRotirajDesno: TAction
      Category = '2D'
      Caption = 'Rotiraj desno'
      ShortCut = 16452
      OnExecute = actRotirajDesnoExecute
    end
    object act3DGraf: TAction
      Caption = '3D graf'
      OnExecute = act3DGrafExecute
    end
    object actUcitajIzFajla: TAction
      Caption = 'U'#269'itaj iz fajla'
      OnExecute = actUcitajIzFajlaExecute
    end
    object actRotirajGore: TAction
      Category = '2D'
      Caption = 'Rotiraj gore'
      ShortCut = 16471
      OnExecute = actRotirajGoreExecute
    end
    object actRotirajDolje: TAction
      Category = '2D'
      Caption = 'Rotiraj dolje'
      ShortCut = 16472
      OnExecute = actRotirajDoljeExecute
    end
    object actPriblizi: TAction
      Category = '2D'
      Caption = 'Pribli'#382'i'
      ShortCut = 16469
      OnExecute = actPribliziExecute
    end
    object actUdalji: TAction
      Category = '2D'
      Caption = 'Udalji'
      ShortCut = 16457
      OnExecute = actUdaljiExecute
    end
  end
  object cdsTacke: TClientDataSet
    Aggregates = <>
    FieldDefs = <
      item
        Name = 'x_koor'
        DataType = ftFloat
      end
      item
        Name = 'y_koor'
        DataType = ftFloat
      end
      item
        Name = 'oznaka'
        DataType = ftString
        Size = 20
      end>
    IndexDefs = <>
    Params = <>
    StoreDefs = True
    Left = 431
    Top = 305
    object cdsTackex_koor: TFloatField
      FieldName = 'x_koor'
    end
    object cdsTackey_koor: TFloatField
      FieldName = 'y_koor'
    end
    object cdsTackeoznaka: TStringField
      FieldName = 'oznaka'
    end
  end
  object dsrTacke: TDataSource
    DataSet = cdsTacke
    Left = 503
    Top = 305
  end
  object MainMenu1: TMainMenu
    Left = 120
    Top = 32
    object estovi1: TMenuItem
      Caption = 'Testovi'
      object Orijentacija1: TMenuItem
        Action = actOrijentacija
      end
      object Sjeenje1: TMenuItem
        Action = actSjecenje
      end
      object Poligin1: TMenuItem
        Action = actPoligon
      end
      object Pripadnostpoligonu1: TMenuItem
        Action = actPripadnostPoligonu
      end
      object Konveksniomota1: TMenuItem
        Action = actKonveksniOmotac
      end
      object rijangulacija1: TMenuItem
        Action = actTriangulacija
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Obriisve1: TMenuItem
        Action = actObrisi
      end
    end
    object Grafika2: TMenuItem
      Caption = 'Grafika'
      object Grafika3: TMenuItem
        Action = act2DTest
      end
      object N3Dgraf1: TMenuItem
        Action = act3DGraf
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Uitajizfajla1: TMenuItem
        Action = actUcitajIzFajla
      end
    end
  end
end
