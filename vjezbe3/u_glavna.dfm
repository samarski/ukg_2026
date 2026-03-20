object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 364
  ClientWidth = 576
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object pnlGornji: TPanel
    Left = 0
    Top = 0
    Width = 576
    Height = 113
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitTop = -6
    object Panel1: TPanel
      Left = 391
      Top = 0
      Width = 185
      Height = 113
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      ExplicitLeft = 376
      ExplicitTop = 36
      ExplicitHeight = 41
      object Button1: TButton
        Left = 64
        Top = 24
        Width = 75
        Height = 25
        Action = actTest
        TabOrder = 0
      end
    end
  end
  object pnlDonji: TPanel
    Left = 0
    Top = 113
    Width = 576
    Height = 251
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitLeft = 264
    ExplicitTop = 232
    ExplicitWidth = 185
    ExplicitHeight = 41
    object pnlKoordinate: TPanel
      Left = 391
      Top = 0
      Width = 185
      Height = 251
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      ExplicitLeft = 367
      ExplicitTop = 88
      ExplicitHeight = 41
    end
    object pnlPovrsina: TPanel
      Left = 0
      Top = 0
      Width = 391
      Height = 251
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
      ExplicitLeft = -6
      inline Grafika1: TGrafika
        Left = 0
        Top = 0
        Width = 391
        Height = 251
        Align = alClient
        TabOrder = 0
        ExplicitLeft = -105
        ExplicitTop = -134
        inherited img: TImage
          Width = 391
          Height = 251
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
  end
end
