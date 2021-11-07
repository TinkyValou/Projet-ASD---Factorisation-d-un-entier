#include "fint.h"
#include <iostream>
#include <map>
#include <cmath>
#include <assert.h>
using namespace std;

//--------------------------------------------------
fint::fint(){
  //vide
}

//--------------------------------------------------
// constructeur à partir d'un entier n >= 0
fint::fint(int_t n) {
  int facteur;
  if(n==1){
    this->inserer_element_fin(pair<int,int> (2,0));
  }
  while(n>1){
    facteur = this->facteur_premier(n);//on trouve un facteur premier de n
    this->dicofint[facteur]++;//si facteur correspond a un élément alors la fonction [] retourne la référence de la valeur, on incrémente cette valeur de 1.
    //Si facteur ne correspond a aucun élément du dictionnaire, la fonction [] insère un nouvel élément avec comme clé facteur et une valeur initialisée à 0 et retourne la référence de la valeur, on incrémente cette valeur de 1.
    n /= facteur;//on le divise par le facteur trouvé et on recommence avec le n
  }
}

//--------------------------------------------------
// constructeur à partir d'une liste de facteurs premiers lf
// et d'une liste de multiplicité lm telles que lm et lf ont la
// même taille et lm[i]>0 est la multiplicité de lf[i] pour tout i
// exemple d'appel de ce constructeur :
// fint f({2,5,11}, {1,2,2});
fint::fint(const initializer_list<int_t>& lf, const initializer_list<int_t>& lm) {
  assert(lf.size()==lm.size());//précondition

  auto itlf = lf.begin();
  auto itlm = lm.begin();
  for(int i=0;i<lf.size();i++){
    this->inserer_element_fin(pair<int,int> (*itlf,*itlm));
    itlf++;
    itlm++;
  }
}

//--------------------------------------------------
// destructeur
fint::~fint() {
}

//--------------------------------------------------
// insère un élément dans le dictionnaire de this
void fint::inserer_element(pair<int,int> p){
  this->dicofint.insert(p);
}

//--------------------------------------------------
// insère un élément à la fin du dictionnaire de this
void fint::inserer_element_fin(pair<int,int> p){
  this->dicofint.insert(this->dicofint.end(),p);
}

//--------------------------------------------------
// retourne l'élément lié à la clé c du dictionnaire de this 
int fint::rechercher(int c) const{
  if(this->dicofint.find(c)==this->dicofint.end()){
    return -1;
  }
  else{
    return this->dicofint.find(c)->second;
  }
}

//--------------------------------------------------
// retourne la valeur décimale de this, throws std::overflow_error
int_t fint::to_int() const{
  int_t result=1;
  if(!this->est_vide()){
    for (auto it=this->dicofint.begin(); it!=this->dicofint.end(); it++){
      result *= pow(it->first,it->second);
    }
  }
  if(result==0){
    throw overflow_error("ERREUR : nombre trop grand");
  }
  return result;
}

//--------------------------------------------------
// teste si this divise a
bool fint::divides(const fint& a) const{
  int_t valeur_a;
  //on parcours tout this pour voir si chaque éléments est au moins une fois dans a
  for (auto ithis=this->dicofint.begin(); ithis!=this->dicofint.end(); ithis++){
    valeur_a = a.rechercher(ithis->first);
    if( (valeur_a < ithis->second) || (valeur_a==-1)){
      return false;
    }
  }
  return true; 
}

//--------------------------------------------------
// teste si this est premier
bool fint::is_prime() const {
  return (this->taille()==1) && (this->dicofint.begin()->second==1);
}

//--------------------------------------------------
// retourne la taille de this
int_t fint::taille() const{
  return this->dicofint.size();
}

//--------------------------------------------------
// teste si this est vide
bool fint::est_vide() const{
  return this->dicofint.empty();
}

