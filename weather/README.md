#Stacja pogody
* pomiar ciśnienia
* pomiar temperatury
* pomiar wilgotności
* prędkość wiatru
* zasilanie z baterii słonecznej i wiatraka

## Budowa
* stacja zewnętrzna z miernikami i zasilaniem
* łacznik komunikujący się ze stacją zewnętrzną radiowo
* komputer (serwer) połączony z łącznikiem USB

## Oprogramowanie
* na serwerze Node.js z node-usb
* odczytywanie danych ze stacji
* zapis do bazy danych SQLite
* generowanie raportu o obecnej pogodzie
* pokaz historii pogody
