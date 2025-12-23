print("=== Test WHILE ===");

// Boucle simple
int i = 0;
while (i < 5) {
    print(i);
    i = i + 1;
}

print("=== Compte à rebours ===");
int compte = 5;
while (compte > 0) {
    print(compte);
    compte = compte - 1;
}
print("Décollage!");

print("=== Somme avec while ===");
int n = 1;
int somme = 0;
while (n <= 10) {
    somme = somme + n;
    n = n + 1;
}
print("Somme de 1 à 10:");
print(somme);

print("=== Tables de multiplication ===");
int table = 5;
int mult = 1;
while (mult <= 5) {
    int resultat = table * mult;
    print(resultat);
    mult = mult + 1;
}
