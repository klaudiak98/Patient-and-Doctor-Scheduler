#include <iostream>
#include <string>
#include <fstream>
#include "lekarz.cpp"
#include <unistd.h>                //biblioteka do funkcji sleep() -> dostepna dla systemow zgodnych ze standardem POSIX (Mac OS, Linux itd.)
using namespace std;

string tab[99];
fstream plik;

string link()
{
    int a = wyborl  + 48;        //+ 48 -> ASCII
    char nr = (char) a;

    string napis = "lek";
    napis += nr;
    napis += ".txt";
    
    return napis;
}

void poczatek();
int dzien;

//WYBOR DNIA
int wybordnia()
{
    cout << endl << "Wybierz dzień:" << endl;
    cout << "1. Poniedziałek" << endl << "2. Wtorek" << endl << "3. Środa" << endl << "4. Czwartek" << endl << "5. Piątek" << endl << "6. Cofnij" << endl;

    while (!(cin >> dzien || cin.peek() != char_traits <char> :: to_int_type('\n') ) || dzien > 6 || dzien <= 0)
    {
        cout << "Wybrano nieodpowiedni numer opcji!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }

    switch (dzien)
    {
        case 1:
            system("clear");
            cout << "Poniedziałek" << endl;
            return 1;
            break;

        case 2:
            system("clear");
            cout << "Wtorek" << endl;
            return 21;
            break;

        case 3:
            system("clear");
            cout << "Środa" << endl;
            return 41;
            break;

        case 4:
            system("clear");
            cout << "Czwartek" << endl;
            return 61;
            break;

        case 5:
            system("clear");
            cout << "Piątek" << endl;
            return 81;
            break;
            
        case 6: 
            //powrot do poprzedniej strony
            system("clear");
            poczatek();
            return -1;
            break;

        default:
            cout << endl << "Wybrałeś nieodpowiednią literę" << endl;
            return -1;
            break;
    }
}


class Pacjent
{
    string m_imie, m_nazwisko, m_pesel, m_tel;

public:
    Pacjent (const string& imie = "", const string& nazwisko = "", const string& pesel = "", const string& tel = "")  : m_imie(imie), m_nazwisko(nazwisko), m_pesel(pesel), m_tel(tel){}

    string get_imie (void) const {return m_imie;}
    string get_nazwisko (void) const {return m_nazwisko;}
    string get_pesel (void) const {return m_pesel;}
    string get_tel (void) const {return m_tel;}

    void set_imie ( const string& imie) { m_imie = imie; }
    void set_nazwisko ( const string& nazwisko) { m_nazwisko = nazwisko; }
    void set_pesel ( const string& pesel) { m_pesel = pesel; }
    void set_tel ( const string& tel) { m_tel = tel; }


    string to_string()
    {
        return "Pacjent: " + m_pesel + " " + m_imie + " " + m_nazwisko +  " nr. tel.: " + m_tel;
    }
};

Pacjent p1;

//Sprawdznie czy wpisany tekst sklada sie tylko z cyfr
int czy_cyfra(string tekst)
{
    int ile = 0;
    int dl = tekst.length();

    for (int i = 0; i < dl; i++)
    {
        //isdigit() -> sprawdzenie, czy podany znak jest cyfra
        if (isdigit(tekst[i]))
        {
            ile++;
        }
    }

    if(ile!=dl)
    {
        return 0;
    }
    else return 1;
}

//Sprawdzenie poprawnosci wpisanego peselu
int spr_pesel(string pesel)
{
    int dl = pesel.length();

    if (dl == 11)
    {
        if(czy_cyfra(pesel))            //sprawdzenie, czy wpisany pesel sklada sie z samych cyfr
        {
            return 1;
        }
        else 
        {
            cout << "Podany pesel jest niepoprawny!" << endl;
            return 0;
        }
    }
    else
    {
        cout << "Podany pesel jest niepoprawny!" << endl;
        return 0;
    }
}

//Sprawdzenie poprawnosci wpisanego numeru telefonu
int spr_tel()
{
    if (czy_cyfra(p1.get_tel()))
    {
        return 1;
    }
    else 
    {
        cout << "Podany numer telefonu jest niepoprawny!" << endl;
        return 0;
    }
}

int dane()
{
    //Pobieranie danych od pacjenta
    string imie, nazwisko, pesel, telefon;
    cout << "Podaj imię: ";
    cin >> imie;
    imie[0] = toupper(imie[0]);
    p1.set_imie(imie);
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    nazwisko[0] = toupper(nazwisko[0]);
    p1.set_nazwisko(nazwisko);
    cout << "Podaj pesel: ";
    cin >> pesel;
    p1.set_pesel(pesel);
    cout << "Podaj nr telefonu: ";
    cin >> telefon;
    p1.set_tel(telefon);
    string tekst;
    tekst = p1.to_string();

    //Sprawdzenie, czy podane dane sa prawidlowe
    if  (spr_pesel(p1.get_pesel()) && spr_tel())
    {
        cout << tekst << endl;
        return 1;
    }
    else {return 0;}
}

void wczytanie()
{
    string adres = link();

    plik.open(adres, ios::in);

    if (!plik.is_open())
    {cout << "ERROR! Nie można otworzyć pliku" << endl;}

    //Pobranie danych z pliku
    string linia;
    for (int i = 0; i < 99; i++)
    {
        getline (plik, linia);
        tab[i] = linia;
    } 

    //Wyswietlenie dostepnych terminow
    cout << "REZERWACJA WIZYTY U LEKARZA" << endl << "Dostępne terminy:" << endl << endl;
    for (int i = 0; i < 99; i++)
    {
        if (tab[i].length()<=9 || i == 0)       //tab[0] == "PONIEDZIELEK" -> length() > 9
        {
            cout << tab[i] << endl;
        }    
    }

    plik.close();
}

void sprawdzenie(int a);

//Wybor godziny
int wyborgodz;
int wyborgodziny(int a)
{
    cout << "Wybierz godzine:" << endl;

    //Wyswietlenie dostepnych godzin danego dnia
    for (int i = a; i < a+18 ;  i++)
    {
        if (tab[i].length()<10)
        {cout << tab[i] << endl;}
    }
    cout << "19. Wybierz inny dzień" << endl;

    while (!(cin >> wyborgodz) || cin.peek() != char_traits <char> :: to_int_type('\n')  || wyborgodz > 19 || wyborgodz <= 0)
    {
        cout << "Wybrano nieodpowiedni numer opcji!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << endl;    
    sprawdzenie(a);
    
    return wyborgodz;
}

//Rezerwacja terminu
void rezerwuj(int i)                    // i <- indeks tablicy w ktorym dokonujemy rezerwacji
{
    string adres = link();

    //Wprowadzenie danych od pacjenta
    cout << endl << "WPROWADŹ DANE"  << endl;
    if(dane())
    {
        tab[i] += " " + p1.to_string();

        plik.open(adres, ios:: out);        //otwarcie pliku do zapisu

        if (!plik.is_open())
        {cout << "ERROR! Nie można otworzyć pliku" << endl;}

        for (int j = 0; j < 99; j++)
        {
            plik << tab [j]<< endl;
        }
        plik.close();

        cout << endl << "Rezerwacja terminu przebiegła pomyślnie" << endl << "Zaraz zostaniesz przekierowany do menu głównego" << endl;
        cout<< endl ;
        sleep (4);
        system("clear");
        poczatek();
    }
    else
    {
        char tn;
        cout << "Chcesz sprobować ponownie? t/n" << endl;
        cin >> tn;
        cout << endl;
        tn = tolower(tn);       //zamiana na male litery

        switch (tn)
        {
            case 't':
                rezerwuj(i); break;
            case 'n':
                system("clear"); poczatek(); break;
            default:
                cout << "Wybrano nieprawidłową opcje" << endl; break;
        }
    }
}

//Sprawdzenie, czy wybrany termin jest wolny
void sprawdzenie(int a)                     //int a <- zalezy od wybranego dnia
{
    for (int i = a; i < a+18 ;  i++)
    {
        string s = tab[i];          
        int godzina = atoi(s.c_str());          //rzutowanie stringa na inta -> linia w terminarzu z godzina np. 9. 13:00 zamieniana                                             jest na 9

        if (wyborgodz == 19)    //zmiana wyboru dnia
        {
            a = wybordnia();
            wyborgodziny(a);
            break;
        }
        else
        {
            if (wyborgodz == godzina)
            {
                if (tab[i].length()>9)      //sprawdzenie dostepnosci wybranego terminu
                {
                    cout << "TERMIN ZAJETY! Wybierz inny" << endl;
                    wyborgodziny(a);
                }
                else 
                {
                    rezerwuj(i);            // 'i' <- indeks tablicy, w ktorym dokonujemy rezerwacji
                    exit(1);
                }
            }
        }
    }
}