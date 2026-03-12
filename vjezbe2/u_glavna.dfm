object frmGlavna: TfrmGlavna
  Left = 0
  Top = 0
  Caption = 'Aleksandar'
  ClientHeight = 337
  ClientWidth = 496
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Menu = MainMenu1
  TextHeight = 15
  object Image1: TImage
    Left = 0
    Top = 88
    Width = 496
    Height = 249
    Align = alBottom
  end
  object Button1: TButton
    Left = 352
    Top = 32
    Width = 75
    Height = 25
    Action = actUnos
    TabOrder = 0
  end
  object ActionList1: TActionList
    Left = 32
    Top = 24
    object actUnos: TAction
      Caption = 'Unos...'
      Hint = 'Unos podataka'
      OnExecute = actUnosExecute
    end
  end
  object MainMenu1: TMainMenu
    Left = 112
    Top = 24
    object Opcije1: TMenuItem
      Caption = 'Opcije'
      object Unos1: TMenuItem
        Action = actUnos
      end
    end
    object Drugakolona1: TMenuItem
      Caption = 'Druga kolona'
    end
    object reakolona1: TMenuItem
      Caption = 'Tre'#263'a kolona'
    end
  end
end
