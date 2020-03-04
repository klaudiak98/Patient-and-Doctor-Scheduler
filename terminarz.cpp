#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void usun();
void przejscie_term(int wybor_t)
{
    int a;
    switch (wybor_t)
    {
        case 1:
            //Rezerwacja terminu
            system("clear");
            wczytanie();
            a = wybordnia();
            wyborgodziny(a);
            break;

        case 2:
            //Usuwanie terminu
            usun();
            break;

        case 3:
            //Wybor lekarza
             wybor_lek();
             poczatek();
             break;
            
        case 4:
            //Koniec programu
            exit (0);        

        default:
            cout << "Nieprawidłowy znak" << endl;
            break;
    }
}

void poczatek_term()
{
    int wybor_t;
    cout << "Wybierz:" << endl;
    cout << "1. Zarezerwuj termin" << endl << "2. Usuń rezerwacje" << endl << "3. Wróć do wyboru lekarza" << endl << "4. Zakończ program" << endl;

    while (!(cin >> wybor_t) || cin.peek() != char_traits <char> :: to_int_type('\n')  || wybor_t > 4 || wybor_t <= 0)
    {
        cout << "Wybrano nieodpowiedni numer opcji!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << endl;
    przejscie_term (wybor_t);
}

void terminarz()
{
    string adres = link();
    fstream plik;
    plik.open(adres, ios::in);

    if (!plik.is_open())
    {cout << "ERROR! Nie można otworzyć pliku" << endl;}

    //Pobranie i wyswietlenie danych z pliku
    string linia;
    cout << "TERMINARZ" << endl;
    for (int i = 0; i < 99; i++)
    {
        getline (plik, linia);
        cout << linia << endl;
    } 
    cout << endl;
    poczatek_term();

    plik.close();
}