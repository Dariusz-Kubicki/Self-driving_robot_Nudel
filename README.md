# Self-driving_robot_Nudel

**Nudel** to mój pierwszy projekt robotyczny: czterokołowy robot mobilny budowany na bazie zestawu z AliExpress i rozwijany jako line follower. Jego pierwszym zadaniem jest samodzielne poruszanie się po czarnej linii przy użyciu czterech cyfrowych czujników podczerwieni.

Projekt nadal jest rozwijany. Robot poprawnie uruchamia napęd i reaguje na czujniki, ale algorytm oraz wartości PWM wymagają dalszego strojenia na większym torze z łagodniejszymi zakrętami.

## Aktualny stan projektu

- podwozie 4WD zostało złożone i okablowane;
- pierwotny sterownik L293D został zastąpiony modułem DRV8833;
- zamontowano wydrukowaną podstawkę Arduino i dystanse czujników IR;
- koszyk 4×AA został zastąpiony koszykiem 6×AA;
- Arduino otrzymało osobne zasilanie 9 V przez gniazdo DC;
- dodano kondensatory ograniczające zakłócenia zasilania;
- powstała plansza testowa z 12 połączonych kartek A4;
- działa podstawowy program reagujący na cztery czujniki IR;
- trwają testy prędkości i zachowania robota na zakrętach.

Najbliższy test zostanie wykonany na dużym, łagodnym okręgu. Obecny tor ma zbyt ciasne zakręty dla długiego podwozia 4WD, które podczas skręcania musi pokonać duże tarcie boczne czterech opon.

## Cel projektu

Celem projektu jest praktyczna nauka podstaw robotyki i zbudowanie pierwszego autonomicznego pojazdu. Podczas pracy uczę się:

- sterowania silnikami DC za pomocą mostka H;
- generowania sygnału PWM i doboru prędkości silników;
- konfiguracji oraz kalibracji cyfrowych czujników IR;
- projektowania algorytmu line followera;
- diagnozowania spadków napięcia, zakłóceń i resetów mikrokontrolera;
- lutowania, prowadzenia przewodów i prototypowania;
- projektowania prostych elementów mechanicznych do druku 3D;
- dokumentowania kolejnych wersji konstrukcji i kodu.

W przyszłości planuję rozbudować Nudla o czujnik odległości HC-SR04, serwomechanizm SG90, a w dalszej perspektywie również kamerę.

### Skąd nazwa „Nudel”?

Nazwa robota upamiętnia mojego pierwszego kota, który wabił się Nudel. Uznałem, że będzie to dobre imię dla mojego debiutanckiego projektu robotycznego.

## Elementy projektu

