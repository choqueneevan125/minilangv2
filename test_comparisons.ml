// Test des commentaires et comparaisons

/* 
   Commentaire
   sur plusieurs
   lignes
*/

print("=== Comparaisons ===");

int a = 10;
int b = 20;

// Égalité
if (a == 10) {
    print("a est égal à 10");
}

// Différent
if (a != b) {
    print("a est différent de b");
}

// Plus petit
if (a < b) {
    print("a est plus petit que b");
}

// Plus grand ou égal
if (b >= a) {
    print("b est plus grand ou égal à a");
}

print("=== Opérateurs logiques ===");

int x = 5;
int y = 15;

// ET logique
if (x > 0 && y > 0) {
    print("x et y sont positifs");
}

// OU logique
if (x == 5 || y == 5) {
    print("x ou y vaut 5");
}

// NOT logique
int z = 0;
if (!z) {
    print("z est faux (0)");
}

print("=== Expressions complexes ===");

if ((a < b) && (x == 5)) {
    print("Condition complexe vraie");
}

if (a > 0 && b > 0 && x > 0) {
    print("Tous positifs");
}
