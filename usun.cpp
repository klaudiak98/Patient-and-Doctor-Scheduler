#include <iostream>
#include <fstream>
using namespace std;

string s;
int godzina_u = 0;

string pesel_usun(string napis)
{
    string pesel_u;
    cout << "Podaj pesel: ";
    cin >> pesel_u;

    if(spr_pesel(pesel_u))      //sprawdzenie poprawnosci wpisanego peselu
    {
        int ok1 = 0, ok2 = 0;

        //Porownanie peselu cyfra po cyfrze
        for (int k = 0; k <11 ; k++)
        {   
            if ((godzina_u>9) && (napis[k+19] == pesel_u[k]))           //godziny od 10. 13:30 - 18. 17:30
            {
                ok1++;
            }
            else if (napis[k+18] == pesel_u[k])                         //od 1. 9:00 do 9. 13:30
            {
                ok2++;
            }           
        }

        if (ok1 == 11)
            {
                int dl = napis.length(); 
                napis.erase(9, dl);
            }
        else if (ok2 == 11)
            {
                int dl = napis.length();
                napis.erase(8, dl);
            }
        else {
                cout << "Wprowadzony pesel nie zgadza się z wpisanym przy rezerwacji! Spróbuj ponownie:" << endl;
                napis = pesel_usun(napis);
            }
    }
    else
    {
            pesel_usun(napis);        
    }
    return napis;
}

void usun()
{
    system("clear");
    int wybor_dnia, wybor_godziny;
    cout << "Podaj dzien twojej wizyty:" << endl << "1. Poniedzialek" << endl << "2. Wtorek" << endl << "3. Środa" << endl << "4. Czwartek" << endl << "5. Piątek" << endl << "6. Wróć do menu" << endl;

    while (!(cin >> wybor_dnia) || cin.peek() != char_traits <char> :: to_int_type('\n')  || wybor_dnia > 6 || wybor_dnia <= 0)
    {
        cout << "Wybrano nieodpowiedni numer opcji!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }

    string dzien;
    int a = 0;
    switch (wybor_dnia)
    {
        case 1: dzien = "PONIEDZIAŁEK"; a = 1; break;       //'a' <- indeks od ktorego sprawdzamy godzine
        case 2: dzien = "WTOREK"; a = 21; break;
        case 3: dzien = "ŚRODA"; a = 41; break;
        case 4: dzien = "CZWARTEK"; a = 61; break;
        case 5: dzien = "PIĄTEK"; a = 81; break;
        case 6: system("clear"); poczatek(); break;
        
        default : cout << "Wybrano zły dzień"; break;
    }

    string tab[99];
    fstream plik;
    string adres = link();
    plik.open(adres, ios::in);

    if (!plik.is_open())
    {
        cout << "ERROR! Nie można otworzyć pliku" << endl;
        exit(0);
    }

    string linia;
    for (int i = 0; i < 99; i++)
    {
        getline (plik, linia);
        tab[i] = linia;
    } 

    cout << endl << "Podaj godzine:" << endl;

    for (int i = a; i < a+18 ;  i++)        //'a' <- indeks od ktorego zaczynamy wyswietlac godziny, zgodnie z wybranym dniem
    {
        if (tab[i].length()>10)             //wyswietlenie jedynie zarezerwowanych terminow
        {
            for (int j =0; j < 9; j++)      //wyswietlenie numerow opcji i godzin, bez danych pacjentow
            {cout << tab[i][j];}
            cout << endl;
        }
    }
    cout << "19. Zmień dzień" << endl;

    while (!(cin >> wybor_godziny) || cin.peek() != char_traits <char> :: to_int_type('\n')  || wybor_godziny > 19 || wybor_godziny <= 0)
    {
        cout << "Wybrano nieodpowiedni numer opcji!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }

    if (wybor_godziny == 19)
    {
        usun();         //zmiana wyboru dnia
    }

    //Sprawdzenie poprawnosci wprowadzonego dnia, godziny i peselu
    for (int i = 0; i < 99; i++)
    {
        if(tab[i] == dzien)
        {
            for (int j = i+1; j < i +19 ; j++)
            {
                s = tab[j];                                 //rzutownie string na int -> np. 9. 13:00 na 9
                godzina_u = atoi(s.c_str());

                if(godzina_u == wybor_godziny)
                {   
                    if (tab[j].length() > 9)        //sprawdzenie czy wybrana godzina jest zarezerwowana
                    {
                        string napis = tab[j];
                        tab[j] = pesel_usun(napis);     //porownanie wprowadzonego peselu z tym wpisanym w pliku

                        cout << "Termin został usunięty" << endl << "Zaraz zostaniesz przekierowany do menu głównego" << endl;
                        sleep(3);
                        system("clear");
                    }
                    else 
                    {
                        cout << "Wybrany termin nie jest zarezerwowany!" << endl << "Chcesz zmienić dzień? (t/n)" << endl;

                        char tn;
                        cin >> tn;
                        switch (tn)
                        {
                            case 't':
                                sleep(1);
                                usun();
                            case 'n':
                                system("clear"); poczatek(); break;
                            default:
                                cout << "Wybrano nieprawidłową opcje" << endl; break;
                        }
                    }
                }
            }
        }
    } 
    plik.close();

    //Usuniecie rezerwacji z pliku
    for (int i = 0; i < 99; i++)
    {
        fstream plik;
        string adres = link();
        plik.open(adres, ios::out);

        if (!plik.is_open())
        {cout << "ERROR! Nie można otworzyć pliku" << endl;}

        for (int j = 0; j < 99; j++)
        {
            plik << tab [j]<< endl;
        }
        plik.close();    
    }
    poczatek();
}