//--------------------------------------------------
// comparaisons
bool operator==(const fint& a, const fint& b){
  int egal=0;
  if(a.taille() != b.taille()){
    return false;
  }
  map<int,int> mapa = a.get_dicofint();
  auto it_a = mapa.begin();
  map<int,int> mapb = b.get_dicofint();
  auto it_b = mapb.begin();

  while(egal < a.taille()){
    if( (it_a->first == it_b->first) && (it_a->second == it_b->second) ){
      egal++;
      it_a++;
      it_b++;
    }
    else{
      return false;
    }
  }
  return true;
}

//--------------------------------------------------
bool operator!=(const fint& a, const fint& b) {
    return !(a==b);
}

//--------------------------------------------------
// retourne le plus petit commun multiple de a et b
fint lcm(const fint& a, const fint& b) {
  fint fint_result;

  map<int,int> mapa = a.get_dicofint();
  map<int,int> mapb = b.get_dicofint();
  auto it_a = mapa.begin();
  auto it_b = mapb.begin();

  while (it_a!=mapa.end() && it_b!=mapb.end()) {
    if ( it_a->first < it_b->first) {
      fint_result.inserer_element_fin(pair<int, int> (it_a->first,it_a->second));
      it_a++;
    } else if ( it_b->first > it_b->first ) {
      fint_result.inserer_element_fin(pair<int, int> (it_b->first,it_b->second));
      it_b++;
    } else {
      fint_result.inserer_element_fin(pair<int, int> (it_a->first,max(it_a->second, it_b->second) ));
      it_a++;
      it_b++;
    }
  }

  while (it_a!=mapa.end()) {
    fint_result.inserer_element_fin(pair<int, int> (it_a->first,it_a->second));
    it_a++;
  }
  while (it_b!=mapb.end()) {
    fint_result.inserer_element_fin(pair<int, int> (it_b->first,it_b->second));
    it_b++;
  }
  
  return fint_result; 
}

//--------------------------------------------------
// retourne le plus grand diviseur commun de a et b
fint gcd(const fint& a, const fint& b) {
  fint newFint;
  map<int,int> mapa = a.get_dicofint();
  map<int,int> mapb = b.get_dicofint();
  auto it_a = mapa.begin();
  auto it_b = mapb.begin();

  //tant que un des itérateur n'arrive pas à la fin de son fint
  while(it_a!=mapa.end() && it_b!=mapb.end()){
    if(it_a->first==it_b->first){
      newFint.inserer_element_fin(pair<int,int>(it_a->first, min(it_a->second,it_b->second)));
      it_a++;
      it_b++;
    }
    else if(it_a->first < it_b->first){
      it_a++;
    }
    else{//(it_a->first > it_b->first)
      it_b++;
    }
  }
  return newFint;
}

//--------------------------------------------------
// retourne a * b
fint operator*(const fint& a, const fint& b) {
  fint newFint;
  map<int,int> mapa = a.get_dicofint();
  map<int,int> mapb = b.get_dicofint();
  auto it_a = mapa.begin();
  auto it_b = mapb.begin();
  
  //s'arrete quand un des fint est terminé
  while(it_a!=mapa.end() && it_b!=mapb.end()){
    if(it_a->first == it_b->first){
      //ajout avec addition des puissances
      newFint.inserer_element_fin(pair<int, int> (it_a->first,(it_a->second+it_b->second)));
      it_a++;
      it_b++;
    }
    else{//si ils sont différents
      if(it_a->first < it_b->first){
        //ajout de it_a->first et incrémentation de  l'itérateur sur a
        newFint.inserer_element_fin(pair<int, int> (it_a->first,it_a->second));
        it_a++;
      }
      else{//(it_a->first > it_b->first)
        //ajout de it_b->first et incrémentation de  l'itérateur sur b
        newFint.inserer_element_fin(pair<int, int> (it_b->first,it_b->second));
        it_b++;
      }
    }
  }

  //si une un des deux fint n'a pas été analyser jusqu'au bout
  while(it_a!=mapa.end()){//on finit a
    newFint.inserer_element_fin(pair<int, int> (it_a->first,it_a->second));
    it_a++;
  }
  while(it_b!=mapb.end()){//on finit b
    newFint.inserer_element_fin(pair<int, int> (it_b->first,it_b->second));
    it_b++;
  }
  return newFint;
}

