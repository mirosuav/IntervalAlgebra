object WstawFrm: TWstawFrm
  Left = 252
  Top = 183
  BorderStyle = bsToolWindow
  Caption = 'IntComp - Wstaw macierz'
  ClientHeight = 395
  ClientWidth = 665
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object pnlHead: TPanel
    Left = 0
    Top = 0
    Width = 665
    Height = 89
    Align = alTop
    TabOrder = 0
    object gbRozmiary: TGroupBox
      Left = 8
      Top = 0
      Width = 105
      Height = 81
      Caption = 'Ustal wymiary'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object Label1: TLabel
        Left = 48
        Top = 24
        Width = 8
        Height = 13
        Caption = 'X'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Verdana'
        Font.Style = []
        ParentFont = False
      end
      object btnGeneruj: TButton
        Left = 8
        Top = 48
        Width = 89
        Height = 25
        Caption = 'Generuj'
        TabOrder = 0
        OnClick = btnGenerujClick
      end
      object edtRows: TCSpinEdit
        Left = 8
        Top = 18
        Width = 37
        Height = 22
        MaxValue = 10
        MinValue = 1
        TabOrder = 1
        Value = 2
      end
      object edtCols: TCSpinEdit
        Left = 61
        Top = 18
        Width = 37
        Height = 22
        MaxValue = 10
        MinValue = 1
        TabOrder = 2
        Value = 2
      end
    end
    object gbPredef: TGroupBox
      Left = 312
      Top = 0
      Width = 345
      Height = 81
      Caption = 'Predefiniowane macierze'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      object lblRozmiar: TLabel
        Left = 8
        Top = 24
        Width = 52
        Height = 13
        Caption = 'Rozmiar:'
      end
      object btnBoothroyd: TBitBtn
        Left = 72
        Top = 16
        Width = 129
        Height = 25
        Hint = 'Macierz Boothroyda - Dekkera.'
        Caption = 'Boothroyd Dekker'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnClick = btnBoothroydClick
      end
      object btnMatrixOne: TBitBtn
        Left = 72
        Top = 48
        Width = 129
        Height = 25
        Hint = 'Macierz: 1/(i+j-1)'
        Caption = 'Hilberta'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = btnMatrixOneClick
      end
      object edtPredefSize: TCSpinEdit
        Left = 8
        Top = 44
        Width = 49
        Height = 22
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Verdana'
        Font.Style = []
        MaxValue = 10
        MinValue = 1
        ParentFont = False
        TabOrder = 2
        Value = 2
      end
      object btnnone: TBitBtn
        Left = 208
        Top = 16
        Width = 129
        Height = 25
        Hint = 'Macierz Boothroyda - Dekkera.'
        Caption = '--------'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
      end
      object BitBtn2: TBitBtn
        Left = 208
        Top = 48
        Width = 129
        Height = 25
        Hint = 'Macierz Boothroyda - Dekkera.'
        Caption = '--------'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 4
      end
    end
    object gbGenerated: TGroupBox
      Left = 120
      Top = 0
      Width = 185
      Height = 81
      Caption = 'Generuj a[i,j]'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Verdana'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      object edtCommand: TEdit
        Left = 8
        Top = 24
        Width = 169
        Height = 21
        Hint = 
          'Wstaw dowolne wyra'#380'enie matematyczne. Dozwolone zmienne: i - num' +
          'er wiersza, j - numer kolumny'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        Text = 'i/(j+1)'
        OnKeyDown = edtCommandKeyDown
      end
      object btnGenaij: TButton
        Left = 88
        Top = 48
        Width = 81
        Height = 25
        Caption = 'Generuj'
        TabOrder = 1
        OnClick = btnGenaijClick
      end
    end
  end
  object pnlMain: TPanel
    Left = 0
    Top = 89
    Width = 665
    Height = 265
    Align = alClient
    TabOrder = 1
  end
  object pnlFoot: TPanel
    Left = 0
    Top = 354
    Width = 665
    Height = 41
    Align = alBottom
    TabOrder = 2
    object btnOk: TButton
      Left = 576
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Ok'
      TabOrder = 0
      OnClick = btnOkClick
    end
    object btnAnuluj: TButton
      Left = 496
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Anuluj'
      TabOrder = 1
      OnClick = btnAnulujClick
    end
  end
end
