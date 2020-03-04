#include <iostream>
#include <string>
#include <fstream>
#include "rejestracja.cpp"
#include "terminarz.cpp"
#include "usun.cpp"

/*  
    cin.clear();                -> czysci flage bledu
    cin.ignore(1000, '\n');     -> usunie z bufora znak '\n' (nowa linia) pozostawiony przez obiekt "cin"
    cin.peek() != char_traits <char> :: to_int_type('\n')       -> cin.peek() zwraca nastepny znak w sekwencji wejscia
*/

using namespace std;
void poczatek(); 
void przejscie(int wybor)       //wywolanie odpowiedniej funkcji zgodnie z wybrana wczesniej opcja
{
    int a;                      //zmienna do ktoej nizej przypisujemy wybrany dzien
    switch (wybor)
    {
        case 1:
            //Przejscie do pliku z rezerwacja terminu
            system("clear");
            wczytanie();            //wczytanie i wyswietlenie dostepnych terminow
            a = wybordnia();        //wybor dnia
            wyborgodziny(a);        //wybor godziny dla daneg dnia
            break;

        case 2:
            //Usuwanie terminu
            system("clear");
            usun();
            break;

        case 3:
            //Sprawdzenie terminarza
            system("clear");
            terminarz();
            break;
            
        case 4:
            //Powrot do wyboru lekarza
            wybor_lek();
            system("clear");
            poczatek();
            break;
          
        case 5:
            //Koniec
            exit (0);

        default:
            cout << "Nieprawidłowy znak" << endl;
            break;
    }
}

void poczatek()
{
    int wybor;
    cout << "Wybierz:" << endl;
    cout << "1. Zarezerwuj termin" << endl << "2. Usuń rezerwacje" << endl << "3. Sprawdź terminarz" << endl << "4. Wróć do wyboru lekarza" << endl << "5. Zakończ program" << endl;

    while (!(cin >> wybor) || cin.peek() != char_traits <char> :: to_int_type('\n')  || wybor > 5 || wybor <= 0)
    {
        cout << "Wybrano nieodpowiedni numer opcji!" << endl;
        cin.clear();                //czyści flagi błędow
        cin.ignore(1000, '\n');     //ignoruje okreslona ilosc znakow z bufora
    }

    cout << endl;
    przejscie (wybor);
}

int main ()
{
    system("clear");
    wybor_lek();
    system("clear");
    poczatek();
    
    return 0;
}