Podstawą konstrukcji jest [zestaw z AliExpress](https://pl.aliexpress.com/item/1005002223616703.html), który został przeze mnie zmodyfikowany.

### Elementy pochodzące z zestawu

- klon Arduino UNO R3;
- cztery czujniki IR;
- płytka z komparatorami i potencjometrami do regulacji czujników;
- cztery silniki DC z przekładniami TT;
- czujnik ultradźwiękowy HC-SR04;
- serwomechanizm SG90;
- nakładka Arduino UNO Sensor Shield V5.0;
- akrylowe podwozie, koła i elementy montażowe;
- pierwotny koszyk na cztery baterie AA.

### Elementy dodane lub zmienione

- dwukanałowy sterownik silników DRV8833;
- koszyk na sześć baterii AA;
- osobne źródło 9 V dla Arduino;
- kondensatory filtrujące zasilanie;
- wydrukowana podstawka pod Arduino;
- wydrukowane dystanse obniżające czujniki IR;
- nowe przewody i poprawione połączenia lutowane.

## Druk 3D

Drukarkę 3D kupiłem już w trakcie budowy robota. Wykorzystałem ją do wykonania elementów dopasowanych do tej konstrukcji:

- [podstawka pod Arduino](Ard.stl);
- [dystanse do czujników IR](dystanse_do_sensorow.stl).

Podstawka porządkuje montaż elektroniki, a dystanse umieszczają czujniki bliżej podłoża. Zbyt duża odległość od planszy powodowała niestabilne wykrywanie czarnej taśmy.

Elementy drukowane nie są niezbędne. Arduino można przykręcić bezpośrednio do podwozia lub zastosować gotowy uchwyt, a wysokość czujników ustawić za pomocą zwykłych dystansów montażowych.

## Zasilanie

Napęd i elektronika korzystają obecnie z oddzielnych źródeł zasilania:

```text
6×AA ───────────────> zasilanie silników przez DRV8833

9 V przez gniazdo DC ─> Arduino UNO i układ sterujący

GND Arduino ─────────> GND DRV8833
```

Wspólna masa jest potrzebna, aby sygnały sterujące z Arduino miały prawidłowy poziom odniesienia.

Rozdzielenie zasilania rozwiązało problem resetowania Arduino podczas jednoczesnego uruchamiania silników. Wcześniej impuls prądowy napędu powodował spadek napięcia całego układu. Zwiększenie samej liczby baterii nie wystarczyło, ponieważ problem dotyczył także wydajności prądowej i wspólnej linii zasilania.

## Połączenia z Arduino

Aktualny program korzysta z następujących pinów:

| Element | Pin Arduino |
|---|---:|
| Lewy czujnik IR | 8 |
| Środkowy lewy czujnik IR | 7 |
| Środkowy prawy czujnik IR | 4 |
| Prawy czujnik IR | 2 |
| DRV8833 — LIN1 | 5 |
| DRV8833 — LIN2 | 3 |
| DRV8833 — RIN1 | 9 |
| DRV8833 — RIN2 | 6 |

Wszystkie cztery wejścia sterownika silników podłączono do pinów obsługujących PWM w Arduino UNO. Dzięki temu program może regulować prędkość obu stron napędu oraz zmieniać ich kierunek.

## Oprogramowanie

Aktualny kod znajduje się w pliku [Robot_Nudel.ino](Robot_Nudel.ino).

Program:

1. odczytuje stany czterech czujników IR;
2. wybiera jazdę prosto, lekką korektę, mocny skręt albo zatrzymanie;
3. steruje lewą i prawą stroną napędu przez DRV8833;
4. podczas mocnego skrętu może napędzać obie strony w przeciwnych kierunkach, aby zmniejszyć promień obrotu.

Aktualne wartości PWM są eksperymentalne. Po ustabilizowaniu zasilania silniki zaczęły pracować znacznie pewniej, dlatego wcześniejsze ustawienia prędkości trzeba było dobrać ponownie.

### Ważna uwaga dotycząca czujników

Stan logiczny czujnika zależy od ustawienia komparatorów i zastosowanego modułu. Przed dalszym strojeniem programu trzeba jednoznacznie sprawdzić w monitorze portu szeregowego, jaki stan (`LOW` lub `HIGH`) odpowiada czarnej taśmie, a jaki białemu podłożu. Kod i opis tej logiki powinny być ze sobą zgodne.

## Proces budowy

### 1. Złożenie podwozia

Prace rozpocząłem od zamontowania przekładni TT, silników, kół i czujników IR.

Z podwoziem wiąże się zabawna historia. Dopiero po pełnym złożeniu konstrukcji zorientowałem się, że akryl jest przezroczysty. Wcześniej uznałem brązową folię ochronną za docelowy kolor materiału, dlatego musiałem rozmontować całość, aby ją usunąć.

Podczas pierwszego montażu pominąłem także gumowe elementy zabezpieczające silniki. Założyłem je później pęsetą na niemal ukończonym robocie. Konstrukcja i tak została następnie ponownie rozebrana podczas wymiany sterownika silników.

### 2. Montaż czujników

Czujniki zamontowane bezpośrednio przy podwoziu znajdowały się zbyt wysoko nad planszą. Zaprojektowałem więc dystanse, które obniżyły moduły i poprawiły powtarzalność odczytów.

Podczas wykonywania otworów dwukrotnie uszkodziłem akrylowe podwozie. Pęknięcia udało się skleić, ale ten etap pokazał, że akryl wymaga ostrożnej obróbki. Najbezpieczniej wiercić na małych obrotach, podeprzeć materiał, zacząć od niewielkiego otworu prowadzącego i stopniowo zwiększać średnicę. Silne podgrzewanie może odkształcić lub uszkodzić tworzywo.

### 3. Montaż elektroniki

Pierwsza wersja powstała bez wcześniejszego prototypu. Elementy były od razu lutowane i montowane na docelowym podwoziu. Utrudniło to znalezienie błędów oraz wymusiło kilkukrotne rozbieranie robota.

Po wymianie przewodów, sterownika silników i sposobu zasilania połączenia zaczęły działać stabilniej.

### 4. Budowa toru testowego

Do testów powstała duża plansza z 12 kartek A4 ułożonych w prostokąt i połączonych ze sobą. Trasę wykonano z czarnej taśmy izolacyjnej.

Pierwszy tor zawierał zakręty zbyt ciasne dla obecnej konstrukcji. Czterokołowe podwozie jest długie, a podczas skręcania wszystkie koła pozostają ustawione równolegle, przez co opony muszą częściowo ślizgać się po podłożu. Kolejna trasa będzie miała kształt dużego, łagodnego okręgu.

## Napotkane problemy

### 1. Brak odpowiedniego sterownika silników

W zestawie nie znalazł się sterownik napędu. Pierwsza wersja robota korzystała więc z układu L293D pochodzącego z zestawu kursu Arduino Forbota.

L293D powodował duży spadek napięcia na wyjściach i nie radził sobie dobrze z czterema silnikami TT połączonymi parami. Robot poruszał się bardzo wolno i nie miał wystarczającego momentu do skręcania. Przy lekkim napędzie 2WD układ mógłby działać, ale zależy to od poboru prądu konkretnych silników, szczególnie podczas rozruchu i zablokowania wału.

**Rozwiązanie:** L293D został zastąpiony modułem DRV8833, który ma mniejsze straty napięcia i lepiej nadaje się do sterowania tym napędem.

### 2. Słabe i zbyt krótkie przewody

Pierwsze przewody pochodziły z taniego zestawu. Źle znosiły lutowanie, a ich końce łatwo się uszkadzały. Część odcinków została także przycięta bez odpowiedniego zapasu, przez co po montażu były naprężone i odrywały się od połączeń.

**Rozwiązanie:** zastosowanie lepszych przewodów, pozostawienie zapasu długości oraz mechaniczne odciążenie połączeń.

### 3. Brak prototypowania

Układ został od razu zlutowany w docelowej formie. Każda większa zmiana wymagała więc rozlutowania przewodów i częściowego demontażu robota.

**Wniosek:** przed montażem docelowym warto sprawdzić osobno zasilanie, każdy kanał sterownika, kierunki wszystkich silników i odczyty czujników.

### 4. Resetowanie Arduino podczas rozruchu

Po zamontowaniu DRV8833 silniki zaczęły pobierać większy prąd przy ruszaniu. Przy wspólnym zasilaniu powodowało to spadki napięcia i wielokrotne restarty Arduino, widoczne w monitorze portu szeregowego jako powtarzający się komunikat `Start`.

Dodanie kondensatorów ograniczyło zakłócenia, ale nie usunęło głównej przyczyny.

**Rozwiązanie:** oddzielenie zasilania Arduino od obwodu silników. Arduino jest obecnie zasilane napięciem 9 V przez gniazdo DC, a napęd z koszyka 6×AA. Oba obwody mają wspólną masę.

### 5. Dobór prędkości i promienia zakrętów

Po ustabilizowaniu zasilania silniki zaczęły osiągać znacznie większą prędkość. Wartości PWM, które wcześniej ledwo poruszały robotem, przestały odpowiadać nowym warunkom testu.

Dodatkowo pierwszy tor miał zbyt mały promień zakrętów dla podwozia 4WD.

**Obecne rozwiązanie:** zmniejszenie PWM, użycie przeciwnego kierunku obrotu stron podczas mocnego skrętu oraz przygotowanie większego toru z łagodniejszymi łukami.

## Uruchomienie

1. Otwórz plik `Robot_Nudel.ino` w Arduino IDE.
2. Wybierz płytkę `Arduino Uno` i właściwy port szeregowy.
3. Wgraj program.
4. Sprawdź położenie robota oraz czujników przed włączeniem zasilania silników.
5. Umieść dwa środkowe czujniki nad linią, a skrajne nad jasnym tłem.
6. Włącz zasilanie napędu i obserwuj zachowanie na prostym odcinku przed testem pełnej trasy.

## Plan dalszych prac

- wykonać duży tor w kształcie łagodnego okręgu;
- potwierdzić poziomy logiczne czujników na czarnej i białej powierzchni;
- dostroić wartości PWM dla jazdy prosto oraz obu rodzajów skrętu;
- uzyskać kilka powtarzalnych pełnych okrążeń bez ręcznej pomocy;
- uporządkować i dodatkowo zabezpieczyć przewody;
- zastąpić testowe zasilanie Arduino rozwiązaniem docelowym;
- dodać HC-SR04 i SG90;
- rozważyć późniejszą rozbudowę o kamerę.

## Najważniejsze wnioski

- liczba baterii nie określa sama w sobie wydajności zasilania;
- prąd rozruchowy silników może resetować mikrokontroler;
- układ może działać bez obciążenia, a zawodzić po postawieniu robota na podłożu;
- kondensatory pomagają ograniczyć zakłócenia, ale nie zastępują poprawnego zasilania;
- elementy trzeba testować osobno przed zlutowaniem całego układu;
- w podwoziu 4WD geometria toru ma duży wpływ na możliwość skręcania;
- po każdej zmianie sprzętowej parametry programu mogą wymagać ponownego strojenia.

