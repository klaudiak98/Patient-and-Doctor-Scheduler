#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int wyborl;
int wybor_lek()
{
  system("clear");
  cout << "Wybierz lekarza:" << endl << "1. Lekarz rodzinny" << endl << "2. Pediatra" << endl << "3. Stomatolog" << endl << "4. Zakończ program" << endl;
  
  while (!(cin >> wyborl) || cin.peek() != char_traits <char> :: to_int_type('\n') || wyborl > 4 || wyborl <= 0)
  {
    cout << "Wybrano nieodpowiedni numer opcji!" << endl;
    cin.clear();
    cin.ignore(1000, '\n');
  }
  cout << endl;
  
  //Koniec programu
  if (wyborl == 4)
  {
    exit (0);
  }

  return wyborl;
}