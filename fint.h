#ifndef FINT_H
#define FINT_H

#include <iostream>
#include <limits>
#include <map>

// choix d'un type entier non signé
typedef unsigned long int int_t;



// valeur maximum du type entier choisi
static const int_t MAX_INT_T = std::numeric_limits<int_t>::max();

// ------------------------------------------------------------------
// Définition partielle de la classe fint à compléter SANS MODIFIER
// les signatures des opérations fournies ci-après, ce qui permettra
// au professeur de compiler un programme utilisateur de son choix
// qui respecte cette spécification.
// ------------------------------------------------------------------
class fint {
public:
  //constructeur qui créé un fint vide
  fint();

  // constructeur à partir d'un entier n >= 1
  fint(int_t n);

  // constructeur à partir d'une liste de facteurs premiers lf
  // et d'une liste de multiplicité lm telles que lm et lf ont la
  // même taille et lm[i]>0 est la multiplicité de lf[i] pour tout i
  // exemple d'appel de ce constructeur :
  // fint f({2,5,11}, {1,2,2});
  fint(const std::initializer_list<int_t>& lf,
      const std::initializer_list<int_t>& lm);

  // destructeur
  ~fint();

  // insère un élément dans le dictionnaire de this
  void inserer_element(std::pair<int,int> p);
  // insère un élément à la fin du dictionnaire de this
  void inserer_element_fin(std::pair<int,int> p);

  // retourne l'élément lié à la clé c du dictionnaire de this , retourne -1 si la clé n'est pas présente
  int rechercher(int c) const;

  // retourne la valeur décimale de this, throws std::overflow_error
  int_t to_int() const;

  // teste si this divise a
  bool divides(const fint& a) const;

  // teste si this est premier
  bool is_prime() const;

  // retourne la taille de this
  int_t taille() const;

  // teste si this est vide
  bool est_vide() const;

  // comparaisons
  friend bool operator==(const fint& a, const fint& b);

  friend bool operator!=(const fint& a, const fint& b);
  
  // retourne le plus petit commun multiple de a et b
  friend fint lcm(const fint& a, const fint& b);

  // retourne le plus grand diviseur commun de a et b
  friend fint gcd(const fint& a, const fint& b);

  // retourne a * b
  friend fint operator*(const fint& a, const fint& b);

  // retourne a / b si b divise a, throws std::domain_error sinon
  friend fint operator/(const fint& a, const fint& b);

  friend fint operator%(const fint& a, const fint& b);

  // retourne a puissance n
  friend fint pow(const fint& a, unsigned int n);

  // écriture de a sur un flot de sortie
  friend std::ostream& operator<<(std::ostream& os, const fint& a);


  // getter
  std::map<int,int> get_dicofint() const;

private:
  std::map<int,int> dicofint;//<facteur,multiplicité>
  //affiche le fint this
  void afficher(std::ostream& os) const;

  //retourne vrai si n est premier
  bool int_is_prime(int_t n);
  //sortie: le plus petit facteur premier de n
  int_t facteur_premier(int_t n);
};

#endif