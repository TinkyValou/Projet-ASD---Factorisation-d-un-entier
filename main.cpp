#include <iostream>
#include <map>
#include "fint.h"
using namespace std;


int main() {

  //Tout nos Constructeurs
  fint a;
  fint b(60);
  fint c({2,3,5}, {2,1,1});
  fint g({2},{2});
  fint i(6);
  fint h({3},{2});

  //Tout nos jeux de tests 
  cout << a << endl;
  cout << b << endl;
  cout << c << endl;
  
  cout << "b|c? " << b.divides(c) << endl;
  cout << "c|b? " << c.divides(b) << endl;
  cout << "b==c? " << (b==c) << endl;
  cout << "ppcm: " << lcm(b,c) << endl;
  cout << "pgcd: " << gcd(b,c) << endl;
  cout << "b*c: " << b*c << endl;
  
  cout << "g = " <<  g.to_int() << endl;
  cout << "h = " <<  h.to_int() << endl;
  cout << "i = " << i << endl;
  
  try{
    cout << "b/c: " << b/c << endl;
    cout << "b^3: " << pow(b,3) << endl;
    cout << "\n g%h: " << g%h << endl; // g < h donc on obtient g
    cout << "\n h%g: " << h%g << endl; // h > g donc on obtient le modulo de h par g
    cout << "\n h%h: " << h%h << endl; // h = h donc on obtient normalement 1

    cout << "\n i%g " << i%g << endl;
  }
  catch(exception const& e){
   cerr << e.what() << endl;
  }
  
  
  return 0;
}