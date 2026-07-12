#Zalogowanie: sudo su postgres
#Utworzenie bazy: createdb weatherstation
#Wejście do bazy danych: psql weatherstation
#Uruchomienie skryptów:
Create user weatherstation with encrypted password 'zaq12wsx';
GRANT ALL ON DATABASE weatherstation TO weatherstation;
GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA public TO weatherstation;
CREATE TABLE measure (th varchar(50), time bigint, T real, h real, p real, s real);

-- t temperatura, wilgotność, ciśnienie, smog
