object frmGlavna: TfrmGlavna
  Left = 0
  Top = 0
  Caption = 'Moja prva aplikacija'
  ClientHeight = 393
  ClientWidth = 570
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
    Width = 570
    Height = 89
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitTop = -6
    DesignSize = (
      570
      89)
    object btnPravougaonik: TButton
      Left = 434
      Top = 18
      Width = 120
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Pravougaonik'
      TabOrder = 0
      OnClick = btnPravougaonikClick
    end
    object edtOdX: TEdit
      Left = 24
      Top = 19
      Width = 121
      Height = 23
      Alignment = taRightJustify
      TabOrder = 1
      Text = '0'
    end
    object edtOdY: TEdit
      Left = 24
      Top = 48
      Width = 121
      Height = 23
      Alignment = taRightJustify
      TabOrder = 2
      Text = '0'
    end
    object edtDoX: TEdit
      Left = 168
      Top = 19
      Width = 121
      Height = 23
      Alignment = taRightJustify
      TabOrder = 3
      Text = '0'
    end
    object edtDoY: TEdit
      Left = 168
      Top = 48
      Width = 121
      Height = 23
      Alignment = taRightJustify
      TabOrder = 4
      Text = '0'
    end
    object btnTacka: TButton
      Left = 434
      Top = 49
      Width = 120
      Height = 25
      Caption = 'Ta'#269'ka'
      TabOrder = 5
      OnClick = btnTackaClick
    end
  end
  object pnlSredina: TPanel
    Left = 0
    Top = 89
    Width = 570
    Height = 304
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitLeft = 232
    ExplicitTop = 240
    ExplicitWidth = 185
    ExplicitHeight = 41
    object Image1: TImage
      Left = 0
      Top = 0
      Width = 570
      Height = 304
      Align = alClient
      OnMouseDown = Image1MouseDown
      OnMouseMove = Image1MouseMove
      OnMouseUp = Image1MouseUp
      ExplicitLeft = 184
      ExplicitTop = 56
      ExplicitWidth = 105
      ExplicitHeight = 105
    end
  end
end
