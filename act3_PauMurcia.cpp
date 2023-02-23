/*Nom: Pau Murcia K'ros.*/

#include <iostream>
#include <cstdlib> //for rand and srand
#include <cstdio>
#include <string>
#include <ctime> // time function for seed value
#include <chrono>
#include <thread>

using namespace std;

//Es crea l'estructura "carta".
struct carta
{
  int numero;
  string palo;
};

//Funció per sumar els punts de la carta i retornar els punts totals.
int s_c(int i, int p, struct carta mano[])
{
  //S'utilitza un switch per imprimir la carta i sumar els punts corresponents.
  switch (mano[i].numero)
  {
  case 1:
    cout << "\033[1;33m A de " << mano[i].palo << "\033[0m" << endl;
    if (p + 11 > 21)
    {
      p = p + 1;
    }
    else
    {
      p = p + 11;
    }
    break;
  case 11:
    cout << "\033[1;33m Sota de " << mano[i].palo << "\033[0m" << endl;
    p = p + 10;
    break;
  case 12:
    cout << "\033[1;33m Caballo de " << mano[i].palo << "\033[0m" << endl;
    p = p + 10;
    break;
  case 13:
    cout << "\033[1;33m Rey de " << mano[i].palo << "\033[0m" << endl;
    p = p + 10;
    break;
  default:
    cout << "\033[1;33m " << mano[i].numero << " de " << mano[i].palo << "\033[0m" << endl;
    p = p + mano[i].numero;
    break;
  }
  return p;
}
//Funció per imprimir i retornar el resultat segons els punts. 
bool r(int p)
{
  if (p > 21)
  {
    cout << "\033[1;31mTe has pasado... puntos: " << p << "\033[0m" << endl;
    cout << "\033[1;31mHas perdido\033[0m" << endl;
    return false;
  }
  else if (p == 21)
  {
    cout << "\033[1;33mFELICIDADES tienes " << p << " puntos!(Blackjack)\033[0m" << endl;
    return false;
  }
  else
  {
    cout << "\033[1;32mTienes " << p << " puntos \033[0m" << endl;
    return true;
  }
};

int main()
{
  struct carta baraja[52], mano[52], manoM[52];
  //Per la funció que té aquest programa en concret no nescessita guardar t_time en una variable.
  srand((unsigned)time(NULL));

  //Variables utilitzades amb alguns valors predeterminats.
  int numeros[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  const string palos[4] = {"Corazones", "Diamantes", "Picas", "Treboles"};
  int opt, i, k, p = 0, pm=0;
  bool repetir = true, inici = true;

  //S'assignen els valors unics a cada carta de la baralla. Passant per tots els números i els 4 pals.
  for (i = 0; i < 13; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      baraja[k].numero = numeros[i];
      baraja[k].palo = palos[j];
      k++;
    }
  }

  // Es reparteixen dues cartes aleatòries.
  for (i = 0; i < 2; i++)
  {
    mano[i] = baraja[rand() % 52];
  }
  k=2;
  do
  {
    //S'imprimeix el menú d'opcions per l'usuari.
    cout << "\033[1;31m \n\nMenu de Opciones \033[0m" << endl;
    cout << "\033[1;32m 1. Robar carta \033[0m" << endl;
    cout << "\033[1;32m 2. Mostrar mano \033[0m" << endl;
    cout << "\033[1;32m 3. Plantarse \033[0m" << endl;
    cout << "\033[1;32m 4. Ver baraja \033[0m" << endl;
    cout << "\033[1;32m 0. SALIR \033[0m" << endl;

    if (inici)
    {
      cout << "\033[1;31m \nTus cartas son: \033[0m" << endl;
      for (i = 0; mano[i].palo != ""; i++)
      {
        //S'imprimeixen les dues primeres cartes sumant els punts amb la funció (p).
        p = s_c(i, p, mano);
      }
      //Segons el retorn de la funció s'acabarà el programa o no.
      if (r(p) == false)
      {
        repetir = false;
        break;
      }
      //Es marca inici com a fals perquè ja no es torni a repetir.
      inici = false;
    }

    cout << "\nIngrese una opcion: ";
    cin >> opt;
    //L'opció que seleccioni l'usuari es compara en un switch.
    switch (opt)
    {
    case 1:
    //Cada cop que es seleccioni l'opció 1 s'assigna una carta aleatoria de la baralla a la posició k de la mà.
      system("clear");
      mano[k] = baraja[rand() % 52];
      cout << "\033[1;32mTu carta es: \033[0m" << endl;
      //S'imprimeix la carta i es suma als punts.
      p = s_c(k, p, mano);
      k++;
      if (r(p) == false)
      {
        //Es calcula el resultat per saber si el programa ha de seguir o no.
        repetir = false;
      }
      break;
    case 2:
      //S'imprimeixen totes les cartes que hi ha a la ma.
      system("clear");
      cout << "\033[1;31m \nTus cartas son: \033[0m" << endl;
      p = 0;
      for (i = 0; mano[i].palo != ""; i++)
      {
        p = s_c(i, p, mano);
      }
      cout << "\033[1;32mTienes " << p << " puntos \033[0m" << endl;
      break;

    case 3:
      system("clear");
      //S'imprimeixen els punts.
      cout << "\033[1;32mHas conseguido " << p << " puntos \033[0m" << endl;
      cout << "\033[1;36mAhora juega la máquina\033[0m" << endl;
      i=0;
      //S'utilitza la mateixa fòrmula per distribuir les cartes a la màquina, sumant els punts en una variable diferent i comparant-los als de l'usuari.
      while (pm < p)
      {
        cout << "\033[1;36mLa maquina roba carta\033[0m" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        manoM[i] = baraja[rand() % 52];
        pm = s_c(i, pm, manoM);
        cout << "\033[1;37m Puntos maquina: " << pm << endl;
        i++;
      }
      if (pm > 21)
      {
        cout << "\033[1;31mLa máquina se ha pasado\033[0m" << endl;
        cout << "\033[1;33mFELICIDADES, HAS GANADO!\033[0m" << endl;
      }
      else if (pm == p)
      {
        cout << "\033[1;33mLa máquina se planta\033[0m" << endl;
        cout << "\033[1;33mEmpate\033[0m" << endl;
      }
      else
      {
        cout << "\033[1;33mLa máquina se planta\033[0m" << endl;
        cout << "\033[1;31mHas perdido...\033[0m" << endl;
      }
      cout << "\033[1;35mTu has conseguido " << p << " puntos y la máquina " << pm << " puntos\033[0m" << endl;
      repetir = false;
      break;
    case 4:
    //S'imprimeixen cada una de les cartes de la baralla, anteriorment assignada.
      for (i = 0; i < 52; i++)
      {
        switch (baraja[i].numero)
        {
        case 1:
          cout << "A de " << baraja[i].palo << endl;         
          break;
        case 11:
          cout << "Sota de " << baraja[i].palo << endl;
          break;
        case 12:
          cout << "Caballo de " << baraja[i].palo << endl;
          break;
        case 13:
          cout << "Rey de " << baraja[i].palo << endl;
          break;
        default:
          cout << baraja[i].numero << " de " << baraja[i].palo << endl;
          break;
        }
      }
      break;

    case 0:
    //Si es selecciona 0, "repetir" s'iguala a false.
      repetir = false;
      break;
    }
  } while (repetir);  //Es repeteix mentres "repetir" sigui true.
}