//--------------------------------------------------
// retourne a / b si b divise a, throws std::domain_error sinon
fint operator/(const fint& a, const fint& b) {
  fint fint_result;
  int puissance_b, valeur_obtenue;

  map<int,int> mapa = a.get_dicofint();

  auto it_a = mapa.begin();

  if (b.divides(a) ) {
    
    while(it_a != mapa.end()) {
      puissance_b = b.rechercher(it_a->first);
      if (puissance_b == -1) {
        fint_result.inserer_element_fin(pair<int, int>(it_a->first,it_a->second));
      } else {
        valeur_obtenue = it_a->second - puissance_b;
        if (valeur_obtenue > 0) {
          fint_result.inserer_element_fin(pair<int, int>(it_a->first,valeur_obtenue));
        }
      }
      it_a++;
    }
    
  } else {
    throw domain_error("ERREUR :a/b, b ne divise pas a ");
  }  return fint_result;
}

//--------------------------------------------------
//retourne le modulo de a et b
fint operator%(const fint& a, const fint& b) {
  fint fint_result; 
  if (!b.divides(a)){ 
    int a_entier, b_entier, result;
    a_entier = a.to_int();
    b_entier = b.to_int();
    result = a_entier % b_entier;
    fint_result = fint(result);
    cout << a_entier << "%" << b_entier << " = " << result << "\n\n";
  }
  //retourne un fint vide représentant 0 si b divise a
  return fint_result;
}

//--------------------------------------------------
// retourne a puissance n
fint pow(const fint& a, unsigned int n) {
  fint newFint;
  map<int,int> mapa = a.get_dicofint();
  
  for(auto it = mapa.begin();it!=mapa.end();it++){
    newFint.inserer_element_fin(pair<int,int>(it->first,it->second*n));
  }
  return newFint;
}

//--------------------------------------------------
// écriture de a sur un flot de sortie
ostream& operator<<(ostream& os, const fint& a){
  a.afficher(os);
  return os;
}

void fint::afficher(std::ostream& os) const{
  os << this->taille() << " éléments:" << endl;
  if(this->est_vide()){
    os << 0;
  }
  for (auto it=this->dicofint.begin(); it!=this->dicofint.end(); it++){
    if(it != this->dicofint.begin())
      os << " x ";
    os << it->first << "^" << it->second;
  }
}
//--------------------------------------------------

// getters
map<int,int> fint::get_dicofint() const{
  return this->dicofint;
}


//--------------------------------------------------

//meilleur cas: omega(1)
//pire cas: O(sqrt(n))
//sortie: vrai si n est premier, faux sinon
bool fint::int_is_prime(int_t n){
  int k = 2;
  int limite = ceil(sqrt(n+1));
  
  while( (n%k)!=0 && k<limite ){
    k++;
  }
  return (k==limite);
}

//--------------------------------------------------

//multiples de 2: theta(1)
//nombres premiers: theta(sqrt(n))
//sortie: le plus petit facteur premier de n
int_t fint::facteur_premier(int_t n){
  assert(n>0);
  if(n==1){
    return 1;
  }

  int_t prime=2;
  if(this->int_is_prime(n)){//si il est premier on le renvoie direct ce qui enlève le pire cas avec un nombre premier
    return n;
  }
  while((n%prime)!=0){//on regarde si il divise n
    prime++;//on cherche un autre nombre premier
    while(!this->int_is_prime(prime)){
      prime++;
    }
  }
  return prime;
}