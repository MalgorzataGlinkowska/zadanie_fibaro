# zadanie_fibaro
Program przygotowany na potrzeby Fibaro z wykorzystaniem NucleoL152RE firmy ST.

## Format ramki komunikacyjnej
|Bajt startu|Liczba danych| Dane | Dane | Dane | ...  |Bajt końca ramki|
|:---------:|:-----------:|:----:|:----:|:----:|:----:|:--------------:|
|   0xAC    |    0x05     | 0x01 | 0x02 | 0x03 | ...  |     0xDC       |

Bajty charakterystyczna mają taki sam początek, długość i koniec. Specyficzne są dane. 
* ACK - 0xAA
* NAK - 0xCC


## Uwagi do projektu

### ACK
W obsłudze ACK powinno być dodatkowo pojedyncze mignięcie diodą. Jednak uznałam, że mogłoby to być mylące przy długich ramkach, gdzie urządzenie musi najpierw zamrugać odpowiednią liczbę bajtów, a następnie bajt ACK.

### Kontrola transmisji
Należałoby uruchomić dodatkowy Timer procesora z przerwaniem ustawionym np. co sekundę. Przy mojej konfiguracji procesora (8MHz) można ustawić Timer2 z Preskalerem = 8000 i zliczaniem = 1000. Mając przerwanie co sekundę można programowo zliczać 180 sekund i wysyłać w UART test transmisji. 
