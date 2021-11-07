## Si vous voulez directement vous amusez, il suffit de rentrer du code de la même manière que l'on a fait dans le _main()_ pour tester nos fonctions. 

# Notre professeur nous fournissait un header .h _fint_ contenant des fonctions avec leur signature et leur(s) valeur(s) d'entrée(s). A partir de cela, nous devions construire une structure de données capable de manipuler de grands entiers avec ces mêmes fonctions données et créer des opérateurs '+','-','*', '/' et '%' fonctionnant avec le type fint.

# Nous avons essayé de gérer un facteur par un dictionnaire. En effet, celle-ci se construit de la manière suivante : ` pair<int,int> ( entier_multiple, puissance ) `où entier_multiple représentait un nombre premier et puissance étant le nombre de fois l'entier fint était divisible par ce nombre.
# Bien entendu, pour que l'`entier_multiple` soit visible lors de la factorisation, il faut que celui-ci soit non-nul, sinon il ne sera tout simplement pas présent, quelque soit les opérations qui seront effectués ensuite (Exception pour le cas où fint = 1).

# `int_t` est défini dans le fichier _fint.h_, avec le type `unsigned long int`.



# Pour finir, voici les principales méthodes que cette structure de données doit pouvoir effectuer :
#   - créer un _fint_ non-vide depuis un entier ( `fint( int_t n )` ). Celui-ci sera factorisé jusqu'à ce que tout les nombres premiers multiples ainsi que leur puissance associée soit trouvée.
#   - créer un _fint_ non-vide depuis deux listes d'entier ( `fint( const initializer_list<int_t>& lf, const initializer_list<int_t>& lm )` ). Le dictionnaire prendra les clés des éléments de la liste _lf_ et comme valeur des clés les éléments de la liste _lm_. Le premier élément de _lf_ est inséré comme clé du premier élément de _lm_ et ainsi de suite. Il y a une vérification pour que la taille des 2 listes soient égales.
#   - insérer un élément _p_ dans le dictionnaire ( `inserer_element(pair<int,int> p)` ).
#   - rechercher si un élément de type `int` appartient au dictionnaire ( `rechercher(int c)` ).
#   - si un élément de type `fint` est premier ou non ( `is_prime()` ).
#   - Comparer ou modifier deux _fint_  _a_ et _b_ à l'aide des opérandes (`'+', '-', '*', '/', '%', '==', '!='`).
#   - Trouver le plus petit commun multiple de _a_ et _b_ ( `lcm(const fint& a, const fint& b)` ).
#   - Trouver le plus grand diviseur commun de _a_ et _b_ ( `gcd(const fint& a, const fint& b)` ).