Nazwa:		Pendrive Guard
Wersja:		1.1
Licencja:	Freeware (kod na licencji GPL)
Autor:		Piotr "rAum" Gródek
Wymagania:	System Windows (testowoano na XP SP2, SP3, Vista, 7)
			Pamiêæ RAM: 16 MB
			HDD: ok. 0,2 MB wolnego miejsca na dysku
			Procesor: ?
=========================
0x0:  |	Spis treœci:
-------------------------
0x1___.Krótki opis programu::..
0x2___.Geneza powstania::..
0x3___.Opis dzia³ania i funkcji programu::..
0x4___.Uwagi ró¿ne::..
=========================
0x1: Krótki opis programu
_________________________
Program s³u¿y do ochrony przeciwko wirusom/robakom itp. przenoszonym
na noœnikach wymiennych (np: pendrive) które w ostatnim czasie sta³y
siê bardzo popularne.
__________________________
0x2: Geneza powstania
__________________________
Drêczony przez infekcje roznoszone drog¹ "pendrajwow¹", zw³aszcza w 
szkole oraz nieprawid³owym/z³ym/wolnym dzia³aniem dostêpnego 
wówczas oprogramowania antywirusowego postanowi³em napisaæ w³asn¹
ma³¹ aplikacjê. Bazuje ona na takich za³o¿eniach jak:
 - prosta, porêczna, ma³a (binarna wersja po spakowaniu zajmuje ~100KB)
 - brak potrzeby instalacji (wystarczy skopiowaæ)
 - wykrywaj¹ca najpopularniejsze infekcje
 - w momencie w³o¿enia pamiêci masowej powinna wykrywaæ nawet nieznane 
	szkodniki (prosta heurystyka)
	
Obecna wersja jest "drug¹" generacj¹. Pierwsza zapewnia³a minimum
funkcjonalnoœci i s³u¿y³a do testów. Obecnie zosta³a porzucona na rzecz
drugiej, która ci¹gle znajdujê siê w gwa³townej fazie rozwojowej.
Czêœæ funkcjonalnoœci zosta³a ju¿ napisana choæ nie jest jeszcze dostêpna
dla u¿ytkowników koñcowych np: dodawanie wyj¹tków do bazy, poprawa reakcji
na infekcje itp.
___________________________
0x3: Opis dzia³ania i funckji programu
___________________________
Program nale¿y skopiowaæ na dysk (dowolny katalog) a nastêpnie uruchomiæ.
Zalecane jest zaznaczenie "Autoruchamianie" aby program ³adowa³ siê razem
z uruchomieniem systemu i dzia³a³ w trybie monitora.

W momencie w³o¿enia np: pendrive'a program dokona skanowania i poinformuje
u¿ytkownika o zlokalizowaniu infekcji. U¿ytkownik mo¿e usun¹æ lub nie 
podejrzany plik.

Przycisk "Skanuj dyski" umo¿liwia przeskanowanie dysku w celu wykrycia
kilku infekcji przy pomocy ma³ej bazy sygnatur. Lista obecnie wykrywanych i
usuwanych infekcji:
 - Wariant MS32DLL.dll.vbs (VBS.Solow, VBS.Pica.E@mm)
 - Wariant PegeFile.pif:
 - Wariant RavMonE.exe / AdobeR.exe (RJump Worm):
 - Wariant activexdebugger32.exe (Amca Worm):
 - Wariant svchost.exe (Perlovga Worm / TrojanDropper.Small.Apl)
 - Wariant ctfmon.exe (FakeRecycled)

a tak¿e wykryte w³asnorêcznie:
 - 2u.com
 - pagefile.sys.vbs
 - yew.bat
 - vva0hc0p.cmd
 - ise.exe
 - x3.exe oraz program.exe
 
 Kolejny przycisk, tj. "Dodaj ochronê" stara siê zabezpieczyæ w prosty sposób
 dyski przed niepo¿¹danym dzia³aniem wirusów w postaci instalacji plików
 autorun.inf - tworzy on folder o takiej samej nazwie jak plik który to mo¿e
 stanowiæ przeszkodê nie do przejœcia dla prostszych wirusów.
 
 Zaznaczenie opcji "Ochrona przed skryptami" spowoduje wy³¹czenie WSH (Windows
 Script Host). Jest to funkcjonalnoœc zbêdna dla 99,99% u¿ytkowników a praktycznie
 jest wykorzystywana jedynie przez twórców wirusów (patrz np: MS32DLL.dll.vbs).
 Zalecane jest wy³¹czenie WSH, czyli po prostu zaznaczenie tej opcji.
 
 Klikniêcie na krzy¿yk nie zamknie programu, ale spowoduje ¿e schowa siê on do 
 tacki systemowej (tzw. tray).
 
 W przypadku chêci zamkniêcia programu nale¿y u¿yæ w tym celu przycisku "Zamknij".
 ______________________________
 0x4: Uwagi ró¿ne
 ______________________________
 Niektóre programy antywirusowe mog¹ potraktowaæ aplikacje jako wirusa, mimo ¿e tak
 nie jest. Spowodowane jest to zastoswaniem kompresora który zmniejsza rozmiar pliku
 wykonywalnego. Aplikacja jest zatem bezpieczna.
 
 Program jest w ci¹g³ej, gwa³twonej fazie rozwoju. Dlatego mimo wielu testów mo¿liwe
 i¿ program mo¿e nie dzia³aæ prawid³owo. Szczerze przepraszam, ale iloœæ kombinacji
 bitów w ca³ym programie jest ogromna i nie sposób wszystkiego sprawdziæ dok³adnie.
 Mimo to program w czasie testów dzia³a³ poprawnie oraz stabilnie.
 
 Pendrive Guard jest programem napisanym w C++ oraz WinAPI.
 
 W przysz³ych wersjach nalezy spodziewaæ siê:
  - dodania nowych funckji
  - poprawienie dzia³ania skanera (mniej uci¹¿liwy)
  - zwiêkszenie wydajnoœci
  - u¿ywanie procesorów wielordzeniowych
  - poprawa estetyki programu (³adniejsze GUI)
  - mo¿liwoœæ aktualizacji bazy wirusów oraz programu
  - mo¿liwoœæ powstawania lokalizacji (powstanie przynajmniej wersja angielsko jêzyczna)
  
