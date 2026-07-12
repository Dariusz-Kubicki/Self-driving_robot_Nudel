# Self-driving_robot_Nudel

Dokumentacja mojego pierwszego projektu robotycznego o nazwie **„Nudel”**. Konstrukcja opiera się na gotowym zestawie z AliExpress i jest napędzana 4 silnikami DC z przekładniami TT. W pierwszej fazie robot będzie działał jako klasyczny **line follower** (pojazd podążający za czarną linią), jednak w przyszłości planuję rozbudować go o czujniki odległości, a nawet kamerę.

## Cel projektu

Głównym celem jest wejście w świat robotyki i samodzielne zbudowanie od zera mojego pierwszego pojazdu autonomicznego. Tworząc ten projekt, nauczyłem się m.in.:
* **Sterowania silnikami prądu stałego** za pomocą Arduino.
* **Konfiguracji i kalibracji** czujników podczerwieni (IR).
* **Pisania wydajnego kodu** dla robotów typu line follower.

### Skąd ta nazwa?
Nazwa robota upamiętnia mojego pierwszego kota, który wabił się właśnie Nudel. Pomyślałem, że to idealne imię dla mojego debiutanckiego projektu!

## Elementy projektu

Robot został zbudowany na bazie gotowego zestawu z AliExpress, do którego link znajduje się [tutaj](https://pl.aliexpress.com/item/1005002223616703.html?spm=a2g0o.order_list.order_list_main.60.6d751c24wbIMJA&gatewayAdapt=glo2pol). 

W skład zestawu wchodzą:
* Klon **Arduino UNO R3**
* 4 czujniki IR
* 4 silniki DC z przekładniami TT
* Płytka do wygodnego podłączenia i regulacji czujników IR
* Czujnik ultradźwiękowy **HC-SR04**
* Serwomechanizm **SG90**
* Koszyk na 4 baterie AA (R6)
* Nakładka rozszerzająca **Arduino UNO Sensor Shield V5.0**
* Elementy montażowe z tworzywa sztucznego
* Plastikowe podwozie oraz koła

### Wykorzystanie druku 3D
Gdy zamawiałem ten zestaw, nie posiadałem jeszcze drukarki 3D, jednak w trakcie prac nad projektem na mojej szafie stanął nowy sprzęt. Wykorzystałem go do ulepszenia konstrukcji: wydrukowałem dedykowaną podstawkę pod Arduino UNO oraz specjalne dystanse do czujników IR, aby umieścić je bliżej podłoża. 

Pliki do druku 3D znajdują się w repozytorium:
* [Podstawka pod Arduino](Ard.stl)
* [Dystanse do czujników IR](dystanse_do_sensorow.stl)

*Wskazówka:* Jeśli nie dysponujesz drukarką 3D, możesz pominąć te elementy. Zamiast drukowanej podstawki pod Arduino można użyć gotowej wersji ze sklepu lub przykręcić płytkę bezpośrednio do podwozia, a jako dystansów pod czujniki użyć klasycznych metalowych lub plastikowych podkładek.

## Napotkane problemy

### 1. Brak i zły dobór sterownika silników (Mostka H)
Podczas montażu zorientowałem się, że w zestawie brakuje sterownika silników. Liczyłem na to, że sprzedawca dorzuci go do kompletu, jednak musiałem poszukać własnego rozwiązania. Przypomniałem sobie, że w posiadanym przeze mnie zestawie *Kursu Arduino (Poziom 1)* od **Forbota** znajduje się układ **L293D** – dwukanałowy sterownik silników prądu stałego. Postanowiłem go zlutować i podłączyć do Arduino.

Po złożeniu robota i rozpoczęciu testów pojawił się poważny problem. Układ L293D okazał się zbyt słaby dla napędu 4WD (silniki były podłączone równolegle, po dwa na stronę, więc sterownik dwukanałowy teoretycznie wystarczał). Powodował on jednak ogromne spadki napięć. Zamiast startowych 6V z baterii, do układu docierało zaledwie 3-4V. W efekcie robot ledwo poruszał się po podłodze, brakowało mu mocy do wykonywania skrętów, a cała elektronika zaczęła szwankować przez niedomiar prądu.

Warto dodać, że przy konstrukcji typu 2WD (z dwoma silnikami) ten sterownik bez problemu dałby sobie radę, jednak zależało mi na napędzie 4WD, który wymaga znacznie więcej mocy.

**Rozwiązanie:** Musiałem rozmontować robota, zrezygnować ze starego sterownika i zamówić wydajniejszy układ – wybór padł na **DRV8833**. Obecnie czekam na dostawę części, aby dokończyć ten etap projektu.
