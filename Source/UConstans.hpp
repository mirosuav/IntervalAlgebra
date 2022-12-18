



 AnsiString Naglowek(int langId)
 {
  if (langId==0)
  return  " -------------------------------------------------------------\n"
          "              INTCOMP - OBLICZENIA PRZEDZIA�OWE               \n"
          " -------------------------------------------------------------\n"
          " \n"
          " Miros�aw Miedziarek\n"
          " Wpisz 'help' aby uzyska� pomoc.\n"
          " -------------------------------------------------------------\n";
  else
  return  " -------------------------------------------------------------\n"
          "            INTCOMP - INTERVAL COMPUTATIONS                   \n"
          " -------------------------------------------------------------\n"
          " \n"
          " Miros�aw Miedziarek\n"
          " Type 'help' for syntax instructions.\n"
          " -------------------------------------------------------------\n";
  }


  AnsiString IntHelp(int langId)
  {
  if (langId==0)
  return
  " \n\n --------------- ARYTMETYKA PRZEDZIA�OWA -----------------\n\n"
  " WPROWADZANIE DANYCH:\n"
  " Przedzia�y musz� by� wprowadzane w nawiasach kwadratowych\n"
  " przez podanie obu granic przedzia�u, oddzielonych przecinkiem \n"
  "                             [inf,sup]\n"
  " np. [1.2,0.15e-1]\n"
  " b�d� przez podanie jednej liczby\n"
  " np. [52e-1] -> Result=[5.2,5.2]\n\n"
  " Przy czym poprawnym separatorem dziesi�tnym jest kropka \'.\'\n"
  " OPERACJE ARYTMETYCZNE:\n"
  " dodawanie                      :  [,]+[,]\n"
  " odejmowanie                    :  [,]-[,]\n"
  " mno�enie                       :  [,]*[,]\n"
  " dzielenie                      :  [,]/[,] (divisor couldn't include zero!)\n"
  " zmiana znaku                   :  -[,]\n\n"
  " FUNKCJE PRZEDZIA�OWE:\n"
  " szeroko�� przedzia�u           :  width[,]\n"
  " promien                        :  rad[,]\n"
  " srodek                         :  mid[,]\n"
  " odleg�o�� dw�ch przedzia��w    :  [,]dist[,]\n"
  " warto�� bezwzgl�dna            :  abs[,]\n"
  " pot�ga naturalna               :  [,]^[n] \n"
  " pierwiastek kwadratowy         :  sqrt[,]\n"
  " eksponent                      :  exp[,] \n"
  " logarytm naturalny             :  log[,] \n"
  " sinus                          :  sin[,] \n"
  " kosinus                        :  cos[,] \n"
  " tangens                        :  tg[,] \n"
  " kotangens                      :  ctg[,] \n\n"
  " OPERACJE NA MACIERZACH:        \n"
  " Macierze i wektory wprowadzamy wiersz po wierszu oddzielone �rednikiem \';\' :\n"
  " np. <[1.3,2][3,4.4];[5,6][6,7]>\n\n"
  " Macierz odwrotna                      :  inv<...> \n"
  " Macierz transponowana                 :  trans<...> \n"
  " Wyznacznik macierzy                   :  det<...> \n"
  " Eliminacja Gaussa                     :  gauss<...> \n"
  " El. Gaussa z wyborem w kolumnie       :  gaussp<...> \n"
  " El. Gaussa z pe�nym wyborem           :  gaussf<...> \n"
  " Rozwi�zanie uk�adu r�wnan AX=B        :  <.A.>solve<.B.> \n"
  " gdzie A musi by� macierz� kwadratow� a B wektorem. \n"
  " Rozwi�zanie uk�adu r�wnan AX=B        :  <.A.>solvef<.B.> \n"
  " z u�yciem rozk�adu gaussp \n"
  " Rozwi�zanie uk�adu r�wnan AX=B        :  <.A.>solvef<.B.> \n"
  " z u�yciem rozk�adu gaussf \n"
  " A/B  jest wykonywane za pomoc� A*inv(B) \n"
  " Norma nieskonczona macierzy           : norm<A> \n"
  " tzn. najwi�ksza z sum wierszy macierzy \n"
  " Wsp�czynnik uwarunkowania macierzy   : cond<A> \n"
  " Pozosta�e operacje elementarne s� wykonywane na poszczeg�lnych elementach macierzy\n\n"
  " Skr�ty klawiaturowe:\n"
  " CTRL+M - otwiera okno wprowadzania macierzy.\n"
  " CTRL+F - wprowadza ostatnio obliczony wynik do lini komend\n"
  " CTRL+D - wprowadza ostatni� komedn�\n\n"
  " Pytanie i sugestie: mirras@tlen.pl\n\n"
  " -------------------------------------------------------------\n\n";
  else
  return
  " \n\n ------------------- INTERVAL ARITHMETIC ---------------------\n\n"
  " TYPING VALUES:\n"
  " Intervals must be typed in following format\n"
  "           [inf,sup]\n"
  " ex. [1.2,0.15e-1]\n"
  " or typing only one number \n"
  "        ex. [0.1]   \n\n"
  " ARITHMETIC OPERATORS:\n"
  " addition       :  [,]+[,]\n"
  " subtraction    :  [,]-[,]\n"
  " multiplication :  [,]*[,]\n"
  " division       :  [,]/[,] (divisor couldn't include zero!)\n"
  " sign change    :  -[,]\n\n"
  " INTERVAL FUNCTIONS:\n"
  " width of interval              :  width[,]\n"
  " radius                         :  rad[,]\n"
  " midpoint                       :  mid[,]\n"
  " distance of two intervals      :  [,]dist[,]\n"
  " absolute value of interval     :  abs[,]\n"
  " natural power                  :  [,]^[n] \n"
  " square root                    :  sqrt[,]\n"
  " exponent                       :  exp[,] \n"
  " natural logarithm              :  log[,] \n"
  " sinus                          :  sin[,] \n"
  " cosinus                        :  cos[,] \n"
  " tangens                        :  tg[,] \n"
  " cotangens                      :  ctg[,] \n\n"
  " MATRIX OPERATIONS\n"
  " Matrices and vectors row by row separated by \';\' :\n"
  " ex. <[1][3,4];[5,6][6]>\n\n"
  " Inverse matrix                 :  inv<...> \n"
  " Transpose matrix               :  trans<...> \n"
  " Matrix determinant             :  det<...> \n"
  " Gauss elimination              :  gauss<...> \n"
  " Gauss partial elimination      :  gaussp<...> \n"
  " Gauss full elimination         :  gaussf<...> \n"
  " Solve linear equations AX=B    :  <.A.>solve<.B.> \n"
  " where A must be square matrix and B row vector \n"
  " Solve linear equations AX=B    :  <.A.>solvep<.B.> \n"
  " using part Gauss elimination method \n"
  " Solve linear equations AX=B    :  <.A.>solvef<.B.> \n"
  " using full Gauss elimination method \n"
  " A/B  uses A*inv(B) \n"
  " A*B \n"
  " Matrix infinity norm           : norm<A> \n"
  " means maximum sum of rows of matrix A \n"
  " Matrix condition factor        : cond<A> \n"
  " The rest of interval functions are performed element by element \n\n"
  " Keyboard shortcuts:\n"
  " CTRL+M - opens matrix input window.\n"
  " CTRL+F - puts the last computed result into command line.\n"
  " CTRL+D - puts the last typed command into command line.\n\n"
  " Questions & sugestions: mirras@tlen.pl\n\n"
  " -------------------------------------------------------------\n\n";
  }

  AnsiString RealHelp(int langId)
  {
   if (langId==0)
   return
  " \n\n --------------- ARYTMETYKA RZECZYWISTA -----------------\n\n"
  " WPROWADZANIE DANYCH:\n"
  " Liczby rzeczywiste musz� wy� wprowadzane w formacie\n"
  "           ddd.dddE-ddd\n"
  " np. 123.3E-3\n"
  " z kropk� '.' dziesi�tn�\n\n"
  " OPERACJE ARYTMETYCZNE:\n"
  " dodawanie                      :  (x)+(x)\n"
  " odejmowanie                    :  (x)-(x)\n"
  " mno�enie                       :  (x)*(x)\n"
  " dzielenie                      :  (x)/(x) (divisor couldn't include zero!)\n"
  " zmiana znaku                   :  -(x)\n\n"
  " FUNKCJE PRZEDZIA�OWE:\n"
  " szeroko�� przedzia�u           :  width(x)\n"
  " promien                        :  rad(x)\n"
  " srodek                         :  mid(x)\n"
  " odleg�o�� dw�ch przedzia��w    :  (x)dist(x)\n"
  " warto�� bezwzgl�dna            :  abs(x)\n"
  " pot�ga naturalna               :  (x)^[n] \n"
  " pierwiastek kwadratowy         :  sqrt(x)\n"
  " eksponent                      :  exp(x) \n"
  " logarytm naturalny             :  log(x) \n"
  " sinus                          :  sin(x) \n"
  " kosinus                        :  cos(x) \n"
  " tangens                        :  tg(x) \n"
  " kotangens                      :  ctg(x) \n\n"
  " OPERACJE NA MACIERZACH:        \n"
  " Macierze i wektory wprowadzamy wiersz po wierszu oddzielone �rednikiem \';\' :\n"
  " np. <1.3,2,4.4;5,6.3E-2,7>\n"
  " elementy wiersza oddzielamy przecinkiem\n\n"
  " Macierz odwrotna                      :  inv<...> \n"
  " Macierz transponowana                 :  trans<...> \n"
  " Wyznacznik macierzy                   :  det<...> \n"
  " Eliminacja Gaussa                     :  gauss<...> \n"
  " El. Gaussa z wyborem w kolumnie       :  gaussp<...> \n"
  " El. Gaussa z pe�nym wyborem           :  gaussf<...> \n"
  " Rozwi�zanie uk�adu r�wnan AX=B        :  <.A.>solve<.B.> \n"
  " gdzie A musi by� macierz� kwadratow� a B wektorem. \n"
  " Rozwi�zanie uk�adu r�wnan AX=B        :  <.A.>solvef<.B.> \n"
  " z u�yciem rozk�adu gaussp \n"
  " Rozwi�zanie uk�adu r�wnan AX=B        :  <.A.>solvef<.B.> \n"
  " z u�yciem rozk�adu gaussf \n"
  " A/B  jest wykonywane za pomoc� A*inv(B) \n"
  " Norma nieskonczona macierzy           : norm<A> \n"
  " tzn. najwi�ksza z sum wierszy macierzy \n"
  " Wsp�czynnik uwarunkowania macierzy   : cond<A> \n"
  " Pozosta�e operacje elementarne s� wykonywane na poszczeg�lnych elementach macierzy\n\n"
  " Skr�ty klawiaturowe:\n"
  " CTRL+M - otwiera okno wprowadzania macierzy.\n"
  " CTRL+F - wprowadza ostatnio obliczony wynik do lini komend\n"
  " CTRL+D - wprowadza ostatni� komedn�\n\n"
  " Pytanie i sugestie: mirras@tlen.pl\n\n"
  " -------------------------------------------------------------\n\n";
  else
  return
  " \n\n ---------------------- REAL RITHMETIC -----------------------\n\n"
  " TYPING VALUES:\n"
  " Real numbers must be typed in following format\n"
  "           ddd.dddE-+ddd\n"
  " ex. 123.3E-3\n\n"
  " ARITHMETIC OPERATORS:\n"
  " addition       :  a+b\n"
  " subtraction    :  a-b\n"
  " multiplication :  a*b\n"
  " division       :  a/b\n"
  " sign change    :  -a\n\n"
  " FUNCTIONS:\n"
  " absolute value                 :  abs(x)\n"
  " natural power                  :  x^n \n"
  " square root                    :  sqrt(x)\n"
  " exponent                       :  exp(x) \n"
  " natural logarithm              :  log(x) \n"
  " sinus                          :  sin(x) \n"
  " cosinus                        :  cos(x) \n"
  " tangens                        :  tg(x) \n"
  " cotangens                      :  ctg(x) \n\n"
  " MATRIX OPERATIONS\n"
  " Matrices and vectors row by row separated by \';\' :\n"
  " ex. <1.5,2.4 ; 3.4,5.6 ; 6.7,8.9>\n\n"
  " Inverse matrix                 :  inv<...> \n"
  " Transpose matrix               :  trans<...> \n"
  " Matrix determinant             :  det<...> \n"
  " Gauss elimination              :  gauss<...> \n"
  " Gauss partial elimination      :  gaussp<...> \n"
  " Gauss full elimination         :  gaussf<...> \n"
  " Solve linear equations AX=B    :  <.A.>solve<.B.> \n"
  " where A must be square matrix and B row vector \n"
  " Solve linear equations AX=B    :  <.A.>solvep<.B.> \n"
  " using part Gauss elimination method \n"
  " Solve linear equations AX=B    :  <.A.>solvef<.B.> \n"
  " using full Gauss elimination method \n"
  " A/B  uses A*inv(B) \n"
  " A*B \n"
  " Matrix infinity norm           : norm<A> \n"
  " means maximum sum of rows of matrix A \n"
  " Matrix condition factor        : cond<A> \n"
  " The rest of functions are performed element by element \n\n"
  " Keyboard shortcuts:\n"
  " CTRL+M - opens matrix input window.\n"
  " CTRL+F - puts the last computed result into command line.\n"
  " CTRL+D - puts the last typed command into command line.\n\n"
  " Questions & sugestions: mirras@tlen.pl\n\n"
  " -------------------------------------------------------------\n\n";
  }

  const AnsiString ResultPL = "Wynik";
  const AnsiString ResultEN = "Result";

  const AnsiString DimensionsPL = "Rozmiar";
  const AnsiString DimensionsEN = "Dimensions";

  const AnsiString FormatMessagePL = "Zaznacz wyra�enie do formatowania i spr�buj ponownie.";
  const AnsiString FormatMessageEN = "Select the text to format and try again.";

  const AnsiString IntCompFrm_CaptionPL = "IntComp - Obliczenia przedzia�owe";
  const AnsiString IntCompFrm_CaptionEN = "IntComp - Interval computations";

  const AnsiString mnuPlik_CaptionPL = "Plik";
  const AnsiString mnuPlik_CaptionEN = "File";

  const AnsiString mnuZapisz_CaptionPL = "Zapisz";
  const AnsiString mnuZapisz_CaptionEN = "Save";

  const AnsiString mnuWyjdz_CaptionPL = "Wyjd�";
  const AnsiString mnuWyjdz_CaptionEN = "Exit";

  const AnsiString mnuOpcje_CaptionPL = "Opcje";
  const AnsiString mnuOpcje_CaptionEN = "Options";

  const AnsiString mnuWynikiPosr_CaptionPL = "Poka� wyniki po�rednie";
  const AnsiString mnuWynikiPosr_CaptionEN = "Show temp results";

  const AnsiString mnuZaokr_CaptionPL = "Zaokr�glanie";
  const AnsiString mnuZaokr_CaptionEN = "Rounding";

  const AnsiString mnuZaokAuto_CaptionPL = "Auto";
  const AnsiString mnuZaokAuto_CaptionEN = "Auto";

  const AnsiString mnuZaokDonajbl_CaptionPL = "Do najbli�szego";
  const AnsiString mnuZaokDonajbl_CaptionEN = "To the nearest";

  const AnsiString mnuZaokrObcinaj_CaptionPL = "Obcinaj";
  const AnsiString mnuZaokrObcinaj_CaptionEN = "Truncate";

  const AnsiString mnuZaokrWDol_CaptionPL = "W d�";
  const AnsiString mnuZaokrWDol_CaptionEN = "Down";

  const AnsiString mnuZaokrWGore_CaptionPL = "W g�r�";
  const AnsiString mnuZaokrWGore_CaptionEN = "Up";

  const AnsiString mnuCzysc_CaptionPL = "Czy�� ekran";
  const AnsiString mnuCzysc_CaptionEN = "Clear screen";

  const AnsiString mnuCzcionka_CaptionPL = "Czcionka";
  const AnsiString mnuCzcionka_CaptionEN = "Font";

  const AnsiString mnuKolorTla_CaptionPL = "Kolor t�a";
  const AnsiString mnuKolorTla_CaptionEN = "Background color";

  const AnsiString mnuJezyk_CaptionPL = "J�zyk";
  const AnsiString mnuJezyk_CaptionEN = "Language";

  const AnsiString mnuPolski_CaptionPL = "Polski";
  const AnsiString mnuPolski_CaptionEN = "Polish";

  const AnsiString mnuAngielski_CaptionPL = "Angielski";
  const AnsiString mnuAngielski_CaptionEN = "English";

  const AnsiString mnuWstaw_CaptionPL = "Wstaw";
  const AnsiString mnuWstaw_CaptionEN = "Insert";

  const AnsiString mnuMacierz_CaptionPL = "Macierz";
  const AnsiString mnuMacierz_CaptionEN = "Matrix";

  const AnsiString mnuPoprzednie_CaptionPL = "Poprzednie polecenie";
  const AnsiString mnuPoprzednie_CaptionEN = "Previous command";

  const AnsiString mnuOstWynik_CaptionPL = "Ostatni wynik";
  const AnsiString mnuOstWynik_CaptionEN = "Last result";

  const AnsiString mnuFormatuj_CaptionPL = "Format";
  const AnsiString mnuFormatuj_CaptionEN = "Format";

  const AnsiString mnuNaPrzedz_CaptionPL = "Na przedzia�ow�";
  const AnsiString mnuNaPrzedz_CaptionEN = "To interval syntax";

  const AnsiString mnuNaRzecz_CaptionPL = "Na rzeczywist�";
  const AnsiString mnuNaRzecz_CaptionEN = "To real syntax";

  const AnsiString mnuFormatFormat_CaptionPL = "Precyzja";
  const AnsiString mnuFormatFormat_CaptionEN = "Precision";

  const AnsiString mnuPrecision_CaptionPL = "Format";
  const AnsiString mnuPrecision_CaptionEN = "Format";

  const AnsiString mnuFormatLong_CaptionPL = "20 cyfr";
  const AnsiString mnuFormatLong_CaptionEN = "20 digits";

  const AnsiString mnuFormatShort_CaptionPL = "5 cyfr";
  const AnsiString mnuFormatShort_CaptionEN = "5 digits";

  const AnsiString mnuPrecFloat_CaptionPL = "Zmiennopozycyjny";
  const AnsiString mnuPrecFloat_CaptionEN = "Floating-point";

  const AnsiString mnuPrecFixed_CaptionPL = "Sta�opozycyjny";
  const AnsiString mnuPrecFixed_CaptionEN = "Fixed";

  const AnsiString mnuArytmetyka_CaptionPL = "Zmie� arytmetyk�";
  const AnsiString mnuArytmetyka_CaptionEN = "Set arithmetic";

  const AnsiString mnuPrzedzialowa_CaptionPL = "Przedzia�owa";
  const AnsiString mnuPrzedzialowa_CaptionEN = "Interval";

  const AnsiString mnuRzeczywista_CaptionPL = "Rzeczywista";
  const AnsiString mnuRzeczywista_CaptionEN = "Real";

  const AnsiString mnuPomoc_CaptionPL = "Pomoc";
  const AnsiString mnuPomoc_CaptionEN = "Help";

  const AnsiString mnuOprogramie_CaptionPL = "O programie";
  const AnsiString mnuOprogramie_CaptionEN = "About";

  const AnsiString mnuPomocPomoc_CaptionPL = "Pomoc";
  const AnsiString mnuPomocPomoc_CaptionEN = "Help";


  const AnsiString WstawFrm_CaptionPL = "IntComp - Wstaw macierz";
  const AnsiString WstawFrm_CaptionEN = "IntComp - Insert matrix";

  const AnsiString btnAnuluj_CaptionPL = "Anuluj";
  const AnsiString btnAnuluj_CaptionEN = "Cancel";

  const AnsiString gbGenerated_CaptionPL = "Generuj a[i,j]";
  const AnsiString gbGenerated_CaptionEN = "Generate a[i,j]";

  const AnsiString edtCommand_HintPL = "Wstaw dowolne wyra�enie matematyczne. Dozwolone zmienne: i - numer wiersza, j - numer kolumny, m - ilo�� wierszy, n - ilo�� kolumn";
  const AnsiString edtCommand_HintEN = "Type any mathematical command. Allowed variables: i - row number, j - column number, m - row count, n - cols count";

  const AnsiString gbPredef_CaptionPL = "Predefiniowane macierze";
  const AnsiString gbPredef_CaptionEN = "Predefinied matrices";

  const AnsiString btnBoothroyd_CaptionPL = "Boothroyda Dekker";
  const AnsiString btnBoothroyd_CaptionEN = "Boothroyda Dekker";

  const AnsiString btnBoothroyd_HintPL = "Macierz Boothroyda - Dekkera.";
  const AnsiString btnBoothroyd_HintEN = "Boothroyda - Dekker matrix";

  const AnsiString btnMatrixOne_CaptionPL = "Hilberta";
  const AnsiString btnMatrixOne_CaptionEN = "Hilbert";

  const AnsiString btnMatrixOne_HintPL = "Macierz postaci: 1/(i+j-1)";
  const AnsiString btnMatrixOne_HintEN = "Matrix of type: 1/(i+j-1)";

  const AnsiString lblRozmiar_CaptionPL = "Rozmiar:";
  const AnsiString lblRozmiar_CaptionEN = "Size:";

  const AnsiString gbRozmiary_CaptionPL = "Ustal wymiary";
  const AnsiString gbRozmiary_CaptionEN = "Dimensions";

  const AnsiString btnGeneruj_CaptionPL = "Generuj";
  const AnsiString btnGeneruj_CaptionEN = "Generate";

  const AnsiString btnGenaij_CaptionPL = "Generuj";
  const AnsiString btnGenaij_CaptionEN = "Generate";


  AnsiString AboutFrm_Caption(int langId)
  {
    if (langId==0)
    return "IntComp - O programie";
    else
    return "IntComp - About";
  }

  AnsiString lblOpis_Caption(int langId)
  {
    if (langId==0)
    return "IntComp jest zaawansowanym systemem algebry przedzia�owej."
           " Umo�liwia wykonywanie oblicze� i bada� z zakresu algebry"
           " liniowej  na arytmetyce przedzia�owej i rzeczywistej.";
    else
    return "IntComp is advanced Interval algebra system."
           " It allows performing computation on linear algebra systems"
           " with use of real and interval arithmetic";
  }

  AnsiString lblCel_Caption(int langId)
  {
    if (langId==0)
    return "Program IntComp zosta� zaprojekto- wany i napisany na potrzeby pracy magisterskiej";
    else
    return "IntComp was designed and implemented as part of master thesis.";
  }




































