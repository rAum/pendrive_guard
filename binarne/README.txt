Nazwa:		Pendrive Guard
Wersja:		1.1
Licencja:	Freeware (kod na licencji GPL)
Autor:		Piotr "rAum" Gr�dek
Wymagania:	System Windows (testowoano na XP SP2, SP3, Vista, 7)
			Pami�� RAM: 16 MB
			HDD: ok. 0,2 MB wolnego miejsca na dysku
			Procesor: ?
=========================
0x0:  |	Spis tre�ci:
-------------------------
0x1___.Kr�tki opis programu::..
0x2___.Geneza powstania::..
0x3___.Opis dzia�ania i funkcji programu::..
0x4___.Uwagi r�ne::..
=========================
0x1: Kr�tki opis programu
_________________________
Program s�u�y do ochrony przeciwko wirusom/robakom itp. przenoszonym
na no�nikach wymiennych (np: pendrive) kt�re w ostatnim czasie sta�y
si� bardzo popularne.
__________________________
0x2: Geneza powstania
__________________________
Dr�czony przez infekcje roznoszone drog� "pendrajwow�", zw�aszcza w 
szkole oraz nieprawid�owym/z�ym/wolnym dzia�aniem dost�pnego 
w�wczas oprogramowania antywirusowego postanowi�em napisa� w�asn�
ma�� aplikacj�. Bazuje ona na takich za�o�eniach jak:
 - prosta, por�czna, ma�a (binarna wersja po spakowaniu zajmuje ~100KB)
 - brak potrzeby instalacji (wystarczy skopiowa�)
 - wykrywaj�ca najpopularniejsze infekcje
 - w momencie w�o�enia pami�ci masowej powinna wykrywa� nawet nieznane 
	szkodniki (prosta heurystyka)
	
Obecna wersja jest "drug�" generacj�. Pierwsza zapewnia�a minimum
funkcjonalno�ci i s�u�y�a do test�w. Obecnie zosta�a porzucona na rzecz
drugiej, kt�ra ci�gle znajduj� si� w gwa�townej fazie rozwojowej.
Cz�� funkcjonalno�ci zosta�a ju� napisana cho� nie jest jeszcze dost�pna
dla u�ytkownik�w ko�cowych np: dodawanie wyj�tk�w do bazy, poprawa reakcji
na infekcje itp.
___________________________
0x3: Opis dzia�ania i funckji programu
___________________________
Program nale�y skopiowa� na dysk (dowolny katalog) a nast�pnie uruchomi�.
Zalecane jest zaznaczenie "Autoruchamianie" aby program �adowa� si� razem
z uruchomieniem systemu i dzia�a� w trybie monitora.

W momencie w�o�enia np: pendrive'a program dokona skanowania i poinformuje
u�ytkownika o zlokalizowaniu infekcji. U�ytkownik mo�e usun�� lub nie 
podejrzany plik.

Przycisk "Skanuj dyski" umo�liwia przeskanowanie dysku w celu wykrycia
kilku infekcji przy pomocy ma�ej bazy sygnatur. Lista obecnie wykrywanych i
usuwanych infekcji:
 - Wariant MS32DLL.dll.vbs (VBS.Solow, VBS.Pica.E@mm)
 - Wariant PegeFile.pif:
 - Wariant RavMonE.exe / AdobeR.exe (RJump Worm):
 - Wariant activexdebugger32.exe (Amca Worm):
 - Wariant svchost.exe (Perlovga Worm / TrojanDropper.Small.Apl)
 - Wariant ctfmon.exe (FakeRecycled)

a tak�e wykryte w�asnor�cznie:
 - 2u.com
 - pagefile.sys.vbs
 - yew.bat
 - vva0hc0p.cmd
 - ise.exe
 - x3.exe oraz program.exe
 
 Kolejny przycisk, tj. "Dodaj ochron�" stara si� zabezpieczy� w prosty spos�b
 dyski przed niepo��danym dzia�aniem wirus�w w postaci instalacji plik�w
 autorun.inf - tworzy on folder o takiej samej nazwie jak plik kt�ry to mo�e
 stanowi� przeszkod� nie do przej�cia dla prostszych wirus�w.
 
 Zaznaczenie opcji "Ochrona przed skryptami" spowoduje wy��czenie WSH (Windows
 Script Host). Jest to funkcjonalno�c zb�dna dla 99,99% u�ytkownik�w a praktycznie
 jest wykorzystywana jedynie przez tw�rc�w wirus�w (patrz np: MS32DLL.dll.vbs).
 Zalecane jest wy��czenie WSH, czyli po prostu zaznaczenie tej opcji.
 
 Klikni�cie na krzy�yk nie zamknie programu, ale spowoduje �e schowa si� on do 
 tacki systemowej (tzw. tray).
 
 W przypadku ch�ci zamkni�cia programu nale�y u�y� w tym celu przycisku "Zamknij".
 ______________________________
 0x4: Uwagi r�ne
 ______________________________
 Niekt�re programy antywirusowe mog� potraktowa� aplikacje jako wirusa, mimo �e tak
 nie jest. Spowodowane jest to zastoswaniem kompresora kt�ry zmniejsza rozmiar pliku
 wykonywalnego. Aplikacja jest zatem bezpieczna.
 
 Program jest w ci�g�ej, gwa�twonej fazie rozwoju. Dlatego mimo wielu test�w mo�liwe
 i� program mo�e nie dzia�a� prawid�owo. Szczerze przepraszam, ale ilo�� kombinacji
 bit�w w ca�ym programie jest ogromna i nie spos�b wszystkiego sprawdzi� dok�adnie.
 Mimo to program w czasie test�w dzia�a� poprawnie oraz stabilnie.
 
 Pendrive Guard jest programem napisanym w C++ oraz WinAPI.
 
 W przysz�ych wersjach nalezy spodziewa� si�:
  - dodania nowych funckji
  - poprawienie dzia�ania skanera (mniej uci��liwy)
  - zwi�kszenie wydajno�ci
  - u�ywanie procesor�w wielordzeniowych
  - poprawa estetyki programu (�adniejsze GUI)
  - mo�liwo�� aktualizacji bazy wirus�w oraz programu
  - mo�liwo�� powstawania lokalizacji (powstanie przynajmniej wersja angielsko j�zyczna)
  
